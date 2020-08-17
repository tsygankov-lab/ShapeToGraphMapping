load step_03_clustering_results;
close all;
% imageList = [1,2,6,8,11,15,17,20,22,26,28,32];
% imageList = 30;
imageList = [1,5,10,51,55,60,91,95,100];
bordersOfInterest = [1:12];
vectorSparse = zeros(numBorders,1);
vectorSparse(bordersOfInterest) = 1:length(bordersOfInterest);
% bordersOfInterest = 1:numBorders;
stat_filenames = loadAllStatFilesNames(folder_name,all_para,false);
for i = 1:length(imageList)
    imageNumber = imageList(i);
    figure('Position',[0,0,500,500]);
    subplot('Position',[0,0,1,1],'Units','Normalize');

borderIndices = all_data(:,end)==imageNumber;
load(stat_filenames{imageNumber});
imshow(records.imageMask);
colorOfBorders = jet(length(bordersOfInterest));
tmp = idx(borderIndices);
tmpMatch = any(tmp == bordersOfInterest,2);
% colorOfBorders = zeros(length(bordersOfInterest),3);
indicesOfMatch = 2:length(tmp)+1;
indicesOfMatch = indicesOfMatch(tmpMatch);
% colorOfBorders(:,:) = cMap(tmp(tmpMatch),:);
hold on;

% plotOutline_Post(records,colorOfBorders,{'LineWidth',6});
edgeIndVec = 1:length(records.edges.color);
for i = 1:length(indicesOfMatch)%1:max(records.edges.color)
    bord = indicesOfMatch(i);
    binVec = records.inputs(:,2) == bord;
%     EL = records.inputs(records.inputs(:,1)==0 & records.inputs(:,2) == i,3:4);
plotOutline_Specific(records, binVec, colorOfBorders(vectorSparse(tmp(bord-1)),:),{'LineWidth',3},{});
%     plotFromEdgeList(edgeIndVec(binVec),records,colorOfBorders(i,:),{});
%     p lotVoronoiSkeleton_SingleRegion(records,i,colorOfBorders(i,:),{});
end
ylim([90,910])
xlim([120,940])
end