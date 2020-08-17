function [EL] = vertices2EL_Path(records,vertexList)
% vertExists = false(records.verts.length,1);
% vertExists(vertexList) = true;
EL = zeros(length(vertexList) - 1,1);
edgeCounter = 1;
for i = 1:length(vertexList) - 1
    id = vertexList(i);
    deg = records.verts.degree(id);
    for j = 1:deg
        edgeID = records.verts.edgeIDList(id,j);
        otherPoint = records.edges.origin(edgeID,2);
        if(otherPoint == vertexList(i+1))
            EL(edgeCounter) = edgeID;
            edgeCounter = edgeCounter+1;
        end
    end
end
EL(edgeCounter:end) = [];