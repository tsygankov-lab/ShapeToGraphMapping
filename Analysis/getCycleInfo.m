%% This function extracts the out-graph and in-graph entries in datastruct for a corresponding boundary
%   This function only works when the boundary metrics were derived 
%   standard image pipeline using 'extractCycles.' If _noImageAssumption
%   code was used, then you will need to use getCycleInfo_noImageAssumption
%% Inputs: 
%       dataStruct from extractCycles
%       regionID - the color of the boundary of interest
%% Outputs:
%       cycleInner - the dataStruct entry for the in-graph subgraph
%       cycleOuter - the dataStruct entry for the out-graph subgraph
%           The outermost boundary of an image (normally color 1) will not
%           have a cycleOuter component. This structure will be empty.
function [cycleInner, cycleOuter] = getCycleInfo(dataStruct,regionID)
cycleInner = [];
cycleOuter = [];
INNERFOUND = false;
OUTERFOUND = false;
if(regionID == 1)
    warning('regionID == 1 lacks any background info, as the background is unbounded')
    OUTERFOUND = true;
end
for i = 1:dataStruct.loop.numInObjectEnclosingHole
    if(dataStruct.loop.object.enclosing(i).color == regionID)
        cycleInner = dataStruct.loop.object.enclosing(i);
        INNERFOUND = true;
        break;
    end
end
if(~INNERFOUND)
    for i = 1:dataStruct.loop.numInObjectEnclosedByHole
        if(regionID == dataStruct.loop.object.enclosed(i).color)
            cycleInner = dataStruct.loop.object.enclosed(i);
            INNERFOUND = true;
            break;
        end
    end
end
if(~INNERFOUND)
    for i = 1:dataStruct.loop.numInObjectNoEnclosure
        if(regionID == dataStruct.loop.object.acyclic(i).color)
            cycleInner = dataStruct.loop.object.acyclic(i);
            INNERFOUND = true;
            break;
        end
    end
end
for i = 1:dataStruct.loop.numInHoleEnclosingObject
    if(regionID == dataStruct.loop.hole.enclosing(i).color)
        cycleOuter = dataStruct.loop.hole.enclosing(i);
        OUTERFOUND = true;
        break;
    end
end
if(~OUTERFOUND)
    for i = 1:dataStruct.loop.numInHoleEnclosedByObject
        if(regionID == dataStruct.loop.hole.enclosed(i).color)
            cycleOuter = dataStruct.loop.hole.enclosed(i);
            
            OUTERFOUND = true;
            break;
        end
    end
end
if(~OUTERFOUND)
    for i = 1:dataStruct.loop.numInHoleNoEnclosure
        if(regionID == dataStruct.loop.hole.acyclic(i).color)
            cycleOuter = dataStruct.loop.hole.acyclic(i);
            OUTERFOUND = true;
            break;
        end
    end
end