%% Ensures all code is on path
close all;
clear all;
if(~exist('endpointLine.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end

%% Load Image, fill holes, get borders.
imageFilesName = 'invbinary MAX intensity_DT2.tif';
filtSize = 0;

holeSizeFilt = filtSize;
tic;
im = imread([imageFilesName]);
imageName = ~bwareaopen(~im(:,:,1),holeSizeFilt+1,4);
imageTest = zeros(size(imageName,1)+2, size(imageName,2)+2);
imageTest(2:size(imageName,1)+1,2:size(imageName,2)+1) = imageName(:,:,1);
imageName = imageTest;
tic
[vertexCoor, EL, imageStruct] = multiLayerBorder(imageName,0.99,0);
prevTime = toc;
thisTime = prevTime;

%% Display image with holes filled
H = figure('Visible','on');
imshow(imageName);
pause(0.1);
pos = get(gcf, 'Position');
records = Voronoi_DT(vertexCoor, EL, 'ImageStruct',imageStruct);



%%Plot 'Outline' Input, then plot the Voronoi diagram in the foreground and
%%background.
H = figure('Position',pos,'Visible','on');
plotOutline_Simple(records, 'k',{});
hold on;
axis ij;
axis equal;
axis off;
for i = records.numNonHoles+1:records.numObjects
    plotRegion(records,i,'Color',[1,0.5,0]);
end

for i = 1:records.numNonHoles
    plotRegion(records,i,'Color','b');
end

%Unbound/infinite background
plotRegion(records,0,'Color',[1,0.5,0]);

xlim([0,size(records.imageMask,2)]);
ylim([0,size(records.imageMask,1)]);

