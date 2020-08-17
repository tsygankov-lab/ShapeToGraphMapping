%% Asks user to supply an image using a ui menu
%filtSize will filter all 4-connected holes in an image with a size equal
%to or less than filtsize.
%For the actual function call to Voronoi_DT and the image pre/post
%processing, look at internalLoop.
function [records, dataStruct, statMat] = runVoronoi(filtSize)
if(nargin < 1 || isempty(filtSize))
    filtSize = 0;
end
% close all
records = [];
dataStruct = [];
if(~exist('endpointLine.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    addpath(genpath(pathOnly));
end
[picName,dirName] = uigetfile({'*.jpg;*.tif;*.tiff;*.png;*.gif','All Image Files';...
          '*.*','All Files' });
[records, dataStruct, statMat] = singleVorDir(picName,dirName,filtSize);
% [path] = uigetdir('','Select Folder with .tif Images');
% [records, dataStruct]  = parForVorDir([path filesep],6);
% dirName = '\\FolderDirectory\';
% parForVorDir(dirName);
% dirName = '\\FolderDirectory\';
% parForVorDir(dirName);
end

%% Runs a single image, with an output log file
function [records, dataStruct, statMat] = singleVorDir(picName,dirName,filt)
% imagefiles = dir([dirName '*.tif']);
    fprintf('Preparing to load file %s\r\n', picName);
    fid = [dirName 'THREADLOG' num2str(1) '.txt'];
    [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt);
end
% end

%% Runs a folder in batch, with output log files
function [records, dataStruct, statMat] = parForVorDir(dirName,filt)
imagefiles = [dir([dirName '*.png']),dir([dirName '*.tif']),dir([dirName '*.tiff'])];
errFlag = zeros(length(imagefiles),1);
fprintf('Preparing to load files from %s\r\n', dirName);
parSession = gcp;
records = cell(1,length(imagefiles));
dataStruct = cell(1,length(imagefiles));
mkdir(dirName, 'VorLog');
mkdir(dirName, 'FiltIM');
for i = 1:parSession.NumWorkers
    fid = fopen([dirName 'VorLog' filesep 'THREADLOG' num2str(i) '.txt'],'w');
    fclose(fid);
end
parfor iter = 1:length(imagefiles)
    
    t = getCurrentTask();
    if(isempty(t))
        t.ID = 1;
    end
    fid = [dirName 'VorLog' filesep 'THREADLOG' num2str(t.ID) '.txt'];
    try
        [records{iter},  dataStruct{iter}] = internalLoop(fid, dirName, imagefiles(iter).name,filt);
    catch ME
        errFlag(iter) = 1;
        printOut(fid, sprintf('----------\r\n%s:     ERROR ERROR ERROR \r\n-----------\r\n', datetime));
        printOut(fid, sprintf('MESSAGE: %s\r\n',ME.message));
        printOut(fid, sprintf('STACK TRACE:\r\n'));
        for i = 1:length(ME.stack)
            printOut(fid, sprintf('%d:    FILE: %s\r\n',i, ME.stack(i).file));
            printOut(fid, sprintf('       FUNCTION:LINE: %s:%d\r\n',ME.stack(i).name,ME.stack(i).line));
        end
    end
end
if(any(errFlag))
   disp('An error was encountered at some point during processing.  Check the log files for details'); 
end
end


%% Primary Function Call
function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
holeSizeFilt = filtSize;
printOut(fid, sprintf('%s:    Loading %s%s\r\n', datetime, dirName, imageFilesName));
tic;
im = imread([dirName imageFilesName]);
printOut(fid,sprintf('%s:     Image %s loaded - %fs\r\n', datetime, [imageFilesName], toc));

%% Add Artificial image border
imageName = ~bwareaopen(~im(:,:,1),holeSizeFilt+1,4);
imageTest = zeros(size(imageName,1)+2, size(imageName,2)+2);
imageTest(2:size(imageName,1)+1,2:size(imageName,2)+1) = imageName(:,:,1);
imageName = imageTest;

%% Extract vertices and edges from the binary mask
tic
[vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.99,0);
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

%% Compute diagram
records = Voronoi_DT(vertexCoor, EL, 'ImageStruct', imageStruct);

%% In-Graph, colored by sub-graph/region color
figure;
subplot(1,2,1)
imshow(records.imageMask);
hold on;
colorMap = jet(records.numObjects);
for i = 1:records.numObjects
    plotSubRegion(records, i, 1, 'Color', colorMap(i,:), 'LineWidth',1);
end
title('In-Graph, colored by sub-graph');

%% Out-graph, colored by sub-graph/region color
subplot(1,2,2)
imshow(records.imageMask);
hold on;
colorMap = jet(records.numObjects);
for i = 1:records.numObjects
    plotSubRegion(records, i, 0, 'Color', colorMap(i,:), 'LineWidth',1);
end
title('Out-Graph, colored by sub-graph');

%% Derive Boundary Metrics
[dataStruct] = processRecords(records);
[dataStruct] = extractCycles(records, dataStruct);
[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles(records,dataStruct);

%% Convert to 40 features per boundary
[statMat] = dataStruct2Stats(records, dataStruct);
end