%% plotRegion - Plots the Voronoi diagram within a region
% plotRegion(records, regionID)
% lineHandle = plotRegion(records, regionID, varargin{:})
%Required Inputs:
%   records - the Voronoi records structure
%   regionID - a numerical value specifying a region to plot.
%Outputs:
%   lineHandle - the handle object tot he plot
function lineHandle = plotRegion(records, regionID, varargin)
numObjects = records.numObjects;
numNonHoles = records.numNonHoles;

i = regionID;
if(i == numObjects + 1)
    objInd = 0;
else
    objInd = i;
end
if(i > numNonHoles)
    vertListBinary = records.verts.borderRegions(:,2) == objInd;
    region = 2;
else
    vertListBinary = records.verts.borderRegions(:,1) == objInd;
    region = 1;
end
edgeInGraph = vertListBinary(records.edges.origin(:,1)) & mod(records.edges.twinID(:),2) & vertListBinary(records.edges.origin(:,2)); %hack to get non-twins only
lineHandle = plotFromEdgeList(records, edgeInGraph, varargin{:});

end