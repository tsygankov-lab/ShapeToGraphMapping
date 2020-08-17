function quickPrettyPlot(dirName)
if(dirName(end) ~= filesep)
    dirName = [dirName filesep];
end
matFiles = dir([dirName '*.mat']);
mkdir([dirName 'VorGraphs']);
figDir = [dirName 'VorGraphs' filesep 'fig'];
mkdir(figDir);
for k = length(matFiles):-1:1
    % remove non-folders
    if ~matFiles(k).isdir
        if((isempty(strfind(matFiles(k).name,'LOOP'))) || ~isempty(strfind(matFiles(k).name,'STATS')) || isempty(strfind(matFiles(k).name,'.mat')))
            matFiles(k) = [ ];
            continue
        end
    else
        matFiles(k) = [ ];
        continue
    end
end
%%NOTE- MAKE SURE THE IMAGE IS AN INTEGER MULTIPLE OF THE BINARY MASK
%%RESOLUTION OR IT WILL LOOK HORRENDOUS
%%Print quality significantly worse in parallel.  No idea why.
imageNameList_Label = cell(size(matFiles));
imageNameList_Graph = cell(size(matFiles));
for iter = 1:length(matFiles)
    loadFile = load([dirName matFiles(iter).name]);
    records = loadFile.records;
    % dataStruct = loadFile.dataStruct;
    % cm = jet(records.numNonHoles);
    tmp = figure('Visible','off');
    xDim = size(records.imageMask,2)-2;
    yDim = size(records.imageMask,1)-2; %????
    subplot('Position',[0,0,1,1]);
    imagesc(records.imageMask);
    colormap('bone')
    hold on;
    % plotVoronoiSkeleton(records,0,cm,1,1,{});
    % test = getframe(gca);
    set(tmp,'PaperPositionMode','manual')
    set(tmp,'InvertHardcopy','off')
    set(tmp,'PaperUnits','inches');
    set(tmp,'PaperPosition',[0,0,.02*xDim,.02*yDim]);
    axis([1,xDim+1,1,yDim+1]);

    imageNameList_Label{iter} = [figDir filesep 'LABEL_IMAGE_' matFiles(iter).name(1:end-4),'.fig'];
    imageNameList_Graph{iter} = [figDir filesep 'COLOR_VOR_BRIDGE_' matFiles(iter).name(1:end-4),'.fig'];
%     saveas(tmp,imageNameList_Label{iter},'fig');
    print(tmp,[dirName 'VorGraphs' filesep 'LABEL_IMAGE_' matFiles(iter).name(1:end-4),'.png'],'-dpng','-painters','-r200');

    colors = jet(max(records.edges.color));
    for i = 1:max(records.edges.color)
%         plotOutline_ByColor(records, i, colors(i,:)/1.25, {'LineWidth',2.0});
        plotSubRegion(records,i,'InGraph',1,'Color',colors(i,:));
    end
    % imwrite(test.cdata,[dirName 'VorGraphs' filesep 'COLOR_VOR_NO_BRIDGE_' matFiles(iter).name,'.png']);
    % if(dataStruct.loop.numInObjectNoEnclosure)
    % for i = 1:length(dataStruct.loop.object.acyclic)
    %     plotFromEdgeList(dataStruct.loop.object.acyclic(i).primaryMajAxis.edge, records, [130, 24, 24]./255,{'LineWidth',2});
    % end
    % end
    % if(dataStruct.loop.numInObjectEnclosedByHole)
    % for i = 1:length(dataStruct.loop.object.enclosed)
    %     plotFromEdgeList(dataStruct.loop.object.enclosed(i).EL, records, [130, 24, 24]./255,{'LineWidth',2});
    % end
    % end
    % if(dataStruct.loop.numInObjectEnclosingHole)
    % for i = 1:length(dataStruct.loop.object.enclosing)
    %     plotFromEdgeList(dataStruct.loop.object.enclosing(i).EL, records, [130, 24, 24]./255,{'LineWidth',2});
    % end
    % end
    % axis([1,xDim+1,1,yDim+1]);
    % print(tmp,[dirName 'VorGraphs' filesep 'COLOR_VOR_BRIDGE_' matFiles(iter).name,'.png'],'-dpng','-painters','-r200');
%     saveas(tmp,imageNameList_Graph{iter},'fig'),
    print(tmp,[dirName 'VorGraphs' filesep 'COLOR_VOR_' matFiles(iter).name(1:end-4),'.png'],'-dpng','-painters','-r200');

    % test = getframe(gca);
    % imwrite(test.cdata,[dirName 'VorGraphs' filesep 'COLOR_VOR_BRIDGE' matFiles(iter).name,'.png']);
    close(tmp);
end

% for iter = 1:length(imageNameList_Label)
%     figFile_Label = openfig(imageNameList_Label{iter});
%     print(figFile_Label,[dirName 'VorGraphs' filesep 'LABEL_IMAGE_' matFiles(iter).name(1:end-4),'.png'],'-dpng','-painters','-r200');
%     close(figFile_Label);
%     figFile_Graph = openfig(imageNameList_Graph{iter});
%     print(figFile_Graph,[dirName 'VorGraphs' filesep 'COLOR_VOR_' matFiles(iter).name(1:end-4),'.png'],'-dpng','-painters','-r200');
%     close(figFile_Graph);
% end
end


% for iter = 1:length(matFiles)
%     loadFile = load([dirName matFiles(iter).name]);
%     records = loadFile.records;
%     % dataStruct = loadFile.dataStruct;
%     % cm = jet(records.numNonHoles);
%     tmp = figure('Visible','off');
%     xDim = size(records.imageMask,2)-2;
%     yDim = size(records.imageMask,1)-2; %????
%     subplot('Position',[0,0,1,1]);
%     imagesc(records.imageMask);
%     colormap('bone')
%     hold on;
%     % plotVoronoiSkeleton(records,0,cm,1,1,{});
%     % test = getframe(gca);
%     set(tmp,'PaperPositionMode','manual')
%     set(tmp,'InvertHardcopy','off')
%     set(tmp,'PaperUnits','inches');
%     set(tmp,'PaperPosition',[0,0,.02*xDim,.02*yDim]);
%     axis([1,xDim+1,1,yDim+1]);
%     print(tmp,[dirName 'VorGraphs' filesep 'LABEL_IMAGE_' matFiles(iter).name(1:end-4),'.png'],'-dpng','-painters','-r200');
%     
%     colors = jet(max(records.edges.color));
%     for i = 1:max(records.edges.color)
%         plotOutline_ByColor(records, i, colors(i,:)/1.25, {'LineWidth',2.0});
%         plotSubRegion(records,i,colors(i,:));
%     end
%     % imwrite(test.cdata,[dirName 'VorGraphs' filesep 'COLOR_VOR_NO_BRIDGE_' matFiles(iter).name,'.png']);
%     % if(dataStruct.loop.numInObjectNoEnclosure)
%     % for i = 1:length(dataStruct.loop.object.acyclic)
%     %     plotFromEdgeList(dataStruct.loop.object.acyclic(i).primaryMajAxis.edge, records, [130, 24, 24]./255,{'LineWidth',2});
%     % end
%     % end
%     % if(dataStruct.loop.numInObjectEnclosedByHole)
%     % for i = 1:length(dataStruct.loop.object.enclosed)
%     %     plotFromEdgeList(dataStruct.loop.object.enclosed(i).EL, records, [130, 24, 24]./255,{'LineWidth',2});
%     % end
%     % end
%     % if(dataStruct.loop.numInObjectEnclosingHole)
%     % for i = 1:length(dataStruct.loop.object.enclosing)
%     %     plotFromEdgeList(dataStruct.loop.object.enclosing(i).EL, records, [130, 24, 24]./255,{'LineWidth',2});
%     % end
%     % end
%     % axis([1,xDim+1,1,yDim+1]);
%     print(tmp,[dirName 'VorGraphs' filesep 'COLOR_VOR_BRIDGE_' matFiles(iter).name,'.png'],'-dpng','-painters','-r200');
%     % test = getframe(gca);
%     % imwrite(test.cdata,[dirName 'VorGraphs' filesep 'COLOR_VOR_BRIDGE' matFiles(iter).name,'.png']);
%     close(tmp);
% end
% end
% plotVoronoiBridge_Post(dataStruct, records)