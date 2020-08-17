%Pretty much only to generate figures...
function lineHandle = plotFromEdgeList_Type0SeperateColor(edgeListSubGraph,records,colorMat, colorMat0, lineParams, lineParams0)
% if(nargin < 4 || isempty(lineParams))
%     lineParams = {'LineWidth',1};
%     %     if(ishold)
%     %         figHandle = gca;
%     %     else
%     %         figHandle = figure;
%     %     end
% end
% if(peturbNormDirBy
%%Assumes no half edge twins.  At worst, this will just leave to each half
%%edge being plotted twice
% resetHoldState = 0;
% if(ishold == 0)
%     cla;
%     resetHoldState = 1;
%     hold on;
% end
numQuads = sum(records.edges.dist(edgeListSubGraph) > 100*eps & (records.edges.edgeType(edgeListSubGraph) == 2 | records.edges.edgeType(edgeListSubGraph) == 102));
numLin = sum(records.edges.edgeType(edgeListSubGraph) ~= 2 & records.edges.edgeType(edgeListSubGraph) ~= 102 & records.edges.edgeType(edgeListSubGraph) ~= 0 & records.edges.dist(edgeListSubGraph) > 10^-7);
numZero = sum(records.edges.edgeType(edgeListSubGraph) == 0);
numPoints = nan(3*numLin + 21*numQuads,2);
numZeros = nan(3*numZero,2);
index = 1;
index0 = 1;
for i = 1:length(edgeListSubGraph)
    edgeID = edgeListSubGraph(i);
    if(records.edges.dist(edgeID) > 10^-7)
        vertA = records.verts.pos(records.edges.origin(edgeID,1),:);
        vertB = records.verts.pos(records.edges.origin(edgeID,2),:);
        if(records.edges.edgeType(edgeID) ~= 0)
            
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
        else
            numZeros(index0:index0+2,:) = [vertA(1),vertA(2);vertB(1),vertB(2);nan,nan];
            index0 = index0 + 3;
        end
    end
    
    
end
lineHandle = line(numPoints(:,1),numPoints(:,2),'color',colorMat,lineParams{:});
lineHandle0 = line(numZeros(:,1),numZeros(:,2),'color',colorMat0, lineParams0{:});
% if(resetHoldState)
%     hold off;
% end
end

