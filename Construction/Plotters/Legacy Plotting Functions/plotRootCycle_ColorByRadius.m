function plotBoundary_ColorByRadius(records, loopStruct)
radList = {};
% boundVertexCoor = {};
maxMeanRad = [];
maxMinRad = [];
maxMaxRad = [];
doBP = false;
% for i = 1:records.numObjects
% %     [radList{i}, boundVertexCoor{i}, BPList{i}] = getBorderRads(records, dataStruct, i);
%     if(doBP)
%         radList{i} = sqrt(BPList{i});
%     end
%     meanRadList{i} = mean(radList{i},2);
%     minRadList{i} = min(radList{i},[],2);
%     maxRadList{i} = max(radList{i},[],2);
%     maxMeanRad = [maxMeanRad,max(meanRadList{i})];
%     maxMinRad = [maxMinRad,max(minRadList{i})];
%     maxMaxRad = [maxMaxRad,max(maxRadList{i})];
% end
boundVertexCoor = loopStruct.Vertices;
boundaryProf = loopStruct.rad;

maxMeanRad_All = quantile(boundaryProf,0.975);
% figure;
hold on;
% for i = 1:records.numObjects
colorIndex1 = floor((meanRadList/(max(maxMeanRad_All)/1023)))+1;
colorIndex1(colorIndex1 > 1024) = 1024;
colorThing1 = im2uint8(jet(1024))';
colorThing1 = [colorThing1;255.*ones(1,length(colorThing1))];
coltest1 = colorThing1(:,colorIndex1);
test1 = plot(boundVertexCoor(:,1),boundVertexCoor(:,2));
drawnow;
set(test1.Edge,'ColorBinding','interpolated','ColorData',coltest1,'LineWidth',1)
% axis equal
% title('Boundary Colored by Boundary Profile')

end
