function dataStruct = resampleAllInteriorCycles(records,dataStruct)
% dataStruct.RESAMPLED.loop
for i = 1:dataStruct.loop.numInObjectEnclosingHole
    dataStruct.loop.object.enclosing(i).resampled = resampleLoop(dataStruct.loop.object.enclosing(i), records, 0.5);
end
for i = 1:dataStruct.loop.numInObjectEnclosedByHole
    dataStruct.loop.object.enclosed(i).resampled = resampleLoop(dataStruct.loop.object.enclosed(i), records, 0.5);
end
for i = 1:dataStruct.loop.numInHoleEnclosingObject
    dataStruct.loop.hole.enclosing(i).resampled = resampleLoop(dataStruct.loop.hole.enclosing(i), records, 0.5);
end
for i = 1:dataStruct.loop.numInHoleEnclosedByObject
    dataStruct.loop.hole.enclosed(i).resampled = resampleLoop(dataStruct.loop.hole.enclosed(i), records, 0.5);
end
end