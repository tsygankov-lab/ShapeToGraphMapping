%%REFACTOR CHECK
function plotBridgeProfiles(dataStruct,records,id)
numObjects = length(dataStruct.bridge);

if(nargin < 2)
    low = 1;
    high = numObjects;
else
    low = id;
    high = id;
end
hold on;
numObjects = length(dataStruct.bridge);

coloringMat = hsv(numObjects);

for i = low:high
    if(dataStruct.bridge(i).completeCircuit)
        lastEdgeDist = records.halfEdge(dataStruct.bridge(i).EL(end),5);
        plot([dataStruct.bridge(i).dist,dataStruct.bridge(i).dist(end) + lastEdgeDist],[dataStruct.bridge(i).rad,dataStruct.bridge(i).rad(1)],'Color',coloringMat(i,:));
    else
        plot([dataStruct.bridge(i).dist],[dataStruct.bridge(i).rad],'Color',coloringMat(i,:));
    end
end

hold off;
end