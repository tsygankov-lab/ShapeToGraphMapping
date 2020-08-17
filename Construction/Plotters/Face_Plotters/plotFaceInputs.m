function plotFaceInputs(records, faceStruct, colorVec, lineParams,pointParams)
if(nargin < 5 || isempty(pointParams))
    pointParams = {'Marker','.'};
end
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
if(nargin < 3)
    colorVec = [0,0,0];
end
plotInputs(records, 'InputIdxFilter',faceStruct.Objects,'Color',colorVec,lineParams{:}, pointParams{:});
end