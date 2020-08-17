%Use 9 for h1152 only.  8 For everything
load step_02_tSNE_results
close all;

figure;
rng(1)
% numBordersInner = 4;
% numBordersOuter = 6;
% idx = zeros(size(normalized_data,1),1);
% borderIndexVec = 1:size(normalized_data,1);
% idx(borderIndexVec(normalized_data(:,20)==0)) = kmeans(normalized_data(normalized_data(:,20)==0,:),numBordersInner);
% idx(borderIndexVec(normalized_data(:,20)==1)) = kmeans(normalized_data(normalized_data(:,20)==1,:),numBordersOuter) + 8;
USEFUZZY = 0;
USEGM = 0;
numBorders = 12;
[idx, clustCentr,~,borderDists] = kmeans(normalized_data,numBorders);

if(~USEFUZZY)
    image_level_cluster_count = [];
    for i=1:max(all_data(:,end))
        tmp = idx(all_data(:,end)==i);
        image_level_cluster_count(i,:) = hist(tmp,1:max(idx));
    end
    
else
    if(~USEGM)
        fuzzOverlap = 1.5;
        [fuzzyCenter, fuzzyIDVec,~] = fcm(normalized_data,numBorders,[fuzzOverlap,NaN,NaN,NaN]);
        fuzzy_image_level_cluster_count = [];
        for i=1:max(all_data(:,end))
            fuzzy_image_level_cluster_count(i,:) = sum(fuzzyIDVec(:,all_data(:,end)==i)');
        end
        image_level_cluster_count = fuzzy_image_level_cluster_count;
    else
        gm = fitgmdist(normalized_data,numBorders,'CovType','Full','SharedCovariance',false,'RegularizationValue',0.01);
        P = posterior(gm,normalized_data);
        [~,idx] = max(P');
        fuzzy_image_level_cluster_count = [];
        
        for i=1:max(all_data(:,end))
            fuzzy_image_level_cluster_count(i,:) = sum(P(all_data(:,end)==i,:));
        end
        image_level_cluster_count = fuzzy_image_level_cluster_count;
        
    end
end
figure(201);
imagesc(clustCentr);
figure(1); scatter(tSNE_map(:,1), tSNE_map(:,2), 20, idx, 'fill')
%%Test - use coverage of border type instead of raw count
% for i=1:max(all_data(:,end))
%     tmp = (all_data(:,end)==i);
%     for j = 1:size(image_level_cluster_count,2)
%         tmpBorderFilt = tmp & idx == j;
%         image_level_cluster_count_area(i,j) = sum(percentImageListFull(tmpBorderFilt));
%     end
% end
save step_03_clustering_results
% step_04_PCA_and_previous_visualizations_VITRO
