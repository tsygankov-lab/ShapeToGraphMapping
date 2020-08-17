function stat_filenames = loadAllStatFilesNames(folder_name,all_para,VITRO)
stat_folder_name = [folder_name filesep 'statFile'];
stat_filenames = getfilenames(stat_folder_name);
stat_filenames = stat_filenames(isInListEnd(stat_filenames,'.mat'));
stat_all_para = [];
if(VITRO)
    for i=1:length(stat_filenames)
        stat_filenames{i} = fullfile(stat_folder_name,stat_filenames{i});
        tmp = stat_filenames{i}(strfind(stat_filenames{i},'CCM=')+4:strfind(stat_filenames{i},'CCM=')+4);
        CCM = str2num(tmp);
        tmp = stat_filenames{i}(strfind(stat_filenames{i},'H1152=')+6:strfind(stat_filenames{i},'H1152=')+6);
        TREATED = str2num(tmp);
        stat_all_para = [stat_all_para; [CCM, TREATED]];
    end
else
    for i=1:length(stat_filenames)
        
        stat_filenames{i} = fullfile(stat_folder_name,stat_filenames{i});
        tmp = stat_filenames{i}(strfind(stat_filenames{i},'R='):strfind(stat_filenames{i},'_gx')-1);
        R = str2num(tmp(3:end));
        tmp = stat_filenames{i}(strfind(stat_filenames{i},'gx='):strfind(stat_filenames{i},'_kb')-1);
        gx = str2num(tmp(4:end));
        tmp = stat_filenames{i}(strfind(stat_filenames{i},'kb='):strfind(stat_filenames{i},'Simulation')-1);
        kb = str2num(tmp(4:end));
        stat_all_para = [stat_all_para; [R, gx, kb]];
    end
end
[C,IA,IB] = intersect(all_para, stat_all_para, 'rows');
stat_filenames(IA) = stat_filenames(IB);

end