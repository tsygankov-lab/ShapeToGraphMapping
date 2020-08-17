function dataStruct = resampleAllInteriorCycles_NoImageAssumption(records,dataStruct)
% dataStruct.RESAMPLED.loop
if(isfield(dataStruct.loop.object, 'cyclic'))
for i = 1:length(dataStruct.loop.object.cyclic)
    [dataStruct.loop.object.cyclic(i).resampled.pos,...
        dataStruct.loop.object.cyclic(i).resampled.rad]= resamplePath(records, dataStruct.loop.object.cyclic(i).EL, 0.5);
end
end

for i = 1:length(dataStruct.loop.object.acyclic)
    [dataStruct.loop.object.acyclic(i).resampled.pos,...
        dataStruct.loop.object.acyclic(i).resampled.rad]  = resamplePath(records,dataStruct.loop.object.acyclic(i).primaryMajAxis.edge, 0.5);
end
end