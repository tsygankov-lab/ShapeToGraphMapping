function [records, dataStruct, statMat] = runVoronoi_LabelImage(filtSize, scaleFactor, dirName, picName)
if(nargin < 1 || isempty(filtSize))
    filtSize = 0;
end
if(nargin < 2)
    scaleFactor = 0.5;
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
if(nargin < 4)
    [picName,dirName] = uigetfile({'*.jpg;*.tif;*.tiff;*.png;*.gif','All Image Files';...
              '*.*','All Files' });
end
[records, dataStruct, statMat] = singleVorDir(picName,dirName,filtSize,scaleFactor);

% [path] = uigetdir('','Select Folder with .tif Images');
% [records, dataStruct]  = parForVorDir([path filesep],6);
% dirName = '\\ad.gatech.edu\bme\labs\tsygankov-lab\WilliamPilcher\BW_Pictues\Cell-Cell\';
% parForVorDir(dirName);
% dirName = '\\ad.gatech.edu\bme\labs\tsygankov-lab\WilliamPilcher\BW_Pictues\Cell-ECM\';
% parForVorDir(dirName);
end

%dirName = 'D:\wpilcher3\U2OS\Images\24638-cellobj'
%picName =
%'cdp2w3_a04_s4_w48c47ffb2-fdd1-4f8f-b296-216d1f6b1028_cellobj.tif'

function [records, dataStruct, statMat] = singleVorDir(picName,dirName,filt,scaleFactor)
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
        [records, dataStruct, statMat] = internalLoop(fid, dirName, picName,filt,scaleFactor);
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



function [records, dataStruct, statMat] = internalLoop(fid, dirName, imageFilesName, filtSize, scaleFactor)
	[~,name,~] = fileparts(imageFilesName);
im = imread([dirName imageFilesName]);

holeSizeFilt = filtSize;
plotDBG = 0;
testOldApproach=0;
holeSizeFilt = filtSize;
%printOut(fid, sprintf('%s:    Loading %s%s\r\n', datetime, dirName, imageFilesName));
tic;
imPad = zeros(size(im,1)+4, size(im,2)+4);
% imPad(1:end,1) = 0;
% imPad(1:end,end) = 0;
% imPad(1,1:end) = 0;
% imPad(end,1:end) = 0;
% imPad(3:size(imPad,1)-2,3:size(imPad,2)-2) = zeros(size(im,1)+2, size(im,2)+2);
imPad(3:size(im,1)+2,3:size(im,2)+2) = im(:,:,1);

nLabels = max(im(:));
imPad(2:end-1,2) = nLabels + 1;
imPad(2,2:end-1) = nLabels + 1;
imPad(2:end-1,end-1) = nLabels + 1;
imPad(end-1,2:end-1) = nLabels + 1;
nLabels = nLabels + 1;
procImage = zeros(size(imPad),'double'); %VoronoiMEX assumes double type, as that's what matlab's label matrices normally are
numEL = 0;
vertexCoor = [];
EL = [];
colorList = [];
m_vCor_EXT = cell(nLabels,1);
m_EL_EXT = cell(nLabels,1);
m_CL_EXT = cell(nLabels,1);
lastColor = 0;

%%For boundary...

for i = 1:nLabels
    subImage = zeros(size(imPad));
    mask = imPad == i;
    subImage(imPad==i) = 1;
    %Hole removal
%     subImage = bwareaopen(subImage(:,:,1),holeSizeFilt+1,4);
%     subImage = ~bwareaopen(~subImage(:,:,1),holeSizeFilt+1,8);
    CC = bwconncomp(subImage(:,:,1),4);
    numPixels = cellfun(@numel,CC.PixelIdxList);
    [~,idx] = max(numPixels);
    subIM_new = zeros(size(subImage));
    subIM_new(CC.PixelIdxList{idx}) = i;
    subImage = subIM_new;

    subMask = subImage > 0;
    
    procImage(subMask) = i;close all

    [m_vCor_EXT{i}, m_EL_EXT{i}, m_CL_EXT{i}, m_vCor_INT{i}, m_EL_INT{i}, m_CL_INT{i}] = multiLayerBorder_Labels(subImage, 0.99, 0, scaleFactor);
    
%     if(min(m_CL_EXT{i}) < max(m_CL_EXT{i}))
%         print(''); %should remove all but the largest
%     end
    vertexCoor = [vertexCoor;m_vCor_EXT{i}];
    EL = [EL;m_EL_EXT{i} + numEL];
    colorList = [colorList; m_CL_EXT{i} + lastColor];
    numEL = numEL + length(m_EL_EXT{i});
    lastColor = max(colorList);
    
    vertexCoor = [vertexCoor;m_vCor_INT{i}];
    EL = [EL;m_EL_INT{i} + numEL];
    colorList = [colorList; m_CL_INT{i} + lastColor];
    numEL = numEL + length(m_CL_INT{i});
    lastColor = max(colorList);
    %We now have artificially created subregions that do not exist in the
    %original image. Will have to group these regions together based on the
    %simple graph search. The question then becomes determining 'inside'
    %versus 'outside' (Maybe erode the masks, and say vertices in these
    %eroded masks are 'safely inside')
        
end
% imwrite(procImage, 'PROCIMAGETEST.png');
numNonHoles = max(colorList);
for i = 1:nLabels
    vertexCoor = [vertexCoor;m_vCor_INT{i}];
    EL = [EL;m_EL_INT{i} + numEL];
    colorList = [colorList; m_CL_INT{i} + lastColor];
    numEL = numEL + length(m_EL_INT{i});
    lastColor = max(colorList);
end
numObjects = lastColor;

procImage = procImage'; %bwconncomp gives coordinates in (row, col) instead of (col, row) [x,y], so this 'image' must be transposed to match the labelmat expected by VoronoiMEX
%Add interior edges/holes after exterior.
if(plotDBG)
    figure;
    imshow(procImage);
    %colormap('gray');
%     axis xy;
%     axis equal;
%     axis off;
    hold on;
    color = hsv(double(nLabels));
    for i = 1:nLabels
       for j = 1:length(m_EL{i}) %Inefficient, just for debug
        plot([m_vCor{i}(m_EL{i}(j,1),1),m_vCor{i}(m_EL{i}(j,2),1),nan],[m_vCor{i}(m_EL{i}(j,1),2),m_vCor{i}(m_EL{i}(j,2),2),nan],'Color', color(i,:),'LineWidth',2,'LineStyle','--');
       end
    end
    title('New Method Edges');
end
% 
% if(testOldApproach)
% nLabels = max(im(:));
% procImage = zeros(size(imPad),'uint8');
% numEL = 0;
% vertexCoor = [];
% EL = [];
% m_vCor = cell(nLabels,1);
% m_EL = cell(nLabels,1);
% for i = 1:nLabels
%     subImage = zeros(size(imPad));
%     mask = imPad == i;
%     subImage(imPad==i) = 1;
%     %Hole removal
%     subImage = bwareaopen(subImage(:,:,1),holeSizeFilt+1,4);
%     subImage = ~bwareaopen(~subImage(:,:,1),holeSizeFilt+1,8);
%     
%     subMask = mask > 0;
%     
%     procImage(subMask) = i;
% 
%     [m_vCor{i}, m_EL{i}] = multiLayerBorder_Labels(subImage, 0.99, 0, 1);
%     
%     vertexCoor = [vertexCoor;m_vCor{i}];
%     EL = [EL;m_EL{i} + numEL];
%     numEL = numEL + length(m_EL{i});
%     
%     %We now have artificially created subregions that do not exist in the
%     %original image. Will have to group these regions together based on the
%     %simple graph search. The question then becomes determining 'inside'
%     %versus 'outside' (Maybe erode the masks, and say vertices in these
%     %eroded masks are 'safely inside')
%         
% end
%     figure;
%     imshow(procImage);
% %     colormap('gray');
% %     axis xy;
% %     axis equal;
% %     axis off;
%     hold on;
%     color = hsv(double(nLabels));
%     for i = 1:nLabels
%        for j = 1:length(m_EL{i}) %Inefficient, just for debug
%         plot([m_vCor{i}(m_EL{i}(j,1),1),m_vCor{i}(m_EL{i}(j,2),1),nan],[m_vCor{i}(m_EL{i}(j,1),2),m_vCor{i}(m_EL{i}(j,2),2),nan],'Color', color(i,:),'LineWidth',2,'LineStyle','--');
%        end
%     end
%     title('Old Method');
%     
%     nLabels = max(im(:));
% procImage = zeros(size(imPad),'uint8');
% numEL = 0;
% vertexCoor = [];
% EL = [];
% m_vCor = cell(nLabels,1);
% m_EL = cell(nLabels,1);
% 
% end
%printOut(fid,sprintf('%s:     Image %s loaded - %fs\r\n', datetime, [imageFilesName], toc));
% if(filtSize > 0)
% imageName = ~bwareaopen(~im(:,:,1),holeSizeFilt+1,4);
% % end
% imageTest = zeros(size(imageName,1)+2, size(imageName,2)+2);
% imageTest(2:size(imageName,1)+1,2:size(imageName,2)+1) = imageName(:,:,1);
% imageName = imageTest;
% % imwrite(imageName,[dirName 'FiltIM' filesep 'filteredIm_' imageFilesName]);
% %ImageStruct: numObjects, numNonHoles, objLength,colorList, pixelIndOffset, labelMat, adjMat
% tic
% [vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.99,0);

%%NOTE - Label mat output by bwconncomp is transposed when read by cpp
%%code. Maybe because it's an 'image' internally?
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

printOut(fid, sprintf('%s:     Image %s Processed - %fs\r\n', datetime, [imageFilesName], toc));

% disp(['Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);
% tic

% save('badMat.mat', 'vertexCoor', 'EL', 'colorList')
records = Voronoi_DT(vertexCoor, EL, 'Color', colorList, 'NumNonHoles', numNonHoles, 'NumObjects', numObjects, 'labelImage', procImage, 'ScaleFactor',ScaleFactor);
% [records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull] = VoronoiMEX(vertexCoor, EL, [0,0],[],[],[],colorList,numNonHoles,procImage, [], [], 2, scaleFactor);

% procImage = procImage'; %Un-transpose it back for drawing
% [dataStruct] = processRecords(records);

% pause(5)
%%ROUTINE TO DESTROY RECORDS_RAW BECAUSE MATLAB LIKES TO CRASH FOR SOME REASON IF YOU
%%DO NOT DO THIS FIRST


% end
% if(exist([dirName 'LOOP_' name '.mat'],2))
% 	printOut(fid, sprintf('%s:     LOOP_ data for %s Found.  Skipping - TIME %fs\r\n\r\n', datetime, [dirName imageFilesName], toc));
% else
 
[dataStruct] = processRecords_NoImageAssumption(records);
[dataStruct] = extractCycles_NoImageAssumption(records, dataStruct);
printOut(fid, sprintf('%s:     Saving %s.mat ...\r\n - %fs\r\n', datetime, [dirName 'LOOP_' name], toc));
saveOut(records,dataStruct,[dirName 'MAT' filesep 'LOOP_' name]);

[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles_NoImageAssumption(records,dataStruct);
[statMat] = dataStruct2Stats_NoImageAssumption(records, dataStruct);



% pause(5)
% end

end