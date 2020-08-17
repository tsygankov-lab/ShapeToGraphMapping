function [area] = computeFaceArea(records,faceStruct)
%%Resamples loopdata
edgeListSubGraph = faceStruct.Edges;
%%From the plottingCode...
numQuads = sum(records.edges.dist(edgeListSubGraph) > 100*eps & (records.edges.edgeType(edgeListSubGraph) == 2 | records.edges.edgeType(edgeListSubGraph) == 102));
numLin = sum(records.edges.edgeType(edgeListSubGraph) ~= 2 & records.edges.edgeType(edgeListSubGraph) ~= 102 & records.edges.dist(edgeListSubGraph) > 10^-7);
numPoints = nan(2*numLin + 20*numQuads,2);
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
area = polyarea(numPoints(:,1),numPoints(:,2));
end
%