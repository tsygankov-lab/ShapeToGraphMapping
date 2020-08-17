load step_03_clustering_results.mat

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
% [C,IA,IB] = intersect(all_para, image_all_para, 'rows');
% image_filenames(IA) = image_filenames(IB);                                  % reorder the image_filenames, such that the order is consistent with the order in filenames and all_para
% 
% for i=1:size(all_para,1)
%     figure(1); subplot(10,10,i);
%     A = imread(image_filenames{i});
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
CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152','CCM1-H1152 Alt'};
labelType = 1;
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
CCMLabels = {'WT','WT-H1152','CCM1','CCM1-H1152','CCM2','CCM2-H1152','CCM3-H1152','CCM1-H1152 Alt'};
labelType = 1;
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



%%
[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count);
for i=1:size(image_level_cluster_count,2)
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
for i=1:size(coeff,2)
    h_subplot = subplot(5,4,i);
    bar(coeff(:,i))
    title(['eigenvector - ', num2str(i)])
    xlim([0,11])
end


%%
all_data = [normalized_data;normalized_data];
group_id = [idx; max(idx)+ones(size(idx))];
figure(5)
for i=1:size(all_data,2)
    h_subplot = subplot(8,5,i);
    h_boxplot = boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([0,max(group_id)+1]);
    title(marker_names{i},'interpret','none')
    xlim([-0.1,1.1])
end



