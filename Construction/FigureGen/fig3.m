%%Uses a modified version of runVoronoi to draw figure3. This will show
%%in-graphs/out-graphs on an image, and exterior/interior boundaries.

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
% end

function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
%% Load/Filter image.
holeSizeFilt = filtSize;
printOut(fid, sprintf('%s:    Loading %s%s\r\n', datetime, dirName, imageFilesName));
tic;
im = imread([dirName imageFilesName]);
printOut(fid,sprintf('%s:     Image %s loaded - %fs\r\n', datetime, [imageFilesName], toc));
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
records = Voronoi_DT(vertexCoor, EL, 'imageStruct',imageStruct);
[records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull] = VoronoiMEX(vertexCoor, EL, [0,0],[],[],[],imageStruct.colorList,imageStruct.numNonHoles,imageStruct.labelMat);

%% Show image, color all exterior boundaries red, and all interior boundaries blue.
H = figure('position',[0,0,size(records.imageMask,2)*3,size(records.imageMask,1)*3],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');

hold on;
for i = 1:records.numNonHoles
    plotOutline_ByColor(records, i, 'r', {'LineWidth',4.0});
end
for i = records.numNonHoles+1:records.numObjects
   plotOutline_ByColor(records, i, 'b', {'LineWidth',4.0});
end

% print(H, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 3\EXTvsINT_FIG3A.png', '-dpng', '-r300');
% delete(H)
%% Show image, color all in-graphs cyan, out-graphs red.
H = figure('position',[0,0,size(records.imageMask,2)*2,size(records.imageMask,1)*2],'Visible','on');
imshow(records.imageMask,'InitialMagnification','fit');
hold on;
for i = records.numNonHoles+1:records.numObjects
    plotRegion(records,i,'Color','c','LineWidth',1.0);
end

for i = 1:records.numNonHoles
    plotRegion(records,i,'Color',[0.75,0,0],'LineWidth',1.0);
end
plotRegion(records,0,'Color','c','LineWidth',1.0);

end