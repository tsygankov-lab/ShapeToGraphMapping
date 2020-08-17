%%REFACTORCHECK
function dijkstra_PlotTree(vertexCoor,parList,lineParams)
if(nargin < 3 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
    xPlot = nan(size(parList,1),3);
    yPlot = nan(size(parList,1),3);
    for i = 1:size(xPlot,1)
        if(parList(i) ~= 0)
            xPlot(i,:) = [vertexCoor(i,1),vertexCoor(parList(i),1),nan];
            yPlot(i,:) = [vertexCoor(i,2),vertexCoor(parList(i),2),nan];
        end
    end
    line(xPlot',yPlot',lineParams{:});

end