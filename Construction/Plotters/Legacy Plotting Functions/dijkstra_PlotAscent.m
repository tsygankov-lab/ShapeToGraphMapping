%%REFACTORCHECK
function dijkstra_PlotAscent(vertexCoor,parList,curVert,lineParams)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
    %xPlot = nan(size(parList,1),3);
    %yPlot = nan(size(parList,1),3);
    validator = 0;
    while(parList(curVert) ~= 0 && validator < size(parList,1))
        line([vertexCoor(curVert,1);vertexCoor(parList(curVert),1)],[vertexCoor(curVert,2);vertexCoor(parList(curVert),2)],lineParams{:});
        curVert = parList(curVert);
    end

end