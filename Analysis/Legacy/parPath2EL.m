function [EL] = parMat2EL(records,vertexList,parVec,curVert)
%%Given the Dijkstras output, creates list of edges forming the resulting
%%tree/path
parPath = zeros(length(parVec),2);
parPath(1,1) = curVert;
parPath(1,2) = parVec(curVert);
iter = 2;
while(parVec(curVert) ~= 0 && iter <= size(parVec,1))
    parPath(iter,1) = curVert;
    parPath(iter,2) = parVec(curVert);
    iter = iter + 1;
    curVert = parVec(curVert);
end
parPath(iter:end,:) = [];
parPath(:,1) = vertexList(parPath(:,1));
parPath(:,2) = vertexList(parPath(:,2));
EL = zeros(size(parPath,1),1);
for i = 1:length(parPath)
    vertID = parPath(i,1);
    targetID = parPath(i,2);
    for j = 1:records.verts.degree(vertID)
       edgeID = records.verts.edgeIDList(vertID,j);
       if(records.edges.origin(edgeID,2) == targetID)
           EL(i) = records.edges.twinID(edgeID);
       end
    end
end

