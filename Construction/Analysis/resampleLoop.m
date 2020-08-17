%refactor checked
function recycledLoopData = resampleLoop(loopStruct, records, desiredStepSize)
%%Resamples loopdata
if(nargin < 3)
    desiredStepSize = 0.5;
end

numSamples = 1;
step = 10000;
while(step > desiredStepSize)
    numSamples = numSamples*2;
    step = loopStruct.totalDistance/numSamples;
end

startPoint = 1;
radiusVector = zeros(numSamples,1);
vertexList = zeros(numSamples,2);
vertexList(1,:) = records.verts.pos(loopStruct.Vertices(1),:);%records.vorVert(loopStruct.Vertices(1),1:2);
radiusVector(1) = records.verts.rad(loopStruct.Vertices(1));%records.vorVert(loopStruct.Vertices(1),3);

for i=2:numSamples
    dist = step*i;
    [index1,index2] = intervalSearch(startPoint,loopStruct.distance,dist);
    startPoint = index1;
    if(index1 == index2)
        radiusVector(i) = records.verts.rad(loopStruct.Vertices(index1));%records.vorVert(loopStruct.Vertices(index1),3);
        vertexList(i,:) = records.verts.pos(loopStruct.Vertices(index1),:);%records.vorVert(loopStruct.Vertices(index1),1:2);
    else
        distA = loopStruct.distance(index1);
        if(index2 == -1)
            distB = loopStruct.totalDistance;
            index2 = 1;
        else
            distB = loopStruct.distance(index2);
        end
        
        edge = loopStruct.EL(index1);%records.halfEdge(loopStruct.EL(index1),:);
        if(records.edges.edgeType(edge) ~= 2 && records.edges.edgeType(edge) ~= 102)%edge(2) ~= 2 && edge(2) ~= 102)
            distDiffA = dist - distA;
            diffTot = distB - distA;
            distRat = distDiffA/diffTot;
            radiusVector(i) = (1-distRat)*records.verts.rad(loopStruct.Vertices(index1)) + (distRat)*records.verts.rad(loopStruct.Vertices(index2));%(1-distRat)*records.vorVert(loopStruct.Vertices(index1),3) + (distRat)*records.vorVert(loopStruct.Vertices(index2),3);
            vertexList(i,:) = (1-distRat).*records.verts.pos(loopStruct.Vertices(index1),:) + (distRat).*records.verts.pos(loopStruct.Vertices(index2),:);
        else
            intervalDensity = 20;
            t=linspace(0,1,intervalDensity);
            %if(abs(edge(10)) > eps || abs(edge(11)) > eps) Control point can be wherever???????
            twinEdge = records.halfEdge(records.edges.twinID(edge),:);
            obj1=records.input(records.edges.obj(edge),:);%edge(8),:);
            obj2=records.input(records.edges.obj(twinEdge),:);
            if(obj1(1))
                pointCorr = obj1(3:4);
            else
                pointCorr = obj2(3:4);
            end
            
            bCurve = kron((1-t).^2,records.verts.pos(records.edges.origin(edge,1),:)') + kron(2*(1-t).*t,records.edges.controlPoint(edge,:)') + kron(t.^2,records.verts.pos(records.edges.origin(edge,2),:)');
            distanceDiff = linspace(distA,distB,intervalDensity);
            [subInd1, subInd2] = intervalSearch(1,distanceDiff,dist);
            radVec1 = EuclidianDistance2d(bCurve(1,subInd1),pointCorr(1),bCurve(2,subInd1),pointCorr(2));
            radVec2 = EuclidianDistance2d(bCurve(1,subInd2),pointCorr(1),bCurve(2,subInd2),pointCorr(2));
            if(subInd2 == -1)
                %?????????
                throw(MException('Resample:What','This should not be possible...'));
            elseif(subInd1 == subInd2)
                radiusVector(i) =radVec1;
                vertexList(i,:) = bCurve(:,subInd1)';
            else
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
                
            end
        end
        
    end
end
recycledLoopData.Vertex = vertexList;
recycledLoopData.rad = radiusVector;
recycledLoopData.numSamples = numSamples;
recycledLoopData.step = step;
recycledLoopData.distance = ((1:numSamples).*step)';
end

function [index1,index2] = intervalSearch(startPoint,valueVector,value)
foundFlag = 0;
for i = startPoint:length(valueVector)-1
    if(value == valueVector(i))
        index1 = i;
        index2 = i;
        foundFlag = 1;
        return;
    elseif(value < valueVector(i+1) && value > valueVector(i))
        index2 = i+1;
        index1 = i;
        foundFlag = 1;
        return;
    elseif(value < valueVector(i))
        throw(MException('IS:NonIncreasingValues','Search array should be monotonically increasing?'));
    end
end
if(~foundFlag)
    if(value == valueVector(end))
        index1 = length(valueVector);
        index2 = length(valueVector);
    elseif(value > valueVector(end))
        index1 = length(valueVector);
        index2 = -1;
    end
end
end