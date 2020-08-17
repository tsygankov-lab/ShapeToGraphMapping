function simplePathPlot_Boundary(records,orderedVertIDs,lineParams)
if(nargin < 2 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
idvec = 1:length(records.input);
idFilt = idvec(orderedVertIDs);
idFilt(end+1) = idFilt(1);
line(records.input(idFilt,3),records.input(idFilt,4),lineParams{:});
end