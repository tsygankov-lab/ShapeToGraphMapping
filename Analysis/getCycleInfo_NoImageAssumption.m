%% This function extracts the out-graph and in-graph entries in datastruct for a corresponding boundary
%   This function only works when the boundary metrics were derived 
%   using 'extractCycles_noImageAssumption.' If the standard image pipeline
%   code was used, then you will need to use getCycleInfo
%% Inputs: 
%       dataStruct from extractCycles
%       regionID - the color of the boundary of interest
%% Outputs:
%       cycleInner - the dataStruct entry for the in-graph subgraph
%       cycleOuter - the dataStruct entry for the out-graph subgraph
%           The outermost boundary of an image (normally color 1) will not
%           have a cycleOuter component. This structure will be empty.
function [cycleInner, cycleOuter] = getCycleInfo_NoImageAssumption(records, dataStruct,regionID)
cycleInner = [];
cycleOuter = [];
innerID = -1;
INNERFOUND = false;
OUTERFOUND = false;
if(regionID == 1)
%     warning('regionID == 1 lacks any background info, as the background is unbounded')
    OUTERFOUND = true;
end
for i = 1:dataStruct.loop.cyclic
    if(dataStruct.loop.object.cyclic(i).color == regionID)
        cycleInner = dataStruct.loop.object.cyclic(i);
        INNERFOUND = true;
        innerID = i;
        break;
    end
end
if(~INNERFOUND)
    for i = 1:dataStruct.loop.acyclic
        if(regionID == dataStruct.loop.object.acyclic(i).color)
            cycleInner = dataStruct.loop.object.acyclic(i);
            INNERFOUND = true;
            innerID = i + dataStruct.loop.cyclic;
            break;
        end
    end
end
for i = 1:dataStruct.loop.cyclic
    if(regionID == dataStruct.loop.object.cyclic(i).color)
        if(i ~= innerID)
            cycleOuter = dataStruct.loop.object.cyclic(i);
            OUTERFOUND = true;
            break;
        end
    end
end
if(~OUTERFOUND)
    for i = 1:dataStruct.loop.acyclic
        if(regionID == dataStruct.loop.object.acyclic(i).color)
            if(i ~= innerID + dataStruct.loop.cyclic)
                
                cycleOuter = dataStruct.loop.object.acyclic(i);
                
                OUTERFOUND = true;
                break;
            end
        end
    end
end

%% Defines the outermost cycle as the one with the left most vertex (assuming a nested polygon structure)
if(~isempty(cycleOuter))
    if(min(records.verts.pos(cycleInner.primaryMajAxis.vert,1)) < min(records.verts.pos(cycleOuter.primaryMajAxis.vert,1)))
        tmp = cycleInner;
        cycleInner = cycleOuter;
        cycleOuter = tmp;
    end
end