function [simpAL, vertexCoor, radList, vertexList, borderIDs, revMap, edgeIDMat, edgeDirMat, edgeRevMap] = recordsToAdjList_Simplified(records,vertexList)
%Converts the records structure to a simpler adjancency list.  Accepts the
%records matrix, and a vertexList (binary or numeric).  Returns a simple
%adjacency list in the form of [degree, neighbor 1, dist1, edgeID1, ... neighbor n, dist n, edgeIDn;...],

if(islogical(vertexList))
    sizeVector = 1:records.verts.length;
    vertexList = sizeVector(vertexList)';
else
    vertexList = sort(vertexList);
    if(size(vertexList,1) == 1)
        vertexList = vertexList';
    end
end
revMap = zeros(records.verts.length,1);
revMap(vertexList) = 1:length(vertexList);
simpAL = zeros(length(vertexList),1+2*max(records.verts.degree(vertexList)));
edgeIDMat = zeros(length(vertexList),max(records.verts.degree(vertexList)));
edgeDirMat = zeros(length(vertexList)*3,2);
edgeRevMap = zeros(length(edgeIDMat)*3,1);
vertexCoor = zeros(length(vertexList),2);
vertexCoor(:,1) = records.verts.pos(vertexList,1);
vertexCoor(:,2) = records.verts.pos(vertexList,2);
radList = records.verts.rad(vertexList);
borderIDs = zeros(records.verts.length,1);
numBorders = 1;
numEdges = 1;
for i = 1:length(vertexList)
    %simpAL(i,1) = records.verts.degree(vertexList(i));
    numValidChildren = 0;
    if(records.verts.vertexCoorID(vertexList(i)) ~= -1)
        borderIDs(numBorders) = i;
        numBorders = numBorders+1;
    end
    for j = 1:records.verts.degree(vertexList(i))
        edgeID = records.verts.edgeIDList(vertexList(i),j);
        otherEP = revMap(records.edges.origin(edgeID,2));
        if((otherEP) ~= 0)
            numValidChildren = numValidChildren + 1;
            simpAL(i,2+(numValidChildren-1)*2) = otherEP;
            simpAL(i,3+(numValidChildren-1)*2) = records.edges.dist(edgeID);
            edgeIDMat(i,numValidChildren) = numEdges;
            edgeRevMap(numEdges) = edgeID;
            edgeDirMat(numEdges,:) = records.edges.dir(edgeID,:);
            numEdges = numEdges+1;
        end
    end
    simpAL(i,1) = numValidChildren;
end
maxValidChildren = max(simpAL(:,1));
simpAL(:,2 + 2*maxValidChildren:size(simpAL,2)) = [];
borderIDs(numBorders:end) = [];

edgeDirMat(numEdges:end,:) = [];
edgeRevMap(numEdges:end) = [];
edgeIDMat(:,1 + maxValidChildren:size(edgeIDMat,2)) = [];
