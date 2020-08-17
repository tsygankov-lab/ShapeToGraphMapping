function [vertexList,radiusVector] = resamplePath(records,edgeList,desiredStepSize)
%%Resamples loopdata
if(nargin < 3)
    desiredStepSize = 0.1;
end
totalDist = sum(records.edges.dist(edgeList));
cumDist = [cumsum(records.edges.dist(edgeList))];
numSamples = 1;
step = 10000;
while(step > desiredStepSize)
    numSamples = numSamples*2;
    step = totalDist/numSamples;
end

curEdge = 1;
numEdge = length(edgeList);
radiusVector = zeros(numSamples,1);
vertexList = zeros(numSamples,2);
vertexList(1,:) = records.verts.pos(records.edges.origin(edgeList(curEdge),1),:);%records.vorVert(loopStruct.Vertices(1),1:2);
radiusVector(1) = records.verts.rad(records.edges.origin(edgeList(curEdge),1));%records.vorVert(loopStruct.Vertices(1),3);

for i=2:numSamples
    dist = step*i;
    while(dist > cumDist(curEdge))
        curEdge = curEdge + 1;
        if(dist > totalDist || curEdge > numEdge)
            %Kind of unecessary to check both...
            break;
        end
    end
    curEdge_Rec = edgeList(curEdge);
    vertA = records.edges.origin(curEdge_Rec,1);
    vertB = records.edges.origin(curEdge_Rec,2);
    if(curEdge == 1)
        startDist = 0.0;
    else
        startDist = cumDist(curEdge - 1);
    end
    if(records.edges.edgeType(curEdge_Rec) ~= 2 && records.edges.edgeType(curEdge_Rec) ~= 102)%edge(2) ~= 2 && edge(2) ~= 102)
        distDiffA = dist - startDist;
        diffTot = records.edges.dist(curEdge_Rec);
        distRat = distDiffA/diffTot;
        radiusVector(i) = (1-distRat)*records.verts.rad(vertA) + (distRat)*records.verts.rad(vertB);%(1-distRat)*records.vorVert(loopStruct.Vertices(index1),3) + (distRat)*records.vorVert(loopStruct.Vertices(index2),3);
        vertexList(i,:) = (1-distRat).*records.verts.pos(vertA,:) + (distRat).*records.verts.pos(vertB,:);
    else
        intervalDensity = 20;
        t=linspace(0,1,intervalDensity);
%         if(abs(edge(10)) > eps || abs(edge(11)) > eps) Control point can be wherever???????
                        twinEdge = records.edges.twinID(curEdge_Rec);
                        obj1=records.inputs(records.edges.obj(curEdge_Rec),:);%edge(8),:);
                        obj2=records.inputs(records.edges.obj(twinEdge),:);
                        if(obj1(1))
                            pointCorr = obj1(3:4);
                        else
                            pointCorr = obj2(3:4);
                        end
        bCurve = kron((1-t).^2,records.verts.pos(records.edges.origin(curEdge_Rec,1),:)') + kron(2*(1-t).*t,records.edges.controlPoint(curEdge_Rec,:)') + kron(t.^2,records.verts.pos(records.edges.origin(curEdge_Rec,2),:)');
                        distanceDiff = linspace(startDist,cumDist(curEdge),intervalDensity);
        distInc = (cumDist(curEdge) - startDist)/intervalDensity;
        subInd1 = floor((dist-startDist)/distInc);
        subInd2 = ceil((dist-startDist)/distInc);
                if(subInd1 == 0)
            subInd1 = 1;
        end
                        radVec1 = EuclidianDistance2d(bCurve(1,subInd1),pointCorr(1),bCurve(2,subInd1),pointCorr(2));
                        radVec2 = EuclidianDistance2d(bCurve(1,subInd2),pointCorr(1),bCurve(2,subInd2),pointCorr(2));
        %                 if(subInd2 == -1)
        %                     %?????????
        %                     throw(MException('Resample:What','This should not be possible...'));
        %                 elseif(subInd1 == subInd2)
        %                     radiusVector(i) =radVec1;
        %                     vertexList(i,:) = bCurve(:,subInd1)';
        %                 else

        dist1 = distanceDiff(subInd1);
        
        dist2 = distanceDiff(subInd2);
        subdiffTot = dist2 - dist1;
        
        if(subdiffTot < sqrt(eps))
                                    radiusVector(i) = radVec1;
            vertexList(i,:) = bCurve(:,subInd1)';
            
            %distanceDiff(subInd1);
        else
            subdistDiffA = dist - dist1;
            distRat = subdistDiffA/subdiffTot;
                                    radiusVector(i) = (1-distRat)*radVec1 + distRat*radVec2;
            vertexList(i,:) = (1-distRat).*bCurve(:,subInd1)' + distRat.*bCurve(:,subInd2)';
            
        end
        
        %                 end
    end
    
end
vertexList(i+1:end,:) = [];
radiusVector(i+1:end,:) = [];
end
%
% function [index1,index2] = intervalSearch(startPoint,valueVector,value)
% foundFlag = 0;
% for i = startPoint:length(valueVector)-1
%     if(value == valueVector(i))
%         index1 = i;
%         index2 = i;
%         foundFlag = 1;
%         return;
%     elseif(value < valueVector(i+1) && value > valueVector(i))
%         index2 = i+1;
%         index1 = i;
%         foundFlag = 1;
%         return;
%     elseif(value < valueVector(i))
%         throw(MException('IS:NonIncreasingValues','Search array should be monotonically increasing?'));
%     end
% end
% if(~foundFlag)
%     if(value == valueVector(end))
%         index1 = length(valueVector);
%         index2 = length(valueVector);
%     elseif(value > valueVector(end))
%         index1 = length(valueVector);
%         index2 = -1;
%     end
% end
% end
%
