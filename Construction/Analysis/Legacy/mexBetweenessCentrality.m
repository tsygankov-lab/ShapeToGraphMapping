
function betweenness = mexBetweenessCentrality(V,E,color,vertFilterList,location,r2sV,s2rV,nonLeafVerts)

% r2sV(vertFilterList) = 1:length(s2rV);
nonCycleFlag = 1;

colorInd = 1;
edgeFilterList       = E.color(:) == color & V.borderRegions(E.origin(:,1),colorInd) == location;
% s2rE                 = find(edgeFilterList);
% r2sE                 = sparse(size(edgeFilterList));
% r2sE(edgeFilterList) = 1:length(s2rE);
%edgeSubGraph         = records.halfEdge(edgeFilterList,:);



% fullGraphBinary = zeros(size(records.vorVert,1),1);

validStartPoints = find(vertFilterList & nonLeafVerts);
betweenness = zeros(length(validStartPoints),1);


for vsp = 1:length(validStartPoints)
    vertexCollectionList = zeros(sum(vertFilterList),1);
    edgeCollectionList   = zeros(sum(edgeFilterList),1);
    
    edgeProcessed        = zeros(size(edgeFilterList),'uint8');
    vertexTerminal       = V.vertexCoorID(:) ~= -1;
    vertexTerminal_SubGraph = V.vertexCoorID(vertFilterList) ~= -1;
    vertexTerminal_SubGraph_Proc = vertexTerminal_SubGraph;
    vertexTerminal_SubGraph_Index = find(vertexTerminal_SubGraph);
    vertexTerminal_circList = zeros(size(vertexTerminal_SubGraph_Index));
    childEdge  = zeros(size(s2rV,1),2);
    parentEdge = zeros(size(s2rV,1),2); %%'2' because concave edges can have two parents
    radMatrix  = zeros(size(s2rV,1),1);
    distMatrix = zeros(size(s2rV,1),1);
    dirMat = zeros(size(s2rV,1),2);
    startPoint = validStartPoints(vsp);%s2rV(startPointID);%records.vorVert(s2rV(startPointID),:);
    startPointID = r2sV(startPoint);
    dirMat(1,:) = -[0,1];  %downward at start
    radMatrix(1) = V.rad(startPoint);%startPoint(3);
    distMatrix(1) = 0;
    vertexCollectionList(1) = startPoint;%s2rV(startPointID);
    parentEdge((startPointID),1) = -1;
    endState = 0;
    iter = 1;
    dbgplot = 0;
    edge = 0;
%     reversing = 0;
    terminals = 0;
    startingVertexInd = vertexCollectionList(1);
    %%loop until a termination condition has been met
    while(~endState)
        %     if(totalCount == 187)
        %         disp('pause')
        %     end
        curVert = vertexCollectionList(iter);%records.vorVert(vertexCollectionList(iter),:);
        if(~vertexTerminal(vertexCollectionList(iter))) %%If it is not a terminal vertex...
            if(parentEdge(r2sV(vertexCollectionList(iter)),2) == 0) %%Store the parent edge
                parEdge = parentEdge(r2sV(vertexCollectionList(iter)),1);
            else
                parEdge = parentEdge(r2sV(vertexCollectionList(iter)),2);
            end
            edgeIndexMatrixFiltConnected  = V.edgeIDList(curVert,1:V.degree(curVert));%curVert(9:8+curVert(8));		%%Edges connected to this vertex
            edgeIndexMatrixFiltInSubGraph = edgeIndexMatrixFiltConnected(edgeFilterList(edgeIndexMatrixFiltConnected));  %%Edges in subgraph region
            edgeIndexMatrixFiltNoReverse  = edgeIndexMatrixFiltInSubGraph((edgeIndexMatrixFiltInSubGraph) ~= parEdge); %%Edge is not an immediate reversal
            edgeIndexMatrixFinal          = edgeIndexMatrixFiltNoReverse(~edgeProcessed(edgeIndexMatrixFiltNoReverse)); %%Edge has not been touched
            
            if(isempty(edgeIndexMatrixFinal) && vertexCollectionList(iter) == startingVertexInd && nonCycleFlag)
                %%all paths exhausted, terminate...
                iter = iter + 1; %to not purge information...
                endState = 1;
                break;
            elseif(isempty(edgeIndexMatrixFinal)) %%If no edges are valid, reverse
                iter = iter - 1;
%                 if(dbgplot)
%                     plot(V.pos(curVert,1),V.pos(curVert,2),'rx','MarkerSize',6,'MarkerFaceColor','r');
%                     xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]);
%                     ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]);
%                     %                 f = getframe;
%                     totalCount = totalCount + 1;
%                     %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff'));
%                     drawnow;
%                 end
%                 reversing = 1;
            else
%                 if(dbgplot && ~reversing)
%                     plot(V.pos(curVert,1),V.pos(curVert,2),'go','MarkerSize',6,'MarkerFaceColor','g');
%                     xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]);
%                     ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]);
%                     totalCount = totalCount + 1;
%                     %                 f = getframe;
%                     %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff'));
%                     drawnow;
%                 end
%                 reversing = 0;
                if(length(edgeIndexMatrixFinal) == 1) %%Don't test if only one edge is there
                    edgeInd = edgeIndexMatrixFinal(1);
                else
                    angleMat = zeros(size(edgeIndexMatrixFinal));
                    for i = 1:length(edgeIndexMatrixFinal)
                        edge = edgeIndexMatrixFinal(i);%records.halfEdge(edgeIndexMatrixFinal(i),:);
                        twinEdge = E.twinID(edge);%records.halfEdge(edge(1),:);
                        if(sqrt(E.dir(edge,1)^2 + E.dir(edge,2)^2) < sqrt(eps))
                            %This code branch is outdated, but there for safety
                            noEdgeFound = 1;
                            parEdge_T = E.twinID(edge);%edge(1); %%Twin edge, temporary parent edge for this cycle
                            twinVert = E.origin(edge,2);%records.vorVert(edge(4),:);
                            while(noEdgeFound)
                                zeroedgeIndexMatrixFiltConnected  = V.edgeIDList(twinVert,1:V.degree(twinVert));%twinVert(9:8+twinVert(8));		%%Edges connected to this vertex
                                zeroedgeIndexMatrixFiltInSubGraph = zeroedgeIndexMatrixFiltConnected(edgeFilterList(zeroedgeIndexMatrixFiltConnected));  %%Edges in subgraph region
                                zeroedgeIndexMatrixFiltNoReverse  = zeroedgeIndexMatrixFiltInSubGraph((zeroedgeIndexMatrixFiltInSubGraph) ~= parEdge_T); %%Edge is not an immediate reversal
                                zeroedgeIndexMatrixFinal          = zeroedgeIndexMatrixFiltNoReverse(~edgeProcessed(zeroedgeIndexMatrixFiltNoReverse)); %%Edge has not been touched
                                if(isempty(zeroedgeIndexMatrixFinal))
                                    %If this is true, this path might lead to
                                    %a vertex? - Or on terminating iteration
                                    noEdgeFound = 0;
                                    angleMat(i) = -2; %%Only occurs on the terminating iteration...
                                else
                                    for j = 1:length(zeroedgeIndexMatrixFinal)
                                        zeroEdge = zeroedgeIndexMatrixFinal(j);%records.halfEdge(zeroedgeIndexMatrixFinal(j),:);
                                        if(sqrt(E.dir(zeroEdge,1)^2 + E.dir(zeroEdge,2)^2) > sqrt(eps(max([V.pos(E.origin(twinEdge,1),1:2)]))))
                                            %%as long as the edge has a valid direction and its not a reversal it is fine.  The left most edge of one branch can not be to the left of the rightmost edge of the other if it is truly to the right
                                            angleMat(i) = angleBetween(dirMat(iter,:),E.dir(zeroEdge,:));%zeroEdge(6:7)); %Alt - grab a linear dist calculation from the previous point
                                            noEdgeFound = 0;
                                        else
                                            parEdge_T = E.twinID(zeroEdge);%zeroEdge(1);
                                            twinVert = E.origin(zeroEdge,2);%records.vorVert(zeroEdge(4),:);
                                        end
                                    end
                                end
                            end
                        else
                            angleMat(i) = angleBetween(dirMat(iter,:),E.dir(edge,:));%edge(6:7));
                        end
                    end
                    [~,ind] = min(angleMat); %%for CCW selection
                    edgeInd = edgeIndexMatrixFinal(ind);
                end
                
                edgeCollectionList(iter) = edgeInd;
                edgeProcessed(edgeInd) = 1;
                edge = edgeInd;%records.halfEdge(edgeInd,:);
                iter = iter + 1;
                
                if(E.origin(edge,2) == startingVertexInd)
                    %%TERMINATE LOOP - DO NOT STORE MORE INFORMATION
                    endState = 1;
                    break;
                else
                    vertexCollectionList(iter) = E.origin(edge,2);%(edge(4));
                    subGraphIndOld = r2sV(vertexCollectionList(iter-1));
                    subGraphIndNew = r2sV(vertexCollectionList(iter));
                    if(parentEdge(subGraphIndNew,1) == 0)
                        parentEdge(subGraphIndNew,1) = E.twinID(edge);%edge(1);
                    else
                        parentEdge(subGraphIndNew,2) = E.twinID(edge);%edge(1);
                    end
                    
                    if(childEdge(subGraphIndOld,1) == 0)
                        childEdge(subGraphIndOld,1) = edgeInd;
                    else
                        childEdge(subGraphIndOld,2) = edgeInd;
                    end
                    
                    if(E.dist(edge) < sqrt(eps(max([V.pos(E.origin(edge,2),1:2)]))))
                        dirMat(iter,:) = dirMat(iter-1,:);
                    else
                        dirMat(iter,:) = -E.dir(E.twinID(edge),:);%-records.halfEdge(edge(1),6:7);
                    end
                    
                    distMatrix(iter) = E.dist(edge);%edge(5);
                    radMatrix(iter) = V.rad(vertexCollectionList(iter));
                end
            end
        else
            if(vertexTerminal_SubGraph_Proc(r2sV(vertexCollectionList(iter))) == 1)
                vertexTerminal_SubGraph_Proc(r2sV(vertexCollectionList(iter))) = 0; %Found
                terminals = terminals + 1;
                vertexTerminal_circList(terminals) = r2sV(vertexCollectionList(iter));
%                 if(dbgplot)
%                     plot(V.pos(curVert,1),V.pos(curVert,2),'go','MarkerSize',6,'MarkerFaceColor','g');
%                     plot(V.pos(curVert,1),V.pos(curVert,2),'rx','MarkerSize',6,'MarkerFaceColor','r');
%                     xlim([V.pos(curVert,1)-20,V.pos(curVert,1)+20]);
%                     ylim([V.pos(curVert,2)-20,V.pos(curVert,2)+20]);
%                     %                 f = getframe;
%                     %                 imwrite(f.cdata,strcat('D:\Miracles\uglyAGAIN',num2str(totalCount), '.tiff'));
%                     drawnow;
%                 end
            end
            
            reversing = 1;
            iter = iter - 1;
            
        end
    end
    
    
    
    vertexCollectionList(iter:end) = [];
    % edgeCollectionList(iter:end) = [];
%     dirMat(iter:end,:) = [];
    % radMatrix(iter:end) = [];
    % distMatrix(iter:end) = [];
    % loopStruct.Vertices = vertexCollectionList;
    % loopStruct.EL = edgeCollectionList;
    % loopStruct.subGraphVerts = vertSubGraph;
    % loopStruct.subGraphParentEdge = parentEdge;
    % loopStruct.subGraphChildEdge = childEdge;
    % loopStruct.direction = dirMat;
    % loopStruct.incrDist = distMatrix;
    % loopStruct.distance = cumsum(distMatrix);
    % if(nonCycleFlag)
    %     loopStruct.totalDistance = 0;
    % else
    %     loopStruct.totalDistance = loopStruct.distance(end) + E.dist(edgeCollectionList(end));%records.halfEdge(edgeCollectionList(end),5);
    % end
    % loopStruct.radius = radMatrix;
    % loopStruct.records2SubgraphMap_Vertices = r2sV;
    % loopStruct.subgraph2RecordsMap_Vertices = s2rV;
    % loopStruct.binaryFilt = vertFilterList;
    
    % loopStruct.color = color;
    % loopStruct.inObject = inObject;
    % loopStruct.subGraphLeafFilter = vertexTerminal_SubGraph;
    % loopStruct.nonCycle = nonCycleFlag;
    isOnBridge = false(V.length,1);
    isOnBridge(vertexCollectionList) = true;
    distMat = zeros(size(vertexTerminal_circList));
    vertTerminal_circList_rootNode = zeros(size(vertexTerminal_circList));
    boundaryVertexCoor = zeros(size(vertTerminal_circList_rootNode,1),2);
    for i = 1:length(vertexTerminal_circList)
        %     if(i == 498)
        %         disp('rev')
        %     end
        vertInd = s2rV(vertexTerminal_circList(i));
        boundaryVertexCoor(i,:) = V.pos(vertInd,:);%records.vorVert(vertInd,1:2);
        distTemp = 0;
        if(~nonCycleFlag)
            while(~isOnBridge(vertInd)) %should short circuit
                edgeTraversal = parentEdge(r2sV(vertInd),1);%records.halfEdge(parentEdge(r2sV(vertInd),1),:);
                distTemp = distTemp + E.dist(edgeTraversal);%edgeTraversal(5);
                vertInd = E.origin(edgeTraversal,2);%edgeTraversal(4);
            end
        else
            while(parentEdge(r2sV(vertInd),1) ~= -1)
                edgeTraversal = parentEdge(r2sV(vertInd),1);%records.halfEdge(parentEdge(r2sV(vertInd),1),:);
                distTemp = distTemp + E.dist(edgeTraversal);
                vertInd = E.origin(edgeTraversal,2);
            end
        end
        vertTerminal_circList_rootNode(i) = vertInd;
        if(parentEdge(vertexTerminal_circList(i),2) ~= 0)
            distTempB = 0;
            vertInd = (vertexTerminal_circList(i));
            edgeTraversal = parentEdge(vertInd,2);%parentEdge(vertInd,2)records.halfEdge(parentEdge(vertInd,2),:);
            distTempB = distTempB + E.dist(edgeTraversal);%edgeTraversal(5);
            vertInd = E.origin(edgeTraversal,2);%edgeTraversal(4);
            if(~nonCycleFlag)
                while(~isOnBridge(vertInd))
                    edgeTraversal = parentEdge(r2sV(vertInd),1);%records.halfEdge(parentEdge(r2sV(vertInd),1),:);
                    distTempB = distTempB + E.dist(edgeTraversal);%edgeTraversal(5);
                    vertInd = E.origin(edgeTraversal,2);
                end
            else
                while(parentEdge(r2sV(vertInd),1) ~= -1)
                    edgeTraversal = parentEdge(r2sV(vertInd),1);%records.halfEdge(parentEdge(r2sV(vertInd),1),:);
                    distTempB = distTempB + E.dist(edgeTraversal);
                    vertInd = E.origin(edgeTraversal,2);
                end
            end
            if(distTempB < distTemp)
                distTemp = distTempB;
                vertTerminal_circList_rootNode(i) = vertInd;
            end
        end
        distMat(i) = distTemp;
        if(distTemp - V.rad(vertTerminal_circList_rootNode(i)) < 0 && distTemp - V.rad(vertTerminal_circList_rootNode(i)) > -sqrt(eps))
            distMat(i) = V.rad(vertTerminal_circList_rootNode(i));%records.vorVert(vertTerminal_circList_rootNode(i),3);
            %         disp('Minor precision error in radius caught and accounted for...');
        elseif(distTemp - V.rad(vertTerminal_circList_rootNode(i)) <= -sqrt(eps))
            disp('Severe precision error detected, review loop plots');
        end
    end
    betweenness(vsp) = (length(s2rV) - 1)/sum(distMat);
    % loopStruct.isRootNode = isOnBridge;
    % loopStruct.parEdge = parentEdge;
    % loopStruct.boundaryVerts = s2rV(vertexTerminal_circList);
    % loopStruct.boundaryVertexCoor = boundaryVertexCoor; %Num = perim, Area requires calculation
    % loopStruct.boundaryProfile = distMat;
    % loopStruct.boundaryToCycleNode = vertTerminal_circList_rootNode;
    % loopStruct.boundaryRatio = distMat./V.rad(vertTerminal_circList_rootNode);%records.vorVert(vertTerminal_circList_rootNode,3);
    % loopStruct.boundaryDiff = distMat - V.rad(vertTerminal_circList_rootNode);
end

end

