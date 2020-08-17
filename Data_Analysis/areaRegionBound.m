% computeAreaImageRegion

stat_folder_name = [folder_name filesep 'statFile'];
stat_filenames = getfilenames(stat_folder_name);
stat_filenames = stat_filenames(isInListEnd(stat_filenames,'.mat'));
stat_all_para = [];
for i=1:length(stat_filenames)
    stat_filenames{i} = fullfile(stat_folder_name,stat_filenames{i});
    tmp = stat_filenames{i}(strfind(stat_filenames{i},'CCM=')+4:strfind(stat_filenames{i},'CCM=')+4);
    CCM = str2num(tmp);
    tmp = stat_filenames{i}(strfind(stat_filenames{i},'H1152=')+6:strfind(stat_filenames{i},'H1152=')+6);
    TREATED = str2num(tmp);
    stat_all_para = [stat_all_para; [CCM, TREATED]];
end
[C,IA,IB] = intersect(all_para, stat_all_para, 'rows');
stat_filenames(IA) = stat_filenames(IB);
borders = cell(length(stat_filenames),1);
percentImageListFull = [];
for k = 1:length(stat_filenames)
    tmpLoad = load(stat_filenames{k});
    pos = tmpLoad.records.verts.pos;
    borders{k} = zeros(size(tmpLoad.dataStruct.statMat.vecMat,1),1);
    for i = 2:length(tmpLoad.dataStruct.loop.object.enclosed)
        loopStruct = tmpLoad.dataStruct.loop.object.enclosed(i);
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
    end
    
    for i = 1:tmpLoad.dataStruct.loop.numInObjectEnclosingHole
        loopStruct = tmpLoad.dataStruct.loop.object.enclosing(i);
        
        color = tmpLoad.dataStruct.loop.object.enclosing(i).color;
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
    end
    for i = 1:tmpLoad.dataStruct.loop.numInObjectEnclosedByHole
        loopStruct = tmpLoad.dataStruct.loop.object.enclosed(i);
        color = tmpLoad.dataStruct.loop.object.enclosed(i).color;
        if(color ~= 1)
            
            borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
        end
    end
    for i = 1:tmpLoad.dataStruct.loop.numInObjectNoEnclosure
        loopStruct = tmpLoad.dataStruct.loop.object.acyclic(i);
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
    end
    for i = 1:tmpLoad.dataStruct.loop.numInHoleEnclosingObject
        loopStruct = tmpLoad.dataStruct.loop.hole.enclosing(i);
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
        
    end
    for i = 1:tmpLoad.dataStruct.loop.numInHoleEnclosedByObject
        loopStruct = tmpLoad.dataStruct.loop.hole.enclosed(i);
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
        
    end
    for i = 1:tmpLoad.dataStruct.loop.numInHoleNoEnclosure
        loopStruct = tmpLoad.dataStruct.loop.hole.acyclic(i);
        borders{k}(loopStruct.color - 1) = abs(borders{k}(loopStruct.color - 1) - polyarea(pos(loopStruct.Vertices,1),pos(loopStruct.Vertices,2)));
    end
    borders{k} = borders{k}./((size(tmpLoad.records.imageStruct.imageMask,1)*size(tmpLoad.records.imageStruct.imageMask,2)));
    percentImageListFull = [percentImageListFull; borders{k}];
end
