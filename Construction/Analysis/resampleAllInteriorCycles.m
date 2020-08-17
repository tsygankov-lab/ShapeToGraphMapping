function dataStruct = resampleAllInteriorCycles(records,dataStruct)
% dataStruct.RESAMPLED.loop
for i = 1:dataStruct.loop.numInObjectEnclosingHole
    [dataStruct.loop.object.enclosing(i).resampled.pos,...
        dataStruct.loop.object.enclosing(i).resampled.rad]= resamplePath(records, dataStruct.loop.object.enclosing(i).EL, 0.5);
end
for i = 1:dataStruct.loop.numInObjectEnclosedByHole
    [dataStruct.loop.object.enclosed(i).resampled.pos,...
        dataStruct.loop.object.enclosed(i).resampled.rad] = resamplePath(records, dataStruct.loop.object.enclosed(i).EL, 0.5);
end
for i = 1:dataStruct.loop.numInObjectNoEnclosure
    [dataStruct.loop.object.acyclic(i).resampled.pos,...
        dataStruct.loop.object.acyclic(i).resampled.rad]  = resamplePath(records,dataStruct.loop.object.acyclic(i).primaryMajAxis.edge, 0.5);
end
for i = 1:dataStruct.loop.numInHoleEnclosingObject
    [dataStruct.loop.hole.enclosing(i).resampled.pos,...
        dataStruct.loop.hole.enclosing(i).resampled.rad] = resamplePath(records, dataStruct.loop.hole.enclosing(i).EL, 0.5);
end
for i = 1:dataStruct.loop.numInHoleEnclosedByObject
    [dataStruct.loop.hole.enclosed(i).resampled.pos,...
        dataStruct.loop.hole.enclosed(i).resampled.rad] = resamplePath(records, dataStruct.loop.hole.enclosed(i).EL, 0.5);
end
for i = 1:dataStruct.loop.numInHoleNoEnclosure
   [dataStruct.loop.hole.acyclic(i).resampled.pos,...
        dataStruct.loop.hole.acyclic(i).resampled.rad] = resamplePath(records, dataStruct.loop.hole.acyclic(i).primaryMajAxis.edge, 0.5);
end
end