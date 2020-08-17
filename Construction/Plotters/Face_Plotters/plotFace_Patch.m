function plotFace_Patch(records, faceStruct, colorVec, patchParams)
if(nargin < 4)
    patchParams = {};
end
if(nargin < 3)
    colorVec = [0,0,0];
end
plotFromEdgeList_Patch(faceStruct,records,colorVec,patchParams);
end