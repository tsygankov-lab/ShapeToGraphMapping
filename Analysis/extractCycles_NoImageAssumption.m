function [dataStruct] = extractCycles_NoImageAssumption(records, dataStruct)
LOOP_EXTRACTION_VERSION = 200; 
inHoleEnclosingObject = 1;
inHoleEnclosedByObject = 1;
inHoleNoEnclosure = 1;
inObjEnclosingHole = 1;
inObjNoEnclosure = 1;
inObjEnclosedByHole = 1;

%%Loops through all objects and checks if they are either enclosed by
%%another object, or encloses another object.  If no object is enclosed,
%%falls back to classic definition of boundary profile
cyclicCounter = 0;
acyclicCounter = 0;
for i = 1:records.numObjects %Make regionID = min(reachableColor in range... issue with infinites)
    objInd = i;
    if(length(dataStruct.colorsPresent{i}) > 1)
        for j = 1:length(dataStruct.colorsPresent{i})
            cyclicCounter = cyclicCounter + 1;
            curColor = dataStruct.colorsPresent{i}(j);
            vertList_Binary = (records.verts.borderRegions(:,1) == i  | records.verts.vertexCoorID(:) ~= -1) & (records.verts.color(:,1) == curColor | records.verts.color(:,2) == curColor | records.verts.color(:,3) == curColor);
            loopStruct = extractSubGraphCycles_NoImageAssumption(vertList_Binary, records, dataStruct, curColor, objInd,objInd <= records.numNonHoles,0); %? Was this backwards?
            dataStruct.loop.object.cyclic(cyclicCounter) = loopStruct;
        end
    else
        curColor = dataStruct.colorsPresent{i}(1);
        
        acyclicCounter = acyclicCounter + 1;
        vertList_Binary = (records.verts.borderRegions(:,2) == i  | records.verts.vertexCoorID(:) ~= -1) & (records.verts.color(:,1) == curColor | records.verts.color(:,2) == curColor | records.verts.color(:,3) == curColor);
        loopStruct = extractSubGraphCycles_NoImageAssumption(vertList_Binary, records, dataStruct, curColor, objInd, objInd <= records.numNonHoles,1);
        dataStruct.loop.object.acyclic(acyclicCounter) = loopStruct;
    end
end
dataStruct.loop.cyclic = cyclicCounter;
dataStruct.loop.acyclic = acyclicCounter;
dataStruct.loop.numInObjectEnclosingHole = inObjEnclosingHole - 1;
dataStruct.loop.numInHoleEnclosingObject = inHoleEnclosingObject - 1;
dataStruct.loop.numInObjectEnclosedByHole = inObjEnclosedByHole - 1;
dataStruct.loop.numInHoleEnclosedByObject = inHoleEnclosedByObject - 1;
dataStruct.loop.numInObjectNoEnclosure = inObjNoEnclosure - 1;
dataStruct.loop.numInHoleNoEnclosure = inHoleNoEnclosure - 1;
dataStruct.loop.LOOP_EXTRACTION_VERSION = LOOP_EXTRACTION_VERSION;
end