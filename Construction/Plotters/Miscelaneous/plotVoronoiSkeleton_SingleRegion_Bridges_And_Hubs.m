% This is a function to plot bridges and hubs.
function plotVoronoiSkeleton_SingleRegion_Bridges_And_Hubs(records, regionID, colorMat, colorMatHub, lineParams, mkrParams)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',0.5};
end

numObjects = records.numObjects;
numNonHoles = records.numNonHoles;

%%Alt method - see if either edge has the correct color, then see if the origins are in the correct area

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
        edgeInGraph = vertListBinary(records.edges.origin(:,1)) & vertListBinary(records.edges.origin(:,2)); 
        edgeInGraph = edgeInGraph & records.edges.color(:) ~= records.edges.color(records.edges.twinID(:)); % Edge in graph and color does not match twin = BRIDGE
        edgeIDs = 1:size(records.edges.twinID,1);
        plotFromEdgeList(edgeIDs(edgeInGraph),records, 'Color', colorMat, lineParams{:})
        
        
        isHub = vertListBinary & records.verts.color(:,1) ~= records.verts.color(:,2) & records.verts.color(:, 2) ~= records.verts.color(:, 3) & records.verts.color(:, 1) ~= records.verts.color(:,3); %all three objects have different colors = HUB
        vertIDs = 1:records.verts.length;
        xPos = nan(sum(isHub)*2,1);
        yPos = xPos;
        xPos(1:2:end-1) = records.verts.pos(vertIDs(isHub),1);
        yPos(1:2:end-1) = records.verts.pos(vertIDs(isHub),2);
        line(xPos,yPos,'MarkerEdgeColor', colorMatHub, 'MarkerFaceColor', colorMatHub, mkrParams{:});

end