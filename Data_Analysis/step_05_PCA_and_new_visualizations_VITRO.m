load step_03_clustering_results.mat
borders = 1:12;
USENORM = 0;
% borders = [3,8,10,11,12]; %ONLY DISPLAY CERTAIN BORDER TYPE METRICS
selClass = [1,2,3,4,5,6,7];
CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3','CCM3-H1152'};

imageList = [];
for i = 1:length(selClass)
    imageList = [imageList,(selClass(i)-1)*5 + 1 : selClass(i)*5];
end
borderNames = {};
for i = 1:length(borders)
   borderNames{i} = num2str(borders(i));
end
% borders = 1:size(image_level_cluster_count,2); %DISPLAY ALL BORDERS
%% visualize all the original images
image_folder_name = 'Images_NoFilt';
image_filenames = getfilenames(image_folder_name);
image_filenames = image_filenames(isInListEnd(image_filenames,'.tif'));
image_all_para = [];
for i=1:length(image_filenames)
    image_filenames{i} = fullfile(image_folder_name,image_filenames{i});
    tmp = image_filenames{i}(strfind(image_filenames{i},'CCM=')+4:strfind(image_filenames{i},'CCM=')+4);
    CCM = str2num(tmp);
    tmp = image_filenames{i}(strfind(image_filenames{i},'H1152=')+6:strfind(image_filenames{i},'H1152=')+6);
    TREATED = str2num(tmp);
    image_all_para = [image_all_para; [CCM, TREATED]];
end



stat_folder_name = [folder_name filesep 'statFile'];
stat_filenames = getfilenames(stat_folder_name);
stat_filenames = stat_filenames(isInListEnd(stat_filenames,'.mat'));
stat_all_para = [];
for i=1:length(stat_filenames)
    stat_filenames{i} = fullfile(stat_folder_name,stat_filenames{i});
    tmp = stat_filenames{i}(strfind(stat_filenames{i},'CCM=')+4:strfind(stat_filenames{i},'CCM=')+4);
    CCM = str2num(tmp);
    tmp = stat_filenames{i}(strfind(stat_filenames{i},'H1152=')+6:strfind(stat_filenames{i},'H1152=')+6);
    TREATED = str2num(tmp);
    stat_all_para = [stat_all_para; [CCM, TREATED]];
end


[C,IA,IB] = intersect(all_para, stat_all_para, 'rows');
stat_filenames(IA) = stat_filenames(IB);           


for i = 1:8
%     figure;
    ind = (i-1)*5+1;
    tmpLoad = load(stat_filenames{ind});
    imwrite(tmpLoad.records.imageMask,['im' num2str(ind) '.png']);
end

% [C,IA,IB] = intersect(all_para, image_all_para, 'rows');
% image_filenames(IA) = image_filenames(IB);                                  % reorder the image_filenames, such that the order is consistent with the order in filenames and all_para
% CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152','CCM1-H1152 Alt'};
labelType = 1;
numRows = ceil(size(all_para,1)/5);
numCol = 5;
sidePad = 0.1;
rowWidth = 1 - 2*sidePad;
    height = 1/numRows;
    width = rowWidth/numCol;
textSize = 15;
for i=1:size(stat_filenames,1)
    left = 0.1 + mod(i - 1,5)*width;
    bot = 1 - ceil((i)/5)*height;
    pos = [left,bot,width,height];
    
    figure(1); subplot('Position',pos,'Units','normalized');
    tmpLoad = load(stat_filenames{i});
    imshow(tmpLoad.records.imageMask);
    imHeight = size(tmpLoad.records.imageMask,2);
%     imWidth = size(tmpLoad.records.imageMask,1);
    
        if mod(i,5)==1
       ylabel(CCMLabels{ceil(i/5)},'fontsize',9);
        end
    text(textSize + 5, 5 + textSize, num2str(i),'FontSize',textSize,'FontWeight','bold','Color',[0,180/255,0]);
%         xlabel(['Image ' num2str(i)]);
    drawnow;
end
% image1 = 6;
% image2 = 26;
% figure
%     tmpLoad = load(stat_filenames{image1});
%     imshow(tmpLoad.records.imageMask);
% %     imHeight = size(tmpLoad.records.imageMask,2);
%     figure
%         tmpLoad = load(stat_filenames{image2});
%     imshow(tmpLoad.records.imageMask);
% %     imHeight = size(tmpLoad.records.imageMask,2);
%     
%         figure;
%     bar(image_level_cluster_count(image1,borders))
%     xlim([0.5,length(borders)+0.5])
%     ylim([0,18])
%     
%             figure;
%     bar(image_level_cluster_count(image2,borders))
%     xlim([0.5,length(borders)+0.5])
%     ylim([0,18])
%     imshow(A);
%     if i<=10
%         title(['kb=',num2str(all_para(i,3))],'fontsize',9,'FontWeight','Normal');
%     end
%     if mod(i,10)==1
%        ylabel(['gx=',num2str(all_para(i,2))],'fontsize',9);
%     end
%     drawnow
% end


% large_tmp = [];
% for i=1:size(all_para,1)
%     A = imread(image_filenames{i});
%     if mod(i,10)==1
%         small_tmp=[];
%     end
%     small_tmp = cat(2, small_tmp, A);
%     if mod(i,10)==0
%         large_tmp = cat(1,large_tmp, small_tmp);
%     end
% end



%% histogram of the x boundary-types in each imag

% borders = [1,3,10,11];
% borders = 1:size(image_level_cluster_count,2);
for i=1:size(all_para,1)
    figure(2); subplot(8,5,i);
    bar(image_level_cluster_count(i,:))
    xlim([0.5,size(image_level_cluster_count,2)+0.5])
    ylim([0,size(all_para,1)])
%     if i<=5
%         title(['CCM=',num2str(all_para(i,1))],'fontsize',9,'FontWeight','Normal');
%     end
    if mod(i,5)==1
       ylabel(CCMLabels{ceil(i/5)},'fontsize',9);
    end
    drawnow
end

%% histogram of the x boundary-types in each imag
% A = image_level_cluster_count;
% image_level_cluster_count_norm = diag(1./sum(A,2))*A;
CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3','CCM3-H1152'};
% labelType = 1;
firstSet = 4;
secondSet = 2;
figure(23)
% subplot(1,2,1);
bar(mean(image_level_cluster_count((firstSet-1)*5+1:firstSet*5,borders))-mean(image_level_cluster_count((secondSet-1)*5+1:secondSet*5,borders)));
set(gca,'xticklabel',borderNames);
title(['Difference in Border Type Count Between ' CCMLabels{firstSet} ' and ' CCMLabels{secondSet}]);
% subplot(1,2,2);;
% bar(mean(image_level_cluster_count((firstSet-1)*5+1:firstSet*5,borders))-mean(image_level_cluster_count_norm((secondSet-1)*5:secondSet*5,borders)));
% set(gca,'xticklabel',borderNames);
% title(['Difference in Border Frequency Between ' CCMLabels{firstSet} ' and ' CCMLabels{secondSet}])
% figure(25)
% subplot(1,2,1)
% bar(mean(image_level_cluster_count((firstSet-1)*5+1:firstSet*5,:))-mean(image_level_cluster_count((secondSet-1)*5:secondSet*5,:)));
% title(['Difference in Border Count Between ' CCMLabels{firstSet} ' and ' CCMLabels{secondSet}]);
% subplot(1,2,2);
% bar(mean(image_level_cluster_count_norm((firstSet-1)*5+1:firstSet*5,:))-mean(image_level_cluster_count_norm((secondSet-1)*5:secondSet*5,:)));
% title(['Difference in Border Frequency Between ' CCMLabels{firstSet} ' and ' CCMLabels{secondSet}]);
% for i=1:size(all_para,1)
%     figure(22); subplot(8,5,i);
%     bar(image_level_cluster_count_norm(i,borders))
%     xlim([0.5,size(image_level_cluster_count_norm,2)+0.5])
%     ylim([0,1])
%     if i<=5
%         title(['CCM=',num2str(all_para(i,1))],'fontsize',9,'FontWeight','Normal');
%     end
%     if mod(i,5)==1
%        ylabel(CCMLabels{ceil(i/5)},'fontsize',9);
%     end
%     drawnow
% end
%% histogram of the x boundary-types in each imag NORMALIZED
A = image_level_cluster_count;
image_level_cluster_count_norm = diag(1./sum(A,2))*A;
CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152','CCM1-H1152 Alt'};
labelType = 1;
for i=1:size(all_para,1)
    figure(22); subplot(8,5,i);
    bar(image_level_cluster_count_norm(i,borders))
    xlim([0.5,length(borders)+0.5])
    ylim([0,1])
%     if i<=5
%         title(['CCM=',num2str(all_para(i,1))],'fontsize',9,'FontWeight','Normal');
%     end
    if mod(i,5)==1
       ylabel(CCMLabels{ceil(i/5)},'fontsize',9);
    end
    drawnow
        set(gca,'xticklabel',borderNames)

end


%%
if(USENORM)
A = image_level_cluster_count;
image_level_cluster_count_norm = diag(1./sum(A,2))*A;
end
[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count_norm(imageList,:));
% [coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count(imageList,:));

% score_full = zeros(40,size(score,2));
% score_full(imageList,:) = score;

for i=1:size(image_level_cluster_count_norm,2);
    h = figure(3);
    x = mod(1:35,5); x(x==0)=5;
    y = ceil((1:35)/5);
    scatter(x,y,500,score(:,i),'fill'); colormap('jet');
    axis([0,6,0,8]);
%     subplot(3,4,i);
    set(gca,'Ydir','reverse')
    title(['PC-',num2str(i)])
    drawnow
    
    tmp = getframe(h);
    tmp = tmp.cdata;
    
%     if ir==1
        imwrite(tmp, ['PCA' num2str(i) '.tif']);
%     else
%         imwrite(tmp, 'figure_03_PCA_scores.tif', 'writemode', 'append');
%     end
end

%% 
figure(4)
[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count(imageList,:));

for i=1:size(coeff,2)
    h_subplot = subplot(5,4,i);
    bar(coeff(:,i))
    title(['eigenvector - ', num2str(i)])
    xlim([0,size(coeff,2) + 1])
end


%%
all_data = [normalized_data;normalized_data];
group_id = [idx; max(idx)+ones(size(idx))];
groupLabelCell = {num2str(max(idx) + 1)};
for i = length(borders):-1:1
   groupLabelCell{length(borders) - i + 2} = num2str(borders(i));
end
group_id_filt = group_id(any(group_id==borders,2) | group_id == max(idx) +1);
% group_id_filt(~any(group_id==borders | group_id == max(idx) + 1,2)) = [];
figure(55)
for i=1:size(all_data,2)
    h_subplot = subplot(8,5,i);
    h_boxplot = boxplot(all_data(any(group_id==borders,2) | group_id == max(idx) + 1,i), group_id_filt,'orientation','horizontal','grouporder',groupLabelCell);%[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([0,length(borders)+2]);
    title(marker_names{i},'interpret','none')
    xlim([-0.1,1.1])
end



