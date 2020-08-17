clear all
addpath tools\
folder_name = 'Vitro C w CCM3\';
filenames = getfilenames(folder_name);
filenames = filenames(isInListEnd(filenames,'.csv'));
all_para = [];
datarange = 1:40;
% datarange = [1:19,21:39];

for i=1:length(filenames)
    filenames{i} = fullfile(folder_name,filenames{i});
    tmp = filenames{i}(strfind(filenames{i},'CCM=')+4:strfind(filenames{i},'CCM=')+4);
    CCM = str2num(tmp);
    tmp = filenames{i}(strfind(filenames{i},'H1152=')+6:strfind(filenames{i},'H1152=')+6);
    TREATED = str2num(tmp);
    all_para = [all_para; [CCM, TREATED]];
end
% for gx = unique(all_para(:,2))'
%     IA = find(all_para(:,2)==gx);
%     [~,I] = sort(all_para(IA,3));
%     all_para(IA,:) = all_para(IA(I),:);
%     filenames(IA,:) = filenames(IA(I),:);
% end


table_content_t = read_xls(fullfile(folder_name,'STATS_column_headers.txt'),',',0);
table_content = table_content_t(:,datarange);

marker_names = [table_content, {'CCM_TYPE'}, {'H1152'}, {'file_ind'}];

all_data = [];
for i=1:length(filenames)
    table_content_t = read_xls_v2(filenames{i},',',0);
    table_content = table_content_t(:,datarange);
    tmp_data = cell2num(table_content);
    tmp = filenames{i}(strfind(filenames{i},'CCM='):strfind(filenames{i},'CCM=')+1);
    CCM = str2num(tmp);
    tmp = filenames{i}(strfind(filenames{i},'H1152='):strfind(filenames{i},'H1152=')+1);
    TREATED = str2num(tmp);
    tmp_para = repmat([CCM, TREATED, i],size(tmp_data,1),1);
    all_data = [all_data; [tmp_data, tmp_para]];
end
save raw_data

