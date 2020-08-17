%% plotFullDiagram - Plots the full Voronoi diagram. 
%   plotFullDiagram(records)
%   lineHandle = plotFullDiagram(records,'Options',...)
%   lineHandle = plotFullDiagram(records, inGraph,'Options',...)
%Required Inputs:
%   records - the Voronoi records structure
%Parameters:
%   'inGraph' (default, [])
%       0 - Plots the outgraph only
%       1 - Plots the ingraph only
%       Empty or any other value - Plots Everything
%   
%   Any valid parameter to 'line' can be passed as a parameter
%Outputs:
%   lineHandle - The linehandle to the plot.
function lineHandle = plotFullDiagram(records, varargin)
p = inputParser;
p.KeepUnmatched = true;
addOptional(p,'inGraph',[]);
parse(p, varargin{:})
inp = p.Results;


if(inp.inGraph == 0) %outgraph
    vertListBinary = records.verts.locationType(:) == 0 | records.verts.locationType(:) == 2;
    lineHandle = plotFromVertList(records, vertListBinary,p.Unmatched);
elseif(inp.inGraph == 1) %ingraph
    vertListBinary = records.verts.locationType(:) == 1 | records.verts.locationType(:) == 2;
    lineHandle = plotFromVertList(records, vertListBinary,p.Unmatched);
else %everything
    lineHandle = plotFromEdgeList(records,1:records.edges.length, p.Unmatched);
end

end