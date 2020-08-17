load step_03_clustering_results;
close all
filteredData = image_level_cluster_count;
for i=1:size(filteredData,2)
    data_tmp = filteredData(:,i);
    prc_5 = prctile(data_tmp,5);
    prc_95 = prctile(data_tmp,95);
    data_tmp(data_tmp<prc_5) = prc_5;
    data_tmp(data_tmp>prc_95) = prc_95;
    if prc_95==prc_5
        prc_95 = max(data_tmp);
        prc_5 = min(data_tmp);
    end
    if prc_95~=prc_5
        data_tmp = (data_tmp - prc_5)/(prc_95 - prc_5);
    else
        data_tmp = data_tmp*0;
    end
    filteredData(:,i) = data_tmp;
end
numClust = 5;
VITRO = false;
NORMFLAG = 0;
if(NORMFLAG)
    A = image_level_cluster_count;
    image_level_cluster_count = diag(1./sum(A,2))*A;
end
for i = 1:100
    labelList{i} = ['gx=', num2str(all_para(i,2)), ', kb=' num2str(all_para(i,3))];
end
if(~exist('loadedDataStructs') || isempty(loadedDataStructs))
    
    loadedDataStructs = loadAllIMAGEFiles(folder_name,all_para,VITRO);
end
[idxIm, clustCentrIm,~,imageDistances] = kmeans(filteredData,numClust,'MaxIter',5000);
figure;
scatter(log(all_para(:,2)),log(all_para(:,3)),50./min(imageDistances,[],2),idxIm,'filled');
clustCentroids = zeros(numClust,2);
% for i = 1:numClust
% % w = 1./imageDistances(idxIm==i);
% % w = w./sum(w);
% clustCentroids(i,:) = mean(all_para(idxIm==i,2:3),1);%[mean((all_para(idxIm==i,2))),mean((all_para(idxIm==i,3)))];
% end
% 
% hold on;
% % scatter(log(clustCentroids(:,1)),log(clustCentroids(:,2)),200,1:numClust,'filled');
% for i = 1:numClust
%     thisFig = figure('units','normalized','Position',[0.2,0.2,0.6,0.6]);
%     [~,imID] = sort(imageDistances(:,i),'ascend');
%     for j = 1:9
%         subplot(3,3,j);
%         imshow(loadedDataStructs{imID(j)});
%         title(['Cluster Rep ' num2str(j)]);
%     end
%     drawnow;
%     imData = getframe(thisFig);
%     imwrite(imData.cdata,['ClusterGroup ' num2str(i) '.png']);
% end
