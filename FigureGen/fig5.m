%% Figure 5 - Shows tree structure coming from each vertex on the root path
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
    addpath(genpath(pathOnly));
end

dirName = 'sample\';
picName = 'theBlob.tif';
[records, dataStruct, statMat] = singleVorDir(picName,dirName,filtSize);
end

function [records, dataStruct, statMat] = singleVorDir(picName,dirName,filt)
fprintf('Preparing to load file %s\r\n', picName);
    fid = [dirName 'THREADLOG' num2str(1) '.txt'];
%     try
        [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt);
end
% end

function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
%% Pre-Process image, compute graph and boundary measures.
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

tic
[vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.80,0);
axis ij
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

printOut(fid, sprintf('%s:     Image %s Processed - %fs\r\n', datetime, [imageFilesName], toc));

disp(['Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);
tic
records = Voronoi_DT(vertexCoor, EL, 'ImageStruct', imageStruct);

% 
[dataStruct] = processRecords(records);
[dataStruct] = extractCycles(records, dataStruct);
[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles(records,dataStruct);

%% Plots the 'tree' from the root path at a very specific point
% Show the image, plot the in-graph gray.
H = figure('position',[0,0,size(records.imageMask,2)*3,size(records.imageMask,1)*3],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');
hold on;
plotVoronoiSkeleton_SingleRegion(records,1,[0.75,0.75,0.75],{'LineWidth', 1});
plotVoronoiSkeleton_SingleRegion(records,2,[0.75,0.75,0.75],{'LineWidth', 1});

% Get subgraph information from the in-graph portion
[cycleInt, ~] = getCycleInfo(dataStruct,1); 

% Plot the root path magenta.
plotSubGraph_RootPath(records,cycleInt,'m',{'LineWidth', 2});

% Manual selection of a specific vertex on the root path for which we want
% to find children.
idxsg = 571; idx = cycleInt.Vertices(idxsg);

%records2SubgraphMap_Vertices is a mapping from the 'records indexing' to
%'subgraph indexing' for Vertices. Edges do not need this remapping.
%boundaryVerts = the vertices which are on the boundary of the object
%boundaryToCycleNode = for each entry in boundaryVerts, what is their
%parent node on the root path
verts = cycleInt.records2SubgraphMap_Vertices(cycleInt.boundaryVerts(cycleInt.boundaryToCycleNode==idx));
path = [];
for i = 1:length(verts)
    path = [path;getPathToRoot(records,cycleInt,verts(i))]; %getPathToRoot gives the edges on the path from any point to the root node.
end
path = unique(path);
path = [path;28215;30455]; %Two gray edges with closer ancestor. Found through manual search. Will need to be changed if we choose a different subgraph/
plotFromEdgeList(path, records, 'b',{}); %Direct call to plotFromEdgeList of path vertices
pos = records.verts.pos(idx,:);
plot(pos(1),pos(2),'o','MarkerEdgeColor',[0,0.75,0],'MarkerFaceColor',[0,1,0],'MarkerSize',20);
xrange = [238.4899,273.6913];
yrange = [107.8899, 132.0523];
xlim(xrange);
ylim(yrange);
end