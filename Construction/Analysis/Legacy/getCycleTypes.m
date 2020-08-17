function cycleTypeArray = getCycleTypes(dataStruct)
cycleTypeArray = zeros(6,1);
cycleTypeArray(1) = dataStruct.loop.numInObjectEnclosingHole; 
cycleTypeArray(2) = dataStruct.loop.numInObjectEnclosedByHole;
cycleTypeArray(3) = dataStruct.loop.numInObjectNoEnclosure;
cycleTypeArray(4) = dataStruct.loop.numInHoleEnclosingObject;
cycleTypeArray(5) = dataStruct.loop.numInHoleEnclosingObject;
cycleTypeArray(6) = dataStruct.loop.numInHoleNoEnclosure;
end