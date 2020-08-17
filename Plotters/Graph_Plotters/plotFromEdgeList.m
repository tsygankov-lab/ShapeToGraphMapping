%% plotFromEdgeList - Plots Edges in the Voronoi Diagram
%   lineHandle = plotFromEdgeList(records, edgeListSubgraph, 'Options',...)
%Inputs:
%   records - the Voronoi records struct
%   edgeListSubgraph - either a numerical list of edge IDs, or a binary
%       vector of the same length as records.edges
%
%   Any parameter for line can be passed to this function as an option
%Outputs:
%   lineHandle - the handle object to the plot
%Notes:
%   This is the base plotting function. Be very careful if modifying.
%
%   This has code to detect the legacy function call in which
%   edgeListSubgraph was passed prior to records. Please use the new
%   standard (Specified in the example function calls) going forward.
function lineHandle = plotFromEdgeList(records, edgeListSubGraph, varargin)
if(isstruct(edgeListSubGraph) && (isnumeric(records) || islogical(recordS)))
   records_t = edgeListSubGraph;
   edgeListSubGraph_t = records;
   records = records_t;
   edgeListSubGraph = edgeListSubGraph_t; %legacy function call...
end
if(islogical(edgeListSubGraph))
    edgeVec = 1:records.edges.length;
    edgeListSubGraph = edgeVec(edgeListSubGraph);
end
numQuads = sum(records.edges.dist(edgeListSubGraph) > 100*eps & (records.edges.edgeType(edgeListSubGraph) == 2 | records.edges.edgeType(edgeListSubGraph) == 102));
numLin = sum(records.edges.edgeType(edgeListSubGraph) ~= 2 & records.edges.edgeType(edgeListSubGraph) ~= 102 & records.edges.dist(edgeListSubGraph) > 10^-7);
numPoints = nan(3*numLin + 21*numQuads,2);
index = 1;
for i = 1:length(edgeListSubGraph)
    edgeID = edgeListSubGraph(i);
    if(records.edges.dist(edgeID) > 10^-7)
        vertA = records.verts.pos(records.edges.origin(edgeID,1),:);
        vertB = records.verts.pos(records.edges.origin(edgeID,2),:);
        if(records.edges.edgeType(edgeID) == 2 || records.edges.edgeType(edgeID) == 102)
            if(abs(vertA(1) - vertB(1)) >= sqrt(eps) || abs(vertA(2) - vertB(2)) >= sqrt(eps))         
            t = linspace(0,1,20);
            pt2 = records.edges.controlPoint(edgeID,:);%edge(10:11); %%control point for bezeir curve
            bCurve = kron((1-t).^2,vertA') + kron(2*(1-t).*t,pt2') + kron(t.^2,vertB');
%             bCurveAlt =  kron((1-t).^2,[vertA(1),vertA(2)]') + kron(2*(1-t).*t,pt2') + kron(t.^2,[vertB(1),vertB(2)]');
            numPoints(index:index+20,:) = [bCurve';nan,nan];
            %pt2test=getBezeir_ARR(lineobj,point,vertA,vertB);

            index=index+21;
            end
        else
            numPoints(index:index+2,:) = [vertA(1),vertA(2);vertB(1),vertB(2);nan,nan];
            index=index+3;
        end
    end
end
lineHandle = line(numPoints(:,1),numPoints(:,2),varargin{:});
% if(resetHoldState)
%     hold off;
% end
end

