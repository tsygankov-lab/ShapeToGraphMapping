%Refactorcheccked
function plotVoronoiSkeleton(records, uniformColor, colorMat, subCycleFlag, insideOnly,lineParams)
if(nargin < 4)
    subCycleFlag = 0;
    insideOnly = 0;
end
if(nargin < 6 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end
% resetHoldState = 0;
% if(ishold == 0)
%     cla;
%     resetHoldState = 1;
%     hold on;
% end

%%Loop through object index
%%Color by object index
%%Implicit/infintie edges are half brightness
% numT2 = sum(records.edges.edgeType(:)==2);
% numT1 = sum(~(records.edges.edgeType(:) >= 98) & records.edges.edgeType(:) == 0);
% numImplciit = sum(records.edges.edgeType(:) == 0);
% numInfiniteNorm = sum(records.edges.edgeType(:) > 98 & records.edges.edgeType(:) ~= 102);
% numInfiniteParab = sum(records.edges.edgeType(:) == 102);

%%Alt method - see if either edge has the correct color, then see if the origins are in the correct area
if(subCycleFlag)
    numObjects = records.numObjects;
    adjMat = records.adjMat;
    numNonHoles = records.numNonHoles;
    plotNum = 1;
    if(insideOnly)
        numColors = records.numNonHoles + sum(sum(records.adjMat(1:records.numObjects,1:records.numNonHoles)));
    else
    numColors = numObjects + 1 + sum(sum(records.adjMat));
    end
    if(~uniformColor)
        colorMat = jet(numColors);
    else
        colorMat = repmat(colorMat,numColors);
    end
    for i = 1:numObjects + 1
        if(i == numObjects + 1)
            objInd = 0;
            enclosingBoundaries = [];
            enclosedBoundaries = [];
        else
            objInd = i;
            enclosedBoundaries = find(adjMat(:,i));
            enclosingBoundaries = find(adjMat(i,:));
        end
        if(i == numObjects + 1 && insideOnly ~= 1)
            vertList_Binary = records.verts.borderRegions(:,2) == 0;
            plotVoronoiSubGraph_vertList(records,vertList_Binary,colorMat(1,:),lineParams);
%             plotNum = plotNum + 1;
        elseif(i > numNonHoles)
            if(insideOnly ~= 2)
            for j = 1:length(enclosingBoundaries)
                vertList_Binary = records.verts.borderRegions(:,1) == enclosingBoundaries(j) & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
                plotVoronoiSubGraph_vertList(records,vertList_Binary, colorMat(plotNum,:),lineParams);
                plotNum = plotNum + 1;
            end
            end
            if(insideOnly ~= 1)
                vertList_Binary = records.verts.borderRegions(:,2) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
                plotVoronoiSubGraph_vertList(records,vertList_Binary, colorMat(plotNum+1,:),lineParams);
                plotNum = plotNum + 1;
            end
        else
            if(insideOnly ~= 1)
            for j = 1:length(enclosingBoundaries)
                vertList_Binary = records.verts.borderRegions(:,2) == enclosingBoundaries(j) & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
                plotVoronoiSubGraph_vertList(records,vertList_Binary, colorMat(plotNum+1,:),lineParams);
                plotNum = plotNum + 1;
            end
            end
            if(insideOnly ~=2)
            vertList_Binary = records.verts.borderRegions(:,1) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
            plotVoronoiSubGraph_vertList(records,vertList_Binary, colorMat(plotNum,:),lineParams);
            plotNum = plotNum + 1;
            end
        end
    end

        
        
else
    if(insideOnly)
        maxLimit = records.numNonHoles;
    else
        maxLimit = records.numObjects + 1;
    end
    if(~uniformColor)
        colorMat = jet(maxLimit);
    else
        colorMat = repmat(colorMat,maxLimit,1);
    end

    for i = 1:maxLimit
        if(i == records.numObjects + 1)
            objInd = 0;
        else
            objInd = i;
        end
        if(i > records.numNonHoles)
            vertListBinary = records.verts.borderRegions(:,2) == objInd;
            region = 2;
        else
            vertListBinary = records.verts.borderRegions(:,1) == objInd;
            region = 1;
        end
        vec = 1:length(records.edges.length);
        edgeInGraph = vertListBinary(records.edges.origin(:,1)) & vertListBinary(records.edges.origin(:,2)) & (records.edges.twinID(:) > vec); %hack to get non-twins only
        edgeIDs = 1:size(records.edges.twinID,1);
        plotFromEdgeList(edgeIDs(edgeInGraph),records, colorMat(i,:),lineParams);
        
        %isNotPlotted = ones(2,size(records.halfEdge,1));
        %vorVertNorm = nan(3,3*numT2 + 21*numT1); %%Do not have a way to track numbers of types of edges... yet
        %vorVertImplicit = nan(3,3*numImplciit + 3*numInfiniteNorm + 21*numInfiniteParab);
        %vorVertVertex = nan(3,2*size(vertList,1));
        
        %spacerT01 = 3;
        %spacerT2 = 21;
        %vorVertNormStart = 1;
        %vorVertImplicitStart = 1;
        %vorVertVertexStart = 1;
        %for j = 1:size(vertList,1)
        %    [isNotPlotted, vorVertNorm, vorVertImplicit, vorVertNormStart, vorVertImplicitStart, vorVertVertex, vorVertVertexStart] = plotVorVertsWithEdges_arrayInput(vertList(j,:), records, flag, objInd, isNotPlotted, vorVertNorm, vorVertImplicit, vorVertNormStart, vorVertImplicitStart, vorVertVertex, vorVertVertexStart);
        %end
        %             if(tdFlag)
        %                 plot3(vorVertNorm(1,:),vorVertNorm(2,:)
        %
        %             else
        %line(vorVertNorm(1,:),vorVertNorm(2,:),'Color',colorMat(i,:),'LineWidth',0.1);
        %line(vorVertImplicit(1,:),vorVertImplicit(2,:),'Color',colorMat(i,:)*.5,'LineWidth',0.1);
        %             end
        %if(i <= numNonHoles)
        %    line(vorVertVertex(1,:),vorVertVertex(2,:),'LineStyle','none','Marker','.','Color',colorMat(i,:),'MarkerEdgeColor',colorMat(i,:),'MarkerSize',1.2,'MarkerFaceColor',colorMat(i,:));
        %else
        %    line(vorVertVertex(1,:),vorVertVertex(2,:),'LineStyle','none','Marker','.','Color',colorMat(i,:),'MarkerEdgeColor',colorMat(i,:),'MarkerSize',1.2,'MarkerFaceColor',colorMat(i,:));
        %end
    end
    %if(resetHoldState)
    %    hold off;
    %end
end