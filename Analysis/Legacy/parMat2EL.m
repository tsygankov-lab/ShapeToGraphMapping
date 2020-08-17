function [EL] = parMat2EL(records,vertexList,parVec)
%%Given the Dijkstras output, creates list of edges forming the resulting
%%tree/path
parMat = [vertexList,parVec];
parMat(parMat(:,2)==0,:) = [];
parMat(:,2) = vertexList(parMat(:,2));
EL = zeros(size(parMat,1),1);
for i = 1:length(parMat)
    vertID = parMat(i,1);
    targetID = parMat(i,2);
    for j = 1:records.verts.degree(vertID)
       edgeID = records.verts.edgeIDList(vertID,j);
       if(records.edges.origin(edgeID,2) == targetID)
           EL(i) = records.edges.twinID(edgeID);
       end
    end
end

