function simplePathPlot(records,orderedVertIDs,lineParams)
if(nargin < 2 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
line(records.verts.pos(orderedVertIDs,1),records.verts.pos(orderedVertIDs,2),lineParams{:});
end