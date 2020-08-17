%%REFACTORCHECK
function plotAllFaceInputs(records,lineParams,pointParams)
if(nargin < 2 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
if(nargin < 3 || isempty(pointParams))
    pointParams = {'Marker','.'};
end
hold on;
colorMat = jet(length(records.Faces));
for i = 1:length(records.Faces)
   plotFaceInputs(records, records.Faces(i), colorMat(i,:),lineParams,pointParams);
end