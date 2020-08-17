function plotOutline_ColorByBoundary(records,lineParams,pointParams)
if(nargin < 2 || isempty(lineParams))
    lineParams = {'LineWidth',2};
end
if(nargin < 3 || isempty(pointParams))
    pointParams = {'Marker','.'};
end
plotOutline_Post(records, jet(max(records.inputs(:,2))), lineParams ,pointParams)
end

