load step_03_clustering_results.mat
NORMFLAG = false;
NORMSCALAR = 1.0;
INCLUDE_BORDER_COUNT = false;
figure(100); subplot(2,2,1); scatter(tSNE_map(:,1), tSNE_map(:,2), 20, idx, 'fill')
if(INCLUDE_BORDER_COUNT)
    image_level_cluster_count(:,numBorders+1) = (sum(image_level_cluster_count(:,1:numBorders),2));
end
if(NORMFLAG)
    A = image_level_cluster_count(:,1:numBorders);
    image_level_cluster_count(:,1:numBorders) = diag(1./sum(A,2)).^(NORMSCALAR)*A;
    
    % for i=1:size(filteredData,2)
    %%Normalize so range is the same as other metrics
    if(INCLUDE_BORDER_COUNT)
        data_tmp = image_level_cluster_count(:,numBorders+1);
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
        image_level_cluster_count(:,numBorders+1) = data_tmp;
    end
end
% A = image_level_cluster_count;
% image_level_cluster_count = diag(1./sum(A,2))*A;
%
XPCA = 1;
YPCA = 2;
ZPCA = 3;

vec1t100 = 1:100;
filter = true(1,100);
% filtLow5 = mod(vec1t100-1,10)  < 5;
% filt50bot = floor(vec1t100)/10 < 5;
% filter = ~filt50bot & filtLow5;
imagesInSet = vec1t100(filter);
[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count(filter,:));
node_positions2 = score(:,[XPCA,YPCA,ZPCA])';
node_positions2 = node_positions2 - repmat((max(node_positions2,[],2)+min(node_positions2,[],2))/2,1,size(node_positions2,2));
node_positions2 = node_positions2/max(abs(node_positions2(:)))*50;
node_data = all_para(:,2);
figure(100); subplot(2,2,3); scatter(node_positions2(1,:), node_positions2(2,:), 200, node_data(filter), 'fill'); colormap('jet');
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(2,k), num2str(imagesInSet(k)), 'FontSize', 7); end
title('color by gx'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)])
node_data = all_para(:,3);
figure(100); subplot(2,2,4); scatter(node_positions2(1,:), node_positions2(2,:), 200, node_data(filter), 'fill'); colormap('jet')
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(2,k), num2str(imagesInSet(k)), 'FontSize', 7); end
title('color by kb'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)])

node_data = all_para(:,2);
figure(400)
subplot(2,2,1);
scatter3(node_positions2(1,:), node_positions2(2,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by gx'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]); zlabel(['PC' num2str(ZPCA)]);

subplot(2,2,2);
scatter(node_positions2(1,:), node_positions2(2,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by gx'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(2,k), num2str(imagesInSet(k)), 'FontSize', 7); end

subplot(2,2,3);
scatter(node_positions2(1,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by gx'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(ZPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(3,k), num2str(imagesInSet(k)), 'FontSize', 7); end

subplot(2,2,4);
scatter(node_positions2(2,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by gx'); xlabel(['PC' num2str(YPCA)]); ylabel(['PC' num2str(ZPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(2,k)+2, node_positions2(3,k), num2str(imagesInSet(k)), 'FontSize', 7); end

node_data = all_para(:,3);
figure(401);
subplot(2,2,1);
scatter3(node_positions2(1,:), node_positions2(2,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by kb'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]); zlabel(['PC' num2str(ZPCA)]);

subplot(2,2,2);
scatter(node_positions2(1,:), node_positions2(2,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by kb'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(2,k), num2str(imagesInSet(k)), 'FontSize', 7); end

subplot(2,2,3);
scatter(node_positions2(1,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by kb'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(ZPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(3,k), num2str(imagesInSet(k)), 'FontSize', 7); end

subplot(2,2,4);
scatter(node_positions2(2,:), node_positions2(3,:), 200, node_data(filter), 'fill'); colormap('jet');
title('color by kb'); xlabel(['PC' num2str(YPCA)]); ylabel(['PC' num2str(ZPCA)]);
for k=1:size(node_positions2,2), text(node_positions2(2,k)+2, node_positions2(3,k), num2str(imagesInSet(k)), 'FontSize', 7); end

figure(200); subplot(2,2,1);
scatter(all_para(:,3),node_positions2(1,:),200, all_para(:,2),'fill'); colormap('jet');
xlabel('kb'); ylabel(['PC' num2str(XPCA)]); title('color by gx');
figure(200); subplot(2,2,2);
scatter(all_para(:,2),node_positions2(1,:),200, all_para(:,3),'fill'); colormap('jet');
xlabel('gx'); ylabel(['PC' num2str(XPCA)]); title('color by kb');
figure(200); subplot(2,2,3);
scatter(all_para(:,3),node_positions2(2,:),200, all_para(:,2),'fill'); colormap('jet');
xlabel('kb'); ylabel(['PC' num2str(YPCA)]); title('color by gx');
figure(200); subplot(2,2,4);
scatter(all_para(:,2),node_positions2(2,:),200, all_para(:,3),'fill'); colormap('jet');
xlabel('gx'); ylabel(['PC' num2str(YPCA)]); title('color by kb');
%%
ss = squareform(pdist(image_level_cluster_count));
figure(100); subplot(2,2,2); imagesc(ss,prctile(ss(:),[5,90]))


% save as figure_previous_visualizations