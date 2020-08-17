function statMat = dataStruct2Stats_NoImageAssumption(records, dataStruct)
vectorMatrix = [];
rangeInStats = 1:20;
rangeOutStats = 21:40;

for i = 1:records.numObjects
    [cycleInner, cycleOuter] = getCycleInfo_NoImageAssumption(records, dataStruct, i);
    innerStatObj = perObjectStat(records, cycleInner, 0, 0); %second arg is not needed
    vectorMatrix(i, rangeInStats) = [innerStatObj.VECTOR];
    if(~isempty(cycleOuter))
        outerStatObj = perObjectStat(records, cycleOuter, 0, 1);
        vectorMatrix(i, rangeOutStats) = [outerStatObj.VECTOR];
    else
        vectorMatrix(i, rangeOutStats) = zeros(size(innerStatObj.VECTOR));
    end
end

statMat.vecMat = vectorMatrix;
end

function matObj = perObjectStat(records, loopObj,acyclic,outflag)
%%GENERAL
points = records.verts.pos(loopObj.boundaryVerts,:);
Diffs = [0,0;diff(points,1)];
Dists = sqrt(sum(Diffs .* Diffs,2));
cumDist = cumsum(Dists);
matObj.boundPerim = sum(Dists);%size(loopObj.boundaryVertexCoor,1);
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
interpBoundaryRatio = interp1(cumDist, loopObj.boundaryRatio,linspace(0,max(cumDist),size(loopObj.boundaryVerts,1)));
matObj.BPRAT.mean = mean(interpBoundaryRatio);
matObj.BPRAT.std = std(interpBoundaryRatio);
%matObj.BPRAT.mom3 = moment(loopObj.boundaryRatio,3);
%matObj.BPRAT.mom4 = moment(loopObj.boundaryRatio,3);
%    matObj.BPRAT.mom5 = moment(loopObj.boundaryRatio,3);
%matObj.BPRAT.min = min(loopObj.boundaryRatio);
matObj.BPRAT.max = max(interpBoundaryRatio);

tempMat = interpBoundaryRatio;
quantNo = quantile(tempMat,0.0);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
%numPoints = sum(tempMat>0);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ0 = trapz(tempMat); % %subtract
matObj.BPRAT.NPQ0 = numPositiveCrossings; % %subtract
tempMat = interpBoundaryRatio;
quantNo = quantile(tempMat,0.25);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ25 = trapz(tempMat);
matObj.BPRAT.NPQ25 = numPositiveCrossings;
tempMat = interpBoundaryRatio;
quantNo = quantile(tempMat,0.5);
tempMat = tempMat - quantNo;
numPositiveCrossings = crossingCounter(tempMat);
tempMat(tempMat<0) = 0;
matObj.BPRAT.AUCQ50 = trapz(tempMat);
matObj.BPRAT.NPQ50 = numPositiveCrossings;
tempMat = interpBoundaryRatio;
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