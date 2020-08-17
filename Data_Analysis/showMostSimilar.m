load step_03_clustering_results;
VITRO = true;
    NORMFLAG = false;
    NORMSCALAR = 1;
INCLUDE_BORDER_COUNT = false;
showAssociationGraphs = false;

% A = image_level_cluster_count;
%  image_level_cluster_count = diag(1./sum(A,2))*A;
 
 image_level_cluster_count = [image_level_cluster_count, imageMeasures];

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
image_level_cluster_count = filteredData;
if(VITRO)
    featA = 1;
    featB = 2;
    treatmentFlag = {'','-H1152'};
    CCMFlag = {'WT','CCM1','CCM2','CCM3'};
    labelList = {};
    
    for i = 1:size(all_para,1)
        labelList{i} = [CCMFlag{all_para(i,1)+1}, treatmentFlag{all_para(i,2)+1}];
    end
    % for i = 31:35
    %     labelList{i} = [CCMFlag{4}, treatmentFlag{2}];
    % end
    
    if(~exist('loadedDataStructs') || isempty(loadedDataStructs))
        loadedDataStructs = loadAllIMAGEFiles(folder_name,all_para,VITRO);
    end
else
    featA = 2;
    featB = 3;
    labelList = {};
%     NORMFLAG = 1;
    
    for i = 1:100
        labelList{i} = ['gx=', num2str(all_para(i,featA)), ', kb=' num2str(all_para(i,featB))];
    end
    if(~exist('loadedDataStructs') || isempty(loadedDataStructs))
        loadedDataStructs = loadAllIMAGEFiles(folder_name,all_para,VITRO);
    end
end
if(INCLUDE_BORDER_COUNT)
   image_level_cluster_count(:,numBorders+1) = sqrt(sum(image_level_cluster_count(:,1:numBorders),2)); 
end
if(NORMFLAG)
 A = image_level_cluster_count(:,1:numBorders);
% image_level_cluster_count(:,1:numBorders) = diag(1./sum(A,2))*A;
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
% filteredData = image_level_cluster_count;
% for i=1:size(filteredData,2)
%     data_tmp = filteredData(:,i);
%     prc_5 = prctile(data_tmp,5);
%     prc_95 = prctile(data_tmp,95);
%     data_tmp(data_tmp<prc_5) = prc_5;
%     data_tmp(data_tmp>prc_95) = prc_95;
%     if prc_95==prc_5
%         prc_95 = max(data_tmp);
%         prc_5 = min(data_tmp);
%     end
%     if prc_95~=prc_5
%         data_tmp = (data_tmp - prc_5)/(prc_95 - prc_5);
%     else
%         data_tmp = data_tmp*0;
%     end
%     filteredData(:,i) = data_tmp;
% end
% image_level_cluster_count = filteredData;
%Add sum(border counts) as a feature which is the percentile border count
%for each image relative to others
distMat = squareform(pdist(image_level_cluster_count));

theFig = figure('units','normalized','position',[.1,.1,0.8,0.8]);
scatterFig = figure;
clf(scatterFig);
scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo'); hold on;
if(showAssociationGraphs)
newFig = figure;
clf(newFig);
scatterFigLU = subplot(2,2,1);
cla
scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo'); hold on;
title('Left-Up Connections')
xlabel('gx');
ylabel('kb');

scatterFigRU = subplot(2,2,2);
scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo'); hold on;
title('Right-Up Connections')
xlabel('gx');
ylabel('kb');

scatterFigRD = subplot(2,2,3);
scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo'); hold on;
title('Right-Down Connections')
xlabel('gx');
ylabel('kb');

scatterFigLD = subplot(2,2,4);
scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo'); hold on;
title('Left-Down Connections')
xlabel('gx');
ylabel('kb');

lineColorMap100 = jet(100);
end
indRange = 2:6;
linewidth = 4;
for imNum = 1:size(distMat,1)

    imCompare = imNum;
        [sortedDistMat,ind] = sort(distMat(imCompare,:),'ascend');
    
    clf(theFig);
    figure(theFig);
    subplot('Position',[0.06,0,0.4,1]);
    %     tmpLoad = load(stat_filenames{imCompare});
    imshow(loadedDataStructs{imCompare});
    ylabel(labelList{imCompare});
    text(40,40,num2str(imCompare),'Color','r','FontWeight','bold','FontSize',36);
    title('Top 5 Most Similar Structures');
    indFilt = ind(sortedDistMat < 10);
    subplot('Position',[0.06+0.42,0.53,0.17,0.17]);
    bar(image_level_cluster_count(imCompare,:))
    if(NORMFLAG)
        ylim([0,max(1,max(max(image_level_cluster_count)))]);
    else
        ylim([0,max(1,max(max(image_level_cluster_count)))]);
    end
    subplot('Position',[0.06+0.42,0.3,0.17,0.17]);
    hold on;
    scatter(log(all_para(:,featA)),log(all_para(:,featB)),'bo');
    scatter(log(all_para(imCompare,featA)),log(all_para(imCompare,featB)),150,'kp','filled');
    colorMatTmp = jet(10);
    for i = 1:10
        scatter(log(all_para(ind(i+1),featA)),log(all_para(ind(i+1),featB)),'o','filled','MarkerFaceColor',colorMatTmp(i,:));
    end
    xlim([min(log(all_para(:,featA)))-0.5,max(log(all_para(:,featA)))+0.5]);
    xlabel('log10(gx)');
    ylim([min(log(all_para(:,featB)))-0.5,max(log(all_para(:,featB)))+0.5]);
    ylabel('log10(kb)');
    title('Star = Cur Image, Blue -> Red: Nearest 1->10');
    
    for i=1:5
        bot = 1 - i*0.2;
        subplot('Position',[0.66, bot, 0.17,0.17]);
        %     tmpLoad = load(stat_filenames{ind(i+1)});
        imshow(loadedDataStructs{ind(i+1)});
        imSize = size(loadedDataStructs{ind(i+1)});
        ylabel(labelList{ind(i+1)});
        text(20,30,num2str(ind(i+1)),'Color','r','FontWeight','bold','FontSize',16);
        text(0.25, -.1, ['Dist:' num2str(distMat(imCompare,ind(i+1)))],'Units','Normalized','Color','b','FontWeight','Bold','FontSize',16);
        subplot('Position',[0.66+0.17,bot,0.17,0.17]);
        bar(image_level_cluster_count(ind(i+1),:))
        
        if(NORMFLAG)
            ylim([0,max(1,max(max(image_level_cluster_count)))]);
        else
            ylim([0,max(1,max(max(image_level_cluster_count)))]);
        end
    end
    data = getframe(theFig);
    imwrite(data.cdata,['showSim - ' num2str(imNum) '.png']);
    if(showAssociationGraphs)
    figure(scatterFig);
    indRange = 2:6;
    for i = indRange
        line([log(all_para(imCompare,featA)),log(all_para(ind(i),featA))],[log(all_para(imCompare,featB)),log(all_para(ind(i),featB))],'Color',lineColorMap100(imNum,:));
    end
    paraDiffX = log(all_para(ind(indRange),featA)) - log(all_para(imCompare,featA));
    paraDiffY = log(all_para(ind(indRange),featB)) - log(all_para(imCompare,featB));
    axes(scatterFigLU)
    for i = indRange
        if(paraDiffX(i-1) <= 0 && paraDiffY(i-1) >= 0)
            line([log(all_para(imCompare,featA)),log(all_para(ind(i),featA))],[log(all_para(imCompare,featB)),log(all_para(ind(i),featB))],'Color',lineColorMap100(imNum,:),'LineWidth',linewidth);
        end
    end
    axes(scatterFigRU)
    for i = indRange
        if(paraDiffX(i-1) >= 0 && paraDiffY(i-1) >= 0)
            line([log(all_para(imCompare,featA)),log(all_para(ind(i),featA))],[log(all_para(imCompare,featB)),log(all_para(ind(i),featB))],'Color',lineColorMap100(imNum,:),'LineWidth',linewidth);
        end
    end
    axes(scatterFigRD)
    for i = indRange
        if(paraDiffX(i-1) >= 0 && paraDiffY(i-1) <= 0)
            line([log(all_para(imCompare,featA)),log(all_para(ind(i),featA))],[log(all_para(imCompare,featB)),log(all_para(ind(i),featB))],'Color',lineColorMap100(imNum,:),'LineWidth',linewidth);
        end
    end
    axes(scatterFigLD)
    for i = indRange
        if(paraDiffX(i-1) <= 0 && paraDiffY(i-1) <= 0)
            line([log(all_para(imCompare,featA)),log(all_para(ind(i),featA))],[log(all_para(imCompare,featB)),log(all_para(ind(i),featB))],'Color',lineColorMap100(imNum,:),'LineWidth',linewidth);
        end
    end
    end
end