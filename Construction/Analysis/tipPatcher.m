
close all;
if(~exist('endpointLine.m','file'))
    path2script = mfilename('fullpath');
    [pathOnly, ~, ~] = fileparts(path2script);
    % cd(pathOnly);
    % mainDir = cd;
    addpath(genpath(pathOnly));
    % javaaddpath([mainDir filesep 'JAVA' filesep 'build' filesep]);
end
FILTERSIZE = 40;
PREFER_MAJOR_AXIS_CONNECTIONS = true;
IGNORE_SINGLETON_TIPS = true;
figure('position',[0,0,1024,1024]);
savAxis = subplot('position',[0,0,1,1]);
axis equal
axis off
imagesc(records.imageMask);

colormap('bone');
hold on;
plotVoronoiSkeleton(records,1,[0.05,0.05,0.05],0,0,{'LineWidth',0.25});
i = 1;
out = tipDetection(records,dataStruct.loop.object.enclosed(i),FILTERSIZE, PREFER_MAJOR_AXIS_CONNECTIONS,IGNORE_SINGLETON_TIPS);
for i = 1:length(out)
   out{i}.radList = records.verts.rad(out{i}.AxisVerts);
   out{i}.strDist = sqrt((records.verts.pos(out{i}.AxisIndexA,1) - records.verts.pos(out{i}.AxisIndexB,1))^2 ...
       +(records.verts.pos(out{i}.AxisIndexA,2) - records.verts.pos(out{i}.AxisIndexB,2))^2);
   
end

blueMeanRad = zeros(length(out{1}.children),1);
blueSTDRad = zeros(length(out{1}.children),1);
blueStrDist = zeros(length(out{1}.children),1);
blueDist = zeros(length(out{1}.children),1);
blueTort =  zeros(length(out{1}.children),1);
blueMaxRad = zeros(length(out{1}.children),1);
blueIsHeadless = zeros(length(out{1}.children),1);
blueHeadRad = nan(length(out{1}.children),1);
blueHeadCircularity =  nan(length(out{1}.children),1);
blueHeadCircularitySub =  nan(length(out{1}.children),1);

headCounter = 0;
for i = 1:length(out{1}.children)
    blueMeanRad(i) = mean(out{out{1}.children(i)}.radList);
    blueSTDRad(i) = std(out{out{1}.children(i)}.radList);
    [blueMaxRad(i),id,blueIsHeadless(i)] = getLocalRadMax(out{out{1}.children(i)}.radList);
    %[blueMaxRad(i),id] = max(out{out{1}.children(i)}.radList);
    blueStrDist(i) = out{out{1}.children(i)}.strDist;
    blueDist(i) = out{out{1}.children(i)}.totalDist;
    blueTort(i) = blueDist(i)/blueStrDist(i);
    if(~blueIsHeadless(i))
        headCounter = headCounter + 1;
        blueHeadRad(headCounter) = blueMaxRad(i);
        blueHeadCircularity(headCounter) = sum(records.edges.dist(out{out{1}.children(i)}.EL(1:(id-1))))./blueHeadRad(headCounter);
        blueHeadCircularitySub(headCounter) = sum(records.edges.dist(out{out{1}.children(i)}.EL(1:(id-1)))) - blueHeadRad(headCounter);

    scatter(records.verts.pos(out{out{1}.children(i)}.AxisVerts(id),1), records.verts.pos(out{out{1}.children(i)}.AxisVerts(id),2), ...
    20,'w','filled');
    else
            scatter(records.verts.pos(out{out{1}.children(i)}.AxisVerts(id),1), records.verts.pos(out{out{1}.children(i)}.AxisVerts(id),2), ...
    20,'k','filled');
    end
end
    blueCoefVarRad = blueSTDRad./blueMeanRad;

% mat = [blueMeanRad,blueCoefVarRad,blueMaxRad,blueHeadRad,blueHeadCircularity,blueHeadCircularitySub blueDist,blueTort];

axis(savAxis);
[~,childMaxDiststr] = max(blueStrDist);
plotFromEdgeList(out{out{1}.children(childMaxDiststr)}.EL,records,'y',{'LineWidth',1});
[~,childMaxDist] = max(blueDist);
plotFromEdgeList(out{out{1}.children(childMaxDist)}.EL,records,'r',{'LineWidth',2});
[~,childMaxTort] = max(blueTort);
plotFromEdgeList(out{out{1}.children(childMaxTort)}.EL,records,'m',{'LineWidth',3});
axis equal
% [~,childMaxRad] = max(blueMaxRad);
% [~,maxMaxRad] = max(out{out{1}.children(childMaxRad)}.radList);
% scatter(records.verts.pos(out{out{1}.children(childMaxRad)}.AxisVerts(maxMaxRad),1), records.verts.pos(out{out{1}.children(childMaxRad)}.AxisVerts(maxMaxRad),2), ...
%     20,'w','filled');
figure;
subplot(3,2,1)
boxplot(blueMeanRad);
title('Mean Radius on Path')
subplot(3,2,2)
boxplot(blueCoefVarRad);
title('Coefficient of Variation of Radius')
subplot(3,2,3)
boxplot(blueHeadRad);
title('Head Sizes')
subplot(3,2,4)
boxplot(blueHeadCircularity)
title('Head Circularity')
subplot(3,2,5)
boxplot(blueDist)
title('Path Length');
subplot(3,2,6)
boxplot(blueTort);
title('Tortuosity');
% g = {"Mean Radius on Path", "CoefVar Rad on Path", "Max Rad on Path", "Head Sizes", "Head Circularity (Division)", "Head Circularity (Subtraction)", "Total Dist", "Tortuosity"};
% boxplot(mat,g);
% for i = 1:length(dataStruct.loop.object.enclosed)
%     tipDetection(records,dataStruct.loop.object.enclosed(i),FILTERSIZE, PREFER_MAJOR_AXIS_CONNECTIONS,IGNORE_SINGLETON_TIPS);
% end
% for i = 1:length(dataStruct.loop.object.acyclic)
%     tipDetection(records,dataStruct.loop.object.acyclic(i),FILTERSIZE, PREFER_MAJOR_AXIS_CONNECTIONS,IGNORE_SINGLETON_TIPS);
% end