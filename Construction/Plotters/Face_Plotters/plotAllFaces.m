%%REFACTORCHECK
function plotAllFaces(records, lineParams)
% if(nargin < 2)
%     contractionOffset = 0;
% end
if(nargin < 2 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
colorMat = jet(length(records.Faces));
for i = 1:length(records.Faces)
   plotFace(records, records.Faces(i), colorMat(i,:),lineParams);
end