function [lineHandle] = plotSubGraph_RootPath(records, cycleInfo, colorMat, lineParams)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth', 1};
end

lineHandle = plotFromEdgeList(cycleInfo.primaryMajAxis.edge, records, 'Color', colorMat, lineParams{:});



end