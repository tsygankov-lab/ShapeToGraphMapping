%Refactorcheccked
function lineHandle = plotVoronoiSkeleton_SingleRegion(records, regionID, color, linespec)
if(nargin < 4)
    linespec = {};
end
lineHandle = plotRegion(records, regionID, 'Color', color, linespec{:});

end