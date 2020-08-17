function statMat = dataStruct2Stats(records, dataStruct)
vectorMatrix = [];
rangeInStats = 1:20;
rangeOutStats = 21:40;

for i = 1:dataStruct.loop.numInObjectEnclosingHole
    color = dataStruct.loop.object.enclosing(i).color;
    statMat.object.enclosing(i) = perObjectStat(records, dataStruct.loop.object.enclosing(i),0,0);
    vectorMatrix(color,rangeInStats) = [statMat.object.enclosing(i).VECTOR];
end
for i = 1:dataStruct.loop.numInObjectEnclosedByHole
    color = dataStruct.loop.object.enclosed(i).color;
%         if(color ~= 1)

    statMat.object.enclosed(i) = perObjectStat(records, dataStruct.loop.object.enclosed(i),0,1);
    vectorMatrix(color,rangeInStats) = [statMat.object.enclosed(i).VECTOR];
%         end
end
for i = 1:dataStruct.loop.numInObjectNoEnclosure
    color = dataStruct.loop.object.acyclic(i).color;
    statMat.object.acyclic(i) = perObjectStat(records, dataStruct.loop.object.acyclic(i),1,1);
    vectorMatrix(color,rangeInStats) = [statMat.object.acyclic(i).VECTOR];
end
for i = 1:dataStruct.loop.numInHoleEnclosingObject
    color = dataStruct.loop.hole.enclosing(i).color;
    
    statMat.hole.enclosing(i) = perObjectStat(records, dataStruct.loop.hole.enclosing(i),0,0);
    vectorMatrix(color,rangeOutStats) = [statMat.hole.enclosing(i).VECTOR];
end
for i = 1:dataStruct.loop.numInHoleEnclosedByObject
    color = dataStruct.loop.hole.enclosed(i).color;
    
    statMat.hole.enclosed(i) = perObjectStat(records, dataStruct.loop.hole.enclosed(i),0,1);
    vectorMatrix(color,rangeOutStats) = [statMat.hole.enclosed(i).VECTOR];
end
for i = 1:dataStruct.loop.numInHoleNoEnclosure
    color = dataStruct.loop.hole.acyclic(i).color;
    
    statMat.hole.acyclic(i) = perObjectStat(records, dataStruct.loop.hole.acyclic(i),1,1);
    vectorMatrix(color,rangeOutStats) = [statMat.hole.acyclic(i).VECTOR];
end
%%Here loop through and pair the vectorMatrix rows with the corresponding
%%background cycles
%
%      numInObjectEnclosingHole: 3
%      numInHoleEnclosingObject: 16
%     numInObjectEnclosedByHole: 1
%     numInHoleEnclosedByObject: 1
%        numInObjectNoEnclosure: 16
%          numInHoleNoEnclosure: 2
%
statMat.vecMat = vectorMatrix;
end

function matObj = perObjectStat(records, loopObj,acyclic,outflag)
%%GENERAL
matObj.boundPerim = size(loopObj.boundaryVertexCoor,1);
matObj.enclosedArea = polyarea(loopObj.boundaryVertexCoor(:,1),loopObj.boundaryVertexCoor(:,2));
matObj.outerBoundary = outflag;
%%RADIUS
% if(~acyclic)
    matObj.RAD.mean = mean(loopObj.resampled.rad);%mean(loopObj.subGraphVerts(:,3));%resampled.rad);
    matObj.RAD.std = std((loopObj.resampled.rad));
    matObj.RAD.mom3 = moment((loopObj.resampled.rad),3);
    matObj.RAD.mom4 = moment((loopObj.resampled.rad),4);
    %    matObj.RAD.mom5 = moment(loopObj.resampled.rad,5);
    matObj.RAD.min = min((loopObj.resampled.rad));
    matObj.RAD.max = max((loopObj.resampled.rad));
    
    
    %matObj.length = loopObj.resampled.distance(end);
    %matObj.cyclePolyArea =  polyarea(loopObj.resampled.Vertex(:,1),loopObj.resampled.Vertex(:,2)); %%Area of the polygon described by the cycle
    %matObj.subGraphArea = trapz(loopObj.resampled.distance,loopObj.resampled.rad); %Area of the subgraph region contained by the cycle
% else
%     matObj.RAD.mean = mean(loopObj.subGraphVerts(:,3));
%     matObj.RAD.std = std(loopObj.subGraphVerts(:,3));
%     matObj.RAD.mom3 = moment(loopObj.subGraphVerts(:,3),3);
%     matObj.RAD.mom4 = moment(loopObj.subGraphVerts(:,3),4);
%     %    matObj.RAD.mom5 = moment(loopObj.resampled.rad,5);
%     matObj.RAD.min = min(loopObj.subGraphVerts(:,3));
%     matObj.RAD.max = max(loopObj.subGraphVerts(:,3));
%     %matObj.length = loopObj.totalDistance;
%     %matObj.cyclePolyArea =  0;%polyarea(loopObj.resampled.Vertex(:,1),loopObj.resampled.Vertex(:,2)); %%Area of the polygon described by the cycle
%     %matObj.subGraphArea = 0;%May need to be calculated differently? trapz(loopObj.resampled.distance,loopObj.resampled.rad); %Area of the subgraph region contained by the cycle
% end

%%BOUNDARY PROFILE RATIO
matObj.BPRAT.mean = mean(loopObj.boundaryRatio);
matObj.BPRAT.std = std(loopObj.boundaryRatio);
%matObj.BPRAT.mom3 = moment(loopObj.boundaryRatio,3);
%matObj.BPRAT.mom4 = moment(loopObj.boundaryRatio,3);
%    matObj.BPRAT.mom5 = moment(loopObj.boundaryRatio,3);
%matObj.BPRAT.min = min(loopObj.boundaryRatio);
matObj.BPRAT.max = max(loopObj.boundaryRatio);

tempMat = loopObj.boundaryRatio;
quantNo = quantile(tempMat,0.0);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
%numPoints = sum(tempMat>0);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ0 = trapz(tempMat); % %subtract
matObj.BPRAT.NPQ0 = numPositiveCrossings; % %subtract
tempMat = loopObj.boundaryRatio;
quantNo = quantile(tempMat,0.25);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ25 = trapz(tempMat);
matObj.BPRAT.NPQ25 = numPositiveCrossings;
tempMat = loopObj.boundaryRatio;
quantNo = quantile(tempMat,0.5);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ50 = trapz(tempMat);
matObj.BPRAT.NPQ50 = numPositiveCrossings;
tempMat = loopObj.boundaryRatio;
quantNo = quantile(tempMat,0.75);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ75 = trapz(tempMat);
matObj.BPRAT.NPQ75 = numPositiveCrossings;
matObj.VECTOR = [matObj.RAD.mean,matObj.RAD.std,matObj.RAD.mom3,matObj.RAD.mom4,matObj.RAD.min,matObj.RAD.max,matObj.BPRAT.mean,matObj.BPRAT.std,matObj.BPRAT.max,matObj.BPRAT.AUCQ0,matObj.BPRAT.NPQ0,matObj.BPRAT.AUCQ25,matObj.BPRAT.NPQ25,matObj.BPRAT.AUCQ50,matObj.BPRAT.NPQ50,matObj.BPRAT.AUCQ75,matObj.BPRAT.NPQ75,matObj.boundPerim,matObj.enclosedArea,matObj.outerBoundary];
end

function [crossP,crossN] = crossingCounter(matthing)
signdiff = diff(sign(matthing));
crossP = sum(signdiff>0);
crossN = sum(signdiff<0);
end