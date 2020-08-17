function queue = tipDetection(records, regionObj,filtSize,preferMA,ignoreSingletons)

% [records, dataStruct] = runVoronoi;
%E1 = enclosed(2)
%E2 = acyclic(20)
%E3 = enclosed(1)
%%Perform a BFS from all nodes on major axis.  IF dist child->node (direect) < rad, collect and continue.  Else end search.
% close all;
if(~exist('endpointLine.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end
% regionObj = dataStruct.loop.object.enclosed(2);
% filtBound = filterBoundary(regionObj,30);
% close all;
% figure;
clear vertList radList distList lastVertBelowThresh lastVertBelowThresh_ListID boundVerts nonRepeatBases,


subGraphBoundaryVerts = regionObj.boundaryVerts;
% if(length(subGraphBoundaryVerts) == 4)
%     return;
% end
% binaryFiltBoundaryVerts = false(size(records.input,1),1);
% binaryFiltBoundaryVerts(records.verts.vertexCoorID(subGraphBoundaryVerts)) = true;


%Queue of subregions to operate on.
protrusionTips = subGraphBoundaryVerts(findProtrusionTips(regionObj,filtSize));

queuePlace = 1;
queuePos = 0;
queue = {};
queueStruct.localProtrusionTips_global = protrusionTips;
queueStruct.globalVertIds = find(records.verts.borderRegions(:,1) == regionObj.objectNumber);
queueStruct.majorAxisPoints = [];
queueStruct.depth = 1;
if(length(queueStruct.globalVertIds) < 300)
    queueStruct.depth = queueStruct.depth + 1;
end

queuePos=queuePos+1;
queue{queuePlace} = queueStruct;
queuePlace=queuePlace+1;
depthLevels = 4;
colorDepths = hsv(depthLevels);
objectIDGlobal = zeros(records.verts.length,1);
while(queuePos ~= queuePlace)
    queue{queuePos}.children = [];
    regionData = queue{queuePos};
    %Get matrix for region to send to C code
    [adjList, vertCoor, radList, vertexList, borders,revMap] = recordsToAdjList_Simplified(records, regionData.globalVertIds);
    objectIDGlobal(vertexList) = queuePos;
    %Get the tipIDs in the subregion
    protrusionTips_Sub = revMap(regionData.localProtrusionTips_global);
    if(~isempty(regionData.majorAxisPoints))
        majorAxis_Sub = revMap(regionData.majorAxisPoints);
    else
        majorAxis_Sub = [];
    end
    %Include the majoraxis tips 
    combinedTargets = [protrusionTips_Sub; majorAxis_Sub];
    if(length(combinedTargets) > 2)
        if(preferMA && ~isempty(majorAxis_Sub))
            if(length(majorAxis_Sub) == 1)
                root = majorAxis_Sub;
            else
                [~, root] = max(radList);
                [dist] = dijkstra_mex(adjList, root, majorAxis_Sub, borders);
                targetDists = dist(majorAxis_Sub);
                [~,maxMA] = max(targetDists);
                root = majorAxis_Sub(maxMA);
            end
            [dist, par, child] = dijkstra_mex(adjList, root, combinedTargets, borders);
            targetDists = dist(combinedTargets);
            [~,maxProt] = max(targetDists);
            maxProt = combinedTargets(maxProt);
            axisTips = [maxProt, root];
            
            curPoint = axisTips(1);
            axisVerts = zeros(size(adjList,1),1);
            axisVerts(1) = curPoint;
            counter = 2;
            while(par(curPoint) ~= 0)
                curPoint = par(curPoint);
                axisVerts(counter) = curPoint;
                counter = counter + 1;
            end
            axisVerts(counter:end) = [];
        elseif(length(combinedTargets) > 2)
            [~, root] = max(radList);
            [dist, par, child] = dijkstra_mex(adjList, root, combinedTargets, borders);
            onAxis = false(size(adjList,1),1);
            targetDists = dist(combinedTargets);
            [distOrdered,targetID] = sort(targetDists,'descend');
            targetID = combinedTargets(targetID);
            numTipsReached = 0;
            axisTips = zeros(1,2);
            axisPath.first = 0;
            axisPath.second = 0;
            for i = 1:length(distOrdered)
                indexCollect = zeros(size(onAxis,1),1);
                curPoint = targetID(i);
                counter = 1;
                indexCollect(counter) = curPoint;
                interrupted = false;
                while(par(curPoint) ~= 0)
                    curPoint = par(curPoint);
                    if(onAxis(curPoint) && curPoint ~= root)
                        interrupted = true;
                        break;
                    end
                    counter = counter+1;
                    indexCollect(counter) = curPoint;
                    %        if(curPoint == root)
                    %            disp('');
                    %        end
                end
                indexCollect(counter+1:end) = [];
                if(~interrupted)
                    numTipsReached = numTipsReached + 1;
                    axisTips(numTipsReached) = targetID(i);
                    if(numTipsReached == 1)
                        axisPath.first = indexCollect;
                    else
                        axisPath.second = indexCollect;
                    end
                    onAxis(indexCollect) = true;
                end
                if(numTipsReached > 1)
                    subTreeList = 1:size(adjList,1);
                    axisVerts = subTreeList(onAxis);
                    break;
                end
            end
            if(numTipsReached == 1)
                otherVerts = combinedTargets;
                otherVerts(otherVerts==axisTips(1)) = [];
                [dist, par, child] = dijkstra_mex(adjList, axisTips(1), otherVerts, borders);
                targetDists = dist(otherVerts);
                [~,furthestTarget] = max(targetDists);
                furthestTarget = otherVerts(furthestTarget);
                axisTips(2) = furthestTarget;
                curPoint = axisTips(2);
                axisVerts = zeros(size(adjList,1),1);
                axisVerts(1) = curPoint;
                counter = 2;
                while(par(curPoint) ~= 0)
                    curPoint = par(curPoint);
                    axisVerts(counter) = curPoint;
                    counter = counter + 1;
                end
                axisVerts(counter:end) = [];
                axisPath.second = axisVerts;
            end
        end
        
        
        
        %     vertexCoor = records.verts.pos(vertexList,:);
        allReachable = BFS_InRad_Search(adjList, axisVerts, radList, vertCoor);
        
        protrusionReached = false(size(radList,1),1);
        protrusionReached(axisTips) = true;
        numChild = 1;
        queue{queuePos}.AxisIndexA = vertexList(axisTips(1));
        queue{queuePos}.AxisIndexB = vertexList(axisTips(2));
        queue{queuePos}.AxisIndex = vertexList([axisTips(1),axisTips(2)]);
%         queue{queuePos}.isTip = vertexList([axisTips(1),axisTips(2)]);

        
        queue{queuePos}.AllReachable = vertexList(allReachable);
        queue{queuePos}.AxisVerts = vertexList(axisVerts);
                    queue{queuePos}.totalDist = dist(axisTips(1)) + dist(axisTips(2));
        queue{queuePos}.dist = dist;

        for i = 1:length(protrusionTips_Sub)
            protrusionID = protrusionTips_Sub(i);
            if(~protrusionReached(protrusionID))
                [globalVertIds,localProtrusionTips_global,majorAxisPoints] = BFS_mex(adjList,protrusionID,protrusionTips_Sub,allReachable,borders);
                queueStruct.globalVertIds = sort(vertexList(globalVertIds));
                queueStruct.localProtrusionTips_global = sort(vertexList(localProtrusionTips_global));
                queueStruct.majorAxisPoints = sort(vertexList(majorAxisPoints));
                protrusionReached(localProtrusionTips_global) = true;
                if(~(ignoreSingletons && length(queueStruct.globalVertIds) == length(queueStruct.localProtrusionTips_global)))
                    queueStruct.depth = regionData.depth+1;
                    queue{queuePlace} = queueStruct;
                    queue{queuePos}.children(numChild) = queuePlace;
                    numChild = numChild + 1;
                    queuePlace = queuePlace + 1;
                end
            end
        end
    elseif(length(combinedTargets) == 2)
        [dist, par, child] = dijkstra_mex(adjList, combinedTargets(2), combinedTargets(1), borders);
        curPoint = combinedTargets(1);
        axisVerts = zeros(size(adjList,1),1);
        axisVerts(1) = curPoint;
        counter = 2;
        while(par(curPoint) ~= 0)
            curPoint = par(curPoint);
            axisVerts(counter) = curPoint;
            counter = counter + 1;
        end
        axisVerts(counter:end) = [];
        allReachable = BFS_InRad_Search(adjList, axisVerts, radList, vertCoor);
        axisPath.first = combinedTargets(2);
        axisPath.second = combinedTargets(1);
        queue{queuePos}.AxisIndexA = vertexList(axisPath.first);
        queue{queuePos}.AxisIndexB = vertexList(axisPath.second);
        queue{queuePos}.AllReachable = vertexList(allReachable);
        queue{queuePos}.AxisVerts = vertexList(axisVerts);
                    queue{queuePos}.totalDist = dist(combinedTargets(2)) + dist(combinedTargets(1));
        queue{queuePos}.dist = dist;

    elseif(length(combinedTargets) == 1)
        otherVerts = 1:size(adjList,1);
        otherVerts(combinedTargets(1)) = [];
        [dist, par, child] = dijkstra_mex(adjList, combinedTargets(1), otherVerts, borders);
        targetDists = dist(otherVerts);
        [~,furthestTarget] = max(targetDists);
        furthestTarget = otherVerts(furthestTarget);
        
        axisPath.first = combinedTargets(1);
        axisPath.second = furthestTarget;
        
        curPoint = furthestTarget;
        axisVerts = zeros(size(adjList,1),1);
        axisVerts(1) = curPoint;
        counter = 2;
        while(par(curPoint) ~= 0)
            curPoint = par(curPoint);
            axisVerts(counter) = curPoint;
            counter = counter + 1;
        end
        axisVerts(counter:end) = [];
        allReachable = BFS_InRad_Search(adjList, axisVerts, radList, vertCoor);
        queue{queuePos}.AxisIndexA = vertexList(axisPath.first);
        queue{queuePos}.AxisIndexB = vertexList(axisPath.second);
        queue{queuePos}.AllReachable = vertexList(allReachable);
        queue{queuePos}.AxisVerts = vertexList(axisVerts);
                    queue{queuePos}.totalDist = dist(axisTips(1)) + dist(axisTips(2));
        queue{queuePos}.dist = dist;
    end
    
%     ELpath = vertices2EL(records,vertexList);
    % ELfull = vertices2EL(records,vertexList(allReachable));
%     colorinfo = colorDepths(mod(regionData.depth,depthLevels)+1,:);
    
    %fill(vertCoor(borders,1),vertCoor(borders,2),colorinfo);
    % plotFromEdgeList(ELfull,records,colorinfo,{'LineWidth',3});
%     plotFromEdgeList(ELpath,records,colorinfo,{'LineWidth',1});

    queuePos = queuePos + 1;
end

allVerts = queue{1}.globalVertIds;
[adjList, vertCoor, radList, vertexList, borders,revMap,edgeIDMat, edgeDirMat, edgeRevMap] = recordsToAdjList_Simplified(records, allVerts);
binToNum = 1:length(radList);
for i = 1:length(queue)
    colorinfo = colorDepths(mod(queue{i}.depth,depthLevels)+1,:);
    
    binMap = objectIDGlobal == i;
    for j = 1:length(queue{i}.children)
        binMap(queue{queue{i}.children(j)}.majorAxisPoints) = false;
    end
    validList = binToNum(revMap(binMap));
    %     if(i == 8)
    %         disp('test');
    %     end
    invalidAll = revMap(~binMap);
    invalidList = binToNum(invalidAll(invalidAll ~= 0));
    %   [adjList, vertCoor, radList, vertexList, borders,revMap,edgeIDMat, edgeDirMat, edgeRevMap] = recordsToAdjList_Simplified(records, validList);
    [~,rootIDlist] = max(radList(validList));
    rootID = validList(rootIDlist);
    reachableBorderPoints = DFS_mex(adjList, edgeIDMat, edgeDirMat, rootID, borders, invalidList);
    patch(vertCoor(reachableBorderPoints,1),vertCoor(reachableBorderPoints,2),colorinfo,'EdgeColor','none');
    
    
end
for i = 1:length(queue)
    colorinfo = colorDepths(mod(queue{i}.depth,depthLevels)+1,:);
    
    binMap = objectIDGlobal == i;
    for j = 1:length(queue{i}.children)
        binMap(queue{queue{i}.children(j)}.majorAxisPoints) = true;
    end
    
    ELpath = vertices2EL(records,queue{i}.AxisVerts);
    queue{i}.EL = vertices2EL_Path(records,queue{i}.AxisVerts);
    queue{i}.EL_path_both = ELpath;
    ELMAall = vertices2EL(records,queue{i}.AllReachable);
    allVert = 1:records.verts.length;
    ELFullVor = vertices2EL(records,allVert(binMap));
    %     axisVertsAll = queue{i}.AllReachable;
    
    %     for j = 1:length(queue{i}.children)
    %         axisVertsAll(length(axisVertsAll)+1:length(axisVertsAll)+length(queue{queue{i}.children(j)}.majorAxisPoints)) = queue{queue{i}.children(j)}.majorAxisPoints;
    %     end
    %     ELMAllANDSUB = vertices2EL(records,axisVertsAll);
    
    plotFromEdgeList(ELFullVor,records,colorinfo/1.175,{'LineWidth',0.5,'LineStyle',':'});
    plotFromEdgeList(ELMAall,records,colorinfo./1.25,{'LineWidth',0.5});
    
    plotFromEdgeList(ELpath,records,colorinfo./2,{'LineWidth',3});
    
    scatter(records.verts.pos(queue{i}.AxisIndexA(1),1),records.verts.pos(queue{i}.AxisIndexA(1),2),.5,'MarkerEdgeColor',colorinfo./3,'MarkerFaceColor',colorinfo./1.5);
    scatter(records.verts.pos(queue{i}.AxisIndexB(1),1),records.verts.pos(queue{i}.AxisIndexB(1),2),.5,'MarkerEdgeColor',colorinfo./3,'MarkerFaceColor',colorinfo./1.5);
end
%BFS_inrad_search on onAxis and adjacency list
%BFS_search from tips to expanded axis
%Collect subtree and repeat
%simplePathPlot_Boundary(records,binaryFiltBoundaryVerts,{'LineWidth',2,'Color','b'});
% %boundaryVCoor = records.input(binaryFiltBoundaryVerts,3:4);
% for i = 1:length(protrusionTips)
%
% [vertList{i}, radList{i}, distList{i}, lastVertBelowThresh{i}, lastVertBelowThresh_ListID{i}] = boundaryPathToRoot(records, regionObj, protrusionTips(i), 3);
% simplePathPlot(records,vertList{i}(1:lastVertBelowThresh_ListID{i}),{'LineWidth',1,'Color','r'});
% end
% subGraphBoundaryVertsFilt = subGraphBoundaryVerts;
% nonRepeatBases = ([lastVertBelowThresh{:}]);
% for i = 1:length(nonRepeatBases)
%     if(i==9)
%     disp('');
% end
% boundVerts{i} = internalNodeToBoundary(records, regionObj, nonRepeatBases(i),vertList{i}(1:lastVertBelowThresh_ListID{i}));
% binaryFiltBoundaryVerts(records.verts.vertexCoorID(boundVerts{i})) = false;
% boundaryVCoor(records.verts.vertexCoorID(boundVerts{i}),1:2) = repmat(records.verts.pos(nonRepeatBases(i),1:2),length(boundVerts{i}),1);
% end
% simplePathPlot_Boundary(records,binaryFiltBoundaryVerts,{'LineWidth',2,'Color','g'});
%figure;
%simplePathPlot_Boundary(records,records.verts.vertexCoorID(subGraphBoundaryVerts),{'LineWidth',1,'Color','b'});
%for i = 1:length(protrusionTips)
%simplePathPlot(records,vertList{i}(1:lastVertBelowThresh_ListID{i}),{'LineWidth',3,'Color','r'});
%end
%line([boundaryVCoor(:,1);boundaryVCoor(1,1)],[boundaryVCoor(:,2);boundaryVCoor(1,2)],'LineWidth',2,'Color','g');
