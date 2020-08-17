%%refactor check
function plotFromEdgeList_Patch(face,records,colorMat, patchParams)
% edgeListSubGraph = face.Edges;
if(nargin < 4 || isempty(patchParams))
    patchParams = {'LineStyle','-'};
end
% if(peturbNormDirBy
%%Assumes no half edge twins.  At worst, this will just leave to each half
%%edge being plotted twice
resetHoldState = 0;
if(ishold == 0)
    cla;
    resetHoldState = 1;
    hold on;
end
%Workaround investigate later...
for i = 1:length(face.FaceStartingIndex)%(face.subFaces)
    edgeListFilt = face.Edges(face.FaceStartingIndex(i):face.FaceEndingIndex(i) - ~face.Finite(i));
    numQuads = sum(records.edges.dist(edgeListFilt) > 100*eps & (records.edges.edgeType(edgeListFilt) == 2 | records.edges.edgeType(edgeListFilt) == 102));
    numLin = sum(records.edges.edgeType(edgeListFilt) ~= 2 & records.edges.edgeType(edgeListFilt) ~= 102 & records.edges.dist(edgeListFilt) > 10^-7);
    numPoints = nan(2*numLin + 20*numQuads,2);
    index = 1;
    for k = 1:length(edgeListFilt)
        edgeID = edgeListFilt(k);
        if(records.edges.dist(k) > 10^-7)
            vertA = records.verts.pos(records.edges.origin(edgeID,1),:);
            vertB = records.verts.pos(records.edges.origin(edgeID,2),:);
            if(records.edges.edgeType(edgeID) == 2 || records.edges.edgeType(edgeID) == 102)
                if(abs(vertA(1) - vertB(1)) >= sqrt(eps) || abs(vertA(2) - vertB(2)) >= sqrt(eps))         
                t = linspace(0,1,20);
                pt2 = records.edges.controlPoint(edgeID,:);%edge(10:11); %%control point for bezeir curve
                bCurve = kron((1-t).^2,vertA') + kron(2*(1-t).*t,pt2') + kron(t.^2,vertB');
    %             bCurveAlt =  kron((1-t).^2,[vertA(1),vertA(2)]') + kron(2*(1-t).*t,pt2') + kron(t.^2,[vertB(1),vertB(2)]');
                numPoints(index:index+19,:) = [bCurve'];
                %pt2test=getBezeir_ARR(lineobj,point,vertA,vertB);

                index=index+20;
                end
            else
                numPoints(index:index+1,:) = [vertA(1),vertA(2);vertB(1),vertB(2)];
                index=index+2;
            end
        end
    end
    numPoints(index:end,:) = [];
    if(~face.Finite)
        numPoints = [numPoints;records.verts.pos(face.Vertices(end),1:2)];
    end
    patch(numPoints(:,1),numPoints(:,2),colorMat,patchParams{:});
end
if(resetHoldState)
    hold off;
end
end

