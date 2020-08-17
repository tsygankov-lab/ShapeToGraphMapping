clear all
addpath tools\
folder_name = 'StatFiles3';
filenames = getfilenames(folder_name);
filenames = filenames(isInListEnd(filenames,'.csv'));
all_para = [];
datarange = 1:40;
for i=1:length(filenames)
    filenames{i} = fullfile(folder_name,filenames{i});
    tmp = filenames{i}(strfind(filenames{i},'R='):strfind(filenames{i},'_gx')-1);
    R = str2num(tmp(3:end));
    tmp = filenames{i}(strfind(filenames{i},'gx='):strfind(filenames{i},'_kb')-1);
    gx = str2num(tmp(4:end));
    tmp = filenames{i}(strfind(filenames{i},'kb='):strfind(filenames{i},'Simulation')-1);
    kb = str2num(tmp(4:end));
    all_para = [all_para; [R, gx, kb]];
end
for gx = unique(all_para(:,2))'
    IA = find(all_para(:,2)==gx);
    [~,I] = sort(all_para(IA,3));
    all_para(IA,:) = all_para(IA(I),:);
    filenames(IA,:) = filenames(IA(I),:);
end


table_content_t = read_xls(fullfile(folder_name,'STATS_column_headers.txt'),',',0);
table_content = table_content_t(:,datarange);

marker_names = [table_content, {'R'}, {'gx'}, {'kb'}, {'file_ind'}];

all_data = [];
for i=1:length(filenames)
    table_content_t = read_xls_v2(filenames{i},',',0);
    table_content = table_content_t(:,datarange);
    tmp_data = cell2num(table_content);
    tmp = filenames{i}(strfind(filenames{i},'R='):strfind(filenames{i},'_gx')-1);
    R = str2num(tmp(3:end));
    tmp = filenames{i}(strfind(filenames{i},'gx='):strfind(filenames{i},'_kb')-1);
    gx = str2num(tmp(4:end));
    tmp = filenames{i}(strfind(filenames{i},'kb='):strfind(filenames{i},'Simulation')-1);
    kb = str2num(tmp(4:end));
    tmp_para = repmat([R, gx, kb, i],size(tmp_data,1),1);
    all_data = [all_data; [tmp_data, tmp_para]];
end
save raw_data

