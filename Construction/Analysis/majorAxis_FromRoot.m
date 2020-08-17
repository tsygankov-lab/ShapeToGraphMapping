function [path] = majorAxis_FromRoot(records,regionObj,filtSize)
subGraphBoundaryVerts = regionObj.boundaryVerts;
r2sV = regionObj.records2SubgraphMap_Vertices;

protrusionTips_BID = findProtrusionTips(regionObj,filtSize);
[~,maxDistTips] = sort(regionObj.boundaryProfile(protrusionTips_BID),'descend');
sortedMaxDistTips = (subGraphBoundaryVerts(protrusionTips_BID(maxDistTips)));

onPath = false(records.verts.length,1);
[~, path.vert, path.edge, path.rad, path.dist] = boundaryPathToRoot_Restrict(records, regionObj, sortedMaxDistTips(1), onPath, 0);
onPath(path.vert) = true;
for i = 2:length(sortedMaxDistTips)
    [pathFound, tmpPath.vert, tmpPath.edge, tmpPath.rad, tmpPath.dist] =  boundaryPathToRoot_Restrict(records, regionObj, sortedMaxDistTips(i), onPath, 1);
    if(pathFound)
        path.vert = [path.vert;tmpPath.vert];
        path.edge = [path.edge;tmpPath.edge];
        path.rad  = [path.rad; tmpPath.rad];
        path.dist = [path.dist; tmpPath.dist];
        path.dist = cumsum(path.dist);
        return;
    end
end
[~, sortedBP] = sort(regionObj.boundaryProfile,'descend');
sortedBP = subGraphBoundaryVerts(sortedBP);
for i = 2:length(sortedBP)
    [pathFound, tmpPath.vert, tmpPath.edge, tmpPath.rad, tmpPath.dist] =  boundaryPathToRoot_Restrict(records, regionObj, sortedBP(i), onPath, 1);
    if(pathFound)
        path.vert = [path.vert;tmpPath.vert];
        path.edge = [path.edge;tmpPath.edge];
        path.rad  = [path.rad; tmpPath.rad];
        path.dist = [path.dist; tmpPath.dist];
        path.dist = cumsum(path.dist);
        return;
    end
end
disp('A second path was never found even when search across all points');
path.dist = cumsum(path.dist); %If only one route is found
end

function [pathFound, vertList, edgeList, radList, distList] = boundaryPathToRoot_Restrict(records, regionObj, boundaryPointIdx, restrictList, reverse)
%%Go through the pre-caclulated loop boundary profile info.
%%Traverse back up from boundary to root, storing radii and instantaneous distance
%%Determine edge weights at each stage (average radius).
%%Force to be strictly increasing (if i > i+1, i = i+1).
%%Calculate AUC
%%Normalize by Radius

pathFound = true;
r2sV = regionObj.records2SubgraphMap_Vertices;
vertList = zeros(20,1);
radList = zeros(20,1);
edgeList = zeros(20,1);
distList = zeros(20,1);

iter =2;
curVert = boundaryPointIdx; %loopStruct.boundaryVerts(boundaryPointIdx);
vertList(1) = curVert;
radList(1) = 0;
while(~regionObj.isRootNode(curVert))
    if(restrictList(curVert))
        pathFound = false;
        return;
    end
    nextEdge = regionObj.parEdge(r2sV(curVert),1);
    curVert = records.edges.origin(nextEdge,2);
    radList(iter) = records.verts.rad(curVert);
    vertList(iter) = curVert;
    distList(iter) = records.edges.dist(nextEdge);
    if(~reverse)
        edgeList(iter - 1) = nextEdge;
    else
        edgeList(iter - 1) = records.edges.twinID(nextEdge);
    end
    iter = iter + 1;
end
vertList(iter:end) = [];
radList(iter:end) = [];
edgeList((iter - 1):end) = [];
distList(iter:end) = [];
if(reverse)
    vertList(1:end) = vertList(end:-1:1);
    edgeList(1:end) = edgeList(end:-1:1);
    radList(1:end) = radList(end:-1:1);
    distList(1:end) = distList(end:-1:1);
end
end