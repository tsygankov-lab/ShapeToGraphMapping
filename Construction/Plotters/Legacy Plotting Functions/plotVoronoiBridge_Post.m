% This is a legacy plotting function

function plotVoronoiBridge_Post(bridgeRecords, records)
%     numBridges = sum(~isempty(dataStruct.bridge));
%     figureHandle = figure('units','pixel','visible','on','position',[0,1000-960,1920,960],'color',[0,0,0],'defaultaxesposition',[0,0,1,1],'InvertHardCopy', 'off','PaperSize', [19.2,9.6]);
%     set(figureHandle, 'Visible', 'off');
%     whitebg(0,[0,0,0]);
%     set(gcf, 'color', [0,0,0]);
%     set(gca, 'color', [0,0,0]);
%     set(gcf, 'InvertHardCopy', 'off');
%     setappdata(figureHandle,'LegendColorbarManualSpace',1);
%     setappdata(figureHandle.Children,'LegendColorbarManualSpace',1);
%     setappdata(figureHandle,'LegendColorbarReclaimSpace',1);
%     setappdata(figureHandle.Children,'LegendColorbarReclaimSpace',1);

coloringMat = hsv(length(bridgeRecords.bridge));

hold on;
% axis off;
axis equal
% axis ij;

    for i = 1:length(bridgeRecords.bridge)
        hold on;
        logicalFilter = zeros(size(records.vorVert,1),1,'logical');
        logicalFilter(bridgeRecords.bridge(i).Vertices(:)) = true;
        plotVoronoiSubGraph_vertList(records,logicalFilter,coloringMat(i,:));
%             linearEdges = [];
%             quadEdges = [];
%             for k = 1:length(bridgeRecords.bridge(i).EL)
% %              set(0,'CurrentFigure',figureHandle);
%              edge = records.halfEdge(bridgeRecords.bridge(i).EL(k),:);
%              twinEdge = records.halfEdge(edge(1),:);
%              vertA = records.vorVert(edge(3));
%              vertB = records.vorVert(edge(4));
%              if(edge(2) ~= 2 && edge(2) ~= 102)
%                  linearEdges = [linearEdges;vertA(1),vertA(2);vertB(1),vertB(2);nan,nan];
%              else
%                if(abs(vertA(1) - vertB(1)) >= sqrt(eps) || abs(vertA(2) - vertB(2)) >= sqrt(eps))
% %                 obj1=records.bridge(i).EL(k).adjacentFace.siteObject;
% %                 obj2=records.bridge(i).EL(k).Twin.adjacentFace.siteObject;
%                 if(record.input(edge(8),1)) %This is a point
%                     line = records.edgeSup(twinEdge(8) - records.numInputVerts,:);
%                     point = records.input(edge(8),:);
%                 else
%                     line = records.edgeSup(edge(8) - records.numInputVerts,:);
%                     point = records.input(twinEdge(8),:);
%                 end
% 
%                 pt2=getBezeir_ARR(line,point,vertA,vertB);
%                 t=linspace(0,1,20);
%                 
%                 bCurve = kron((1-t).^2,vertA.corr') + kron(2*(1-t).*t,pt2') + kron(t.^2,vertB.corr');
%                 quadEdges = [quadEdges;bCurve';nan,nan]; %Can be predicted now... will wait
%                end
%              end
% %             [isNotPlotted] = plotVorVertsWithEdges_Post(records.Vertex{j}, isNotPlotted, colorMat);
%             end
%             if(~isempty(linearEdges))
%                 plot(linearEdges(:,1),linearEdges(:,2),'Color',coloringMat(i,:),'LineWidth',2)
%             end
%             if(~isempty(quadEdges))
%                 plot(quadEdges(:,1),quadEdges(:,2),'Color',coloringMat(i,:),'LineWidth',2)
%             end
    end
   
%     [xEdge, yEdge] = plotVertCoorandEdgeList(vertexCoor, EL,settingsList,records);
%             xEdge = nan(size(EL,1),3);
%             yEdge = nan(size(EL,1),3);
%             
%             xEdge(1:end,:) = [vertexCoor(EL(:,1),1),vertexCoor(EL(:,2),1),nan(size(EL(:,1)))];
%             yEdge(1:end,:) = [vertexCoor(EL(:,1),2),vertexCoor(EL(:,2),2),nan(size(EL(:,1)))];
%     set(0,'CurrentFigure',figureHandle);
%     plot(reshape(xEdge',[size(xEdge,1)*size(xEdge,2),1]), reshape(yEdge',[size(yEdge,1)*size(yEdge,2),1]),'Color',[1,1,1],'LineWidth',0.1);
%     plot(vertexCoor(:,1),vertexCoor(:,2),'.','Color',[1,1,1],'MarkerSize',1.2,'LineWidth',0.1);
% axis(AXISWIDTH);
%     print(strcat('Outputs2\frame',num2str(IterationNumber),'.png'),'-dpng');
hold off;
end
