function plotFace(records, faceStruct, colorVec, lineParams)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
if(nargin < 3 || isempty(colorVec))
    colorVec = [0,0,1];
end
for i = 1:faceStruct.subFaces
    edges = faceStruct.Edges(faceStruct.FaceStartingIndex(i):faceStruct.FaceEndingIndex(i) - ~faceStruct.Finite(i));
    plotFromEdgeList(edges,records,colorVec,lineParams);
end
end