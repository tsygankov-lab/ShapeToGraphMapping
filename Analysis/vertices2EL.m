function [EL] = vertices2EL(records,vertexList)
vertExists = false(records.verts.length,1);
vertExists(vertexList) = true;
EL = zeros(3*length(vertexList),1);
edgeCounter = 1;
for i = 1:length(vertexList)
    id = vertexList(i);
    deg = records.verts.degree(id);
    for j = 1:deg
        edgeID = records.verts.edgeIDList(id,j);
        otherPoint = records.edges.origin(edgeID,2);
        if(vertExists(otherPoint))
            EL(edgeCounter) = edgeID;
            edgeCounter = edgeCounter+1;
        end
    end
end
EL(edgeCounter:end) = [];