load step_03_clustering_results.mat
close all
NORMFLAG = false;
NORMSCALAR = 1;
INCLUDE_BORDER_COUNT = false;
INCLUDE_BORDER_DIVERSITY = false;
figure(100); subplot(2,2,1); scatter(tSNE_map(:,1), tSNE_map(:,2), 20, idx, 'fill')

if(INCLUDE_BORDER_COUNT)
    image_level_cluster_count(:,numBorders+1) = sqrt(sum(image_level_cluster_count(:,1:numBorders),2));
end
if(INCLUDE_BORDER_DIVERSITY)
    image_level_cluster_count(:,end+1) = log(sum(image_level_cluster_count(:,1:numBorders)>0,2)./numBorders);
end

% fullLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3','CCM3-H1152'};
%%CCM3 is just completely isolated circular islands.  These images contain
%%an unusually large amount of borders compared to other images, so it is
%%removed from the analysis stages so the border types can be derived from
%%images with more similar patterns
fullLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152'};

%
selClass = [1,2,3,4,5,6,7];
legendLabels = fullLabels(selClass);
imageList = [];
for i = 1:length(selClass)
    imageList = [imageList,(selClass(i)-1)*5 + 1 : selClass(i)*5];
end
XPCA = 1;
YPCA = 2;
ZPCA = 3;
% image_level_cluster_count = fuzzy_image_level_cluster_count;

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

[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count(imageList,:));
figure(104)
for i=1:size(coeff,2)
    h_subplot = subplot(5,4,i);
    bar(coeff(:,i))
    title(['eigenvector - ', num2str(i)])
    xlim([0,size(coeff,2) + 1])
end
node_positions2 = score(:,[XPCA,YPCA,ZPCA])';
% rangeX = max(node_positions2(1,:)) - min(node_positions2(1,:));
% offsetTextX = 2/100*rangeX;
% rangeY = max(node_positions2(2,:)) - min(node_positions2(2,:));
% offsetTextY = 2/100*rangeY;

% node_positions2 = node_positions2 - repmat((max(node_positions2,[],2)+min(node_positions2,[],2))/2,1,size(node_positions2,2));
% node_positions2 = node_positions2/max(abs(node_positions2(:)))*50;
% node_data = all_para(:,1);
[classList,~,node_data] = unique(all_para(imageList,:),'rows');
figure(100);
subplot(2,2,3);
cla;
hold on;
cmap= jet(length(classList));
% node_data_tmp = node_data;
% node_data_tmp(~any(node_data == selClass,2)) = [];
figure; hold on;

for i = 1:length(selClass)
    toPlot = node_data == i;
    scatter(node_positions2(1,toPlot), node_positions2(2,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end

rangeX = xlim(gca);
rangeY = ylim(gca);

offsetTextX = 1/100*(rangeX(2) - rangeX(1));
offsetTextY = 1/100*(rangeY(2) - rangeY(1));

% for k=1:size(node_positions2,2), text(node_positions2(1,k)+offsetTextX, node_positions2(2,k)+offsetTextY, num2str(imageList(k)), 'FontSize', 7); end
% legend(legendLabels{:});

title('In-Vitro Images Colored by Phenotype'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)])
figure(1111);
subplot(2,2,1);
figure
hold on;
for i = 1:length(selClass)
    toPlot = node_data == i;
    scatter3(node_positions2(1,toPlot), node_positions2(2,toPlot), node_positions2(3,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
title('color by CLASS'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]); zlabel(['PC' num2str(ZPCA)]);

subplot(2,2,2);
hold on;
for i = 1:length(selClass)
    toPlot = node_data == i;
    scatter(node_positions2(1,toPlot), node_positions2(2,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
rangeX = xlim(gca);
rangeY = ylim(gca);

offsetTextX = 1/100*(rangeX(2) - rangeX(1));
offsetTextY = 1/100*(rangeY(2) - rangeY(1));

for k=1:size(node_positions2,2), text(node_positions2(1,k)+offsetTextX, node_positions2(2,k)+offsetTextY, num2str(imageList(k)), 'FontSize', 7); end
legend(legendLabels{:});

title('color by CLASS'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)]);
subplot(2,2,3);
hold on;
for i = 1:length(selClass)
    toPlot = node_data == i;
    scatter(node_positions2(1,toPlot), node_positions2(3,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
rangeX = xlim(gca);
rangeY = ylim(gca);

offsetTextX = 1/100*(rangeX(2) - rangeX(1));
offsetTextY = 1/100*(rangeY(2) - rangeY(1));

for k=1:size(node_positions2,2), text(node_positions2(1,k)+offsetTextX, node_positions2(3,k)+offsetTextY, num2str(imageList(k)), 'FontSize', 7); end
legend(legendLabels{:});
title('color by CLASS'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(ZPCA)]);

subplot(2,2,4);
hold on;
for i = 1:length(selClass)
    toPlot = node_data == i;
    scatter(node_positions2(2,toPlot), node_positions2(3,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
rangeX = xlim(gca);
rangeY = ylim(gca);

offsetTextX = 1/100*(rangeX(2) - rangeX(1));
offsetTextY = 1/100*(rangeY(2) - rangeY(1));

for k=1:size(node_positions2,2), text(node_positions2(2,k)+offsetTextX, node_positions2(3,k)+offsetTextY, num2str(imageList(k)), 'FontSize', 7); end
legend(legendLabels{:});
title('color by CLASS'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(ZPCA)]);

% legend('WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152');
% legend('WT','CCM1','CCM2','CCM3');
% node_data = all_para(:,2);
% figure(100); subplot(2,2,4); scatter(node_positions2(1,:), node_positions2(2,:), 200, node_data, 'fill'); colormap('jet')
% for k=1:size(node_positions2,2), text(node_positions2(1,k)+2, node_positions2(2,k), num2str(k), 'FontSize', 7); end
% title('color by TREATMENT'); xlabel(['PC' num2str(XPCA)]); ylabel(['PC' num2str(YPCA)])
% legend('UNTREATED','H1152');
figure(200); subplot(2,2,1); cla; hold on;
for i = 1:length(classList)
    toPlot = node_data == i;
    scatter(all_para(toPlot,1), node_positions2(1,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
legend(legendLabels{:});
title('color by CLASS'); xlabel('CCM Type'); ylabel(['PC' num2str(XPCA)]);xlim([-0.1,3.1]);

figure(200); subplot(2,2,2); cla; hold on;
cla
for i = 1:length(classList)
    toPlot = node_data == i;
    scatter(all_para(toPlot,2), node_positions2(1,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
legend(legendLabels{:});
title('color by CLASS'); xlabel('H1152'); ylabel(['PC' num2str(XPCA)]); xlim([-0.1,1.1]);

figure(200); subplot(2,2,3);cla; hold on;
cla
for i = 1:length(classList)
    toPlot = node_data == i;
    scatter(all_para(toPlot,1), node_positions2(2,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
legend(legendLabels{:});
title('color by CLASS'); xlabel('CCM Type'); ylabel(['PC' num2str(YPCA)]); xlim([-0.1,3.1]);
figure(200); subplot(2,2,4); cla; hold on;
cla
for i = 1:length(classList)
    toPlot = node_data == i;
    scatter(all_para(toPlot,2), node_positions2(2,toPlot), 200, cmap(i,:), 'fill');
    colormap('jet');
end
legend(legendLabels{:});
title('color by CLASS'); xlabel('H1152'); ylabel(['PC' num2str(YPCA)]);
xlim([-0.1,1.1]);
%%
distMat = pdist(image_level_cluster_count);
ss = squareform(pdist(image_level_cluster_count));
figure(100); subplot(2,2,2); imagesc(ss,prctile(ss(:),[5,90]))
classDistList = cell(8,8);

for phenoB = 1:7
    for phenoA = 1:7
        count = 1;
        if(phenoB ~= phenoA)
            classDistList{phenoA,phenoB} = zeros(5*5,1);
            
            for j = 1:5
                for i = 1:5
                    classDistList{phenoA,phenoB}(count) = ss(i+(phenoA-1)*5,j+(phenoB-1)*5);
                    count = count+1;
                end
            end
        else
            
            classDistList{phenoA,phenoB} = zeros(4+3+2+1,1);
            for j = 1:4
                for i = (j+1):5
                    classDistList{phenoA,phenoB}(count) = ss(i+(phenoA-1)*5,j+(phenoB-1)*5);
                    count = count+1;
                end
            end
        end
    end
end

btwClassDist = zeros(7,7);
for i = 1:7
    for j = 1:7
        btwClassDist(i,j) = mean(classDistList{i,j});
    end
end

subplot(2,2,4);
imagesc(btwClassDist,prctile(btwClassDist(:),[5,90]));
set(gca,'xticklabel',fullLabels);
set(gca,'yticklabel',fullLabels);

colormap('jet');
% save as figure_previous_visualizations