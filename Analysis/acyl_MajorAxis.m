function [dataStruct] = acyl_MajorAxis(records,dataStruct,filtSize)

for i = 1:dataStruct.loop.numInObjectNoEnclosure
    dataStruct.loop.object.acyclic(i).primaryMajAxis = majorAxis_FromRoot(records,dataStruct.loop.object.acyclic(i),filtSize);
end
for i = 1:dataStruct.loop.numInHoleNoEnclosure
    dataStruct.loop.hole.acyclic(i).primaryMajAxis = majorAxis_FromRoot(records,dataStruct.loop.hole.acyclic(i),filtSize);
end
end

