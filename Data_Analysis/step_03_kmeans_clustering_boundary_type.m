load step_02_tSNE_results
close all;
figure;
rng(1)
numBorders = 12;
idx = kmeans(normalized_data,numBorders);
figure(1); scatter(tSNE_map(:,1), tSNE_map(:,2), 20, idx, 'fill')

USEFUZZY = 0;
if(~USEFUZZY)
    image_level_cluster_count = [];
    for i=1:max(all_data(:,end))
        tmp = idx(all_data(:,end)==i);
        image_level_cluster_count(i,:) = hist(tmp,1:max(idx));
    end
    
else
    fuzzOverlap = 1.5;
    [fuzzyCenter, fuzzyIDVec,~] = fcm(normalized_data,numBorders,[fuzzOverlap,NaN,NaN,NaN]);
    fuzzy_image_level_cluster_count = [];
    for i=1:max(all_data(:,end))
        fuzzy_image_level_cluster_count(i,:) = sum(fuzzyIDVec(:,all_data(:,end)==i)');
    end
    image_level_cluster_count = fuzzy_image_level_cluster_count;
end
% image_level_cluster_count(:,numBorders+1) = log(sum(image_level_cluster_count(:,1:numBorders),2));


% end
%%Border 'diversity' metric - percent of all border types in image.  Gets
%%weighted too heavily.
% image_level_cluster_count(:,numBorders+2) = sum(image_level_cluster_count(:,1:numBorders)>0,2)./numBorders;

% A = image_level_cluster_count;
% Boundary type counts gives better performance than boundary type
% frequency
% image_level_cluster_count = diag(1./sum(A,2))*A;
% close all;
save step_03_clustering_results

