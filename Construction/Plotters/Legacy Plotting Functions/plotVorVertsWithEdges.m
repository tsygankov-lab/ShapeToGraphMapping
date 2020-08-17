function [isNotPlotted, vorVertT0, vorVertTN1, vorVertT1, vorVertT2, vorVertVertex, vorVertInf0,vorVertInf1,vorVertInf2,vorVertInfN1, vorVertNull, vorVertT0Start, vorVertT1Start, vorVertT2Start,vorVertTN1Start,vorVertVertexStart,vorVertInf0Start,vorVertInf1Start,vorVertInf2Start,vorVertInfN1Start,vorVertNullStart] = plotVorVertsWithEdges(voronoiVertex, isNotPlotted, NumberVertexPoints,ImageMask,nullifyVertices,vorVertT0, vorVertTN1, vorVertT1, vorVertT2, vorVertVertex, vorVertInf0,vorVertInf1,vorVertInf2,vorVertInfN1, vorVertNull, vorVertT0Start, vorVertT1Start, vorVertT2Start, vorVertTN1Start,vorVertVertexStart, vorVertInf0Start,vorVertInf1Start,vorVertInf2Start,vorVertInfN1Start, vorVertNullStart, spacerT01, spacerT2)

% plot(voronoiVertex.corr(1),voronoiVertex.corr(2),'Color',colorVERT,'Marker','*');
if(NumberVertexPoints)
    text(voronoiVertex.corr(1),voronoiVertex.corr(2),num2str(voronoiVertex.eventLog),'Color','w');
else
    vorVertVertex(:,vorVertVertexStart) = [voronoiVertex.corr(1);voronoiVertex.corr(2)];
    vorVertVertexStart = vorVertVertexStart + 1;
    %     plot(voronoiVertex.corr(1),voronoiVertex.corr(2),'Color',colorVERT,'Marker','.');
end
for i = 1:voronoiVertex.degree
    %     voronoiVertex.edge{i}.VERTEX_SET
    %     voronoiVertex.edge{i}.Twin.VERTEX_SET
    if(isNotPlotted(voronoiVertex.edge{i}.ID))
        if(voronoiVertex.edge{i}.COMPLETE_EDGE)
            vertA = voronoiVertex.edge{i}.Origin;
            vertB = voronoiVertex.edge{i}.Twin.Origin;
            if(voronoiVertex.edge{i}.edgeType==-1 || voronoiVertex.edge{i}.edgeType==99)
                if(voronoiVertex.edge{i}.edgeType==-1)
                    if(nullifyVertices)
                        if(vertB.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                        elseif(vertA.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2)));
                            catch
                                inShape = 0;
                            end
                        else
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2))) && ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                        end
                        if(~inShape)
                            vorVertNull = [vorVertNull,[vertA.corr(1);vertA.corr(2)],[vertB.corr(1);vertB.corr(2)],[NaN;NaN]];
                        else
                            vorVertTN1(:,vorVertT1Start:vorVertT1Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                            vorVertT1Start = vorVertT1Start + spacerT01;
                        end
                    else
                        vorVertTN1(:,vorVertT1Start:vorVertT1Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                        vorVertT1Start = vorVertT1Start + spacerT01;
                    end
                    
                else
                    vorVertInf1(:,vorVertInf1Start:vorVertInf1Start+1)=[vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                    vorVertInf1Start = vorVertInf1Start + spacerT01;
                end
            end
            if(voronoiVertex.edge{i}.edgeType==1 || voronoiVertex.edge{i}.edgeType==101)
                if(voronoiVertex.edge{i}.edgeType==1)
                    
                    if(nullifyVertices)
                        if(vertB.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                        elseif(vertA.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2)));
                            catch
                                inShape = 0;
                            end
                        else
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2))) && ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                        end
                        if(~inShape)
                            vorVertNull = [vorVertNull,[vertA.corr(1);vertA.corr(2)],[vertB.corr(1);vertB.corr(2)],[NaN;NaN]];
                        else
                            vorVertT1(:,vorVertT1Start:vorVertT1Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                            vorVertT1Start = vorVertT1Start + spacerT01;
                        end
                    else
                        
                        
                        vorVertT1(:,vorVertT1Start:vorVertT1Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                        vorVertT1Start = vorVertT1Start + spacerT01;
                    end
                    
                else
                    vorVertInf1(:,vorVertInf1Start:vorVertInf1Start+1)=[vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                    vorVertInf1Start = vorVertInf1Start + spacerT01;
                end
                
                
                %             plot([vertA.corr(1), vertB.corr(1)],[vertA.corr(2),vertB.corr(2)],'Color',colorEDGE);
            elseif(voronoiVertex.edge{i}.edgeType==0 || voronoiVertex.edge{i}.edgeType==100)

                if(voronoiVertex.edge{i}.edgeType==0)
                    if(nullifyVertices)
                        if(vertB.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                        elseif(vertA.vertexCoorID == -1)
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2)));
                            catch
                                inShape = 0;
                            end
                        else
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2))) && ImageMask(round(vertB.corr(1)),round(vertB.corr(2))); 
                            catch
                                inShape = 0;
                            end
                        end
                        
                        if(~inShape)
                            vorVertNull = [vorVertNull,[vertA.corr(1);vertA.corr(2)],[vertB.corr(1);vertB.corr(2)],[NaN;NaN]];
                        else
                            vorVertT0(:,vorVertT0Start:vorVertT0Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                            vorVertT0Start = vorVertT0Start + spacerT01;
                        end
                    else
                        
                        vorVertT0(:,vorVertT0Start:vorVertT0Start+1) = [vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                        vorVertT0Start = vorVertT0Start + spacerT01;
                    end
                else
                    vorVertInf0(:,vorVertInf0Start:vorVertInf0Start+1)=[vertA.corr(1),vertB.corr(1);vertA.corr(2),vertB.corr(2)];
                    vorVertInf0Start = vorVertInf0Start + spacerT01;
                end
                %             plot([vertA.corr(1), vertB.corr(1)],[vertA.corr(2),vertB.corr(2)],'-','Color',colorIMPLICIT);
            elseif(voronoiVertex.edge{i}.edgeType==2 || voronoiVertex.edge{i}.edgeType == 102)
                if(abs(vertA.corr(1) - vertB.corr(1)) >= sqrt(eps) || abs(vertA.corr(2) - vertB.corr(2)) >= sqrt(eps))
                    obj1=voronoiVertex.edge{i}.adjacentFace.siteObject;
                    obj2=voronoiVertex.edge{i}.Twin.adjacentFace.siteObject;
                    if(obj1.isLine)
                        line = obj1;
                        point = obj2;
                    else
                        line = obj2;
                        point = obj1;
                    end
                    pt2=getBezeir(line,point,vertA.corr,vertB.corr);
                    t=linspace(0,1,20);
                    
                    bCurve = kron((1-t).^2,vertA.corr') + kron(2*(1-t).*t,pt2') + kron(t.^2,vertB.corr');
                    if(voronoiVertex.edge{i}.edgeType==2)
                        
                        if(nullifyVertices)
                            try
                                inShape = ImageMask(round(vertA.corr(1)),round(vertA.corr(2))) && ImageMask(round(vertB.corr(1)),round(vertB.corr(2)));
                            catch
                                inShape = 0;
                            end
                            if(~inShape)
                                vorVertNull = [vorVertNull,[bCurve],[NaN;NaN]];
                            else
                                vorVertT2(:,vorVertT2Start:vorVertT2Start+spacerT2-2) = [bCurve];
                                vorVertT2Start = vorVertT2Start + spacerT2;
                            end
                        else
                            
                            
                            
                            vorVertT2(:,vorVertT2Start:vorVertT2Start+spacerT2-2) = [bCurve];
                            vorVertT2Start = vorVertT2Start + spacerT2;
                        end
                    else
                        vorVertInf2(:,vorVertInf2Start:vorVertInf2Start+spacerT2-2) = [bCurve];
                        vorVertInf2Start = vorVertInf2Start + spacerT2;
                    end
                end
                %             plot(bCurve(1,:),bCurve(2,:),'Color',colorEDGE);
            end
        end
        isNotPlotted(voronoiVertex.edge{i}.ID) = 0;
        isNotPlotted(voronoiVertex.edge{i}.Twin.ID) = 0;
        
    end
end
