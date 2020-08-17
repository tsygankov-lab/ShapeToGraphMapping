function edgePath = getPathToRoot(records, cycleInfo, startVert, onlyBestPath)
if(nargin < 4 || isempty(onlyBestPath))
    onlyBestPath = 0;
end
    edgePath = [];
    vert = cycleInfo.subgraph2RecordsMap_Vertices(startVert);
    curVert = startVert;
    while(~cycleInfo.isRootNode(vert))
        newEdge = cycleInfo.parEdge(curVert,1);
        edgePath = [edgePath;newEdge];
        vert = records.edges.origin(newEdge,2);
        curVert = cycleInfo.records2SubgraphMap_Vertices(vert);
    end
    
    edgePath_t = [];
if(cycleInfo.parEdge(startVert,2) ~= 0 && ~onlyBestPath)
    terminalVert = vert;
    newEdge = cycleInfo.parEdge(startVert,2);
    edgePath_t = [edgePath_t;newEdge];
    vert = records.edges.origin(newEdge,2);
    curVert = cycleInfo.records2SubgraphMap_Vertices(vert);
    while(~cycleInfo.isRootNode(vert))
            newEdge = cycleInfo.parEdge(curVert,1);
            edgePath_t = [edgePath_t;newEdge];
            vert = records.edges.origin(newEdge,2);
            curVert = cycleInfo.records2SubgraphMap_Vertices(vert);
    end
    if(vert == terminalVert)
        edgePath = unique([edgePath;edgePath_t]);
    end
end
end