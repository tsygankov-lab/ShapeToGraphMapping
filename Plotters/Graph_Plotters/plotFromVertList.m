%% plotFromVertList - Converts a list of vertices into a list of edges to pass into plotFromEdgeList
%   lineHandle = plotFromVertList(records, vertList, 'Options',...)
%Inputs:
%   records - the Voronoi records struct
%   vertList - either a numerical list of vertex IDs, or a binary vector
%       with the same length as records.verts
%
%   Any parameter for line can be passed to this function as an option
%Outputs:
%   lineHandle, the lineHandle to the plot
%Notes:
%   This function calls plotFromEdgeList
function lineHandle = plotFromVertList(records,vertList,varargin)
    if(length(vertList) ~= records.verts.length)
        vertList_t = false(records.verts.length,1);
        vertList_t(vertList) = true;
        vertList = vertList_t;
    end
    edgeInGraph = vertList(records.edges.origin(:,1)) & vertList(records.edges.origin(:,2)); %needs binary vector.
    edgeIDs = 1:records.edges.length;

    lineHandle = plotFromEdgeList(records, edgeIDs(edgeInGraph), varargin{:});
end