close all;
dataReload = true;
% matFileName = 'LOOP_20585_D11_s3_cmock-MASK.mat';

%% Compute the Voronoi diagram using a modified runVoronoi - Output the adjusted boundaries (for label images)
if(dataReload)
    imageFileName = '20585_D11_s3_cmock-MASK.tiff';
    dirName = 'sample\';
    % fileName = [dirName, matFileName];

    im = imread([dirName imageFileName]);
    figure
    % cm = jet(3);
    cm_img = bone(4);
    cm = [0,0.5,1; 1,0,0.25; 0,0.8,0];
    % imshow(records.imageMask);
    image = zeros(size(im));
    image(im==30) = 1; %regions of interest
    image(im==31) = 2;
    image(im==42) = 3;
    imagesc(image);
    colormap('bone')

    [records, dataStruct, m_vCor_EXT, m_EL_EXT, m_vCor_EXT_old, m_EL_EXT_old] = customLoop(0, image, 0.5);
end

%% Organizes the boundaries output from customLoop
for i = 1:3
    bound_new{i} = [m_vCor_EXT{i};m_vCor_EXT{i}(1,:)];
    bound_old{i} = [m_vCor_EXT_old{i};m_vCor_EXT_old{i}(1,:)];
end

%% Plot patches to draw the normal cell boundaries.
A = figure;
hold on;
image = records.imageMask;
imageBlank = zeros(size(image));
imshow(imageBlank);
colormap('bone')
boneCM = bone(5);
xlim([280.9131, 444.4167]);
ylim([111.9598, 240.7999]);
axis square;
for i = 1:3
    bound = bound_old{i};
    patch('XData',bound(:,1),'YData',bound(:,2), 'FaceColor',boneCM(i+1,:),'EdgeColor',cm(i,:),'LineWidth',1);
end
% title('Old Boundaries');

%% Plot patches to draw the modified boundaries (contracted inward).
B = figure;
hold on;
image = records.imageMask;
imageBlank = zeros(size(image));
imshow(imageBlank);
colormap('bone')
boneCM = bone(5);
% boundaryList = [1, 2, 3];
xlim([280.9131, 444.4167]);
ylim([111.9598, 240.7999]);
axis square;
for i = 1:3
    bound = bound_new{i};
    patch('XData',bound(:,1),'YData',bound(:,2), 'FaceColor',boneCM(i+1,:),'EdgeColor',cm(i,:),'LineWidth',1);
end
% title('New Boundaries');

xlimB = [348.2414, 364.3488];
ylimB = [158.0593, 169.7158];

%% Repeat, but zoomed in.
C = figure;
hold on;
image = records.imageMask;
imageBlank = zeros(size(image));
imshow(imageBlank);
colormap('bone')
boneCM = bone(5);
% boundaryList = [1, 2, 3];
xlim(xlimB);
ylim(ylimB);
axis square;
for i = 1:3
    bound = bound_old{i};
    patch('XData',bound(:,1),'YData',bound(:,2), 'FaceColor',boneCM(i+1,:),'EdgeColor',cm(i,:),'LineWidth',2);
end
% title('Old Boundaries');

D = figure;
hold on;
image = records.imageMask;
imageBlank = zeros(size(image));
imshow(imageBlank);
colormap('bone')
boneCM = bone(5);
% boundaryList = [1, 2, 3];
xlim(xlimB);
ylim(ylimB);
axis square;
for i = 1:3
    bound = bound_new{i};
    patch('XData',bound(:,1),'YData',bound(:,2), 'FaceColor',boneCM(i+1,:),'EdgeColor',cm(i,:),'LineWidth',2);
end
% title('New Boundaries');

%% Draw Voronoi diagram over the image with contracted boundaries.
E = figure;
hold on;
% image = records.imageMask;
imshow(imageBlank);
colormap('bone')
boundaryList = [1, 2, 3];
% xlim([280.9131, 444.4167]);
% ylim([111.9598, 240.7999]);
xlim(xlimB);
ylim(ylimB);
axis square
axis ij
count = 1;
for i = 1:3
    bound = bound_new{i};
    patch('XData',bound(:,1),'YData',bound(:,2), 'FaceColor',boneCM(i+1,:),'EdgeColor',boneCM(i+1,:));
end
for i = boundaryList
%    subGraph = getCycleInfo_NoImageAssumption(records,dataStruct,i);
%    bound = subGraph.boundaryVertexCoor;
%    bound = [bound;bound(1,:)];
%     bound = bound_new{i};
%    plot(bound(:,1),bound(:,2),'Color',cm(count,:),'LineWidth',2);
   plotVoronoiSkeleton_SingleRegion(records,i,[0,0.5,1]); 
   count = count+1;
end
   plotVoronoiSkeleton_SingleRegion(records,5,[1,0.5,0]);  % background region

% print(A, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\OldBound_Fig11A.png', '-dpng', '-r300');
% print(B, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\NewBound_Fig11B.png', '-dpng', '-r300');
% print(C, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\OldBound_Zoom_Fig11C.png', '-dpng', '-r300');
% print(D, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\NewBound_Zoom_Fig11D.png', '-dpng', '-r300');
% print(E, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\Voronoi_Zoom_Fig11E.png', '-dpng', '-r300');

% savefig(G, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 11\.fig');
% savefig(I, 'Y:\tsygankov-lab\William Pilcher\Publication Figures\Figure 1\BOUNDARY_Fig5C.fig');

% for i = 1:records.numNonHoles
%     plotVoronoiSkeleton_SingleRegion(records,i,cm(i,:));
% end

%21-23? 30, 31, 42

%43,45, 57

function [records, dataStruct, m_vCor_EXT, m_EL_EXT, m_vCor_EXT_old, m_EL_EXT_old] = customLoop(fid, image, scaleFactor)
cm = [0,0.5,1; 1,0,0.25; 0,0.8,0];

% 	[~,name,~] = fileparts(imageFilesName);
name = 'Fig11_GenScript';
imageFilesName = 'Fig11_GenScript';
dirName = '';
im = image;

% holeSizeFilt = filtSize;
plotDBG = 0;
testOldApproach=1;
% holeSizeFilt = filtSize;
%printOut(fid, sprintf('%s:    Loading %s%s\r\n', datetime, dirName, imageFilesName));
tic;
imPad = zeros(size(im,1)+4, size(im,2)+4);
% imPad(1:end,1) = 0;
% imPad(1:end,end) = 0;
% imPad(1,1:end) = 0;
% imPad(end,1:end) = 0;
% imPad(3:size(imPad,1)-2,3:size(imPad,2)-2) = zeros(size(im,1)+2, size(im,2)+2);
imPad(3:size(im,1)+2,3:size(im,2)+2) = im(:,:,1);

%% number of objects in the image.
% This will assume no holes in labeled objects.
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

%% For boundary...
% Go through each object. Find largest 4 connected componenet for each
% label. Get contracted boundary verts/edges for each object, and merge
% later.
for i = 1:nLabels
    subImage = zeros(size(imPad));
    mask = imPad == i;
    subImage(imPad==i) = 1;
    %Hole removal
    CC = bwconncomp(subImage(:,:,1),4);
    numPixels = cellfun(@numel,CC.PixelIdxList);
    [~,idx] = max(numPixels);
    subIM_new = zeros(size(subImage));
    subIM_new(CC.PixelIdxList{idx}) = i;
    subImage = subIM_new;

    subMask = subImage > 0;
    
    procImage(subMask) = i;

    % modified mulitlayer border with scalefactor.
    [m_vCor_EXT{i}, m_EL_EXT{i}, m_CL_EXT{i}, m_vCor_INT{i}, m_EL_INT{i}, m_CL_INT{i}] = multiLayerBorder_Labels(subImage, 0.99, 0, scaleFactor);
    
    if(min(m_CL_EXT{i}) < max(m_CL_EXT{i}))
        print(''); %There should only be one 'color' as there should only be one object (not universally true for all label images).
    end
    vertexCoor = [vertexCoor;m_vCor_EXT{i}];
    EL = [EL;m_EL_EXT{i} + numEL];
    colorList = [colorList; m_CL_EXT{i} + lastColor];
    numEL = numEL + length(m_EL_EXT{i});
    lastColor = max(colorList);
    %We now have artificially created subregions that do not exist in the
    %original image. Will have to group these regions together based on the
    %simple graph search. The question then becomes determining 'inside'
    %versus 'outside' (Maybe erode the masks, and say vertices in these
    %eroded masks are 'safely inside')
        
end
% Create vertexCoor/EL
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
    imagesc(procImage');
    drawnow;
    colormap('bone');
%     axis xy;
    axis square;
%     axis off;
    hold on;
%     color = hsv(double(nLabels));
    for i = 1:nLabels-1
       for j = 1:length(m_EL_EXT{i}) %Inefficient, just for debug
        plot([m_vCor_EXT{i}(m_EL_EXT{i}(j,1),1),m_vCor_EXT{i}(m_EL_EXT{i}(j,2),1),nan],[m_vCor_EXT{i}(m_EL_EXT{i}(j,1),2),m_vCor_EXT{i}(m_EL_EXT{i}(j,2),2),nan],'Color', cm(i,:),'LineWidth',2);
       end
    end
%     title('New Method Edges');
    xlim([280.9131, 444.4167]);
    ylim([111.9598, 240.7999]);
    axis square;
end
% 
if(testOldApproach)
% nLabels = max(im(:));
% procImage = zeros(size(imPad),'uint8');
% numEL = 0;
% vertexCoor = [];
% EL = [];
m_vCor = cell(nLabels,1);
m_EL = cell(nLabels,1);
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
    
%     procImage(subMask) = i;


    [m_vCor_EXT_old{i}, m_EL_EXT_old{i}, m_CL_EXT_old{i}, m_vCor_INT_old{i}, m_EL_INT_old{i}, m_CL_INT_old{i}] = multiLayerBorder_Labels(subImage, 0.99, 0, 1);
    
    if(min(m_CL_EXT_old{i}) < max(m_CL_EXT_old{i}))
        print(''); %should remove all but the largest
    end
%     vertexCoor = [vertexCoor;m_vCor_EXT{i}];
%     EL = [EL;m_EL_EXT{i} + numEL];
%     colorList = [colorList; m_CL_EXT_old{i} + lastColor];
%     numEL = numEL + length(m_EL_EXT_old{i});
%     lastColor = max(colorList);    
%     vertexCoor = [vertexCoor;m_vCor{i}];
%     EL = [EL;m_EL{i} + numEL];
%     numEL = numEL + length(m_EL{i});
    
    %We now have artificially created subregions that do not exist in the
    %original image. Will have to group these regions together based on the
    %simple graph search. The question then becomes determining 'inside'
    %versus 'outside' (Maybe erode the masks, and say vertices in these
    %eroded masks are 'safely inside')
        
end
    figure;
    imagesc(procImage');
    colormap('bone');
%     axis xy;
%     axis equal;
%     axis off;
    hold on;
    color = cm;
    for i = 1:nLabels-1
       for j = 1:length(m_EL_EXT_old{i}) %Inefficient, just for debug
        plot([m_vCor_EXT_old{i}(m_EL_EXT_old{i}(j,1),1),m_vCor_EXT_old{i}(m_EL_EXT_old{i}(j,2),1),nan],[m_vCor_EXT_old{i}(m_EL_EXT_old{i}(j,1),2),m_vCor_EXT_old{i}(m_EL_EXT_old{i}(j,2),2),nan],'Color', color(i,:),'LineWidth',2);
       end
    end
%     title('Old Method');
    xlim([280.9131, 444.4167]);
    ylim([111.9598, 240.7999]);
    axis square;

end
prevTime = toc;
thisTime = prevTime;
disp(['(MATLAB) Borders Traced:' num2str(thisTime) 's. Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);

printOut(fid, sprintf('%s:     Image %s Processed - %fs\r\n', datetime, [imageFilesName], toc));

% disp(['Num Verts: ' num2str(size(vertexCoor,1)) ', Num Edges: ' num2str(size(EL,1))]);
% tic

% save('badMat.mat', 'vertexCoor', 'EL', 'colorList')
records = Voronoi_DT(vertexCoor, EL, 'Color', colorList, 'numObjects',numObjects,'numNonHoles',numNonHoles,'labelMat',procImage,'searchMode',2,'scaleFactor',scaleFactor);
records.imageName = imageFilesName;
records.imageDir = dirName;
records.imageMask = procImage'; %procImage from multiLayerBorder is transposed from the input image.


procImage = procImage'; %Un-transpose it back for drawing
% [dataStruct] = processRecords(records); %should not have been run
printOut(fid, sprintf('%s:     Image %s Records Processed for Bridges - %d\r\n', datetime, [name], toc));

printOut(fid, sprintf('%s:     Saving %s.mat ...\r\n - %fs\r\n', datetime, [dirName 'RAW_' name], toc));

%% Featurize
[dataStruct] = processRecords_NoImageAssumption(records);
[dataStruct] = extractCycles_NoImageAssumption(records, dataStruct);
printOut(fid, sprintf('%s:     Saving %s.mat ...\r\n - %fs\r\n', datetime, [dirName 'LOOP_' name], toc));
% saveOut(records,dataStruct,[dirName 'MAT' filesep 'LOOP_' name]);

[dataStruct] = acyl_MajorAxis(records, dataStruct, 30);
[dataStruct] = resampleAllInteriorCycles_NoImageAssumption(records,dataStruct);
% [statMat] = dataStruct2Stats_NoImageAssumption(records, dataStruct);
end