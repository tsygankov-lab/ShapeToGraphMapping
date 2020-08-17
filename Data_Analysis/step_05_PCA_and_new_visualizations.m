load step_03_clustering_results.mat

%% visualize all the original images
image_folder_name = 'Images_NoFilt';
image_filenames = getfilenames(image_folder_name);
image_filenames = image_filenames(isInListEnd(image_filenames,'.tif'));
image_all_para = [];
for i=1:length(image_filenames)
    image_filenames{i} = fullfile(image_folder_name,image_filenames{i});
    tmp = image_filenames{i}(strfind(image_filenames{i},'R='):strfind(image_filenames{i},'_gx')-1);
    R = str2num(tmp(3:end));
    tmp = image_filenames{i}(strfind(image_filenames{i},'gx='):strfind(image_filenames{i},'_kb')-1);
    gx = str2num(tmp(4:end));
    tmp = image_filenames{i}(strfind(image_filenames{i},'kb='):strfind(image_filenames{i},'Simulation')-1);
    kb = str2num(tmp(4:end));
    image_all_para = [image_all_para; [R, gx, kb]];
end
[C,IA,IB] = intersect(all_para, image_all_para, 'rows');
image_filenames(IA) = image_filenames(IB);                                  % reorder the image_filenames, such that the order is consistent with the order in filenames and all_para


IM_List = [1,5,10,51,55,60,91,95,100];

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





for i=1:size(all_para,1)
    figure(1); subplot(10,10,i);
    A = imread(image_filenames{i});
    imshow(A);
    if i<=10
        title(['kb=',num2str(all_para(i,3))],'fontsize',9,'FontWeight','Normal');
    end
    if mod(i,10)==1
       ylabel(['gx=',num2str(all_para(i,2))],'fontsize',9);
    end
    drawnow
end


large_tmp = [];
for i=1:size(all_para,1)
    A = imread(image_filenames{i});
    if mod(i,10)==1
        small_tmp=[];
    end
    small_tmp = cat(2, small_tmp, A);
    if mod(i,10)==0
        large_tmp = cat(1,large_tmp, small_tmp);
    end
end

IM_List = [1,5,10,51,55,60,91,95,100];
for j=1:length(IM_List)
    i = IM_List(j);
%     figure(2); subplot(10,10,i);
figure;
    bar(image_level_cluster_count(i,:))
    xlim([0.5,12.5])
    ylim([0,40])
%     if i<=10
%         title(['kb=',num2str(all_para(i,3))],'fontsize',9,'FontWeight','Normal');
%     end
%     if mod(i,10)==1
%        ylabel(['gx=',num2str(all_para(i,2))],'fontsize',9);
%     end
    drawnow
end

%% histogram of the 10 boundary-types in each image
for i=1:size(all_para,1)
    figure(2); subplot(10,10,i);
    bar(image_level_cluster_count(i,:))
    xlim([0.5,10.5])
    ylim([0,40])
    if i<=10
        title(['kb=',num2str(all_para(i,3))],'fontsize',9,'FontWeight','Normal');
    end
    if mod(i,10)==1
       ylabel(['gx=',num2str(all_para(i,2))],'fontsize',9);
    end
    drawnow
end



%%
[coeff, score, latent, tsquared, explained, mu] = pca(image_level_cluster_count);
for i=1:size(image_level_cluster_count,2)
    h = figure(3);
    x = mod(1:100,10); x(x==0)=10;
    y = ceil((1:100)/10);
    scatter(x,y,500,score(:,i),'fill'); colormap('jet');
    axis([0,11,0,11]);
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
    subplot(ceil(size(coeff,2)/4),4,i);
    bar(coeff(:,i))
    title(['eigenvector - ', num2str(i)])
    xlim([0,11])
end


%%
all_data = [normalized_data;normalized_data];
% all_data = normalized_data;
group_id = [idx; max(idx)+ones(size(idx))]; %Gets the average boundary descriptor
if(max(group_id) > 9)
    groupCharOrder = [regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(min([9,max(group_id)]):-1:1),'  ','split')];
else
    groupCharOrder = regexp(num2str(min([9,max(group_id)]):-1:1),'  ','split');
end
figure(5)
for i=1:size(all_data,2)
    subplot(4,10,i);
    h_boxplot = boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',groupCharOrder);
    delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([0,max(group_id)+1]);
    title(marker_names{i},'interpret','none')
    xlim([-0.1,1.1])
end
medFeat = zeros(max(idx),size(normalized_data,2));
rangeFeat = zeros(max(idx),size(normalized_data,2));
Quart25 = zeros(max(idx),size(normalized_data,2));
Quart75 = zeros(max(idx),size(normalized_data,2));

for i=1:max(idx)
    medFeat(i,:) = median(normalized_data(idx==i,:));
    Quart25(i,:) = quantile(normalized_data(idx==i,:),0.25);
    Quart75(i,:) = quantile(normalized_data(idx==i,:),0.75);

    rangeFeat(i,:) = 1.0-(Quart75(i,:) -Quart25(i,:));
end
figure(6);
for i=1:max(idx)
%     subplot(4,ceil(max(idx)/4),i);
figure
    bar(medFeat(i,:));%boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    %delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([-0.1,1.1]);
    title(['Boundary' num2str(i) ' Measures'],'interpret','none')
    xlim([-0.5,size(normalized_data,2)]);
end
figure(7);
for i=1:size(normalized_data,2)
    subplot(4,ceil(size(normalized_data,2)/4),i);
    bar(medFeat(:,i));%boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    %delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([-0.1,1.1]);
    title(['median ' marker_names{i}],'interpret','none')
    xlim([-0.5,max(idx)]);
end
figure(8);
for i=1:max(idx)
    subplot(4,ceil(max(idx)/4),i);
    bar(rangeFeat(i,:));%boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    %delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([-0.1,1.1]);
    title(['Boundary ' num2str(i) '1.0 - feat range'],'interpret','none')
    xlim([-0.5,size(normalized_data,2)]);
end
figure(9);
for i=1:size(normalized_data,2)
    subplot(4,ceil(size(normalized_data,2)/4),i);
    bar(rangeFeat(:,i));%boxplot(all_data(:,i), group_id,'orientation','horizontal','grouporder',[regexp(num2str(max(group_id):-1:10),'  ','split'),regexp(num2str(9:-1:1),'  ','split')]);
    %delete(h_boxplot([1:4],2:end)); delete(h_boxplot(7,:));
    axis tight; ylim([-0.1,1.1]);
    title(['1.0-range ' marker_names{i}],'interpret','none')
    xlim([-0.5,max(idx)]);
end

