function [regionID_INNER, regionID_OUTER] = convertColor2RegionID(dataStruct, color)
regionID_INNER = 0;
INNERFOUND = false;
regionID_OUTER = 0;
OUTERFOUND = false;
if(color == 1)
    warning('Color == 1 will not have a valid statistics matrix and should be ignored.  The output will return 0.')
end
for i = 1:dataStruct.loop.numInObjectEnclosingHole
    regionID_INNER = regionID_INNER+1;
    if(dataStruct.loop.object.enclosing(i).color == color)
        INNERFOUND = true;
        break;
    end
end
if(~INNERFOUND)
    for i = 1:dataStruct.loop.numInObjectEnclosedByHole
        regionID_INNER = regionID_INNER+1;
        
        if(color == dataStruct.loop.object.enclosed(i).color)
            INNERFOUND = true;
            break;
        end
    end
end
if(~INNERFOUND)
    for i = 1:dataStruct.loop.numInObjectNoEnclosure
        regionID_INNER = regionID_INNER+1;
        
        if(color == dataStruct.loop.object.acyclic(i).color)
            INNERFOUND = true;
            break;
        end
    end
end
for i = 1:dataStruct.loop.numInHoleEnclosingObject
    regionID_OUTER = regionID_OUTER + 1;
    if(color == dataStruct.loop.hole.enclosing(i).color)
        OUTERFOUND = true;
        break;
    end
end
if(~OUTERFOUND)
for i = 1:dataStruct.loop.numInHoleEnclosedByObject
    regionID_OUTER = regionID_OUTER + 1;
    if(color == dataStruct.loop.hole.enclosed(i).color
        OUTERFOUND = true;
        break;
    end
end
end
if(~OUTERFOUND)
for i = 1:dataStruct.loop.numInHoleNoEnclosure
    regionID_OUTER = regionID_OUTER + 1;
    if(color == dataStruct.loop.hole.acyclic(i).color)
       OUTERFOUND = true;
       break;
    end
end
end