%Refactorcheccked
function plotVoronoiSkeleton_SingleRegion_Type0(records, regionID, colorMat, colorMat0, lineParams, lineParams0)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',0.5};
end

numObjects = records.numObjects;
numNonHoles = records.numNonHoles;
%%Loop through object index
%%Color by object index
%%Implicit/infintie edges are half brightness
% numT2 = sum(records.edges.edgeType(:)==2);
% numT1 = sum(~(records.edges.edgeType(:) >= 98) & records.edges.edgeType(:) == 0);
% numImplciit = sum(records.edges.edgeType(:) == 0);
% numInfiniteNorm = sum(records.edges.edgeType(:) > 98 & records.edges.edgeType(:) ~= 102);
% numInfiniteParab = sum(records.edges.edgeType(:) == 102);

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
        edgeInGraph = vertListBinary(records.edges.origin(:,1)) & mod(records.edges.twinID(:),2) & vertListBinary(records.edges.origin(:,2)); %hack to get non-twins only
        edgeIDs = 1:size(records.edges.twinID,1);
        plotFromEdgeList_Type0SeperateColor(edgeIDs(edgeInGraph),records, colorMat, colorMat0, lineParams, lineParams0)
        
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
%     if(resetHoldState)
%        hold off;
%     end
end