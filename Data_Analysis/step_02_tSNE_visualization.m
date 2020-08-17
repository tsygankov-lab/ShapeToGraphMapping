addpath(genpath('tools\'))


load('raw_data.mat')
data = all_data(:,datarange);
normalized_data = data;
for i=1:size(data,2)
    data_tmp = data(:,i);
    prc_5 = prctile(data_tmp,5);
    prc_95 = prctile(data_tmp,95);
    data_tmp(data_tmp<prc_5) = prc_5;
    data_tmp(data_tmp>prc_95) = prc_95;
    if prc_95==prc_5
        prc_95 = max(data_tmp);
        prc_5 = min(data_tmp);
    end
    if prc_95~=prc_5
        data_tmp = (data_tmp - prc_5)/(prc_95 - prc_5);
    else
        data_tmp = data_tmp*0;
    end
    normalized_data(:,i) = data_tmp;
end


tSNE_map = fast_tsne(normalized_data);
figure(1); 
scatter(tSNE_map(:,1),tSNE_map(:,2),30, all_data(:,20),'fill'); title('inner vs outer')


save step_02_tSNE_results