function simulationRecordsToCSV(dirName)
if(dirName(end) ~= filesep)
    dirName = [dirName filesep];
end
matFiles = dir([dirName '*.mat']);

for k = length(matFiles):-1:1
    % remove non-folders
    if ~matFiles(k).isdir
        if((isempty(strfind(matFiles(k).name,'LOOP'))) || ~isempty(strfind(matFiles(k).name,'STATS')) || isempty(strfind(matFiles(k).name,'.mat')))
            matFiles(k) = [ ];
            continue
        end
    else
        matFiles(k) = [ ];
        continue
    end
end
for iter = 1:length(matFiles)
    loadFile = load([dirName matFiles(iter).name]);
%     [loadFile.dataStruct] = extractCycles(loadFile.records, loadFile.dataStruct);
%     [loadFile.dataStruct] = acyl_MajorAxis(loadFile.records, loadFile.dataStruct, 30); 
    loadFile.dataStruct = resampleAllInteriorCycles(loadFile.records,loadFile.dataStruct);
    loadFile.dataStruct.statMat = dataStruct2Stats(loadFile.records, loadFile.dataStruct);
    [~,name,~] = fileparts(matFiles(iter).name);
    csvwrite([dirName 'STATS_OUTER_' name '.csv'],loadFile.dataStruct.statMat.vecMat(2:end,:));
    saveOut(loadFile.records,loadFile.dataStruct,[dirName 'STATS_' matFiles(iter).name]);
end
end