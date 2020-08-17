%Depreciated (thank god)
function [isNotPlotted, vorVertNorm, vorVertImplicit, vorVertNormStart, vorVertImplicitStart, vorVertVertex, vorVertVertexStart] = plotVorVertsWithEdges_arrayInput(vertexArray, records, inObjectFlag, colorFlag, isNotPlotted, vorVertNorm, vorVertImplicit, vorVertNormStart, vorVertImplicitStart, vorVertVertex, vorVertVertexStart)

% plot(voronoiVertex.corr(1),voronoiVertex.corr(2),'Color',colorVERT,'Marker','*');
if(inObjectFlag)
    coInd = 4;
else
    coInd = 5;
end
    vorVertVertex(:,vorVertVertexStart) = [vertexArray(1);vertexArray(2);vertexArray(3)];
    vorVertVertexStart = vorVertVertexStart + 1;
    %     plot(voronoiVertex.corr(1),voronoiVertex.corr(2),'Color',colorVERT,'Marker','.');
for i = 1:vertexArray(8)
    %     voronoiVertex.edge{i}.VERTEX_SET
    %     voronoiVertex.edge{i}.Twin.VERTEX_SET
    if(isNotPlotted(vertexArray(8+i)))
        edge = records.halfEdge(vertexArray(8+i),:);
        twinEdge = records.halfEdge(edge(1),:);
        vertA = records.vorVert(edge(3),:);
        vertB = records.vorVert(twinEdge(3),:);

        if(vertA(coInd) == colorFlag && vertB(coInd) == colorFlag)

            if(edge(2)==-1 || edge(2)==99) %%Cannot recall what type of edge this is...
                if(voronoiVertex.edge{i}.edgeType==-1)
                        vorVertNorm(:,vorVertNormStart:vorVertNormStart+1) = [vertA(1),vertB(1);vertA(2),vertB(2);vertA(3),vertB(3)];
                        vorVertNormStart = vorVertNormStart + 3;
                else
                    vorVertImplicit(:,vorVertImplicitStart:vorVertImplicitStart+1)=[vertA(1),vertB(1);vertA(2),vertB(2);vertA(3),vertB(3)];
                    vorVertImplicitStart = vorVertImplicitStart + 3;
                end
            elseif(edge(2)==1 || edge(2)==101)
                if(edge(2) == 1)
                        vorVertNorm(:,vorVertNormStart:vorVertNormStart+1) = [vertA(1),vertB(1);vertA(2),vertB(2);vertA(3),vertB(3)];
                        vorVertNormStart = vorVertNormStart + 3;
                else
                    vorVertImplicit(:,vorVertImplicitStart:vorVertImplicitStart+1)=[vertA(1),vertB(1);vertA(2),vertB(2);vertA(3),vertB(3)];
                    vorVertImplicitStart = vorVertImplicitStart + 3;
                end
            elseif(edge(2)==0 || edge(2)==100)
                    vorVertImplicit(:,vorVertImplicitStart:vorVertImplicitStart+1)=[vertA(1),vertB(1);vertA(2),vertB(2);vertA(3),vertB(3)];
                    vorVertImplicitStart = vorVertImplicitStart + 3;
            elseif(edge(2)==2 || edge(2) == 102)
                if(abs(vertA(1) - vertB(1)) >= sqrt(eps) || abs(vertA(2) - vertB(2)) >= sqrt(eps))
                    obj1=records.input(edge(8),:);
                    obj2=records.input(twinEdge(8),:);
                    if(obj1(1)) %%Object 1 is the point
                        line = records.edgeSup(twinEdge(8) - records.numInputVerts,:);
                        point = obj1;
                    else
                        line = records.edgeSup(edge(8) - records.numInputVerts,:);
                        point = obj2;
                    end
                    pt2=getBezeir_ARR(line,point,vertA,vertB);
                    t=linspace(0,1,20);
                    
                    bCurve = kron((1-t).^2,[vertA(1),vertA(2)]') + kron(2*(1-t).*t,pt2') + kron(t.^2,[vertB(1),vertB(2)]');
                    if(edge(2)==2)  
                            vorVertNorm(:,vorVertNormStart:vorVertNormStart+19) = [bCurve;sqrt((bCurve(1,:) - repmat(point(3),size(bCurve(1,:)))).^2 + (bCurve(2,:) - repmat(point(4),size(bCurve(2,:)))).^2)];
                            vorVertNormStart = vorVertNormStart + 21;
                    else
                        vorVertImplicit(:,vorVertImplicitStart:vorVertImplicitStart+19) = [bCurve;sqrt((bCurve(1,:) - repmat(point(3),size(bCurve(1,:)))).^2 + (bCurve(2,:) - repmat(point(4),size(bCurve(2,:)))).^2)];
                        vorVertImplicitStart = vorVertImplicitStart + 21;
                    end
                end
            end
        end
    end
        isNotPlotted(vertexArray(8+i)) = 0;
        isNotPlotted(records.halfEdge(vertexArray(8+1),1)) = 0;
end
