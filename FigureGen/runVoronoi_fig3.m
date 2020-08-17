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
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end
% [picName,dirName] = uigetfile({'*.jpg;*.tif;*.tiff;*.png;*.gif','All Image Files';...
%           '*.*','All Files' });
dirName = 'samples\';
picName = 'theBlob.tif';
[records, dataStruct, statMat] = singleVorDir(picName,dirName,filtSize);
% [path] = uigetdir('','Select Folder with .tif Images');
% [records, dataStruct]  = parForVorDir([path filesep],6);
% dirName = '\\ad.gatech.edu\bme\labs\tsygankov-lab\WilliamPilcher\BW_Pictues\Cell-Cell\';
% parForVorDir(dirName);
% dirName = '\\ad.gatech.edu\bme\labs\tsygankov-lab\WilliamPilcher\BW_Pictues\Cell-ECM\';
% parForVorDir(dirName);
end

function [records, dataStruct, statMat] = singleVorDir(picName,dirName,filt)
% imagefiles = dir([dirName '*.tif']);
fprintf('Preparing to load file %s\r\n', picName);
% parSession = gcp;
% for i = 1:parSession.NumWorkers
%     fid = fopen([dirName 'THREADLOG' num2str(1) '.txt'],'w');
%     fclose(fid);

% parfor iter = 1:length(imagefiles)
    
%     t = getCurrentTask();
%     if(isempty(t))
%         t.ID = 1;
%     end
%     errFlag = 0;
    fid = [dirName 'THREADLOG' num2str(1) '.txt'];
%     try
        [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt);
%     catch ME
%         errFlag = 1;
%         printOut(fid, sprintf('----------\r\n%s:     ERROR ERROR ERROR \r\n-----------\r\n', datetime));
%         printOut(fid, sprintf('MESSAGE: %s\r\n',ME.message));
%         printOut(fid, sprintf('STACK TRACE:\r\n'));
%         for i = 1:length(ME.stack)
%             printOut(fid, sprintf('%d:    FILE: %s\r\n',i, ME.stack(i).file));
%             printOut(fid, sprintf('       FUNCTION:LINE: %s:%d\r\n',ME.stack(i).name,ME.stack(i).line));
%         end
%     end
% if((errFlag))
%    disp('An error was encountered at some point during processing.  Check the log files for details'); 
% end
end
% end


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
% 
% function ForVorDir(dirName)
% dbstop if error
% imagefiles = dir([dirName '*.tif']);
% fprintf('Preparing to load files from %s\r\n', dirName);
% % parSession = gcp;
% % i = 1:1
%     fid = fopen([dirName 'THREADLOG' num2str(1) '.txt'],'w');
%     fclose(fid);
% % end
% parfor iter = 1:length(imagefiles)
%     
%     t = getCurrentTask();
%     if(isempty(t))
%         t.ID = 1;
%     end
%     fid = fopen([dirName 'THREADLOG' num2str(t.ID) '.txt'],'at');
%     try
%         internalLoop(fid, dirName, imagefiles(iter).name,100);
%     catch ME
%         fprintf(fid,'----------\r\n%s:     ERROR ERROR ERROR \r\n-----------\r\n', datetime);
%         fprintf(fid,'MESSAGE: %s\r\n',ME.message);
%         fprintf(fid,'STACK TRACE:\r\n');
%         for i = 1:length(ME.stack)
%             fprintf(fid,'%d:    FILE: %s\r\n',i, ME.stack(i).file);
%             fprintf(fid,'       FUNCTION:LINE: %s:%d\r\n',ME.stack(i).name,ME.stack(i).line);
%         end
%     end
%     fclose(fid);
% end
% end


function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize)
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
[vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.80,1);
axis ij
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

printOut(fid, sprintf('%s:     Image %s Processed - %fs\r\n', datetime, [imageFilesName], toc));

disp(['Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);
tic
[records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull] = VoronoiMEX(vertexCoor, EL, [0,0],[],[],[],imageStruct.colorList,imageStruct.numNonHoles,imageStruct.labelMat);
records.imageStruct = imageStruct;
records.fromImage = true;
records.numObjects = imageStruct.numObjects;
records.numNonHoles = imageStruct.numNonHoles;
records.adjMat = imageStruct.adjMat;
records.vertexCoor = vertexCoor;
records.EL = EL;
records.imageMask = imageStruct.imageMask;
records.edges.length = length(records.edges.origin);
records.verts.length = length(records.verts.pos);
records.verts.vertexCoorID(records.verts.vertexCoorID == 0) = -1; %temp fix

% % 
% [dataStruct] = processRecords(records);
% [dataStruct] = extractCycles(records, dataStruct);
% [dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
% [dataStruct] = resampleAllInteriorCycles(records,dataStruct);
% [statMat] = dataStruct2Stats(records, dataStruct);
H = figure('position',[0,0,size(records.imageMask,2)/2,size(records.imageMask,1)/2]);

% subplot('position',[0,0,1,1],'units','normalized');
% 
imshow(records.imageMask);

hold on;
% plotVoronoiSkeleton_SingleRegion_ExtVsInt(records, 1, [0.0,0.5,0.5], [0.0,0.0,0.75], {'LineWidth',1}, {'LineWidth', 1});
plotVoronoiSkeleton_SingleRegion_ExtVsInt(records, 1, [0.75,0,0], [0.0,0.0,0.75], {'LineWidth',1}, {'LineWidth', 1});
plotVoronoiSkeleton_SingleRegion_ExtVsInt(records, 2, [0.75,0,0], [0.0,0.0,0.75], {'LineWidth',1}, {'LineWidth', 1});

% plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, 1, [0.75,0,0], [1,0.75,0], {'LineWidth', 2}, {'MarkerSize', 8, 'Marker', 'd'});
print(H, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 3\EXTvsINT.png', '-dpng', '-r300');

H = figure('position',[0,0,size(records.imageMask,2)/2,size(records.imageMask,1)/2]);
for i = records.numNonHoles+1:records.numObjects
    plotVoronoiSkeleton_SingleRegion(records,i,[0,0,0.75],{});
end

for i = 1:records.numNonHoles
    plotVoronoiSkeleton_SingleRegion(records,i,[0.75,0,0],{});
end
plotVoronoiSkeleton_SingleRegion(records,0,[0,0,0.75],{});
print(H, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 3\INvsOUT.png', '-dpng', '-r300');

% plotVoronoiSkeleton_SingleRegion_Type0(records, 1, [0,0,0.75], [0,0.75,0], {},{})
% 
% 
% figure('position',[0,0,size(records.imageMask,2)/2,size(records.imageMask,1)/2]);
% subplot('position',[0,0,1,1],'units','normalized');imshow(records.imageMask); hold on; 

% plotVoronoiSkeleton(records, 0, [0,0,1], 1, 1,{'LineWidth',1});
% figure
% imshow(records.imageMask); hold on;
% plotVoronoiSkeleton(records, 1, [0.6,0.6,0.6], 1, 2,{'LineWidth',1});

% dataStruct = [];
% for i = 1:length(dataStruct.loop.object.acyclic)
%     plotFromEdgeList(dataStruct.loop.object.acyclic(i).primaryMajAxis.edge, records, [1,1,1],{'LineWidth',2});
% end
% for i = 1:length(dataStruct.loop.object.enclosed)
%     plotFromEdgeList(dataStruct.loop.object.enclosed(i).EL, records, [1,1,1],{'LineWidth',2});
% end
% for i = 1:length(dataStruct.loop.object.enclosing)
%     plotFromEdgeList(dataStruct.loop.object.enclosing(i).EL, records, [1,1,1],{'LineWidth',2});
% end
end