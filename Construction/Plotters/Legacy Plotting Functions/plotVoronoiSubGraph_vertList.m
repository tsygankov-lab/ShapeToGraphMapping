  %function plotVoronoiSubGraph_vertList(vertList,logicalVertFilter, records,colorMatNorm, colorMatImplicit)
  function lineHandle = plotFromVertList(records,vertList,varargin)
    if(length(vertList) ~= records.verts.length)
        vertList_t = false(records.verts.length,1);
        vertList_t(vertList) = true;
        vertList = vertList_t;
    end
    edgeInGraph = vertList(records.edges.origin(:,1)) & vertList(records.edges.origin(:,2)); %needs binary vector.
    edgeIDs = 1:records.edges.length;

    lineHandle = plotFromEdgeList(edgeIDs(edgeInGraph),records,varargin{:});

end