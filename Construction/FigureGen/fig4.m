%% Modified version of runVoronoi to generate figure 4.

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
        [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt);
end

function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
%% Load image, fill holes.
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

%% Generate diagram
records = Voronoi_DT(vertexCoor, EL, 'ImageStruct',imageStruct);


%% Compute boundary measures.
[dataStruct] = processRecords(records);
[dataStruct] = extractCycles(records, dataStruct);
[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles(records,dataStruct);

%% 1: Plotting bridges + connectors
H = figure('position',[0,0,size(records.imageMask,2)*3,size(records.imageMask,1)*3],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');
hold on;

% Plot the diagram in the two in-graph regions in gray.
for i = records.numNonHoles+1:records.numObjects
    plotVoronoiSkeleton_SingleRegion(records,1,[0.75,0.75,0.75],{'LineWidth', 1});
    plotVoronoiSkeleton_SingleRegion(records,2,[0.75,0.75,0.75],{'LineWidth', 1});
end

% Plot the root path blue (this is the central path for which all boundary profile measures are compared to
% This includes both bridges and connectors
for i = 1:records.numObjects
    [cycleInt, ~] = getCycleInfo(dataStruct,i);
    plotSubGraph_RootPath(records,cycleInt,'b',{'LineWidth', 2});
end

% Plot the bridges and hubs (not connectors) in regions 1 and 2
plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, 1, [0.75,0,0], [0,1,0], {'LineWidth', 2}, {'MarkerSize', 8, 'MarkerEdgeColor',[0,0.75,0],'Marker', 'o'});
plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, 2, [0.75,0,0], [0,1,0], {'LineWidth', 2}, {'MarkerSize', 8, 'MarkerEdgeColor',[0,0.75,0],'Marker', 'o'});

%% 2: Plot Subgraphs + root paths
H = figure('position',[0,0,size(records.imageMask,2)*3,size(records.imageMask,1)*3],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');
hold on;

% Plot each sub region and it's corresponding root path
colors = jet(records.numObjects);
for i = 1:records.numObjects
    [cycleInt, ~] = getCycleInfo(dataStruct,i); % Get's the subgraph info from datastruct.
    plotSubRegion(records,i,colors(i,:),[],{'LineWidth', 1});

    plotSubGraph_RootPath(records,cycleInt,[0.5,0.5,0.5],{'LineWidth', 2}); % plot the root path
end

end