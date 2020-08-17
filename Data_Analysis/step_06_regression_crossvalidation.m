addpath(genpath('tools\'))
load step_03_clustering_results
NORMFLAG =  0;
INCLUDE_BORDER_COUNT = false;
if(NORMFLAG)
 A = image_level_cluster_count(:,1:numBorders);
image_level_cluster_count(:,1:numBorders) = (diag((1./sum(A,2))).^(1/2))*A;

% for i=1:size(filteredData,2)
%%Normalize so range is the same as other metrics
if(INCLUDE_BORDER_COUNT)
    data_tmp = image_level_cluster_count(:,numBorders+1);
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
    image_level_cluster_count(:,numBorders+1) = data_tmp;
end
end
figure(6)
[y_hat, mae, y] = cross_validtion_regression(image_level_cluster_count, all_para, 'K', 10, 'Folds', 5, 'log', false);
subplot(1,2,1); plot(y(:,1),y_hat(:,1),'o'); title('Cell-Substrate Strength'); xlabel('true'); ylabel('pred'); axis([-2,7,-2,7]), line([-2 7],[-2 7])
subplot(1,2,2); plot(y(:,2),y_hat(:,2),'o'); title('Cell-Cell Strength'); xlabel('true'); ylabel('pred'); axis([-500,4000,-500,4000]), line([-500 4000],[-500 4000])
disp(mae)

figure(7)
[y_hat, mae, y] = cross_validtion_regression(image_level_cluster_count, all_para, 'K', 10, 'Folds', 5, 'log', true);
subplot(1,2,1); plot(y(:,1),y_hat(:,1),'o'); title('log Cell-Substrate Strength'); xlabel('true'); ylabel('pred'); axis([-2,3,-2,3]), line([-2 3],[-2 3])
subplot(1,2,2); plot(y(:,2),y_hat(:,2),'o'); title('log Cell-Cell Strength'); xlabel('true'); ylabel('pred'); axis([3,9,3,9]), line([3 9],[3 9])
disp(mae)
percentError = (abs(exp(y_hat) - exp(y)))./(exp(y));
% mean(percentError)
