function [vertexCoor, EL, imageStruct] = multiLayerBorder(image, weight, plotDBG, scaleFactor)
if(nargin == 2)
    plotDBG = 0;
end
if(nargin == 1)
    plotDBG = 0;
    weight = 0.99;
end
if(nargin < 4)
    scaleFactor = 1.0;
end

lineParams = {'lineWidth',2};

%%Scale factor -> Each point on the boundary (at the center pixel) is
%%expanded outward to lie on the half pixel border if scaleFactor = 1.0.
%%Scale factors less than 1.0 draws the expanded border inward towards the
%%center.
%%Keep sparse adjacency matrix
%%Keep image of zeros
%%Check if a pixel exists.  IF it does, associate the two
%%Find the edge between this point and the next one.  
 
%%Diagonals have a few cross back types
%%Full double back - must add all four vertices
%%Special case with holes - one pixel gap -> switchback
% plotDBG = 1;
borders_TEMP = image(:,:,1)' > 0;
if(plotDBG)
figtmp = figure('position',[0,0,size(image,2)/2,size(image,1)/2]);
fig1 = subplot('position',[0,0,1,1],'units','normalized');
%     fig1 = subplot(1,1,1);
imshow(borders_TEMP');
hold on;
    axis ij;
figtmp = figure('position',[0,0,size(image,2)/2,size(image,1)/2]);
fig2 = subplot('position',[0,0,1,1],'units','normalized');

imshow(zeros(size(borders_TEMP')));

    axis ij;
hold on;
figtmp = figure('position',[0,0,size(image,2)/2,size(image,1)/2]);
fig3 = subplot('position',[0,0,1,1],'units','normalized');

imshow(zeros(size(borders_TEMP')));

    axis ij;
hold on;
figtmp = figure('position',[0,0,size(image,2)/2,size(image,1)/2]);
fig4 = subplot('position',[0,0,1,1],'units','normalized');
    axis ij;
hold on;
imshow(zeros(size(borders_TEMP')));

end
borders_TEMP = imclearborder(borders_TEMP);
% modifiedBWRoutine = 0;
% if(~modifiedBWRoutine)
[borders_T, labelMat, numNonHoles, adjMat] = bwboundaries(borders_TEMP,'holes');
% else
% [borders_T, ~, numNonHoles, ~] = bwboundaries(borders_TEMP,'noholes');
% borders_TEMP_C = imcomplement(borders_TEMP);
% borders_TEMP_C = imclearborder(borders_TEMP_C, 4);
% 
% % borders_TEMP_C = imclearborder(borders_TEMP_C);
% [borders_T_C, ~, numHoles, ~] = bwboundaries(borders_TEMP_C,'noholes');
% % if(numHoles > 1)
%     borders_T = [borders_T;borders_T_C(2:numHoles)];
% % end
% end
numObjects = length(borders_T);
colorSpace = hsv(numObjects);
numPixels = zeros(numObjects,1);
%vertexColorMap = zeros(0,0);
for i = 1:numObjects
    if(plotDBG)

%     subplot(1,3,1)
% plot(borders_T{i}(:,1),borders_T{i}(:,2),'Color',colorSpace(i,:),'Parent',fig1);
%     subplot(1,3,2)
    end
if(size(borders_T{i},1) > 2)
    pixelList = borders_T{i}(1:end-1,:);
diffY = [0.5*(pixelList(1,2) - pixelList(end,2));0.5*(pixelList(2:end,2) - pixelList(1:end-1,2))];
diffX = [0.5*(pixelList(1,1) - pixelList(end,1));0.5*(pixelList(2:end,1) - pixelList(1:end-1,1))];
nextDiffX = [diffX(2:end);diffX(1)];
nextDiffY = [diffY(2:end);diffY(1)];
	negY = diffY < 0;
	negX = diffX < 0;
	posY = diffY > 0;
	posX = diffX > 0;
% 	eqY = diffY == 0;
% 	eqX = diffX == 0;

    %%Was previously a left shift, now a right shift
	lsnegX = nextDiffX < 0;
	lsposX = nextDiffX > 0;
% 	lseqX =  nextDiffX == 0;
% 	lseqY =  nextDiffY == 0;
	lsnegY = nextDiffY < 0;
	lsposY = nextDiffY > 0;


if(i <= numNonHoles)
    %%The path reached this position with a diagonal move and is reversing
    diagDRSwitchBack = lsposY & lsnegX & posX & negY;
    diagDLSwitchBack = negX & negY & lsposY & lsposX;
    diagURSwitchBack = posY & posX & lsnegX & lsnegY;
    diagULSwitchBack = posY & negX & lsposX & lsnegY;
    diagSB = diagDRSwitchBack | diagDLSwitchBack | diagURSwitchBack | diagULSwitchBack;

    %%The path makes a 270 degree or greater turn with one of the
    %%directions being diagonal
    diagCrossDRDL = ~diagSB & (posX & negY & lsnegX | posX & lsnegX & lsnegY);
    diagCrossDLUL = ~diagSB & (negX & negY & lsposY | negY & lsnegX & lsposY);
    diagCrossULUR = ~diagSB & (negX & posY & lsposX | negX & lsposX & lsposY);
    diagCrossURDR = ~diagSB & (posX & posY & lsnegY | posY & lsposX & lsnegY);
    diagCross = diagCrossDRDL | diagCrossDLUL | diagCrossULUR | diagCrossURDR;

    %%The path changes direction at a 270 degree with the initial angles
    %%being horizontal, or the paths next move is diagonal
    downLeftInd = ~diagSB & ~diagCross & negY & lsnegX;
    downRightInd = ~diagSB & ~diagCross & posX & lsnegY;
    upLeftInd = ~diagSB & ~diagCross & negX & lsposY;
    upRightInd = ~diagSB & ~diagCross & posY & lsposX;
    diagMove = downLeftInd | downRightInd | upLeftInd | upRightInd;

    %%The path got to this point with a diagonal line, but will no longer
    %%be diagonal, and the direction at the end is a turn less than 180
    %%degrees
    restrainDLInd = ~diagMove & ~diagSB & ~diagCross & negY & negX;
    restrainDRInd = ~diagMove & ~diagSB & ~diagCross & negY & posX;
    restrainULInd = ~diagMove & ~diagSB & ~diagCross & posY & negX;
    restrainURInd = ~diagMove & ~diagSB & ~diagCross & posY & posX;
    restrainDiag = restrainDLInd | restrainDRInd | restrainULInd | restrainURInd;
    
    %%The path reached this point by moving left/right/up/down and is
    %%reversing direction
    upDownSwitchBack = ~diagMove & ~diagSB & ~restrainDiag & ~diagCross & lsnegY & posY;
   	downUpSwitchBack = ~diagMove & ~diagSB & ~restrainDiag & ~diagCross & lsposY & negY;
   	leftRightSwitchBack = ~diagMove & ~diagSB & ~restrainDiag & ~diagCross & lsposX & negX;
   	rightLeftSwitchBack = ~diagMove &  ~diagSB & ~restrainDiag & ~diagCross & lsnegX & posX;

    
    allManipulations = diagSB*3  + upLeftInd + upRightInd + downLeftInd + downRightInd + diagCross* 2 + upDownSwitchBack*2 + downUpSwitchBack*2 + leftRightSwitchBack*2 + rightLeftSwitchBack*2;
    indexShift = cumsum(allManipulations);

    upRightIndShift = find(upRightInd) + indexShift(upRightInd);
    upLeftIndShift = find(upLeftInd) + indexShift(upLeftInd);
    downLeftIndShift = find(downLeftInd) + indexShift(downLeftInd);
    downRightIndShift = find(downRightInd) + indexShift(downRightInd);

    restrainDLIndShift = find(restrainDLInd) + indexShift(restrainDLInd);
    restrainDRIndShift = find(restrainDRInd) + indexShift(restrainDRInd);
    restrainULIndShift = find(restrainULInd) + indexShift(restrainULInd);
    restrainURIndShift = find(restrainURInd) + indexShift(restrainURInd);

    diagCrossDRDLIndShift = find(diagCrossDRDL) + indexShift(diagCrossDRDL);
    diagCrossDLULIndShift = find(diagCrossDLUL) + indexShift(diagCrossDLUL);
    diagCrossULURIndShift = find(diagCrossULUR) + indexShift(diagCrossULUR);
    diagCrossURDRIndShift = find(diagCrossURDR) + indexShift(diagCrossURDR);

    upDownSwitchBackIndShift = find(upDownSwitchBack) + indexShift(upDownSwitchBack);
    downUpSwitchBackIndShift = find(downUpSwitchBack) + indexShift(downUpSwitchBack);
    leftRightSwitchBackIndShift = find(leftRightSwitchBack) + indexShift(leftRightSwitchBack);
    rightLeftSwitchBackIndShift = find(rightLeftSwitchBack) + indexShift(rightLeftSwitchBack);
    
    diagDRSwitchBackIndShift = find(diagDRSwitchBack) + indexShift(diagDRSwitchBack);
    diagDLSwitchBackIndShift = find(diagDLSwitchBack) + indexShift(diagDLSwitchBack);
    diagURSwitchBackIndShift = find(diagURSwitchBack) + indexShift(diagURSwitchBack);
    diagULSwitchBackIndShift = find(diagULSwitchBack) + indexShift(diagULSwitchBack);

    movePattern = zeros(length(pixelList)+max(indexShift) -1,2);
    movePattern((1:length(pixelList))' + indexShift,:) = [-diffY + diffX, diffY+ diffX];
    
    movePattern(restrainDLIndShift,:) = repmat([0.5,-0.5],length(restrainDLIndShift),1);
    movePattern(restrainDRIndShift,:) = repmat([0.5,0.5],length(restrainDRIndShift),1);
    movePattern(restrainULIndShift,:) = repmat([-0.5,-0.5],length(restrainULIndShift),1);
    movePattern(restrainURIndShift,:) = repmat([-0.5,0.5],length(restrainURIndShift),1);
    
    movePattern(upRightIndShift,:) = repmat([0.5,0.5],length(upRightIndShift),1);
    movePattern(upLeftIndShift,:)= repmat([-0.5,0.5],length(upLeftIndShift),1);
    movePattern(downLeftIndShift,:) = repmat([-0.5,-0.5],length(downLeftIndShift),1);
    movePattern(downRightIndShift,:) = repmat([0.5,-0.5],length(downRightIndShift),1);
    
    movePattern(upRightIndShift - 1,:) = repmat([-0.5,0.5],length(upRightIndShift),1);
    movePattern(upLeftIndShift - 1,:)= repmat([-0.5,-0.5],length(upLeftIndShift),1);
    movePattern(downLeftIndShift - 1,:) = repmat([0.5,-0.5],length(downLeftIndShift),1);
    movePattern(downRightIndShift - 1,:) = repmat([0.5,0.5],length(downRightIndShift),1);
    
    movePattern(upDownSwitchBackIndShift-2,:) = repmat([-0.5, 0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift-2,:) = repmat([0.5, -0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift-2,:) = repmat([-0.5, -0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift-2,:) = repmat([0.5, 0.5],length(rightLeftSwitchBackIndShift),1);
    
    movePattern(upDownSwitchBackIndShift-1,:) = repmat([0.5, 0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift-1,:) = repmat([-0.5, -0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift-1,:) = repmat([-0.5, 0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift-1,:) = repmat([0.5, -0.5],length(rightLeftSwitchBackIndShift),1);

    movePattern(upDownSwitchBackIndShift,:) = repmat([0.5, -0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift,:) = repmat([-0.5, 0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift,:) = repmat([0.5, 0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift,:) = repmat([-0.5, -0.5],length(rightLeftSwitchBackIndShift),1);
    
    movePattern(diagDRSwitchBackIndShift-3,:) = repmat([0.5, 0.5],length(diagDRSwitchBackIndShift),1);
    movePattern(diagDLSwitchBackIndShift-3,:) = repmat([0.5, -0.5],length(diagDLSwitchBackIndShift),1);
    movePattern(diagURSwitchBackIndShift-3,:) = repmat([-0.5, 0.5],length(diagURSwitchBackIndShift),1);
    movePattern(diagULSwitchBackIndShift-3,:) = repmat([-0.5, -0.5],length(diagULSwitchBackIndShift),1);
    
    movePattern(diagDRSwitchBackIndShift-2,:) = repmat([0.5, -0.5],length(diagDRSwitchBackIndShift),1);
    movePattern(diagDLSwitchBackIndShift-2,:) = repmat([-0.5, -0.5],length(diagDLSwitchBackIndShift),1);
    movePattern(diagURSwitchBackIndShift-2,:) = repmat([0.5, 0.5],length(diagURSwitchBackIndShift),1);
    movePattern(diagULSwitchBackIndShift-2,:) = repmat([-0.5, 0.5],length(diagULSwitchBackIndShift),1);
    
    movePattern(diagDRSwitchBackIndShift-1,:) = repmat([-0.5, -0.5],length(diagDRSwitchBackIndShift),1);
    movePattern(diagDLSwitchBackIndShift-1,:) = repmat([-0.5, 0.5],length(diagDLSwitchBackIndShift),1);
    movePattern(diagURSwitchBackIndShift-1,:) = repmat([0.5, -0.5],length(diagURSwitchBackIndShift),1);
    movePattern(diagULSwitchBackIndShift-1,:) = repmat([0.5, 0.5],length(diagULSwitchBackIndShift),1);
    
    movePattern(diagDRSwitchBackIndShift,:) = repmat([-0.5, 0.5],length(diagDRSwitchBackIndShift),1);
    movePattern(diagDLSwitchBackIndShift,:) = repmat([0.5, 0.5],length(diagDLSwitchBackIndShift),1);
    movePattern(diagURSwitchBackIndShift,:) = repmat([-0.5, -0.5],length(diagURSwitchBackIndShift),1);
    movePattern(diagULSwitchBackIndShift,:) = repmat([0.5, -0.5],length(diagULSwitchBackIndShift),1);
    
    movePattern(diagCrossDRDLIndShift-2,:) = repmat([0.5, 0.5],length(diagCrossDRDLIndShift),1);
    movePattern(diagCrossDLULIndShift-2,:) = repmat([0.5, -0.5],length(diagCrossDLULIndShift),1);
    movePattern(diagCrossULURIndShift-2,:) = repmat([-0.5, -0.5],length(diagCrossULURIndShift),1);
    movePattern(diagCrossURDRIndShift-2,:) = repmat([-0.5, 0.5],length(diagCrossURDRIndShift),1);
    
    movePattern(diagCrossDRDLIndShift-1,:) = repmat([0.5, -0.5],length(diagCrossDRDLIndShift),1);
    movePattern(diagCrossDLULIndShift-1,:) = repmat([-0.5, -0.5],length(diagCrossDLULIndShift),1);
    movePattern(diagCrossULURIndShift-1,:) = repmat([-0.5, 0.5],length(diagCrossULURIndShift),1);
    movePattern(diagCrossURDRIndShift-1,:) = repmat([0.5, 0.5],length(diagCrossURDRIndShift),1);

    movePattern(diagCrossDRDLIndShift,:) = repmat([-0.5, -0.5],length(diagCrossDRDLIndShift),1);
    movePattern(diagCrossDLULIndShift,:) = repmat([-0.5, 0.5],length(diagCrossDLULIndShift),1);
    movePattern(diagCrossULURIndShift,:) = repmat([0.5, 0.5],length(diagCrossULURIndShift),1);
    movePattern(diagCrossURDRIndShift,:) = repmat([0.5, -0.5],length(diagCrossURDRIndShift),1);

    horizSwitchBacks = [upDownSwitchBackIndShift;downUpSwitchBackIndShift;leftRightSwitchBackIndShift;rightLeftSwitchBackIndShift;diagCrossDRDLIndShift;diagCrossDLULIndShift;diagCrossULURIndShift;diagCrossURDRIndShift];
    diagSwitchBacks = [diagDRSwitchBackIndShift; diagDLSwitchBackIndShift; diagURSwitchBackIndShift; diagULSwitchBackIndShift];
    borders_sum{i} = zeros(length(pixelList) + max(indexShift),2);
    borders_sum{i}((1:length(pixelList))' + indexShift,:) = pixelList(:,:);
    
    borders_sum{i}(diagSwitchBacks -3,:) = borders_sum{i}(diagSwitchBacks,:);
    
    borders_sum{i}([horizSwitchBacks;diagSwitchBacks] -2,:) = borders_sum{i}([horizSwitchBacks;diagSwitchBacks],:);
    indexArray = [upRightIndShift; upLeftIndShift; downLeftIndShift; downRightIndShift; horizSwitchBacks; diagSwitchBacks];
    borders_sum{i}(indexArray - 1,:) = borders_sum{i}(indexArray,:);
    borders{i} = borders_sum{i} + movePattern*scaleFactor;
    if(plotDBG)
    plot(borders_T{i}(:,1),borders_T{i}(:,2),'-','Color','c','Parent',fig4,lineParams{:});
    plot(borders_T{i}(:,1),borders_T{i}(:,2),'o','Color',[1,0.5,0],'Parent',fig4,lineParams{:});

    plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'-','Color','c','Parent',fig2,lineParams{:});
        plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'o','Color',[1,0.5,0],'Parent',fig2,lineParams{:});

    end
    numPixels(i) = size(borders{i},1);
else% movePattern
%     upLeftCornerCut = zeros(size(lsnegX));
%     leftDownCornerCut = zeros(size(lsnegX));
%     downRightCornerCut = zeros(size(lsnegX));
%     rightUpCornerCut = zeros(size(lsnegX));
%     numPoints = length(posY);
%     idexVec = [2:numPoints,1];

	upLeftCornerCut =  lsnegX & posY;
	leftDownCornerCut =  lsnegY & negX;
	downRightCornerCut =  lsposX & negY;
	rightUpCornerCut =  lsposY & posX;
    cornerCuts = upLeftCornerCut | leftDownCornerCut | downRightCornerCut | rightUpCornerCut;
    posY = posY(~cornerCuts);
    posX = posX(~cornerCuts);
    negX = negX(~cornerCuts);
    negY = negY(~cornerCuts);
    lsnegX = lsnegX(~cornerCuts);
    lsnegY = lsnegY(~cornerCuts);
    lsposY = lsposY(~cornerCuts);
    lsposX = lsposX(~cornerCuts);
    pixListAdj = pixelList(~cornerCuts,:);

    upDownSwitchBack = lsnegY & posY;
   	downUpSwitchBack = lsposY & negY;
   	leftRightSwitchBack = lsposX & negX;
   	rightLeftSwitchBack = lsnegX & posX;
% 	upLeftCornerCut(idexVec) = ~leftRightSwitchBack(idexVec) & lsnegX & posY;
% 	leftDownCornerCut(idexVec) = ~downUpSwitchBack(idexVec) & lsnegY & negX;
% 	downRightCornerCut(idexVec) = ~rightLeftSwitchBack(idexVec) & lsposX & negY;
% 	rightUpCornerCut(idexVec) = ~upDownSwitchBack(idexVec) & lsposY & posX;

        %%The path changes direction at a 270 degree with the initial angles
    %%being horizontal, or the paths next move is diagonal
    downLeftInd = negY & lsnegX;
    downRightInd = posX & lsnegY;
    upLeftInd = negX & lsposY;
    upRightInd = posY & lsposX;
    diagMove = downLeftInd | downRightInd | upLeftInd | upRightInd;

    
    
    
   	allManipulations = upDownSwitchBack*2 + downUpSwitchBack*2 + leftRightSwitchBack*2 + rightLeftSwitchBack*2 + diagMove;
    indexShift = cumsum(allManipulations);

    %upLeftCornerCutIndShift = find(upLeftCornerCut) + indexShift(upLeftCornerCut);
    %leftDownCornerCutIndShift = find(leftDownCornerCut) + indexShift(leftDownCornerCut);
    %downRightCornerCutIndShift = find(downRightCornerCut) + indexShift(downRightCornerCut);
    %rightUpCornerCutIndShift = find(rightUpCornerCut) + indexShift(rightUpCornerCut);
    upDownSwitchBackIndShift = find(upDownSwitchBack) + indexShift(upDownSwitchBack);% + rightUpCornerCut(upDownSwitchBack);
    downUpSwitchBackIndShift = find(downUpSwitchBack) + indexShift(downUpSwitchBack);% + leftDownCornerCut(downUpSwitchBack);
    leftRightSwitchBackIndShift = find(leftRightSwitchBack) + indexShift(leftRightSwitchBack);% + upLeftCornerCut(leftRightSwitchBack);
    rightLeftSwitchBackIndShift = find(rightLeftSwitchBack) + indexShift(rightLeftSwitchBack);% + downRightCornerCut(rightLeftSwitchBack);

    upRightIndShift = find(upRightInd) + indexShift(upRightInd);
    upLeftIndShift = find(upLeftInd) + indexShift(upLeftInd);
    downLeftIndShift = find(downLeftInd) + indexShift(downLeftInd);
    downRightIndShift = find(downRightInd) + indexShift(downRightInd);

    movePattern = zeros(length(pixListAdj)+indexShift(end),2);
    movePattern((1:length(pixListAdj))' + indexShift,:) = [-diffY(~cornerCuts) + diffX(~cornerCuts), diffY(~cornerCuts)+ diffX(~cornerCuts)];

    movePattern(upRightIndShift,:) = repmat([0.5,0.5],length(upRightIndShift),1);
    movePattern(upLeftIndShift,:)= repmat([-0.5,0.5],length(upLeftIndShift),1);
    movePattern(downLeftIndShift,:) = repmat([-0.5,-0.5],length(downLeftIndShift),1);
    movePattern(downRightIndShift,:) = repmat([0.5,-0.5],length(downRightIndShift),1);
    
    movePattern(upRightIndShift - 1,:) = repmat([-0.5,0.5],length(upRightIndShift),1);
    movePattern(upLeftIndShift - 1,:)= repmat([-0.5,-0.5],length(upLeftIndShift),1);
    movePattern(downLeftIndShift - 1,:) = repmat([0.5,-0.5],length(downLeftIndShift),1);
    movePattern(downRightIndShift - 1,:) = repmat([0.5,0.5],length(downRightIndShift),1);
    
    movePattern(upDownSwitchBackIndShift-2,:) = repmat([-0.5, 0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift-2,:) = repmat([0.5, -0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift-2,:) = repmat([-0.5, -0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift-2,:) = repmat([0.5, 0.5],length(rightLeftSwitchBackIndShift),1);
    
    movePattern(upDownSwitchBackIndShift-1,:) = repmat([0.5, 0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift-1,:) = repmat([-0.5, -0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift-1,:) = repmat([-0.5, 0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift-1,:) = repmat([0.5, -0.5],length(rightLeftSwitchBackIndShift),1);

    movePattern(upDownSwitchBackIndShift,:) = repmat([0.5, -0.5],length(upDownSwitchBackIndShift),1);
    movePattern(downUpSwitchBackIndShift,:) = repmat([-0.5, 0.5],length(downUpSwitchBackIndShift),1);
    movePattern(leftRightSwitchBackIndShift,:) = repmat([0.5, 0.5],length(leftRightSwitchBackIndShift),1);
    movePattern(rightLeftSwitchBackIndShift,:) = repmat([-0.5, -0.5],length(rightLeftSwitchBackIndShift),1);
    
    borders_sum{i} = zeros(length(pixListAdj) + indexShift(end),2);
    borders_sum{i}((1:length(pixListAdj))' + indexShift,:) = pixListAdj(:,:);
    indexArray = [upDownSwitchBackIndShift; downUpSwitchBackIndShift; leftRightSwitchBackIndShift; rightLeftSwitchBackIndShift];
    borders_sum{i}(indexArray - 2,:) = borders_sum{i}(indexArray,:);
    
    indexArray = [indexArray;upRightIndShift;upLeftIndShift;downLeftIndShift;downRightIndShift];
    borders_sum{i}(indexArray - 1,:) = borders_sum{i}([indexArray],:);
    
    borders{i} = borders_sum{i} + movePattern;
    if(plotDBG)
    plot(borders_T{i}(:,1),borders_T{i}(:,2),'-','Color','c','Parent',fig4,lineParams{:});
        plot(borders_T{i}(:,1),borders_T{i}(:,2),'o','Color',[1,0.5,0],'Parent',fig4,lineParams{:});

    plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'-','Color','c','Parent',fig2,lineParams{:});
        plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'o','Color',[1,0.5,0],'Parent',fig2,lineParams{:});

    end
    numPixels(i) = size(borders{i},1);
end

else 
	borders{i} = repmat(borders_T{i}(1,:),4,1) + [-0.5, -0.5; -0.5, 0.5; 0.5, 0.5; 0.5 -0.5];
    if(plotDBG)
    plot(borders_T{i}(:,1),borders_T{i}(:,2),'-','Color','c','Parent',fig4,lineParams{:});
        plot(borders_T{i}(:,1),borders_T{i}(:,2),'o','Color',[1,0.5,0],'Parent',fig4,lineParams{:});

    plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'-','Color','c','Parent',fig2,lineParams{:});
        plot([borders{i}(end,1); borders{i}(:,1)], [borders{i}(end,2); borders{i}(:,2)],'o','Color',[1,0.5,0],'Parent',fig2,lineParams{:});

    end
        numPixels(i) = size(borders{i},1);
end

%for j = 1:size(border{i},1)
%	if(vertexColorMap(borders{i}(j,:)) == 0)
%		vertexColorMap(borders{i}(j,:)) = color;
%		vertUnique = 
end
pixelIndOffset = [0;cumsum(numPixels)];
vertArray = cell2mat(borders');
[uniquePixels,~,unTestB] = unique(vertArray,'rows','stable');
repeatedIndices = find(accumarray(unTestB,1,[size(uniquePixels,1), 1])>1);
% weight = 0.66;
vertArrayNoMod = vertArray;
%%Loop is the safest here...
for i = 1:length(repeatedIndices)
    
    listVertIDs = find(unTestB == repeatedIndices(i));
    for k = 1:length(listVertIDs)
            caseHandled = 0;
        for j = 1:length(pixelIndOffset)
            if(listVertIDs(k) == pixelIndOffset(j))
                vertArray(listVertIDs(k),:) = weight.*vertArrayNoMod(listVertIDs(k),:) + (1-weight).*mean([vertArrayNoMod(listVertIDs(k)-1,:);vertArrayNoMod(pixelIndOffset(j-1)+1,:)],1);
                caseHandled = 1;
            elseif(listVertIDs(k) == pixelIndOffset(j)+1)
                vertArray(listVertIDs(k),:) = weight.*vertArrayNoMod(listVertIDs(k),:) + (1-weight).*mean([vertArrayNoMod(listVertIDs(k)+1,:);vertArrayNoMod(pixelIndOffset(j+1),:)],1);  
                            caseHandled = 1;

            end
        end
        if(~caseHandled)
            vertArray(listVertIDs(k),:) = weight.*vertArrayNoMod(listVertIDs(k),:) + (1-weight).*mean([vertArrayNoMod(listVertIDs(k)-1,:);vertArrayNoMod(listVertIDs(k)+1,:)],1); 
        end
    %     if(any(repeatedIndices(i) == pixelIndOffset))
    end
end
if(plotDBG)
% subplot(1,3,3)

for i = 1:numObjects
    if(i <= numNonHoles)
        plot([vertArray(pixelIndOffset(i+1),1);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),1)],[vertArray(pixelIndOffset(i+1),2);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),2)],'-','Color','c','Parent',fig3,lineParams{:});
                plot([vertArray(pixelIndOffset(i+1),1);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),1)],[vertArray(pixelIndOffset(i+1),2);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),2)],'o','Color',[1,0.5,0],'Parent',fig3,lineParams{:});

    else
        plot([vertArray(pixelIndOffset(i+1),1);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),1)],[vertArray(pixelIndOffset(i+1),2);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),2)],'-','Color','c','Parent',fig3,lineParams{:});
                plot([vertArray(pixelIndOffset(i+1),1);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),1)],[vertArray(pixelIndOffset(i+1),2);vertArray(pixelIndOffset(i)+1:pixelIndOffset(i+1),2)],'o','Color',[1,0.5,0],'Parent',fig3,lineParams{:});

    end
end
end
% subplot(1,2,2)
% imshow(image);
% hold on;
% borders = cell(numNonHoles,1);
% for i = 1:numNonHoles
%    border = label(:,:) == i;
%    [border] = bwboundaries(border,'holes');
%    borders{i}(:,:) = border{1};
%    plot(borders{i}(:,1),borders{i}(:,2),'Color',colorSpace(i,:));
% end
% for i = numNonHoles+1:numObjects
%    border = label(:,:) == i;
%    border = bwdist(border) < 2;
%    [border] = bwboundaries(border,'holes');
%    borders{i}(:,:) = border{1};
%    plot(borders{i}(:,1),borders{i}(:,2),'Color',colorSpace(i,:)); 
% end
vertexCoor = [];
EL = [];
% objLength = zeros(numObjects,1);
objLength = numPixels;
colorList = zeros(size(vertArray,1),1);
% subplot(1,2,2)
% imshow(image);
% hold on;
for i = 1:numObjects
    %fb = regbound(borders{i});
    %fb = regbound(fb);
    %plot(fb(:,1),fb(:,2),'Color',colorSpace(i,:));
    %if(size(fb,1) == 2)
    %    fb = fb(1,:);
    %end
    %objLength(i) = size(fb,1);
%     [tempCorr, ~, idMap] = unique(borders{i},'rows','stable');
    EL = [EL;[pixelIndOffset(i+1),pixelIndOffset(i)+1];[(pixelIndOffset(i)+1:pixelIndOffset(i+1)-1)',(pixelIndOffset(i)+2:pixelIndOffset(i+1))']];
    colorList(pixelIndOffset(i)+1:pixelIndOffset(i+1)) = i;
%     if(i == 1)
%     	obj_idMap(i,:) = idMap;
% 	else
% 		obj_idMap(i,:) = idMap + obj_numVerts(i-1);
% 	end
% 	numRawCoor(i) = length(idMap);
%     vertexCoor = [vertexCoor; tempCorr];
%         obj_numVerts(i) = max(idMap);
%         obj_EL(i) = 0;
%         obj_numEdges(i) = 0;
%     if(numRawCoor(i) > 1)
%     ELtemp = [obj_idMap(i,1:end-1),obj_idMap(i,2:end);obj_idMap(i,end),obj_idMap(i,1)];
%     [~,indices,~] = unique(ELtemp,'rows','stable');
%     indToTake  = find(indices <= numRawCoor(i),'last');
%     ELobj = ELtemp(indices(1:indToTake),:);
%     obj_EL{i} = ELobj;
%     obj_numEdges(i) = length(obj_EL);
%     EL = [EL;ELobj];
% 	end
end
imageStruct.numObjects = numObjects;
imageStruct.numNonHoles = numNonHoles;
imageStruct.objLength = objLength;
imageStruct.colorList = colorList;
imageStruct.pixelIndOffset = pixelIndOffset;
imageStruct.labelMat = labelMat;
imageStruct.adjMat = adjMat;
imageStruct.imageMask = image;
vertexCoor = vertArray;