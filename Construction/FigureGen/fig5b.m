%% Illustrates boundary profile, width distribution.
function [records, dataStruct, statMat] = runVoronoi(filtSize)
close all;
clear all;
if(nargin < 1 || isempty(filtSize))
    filtSize = 0;
end

records = [];
dataStruct = [];
if(~exist('endpointLine.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end

dirName = 'sample\';
picName = 'FIGURE_5.png';
[records, dataStruct, statMat] = singleVorDir(picName,dirName,filtSize);
end

function [records, dataStruct, statMat] = singleVorDir(picName,dirName,filt)
% imagefiles = dir([dirName '*.tif']);
fprintf('Preparing to load file %s\r\n', picName);
    fid = [dirName 'THREADLOG' num2str(1) '.txt'];
%     try
        [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt);
end
% end


function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
%% Load image, build diagram, process diagram.
holeSizeFilt = filtSize;
printOut(fid, sprintf('%s:    Loading %s%s\r\n', datetime, dirName, imageFilesName));
tic;
im = imread([dirName imageFilesName]);
printOut(fid,sprintf('%s:     Image %s loaded - %fs\r\n', datetime, [imageFilesName], toc));
% if(filtSize > 0)
imageName = ~bwareaopen(~im(:,:,1),holeSizeFilt+1,4);
% end
imageTest = zeros(size(imageName,1)+2, size(imageName,2)+2);
imageTest(2:size(imageName,1)+1,2:size(imageName,2)+1) = imageName(:,:,1);
imageName = imageTest;
% imwrite(imageName,[dirName 'FiltIM' filesep 'filteredIm_' imageFilesName]);
%ImageStruct: numObjects, numNonHoles, objLength,colorList, pixelIndOffset, labelMat, adjMat
tic
[vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.80,0);
axis ij
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

printOut(fid, sprintf('%s:     Image %s Processed - %fs\r\n', datetime, [imageFilesName], toc));

disp(['Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);
tic
records = Voronoi_DT(vertexCoor,EL,'imageStruct',imageStruct);

% 
[dataStruct] = processRecords(records);
[dataStruct] = extractCycles(records, dataStruct);
[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles(records,dataStruct);

%% Plot the radius at selecy nodes on the root path
H = figure('position',[0,0,size(records.imageMask,2)*3,size(records.imageMask,1)*3],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');
xmin = 11.3913;
xmax = 227.4745;
ymin = 13.2435;
ymax = 106.9664;
xlim([11.3913,227.4745]);
ylim([13.2435,106.9664]); %manual zoom
hold on;
plotVoronoiSkeleton_SingleRegion(records,1,[0.75,0.75,0.75],{'LineWidth', 1});
[cycleInt, ~] = getCycleInfo(dataStruct,1);

allPathVerts = cycleInt.Vertices; %Vertices on the rootPath of this subgraph
allPathPos = records.verts.pos(allPathVerts,:);

%The vertices on the central path within the window range
inRangeVerts = find(allPathPos(:,1) >= xmin & allPathPos(:,1) <= xmax & allPathPos(:,2) >= ymin & allPathPos(:,2) <= ymax);
plotSubGraph_RootPath(records,cycleInt,'m',{'LineWidth', 2});

% plotVoronoiSkeleton_SingleRegion(records,2,[0.75,0.75,0.75],{'LineWidth', 1});
% end
ancestorNodes = [];
remainingList = cycleInt.boundaryToCycleNode;

%Manually selected nodes on the root path
ancestorNodes = sort([1753;4714;6024;3545;6469;2341]); %Can't plot on radius plot yet - need to convert back to index
colors = jet(length(ancestorNodes));
for i = 1:length(ancestorNodes)
    node = ancestorNodes(i);
    pos = records.verts.pos(node,:);
    rad = records.verts.rad(node);
    [xunit, yunit] = circle(pos(1),pos(2),rad,100);
    patch(xunit, yunit, [0,0.8,0.25],'FaceAlpha',0.25,'EdgeColor',[0,1,0]);
end


%Tips - Manually defined
% Obj1: 105, 168, 198
% Obj2: 268ish
% Obj3: 341
% Obj4: 505
% Obj5: 636, 671
% Obj6: 728ish
bVPos = records.verts.pos(cycleInt.boundaryVerts,:); %Boundary vertices in the window.
inRangeBound = find(bVPos(:,1) > xmin & bVPos(:,1) < xmax & bVPos(:,2) > ymin & bVPos(:,2) < ymax);
rangeStart = inRangeBound(1);
allStartTips = [105, 168, 198, 268, 341, 505, 636, 671, 728]; %Boundary vertices - manually defined
colors = jet(length(allStartTips));
for i = 1:length(allStartTips)
    startTip = allStartTips(i);
    startVert = cycleInt.records2SubgraphMap_Vertices(cycleInt.boundaryVerts(allStartTips(i))); %Get the startTip in terms of it's subgraph index.
    edges = getPathToRoot(records,cycleInt, startVert, 1); % Get the edges on the path to the root node.
    resmPoints = resamplePath(records, edges, 0.01); % Resample the path (We are coloring the portion of the plot within the ancestor radius a different color).
    ancestor = cycleInt.boundaryToCycleNode(startTip);
    aPos = records.verts.pos(ancestor,:);
    aRad = records.verts.rad(ancestor,:);
    diff = resmPoints;
    diff(:,1) = (resmPoints(:,1) - aPos(:,1)).^2; %Distance of each resampled point to the ancestor vertex.
    diff(:,2) = (resmPoints(:,2) - aPos(:,2)).^2;
    dist = sqrt(sum(diff,2));
    
    %For each boundary tip, plot the path from boundary -> root path blue
    %if it is outside of the ancestors radius. Plot red if inside.
    plot(resmPoints(dist>aRad,1),resmPoints(dist>aRad,2),'b', 'LineWidth',2); 
    plot(resmPoints(dist<=aRad,1),resmPoints(dist<=aRad,2),'r', 'LineWidth',2);
    
    posStartTip = records.verts.pos(cycleInt.boundaryVerts(allStartTips(i)),:);
    scatter(posStartTip(1),posStartTip(2),'MarkerFaceColor',colors(i,:),'MarkerEdgeColor',colors(i,:)/1.5);
end

%% Plot Radius along path
G = figure;
plot(cycleInt.distance(inRangeVerts) - min(cycleInt.distance(inRangeVerts)), records.verts.rad(cycleInt.Vertices(inRangeVerts)),'b');
xlim([0,max(cycleInt.distance(inRangeVerts) - min(cycleInt.distance(inRangeVerts)))]);
xlabel('Distance along the Root Path');
ylabel('Radius along the Root Path');

%% Plot boundary profile/boundary difference. Put markers corresponding to selected tips from earlier.
I = figure;
p1 = plot(cycleInt.boundaryProfile(inRangeBound),'r'); hold on;
p2 = plot(cycleInt.boundaryDiff(inRangeBound),'b');
xlim([0,length(inRangeBound)]);
for i = 1:length(allStartTips)
    startTip = allStartTips(i);
    plot([startTip - rangeStart;startTip - rangeStart],[cycleInt.boundaryProfile(startTip);cycleInt.boundaryDiff(startTip)],'--','Color',colors(i,:));
    scatter(startTip - rangeStart, cycleInt.boundaryProfile(startTip),'MarkerFaceColor',colors(i,:),'MarkerEdgeColor',colors(i,:)/1.5);
    scatter(startTip - rangeStart, cycleInt.boundaryDiff(startTip),'MarkerFaceColor',colors(i,:),'MarkerEdgeColor',colors(i,:)/1.5);
end
legend([p1,p2], {'Full Path Length','Normalized Path Length'}, 'Location','northwest');

xlabel('Distance Along the Boundary');
ylabel('Path Length to Boundary');
% 
% print(H, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 5\Complex_Fig5B.png', '-dpng', '-r300');
% print(G, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 5\RADIUS_ON_PATH_Fig5C.png', '-dpng', '-r300');
% print(I, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 5\BOUNDARY_Fig5D.png', '-dpng', '-r300');
% savefig(G, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 5\RADIUS_ON_PATH_Fig5C.fig');
% savefig(I, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 5\BOUNDARY_Fig5C.fig');
% plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, 1, [0.75,0,0], [1,0.75,0], {'LineWidth', 2}, {'MarkerSize', 8, 'Marker', 'd'});
% plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, 2, [0.75,0,0], [1,0.75,0], {'LineWidth', 2}, {'MarkerSize', 8, 'Marker', 'd'});


end