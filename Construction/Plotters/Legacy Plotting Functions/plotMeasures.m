%%Need a plot edge list cycle
close all

%%PLOT 1
%I don't have this - I was sent a thresholded image

%%PLOT2
load('records.mat');
load('dataStruct.mat');
figure('color',[0,0,0]);

imshow(records.imageMask);
set(gca,'Position',[0,0,1,1]);
axis equal;
axis off;
axis xy;
drawnow;
figPos = get(gcf,'Position');

%%PLOT 3
figure('color',[0,0,0],'Position',figPos);
subplot('position',[0,0,1,1])
% axis ij;
axis off;
axis equal
plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);
drawnow;
plotXlim = xlim;
plotYlim = ylim;

%%PLOT 4
figure('color',[0,0,0],'Position',figPos);
subplot('position',[0,0,1,1])
% axis ij;
hold on;
axis off;
axis equal;
xlim(plotXlim);
ylim(plotYlim);
plotVoronoiSkeleton(records,records.numObjects, 1, [1,1,1], records.numNonHoles);
plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);
hold off;
drawnow;

%%PLOT 5
figure('color',[0,0,0],'Position',figPos);
subplot('position',[0,0,1,1])
axis off;
axis equal;
xlim(plotXlim);
ylim(plotYlim);
% numInObjectProfiles = length(dataStruct.loop.object);
% numProfiles = length(dataStruct.loop.object);
% colorMat = jet(numProfiles);
hold on;
for i = 1:records.numObjects
    objInd = i;
    enclosedBoundaries = find(records.adjMat(:,i));
    enclosingBoundaries = find(records.adjMat(i,:));
    if(i > records.numNonHoles)
        
        for j = 1:length(enclosingBoundaries)
            vertList_Binary = records.vorVert(:,4) == enclosingBoundaries(j) & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
            plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records, [1,1,1],0.5.*[1,1,1]);
        end
    else
        vertList_Binary = records.vorVert(:,4) == i & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
        plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records, [1,1,1],0.5.*[1,1,1])
    end
    % plotVoronoiSubGraph_vertList(dataStruct.loop.object(i).subGraphVerts,dataStruct.loop.object(i).binaryFilt, records,colorMat(i,:),[1,1,1].*0.5);
    % plot(records.vorVert(dataStruct.loop.object(i).Vertices(1),1),records.vorVert(dataStruct.loop.object(i).Vertices(1),2),'-p','MarkerFaceColor',[1,1,1],'MarkerSize',12)
end
plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);
xlim(plotXlim);
ylim(plotYlim);
hold off;
drawnow;

%%PLOT 6
figure('color',[0,0,0],'Position',figPos);
subplot('position',[0,0,1,1])
axis off;
axis equal;
xlim(plotXlim);
ylim(plotYlim);
% numInHoleProfiles = length(dataStruct.loop.hole);
hold on;
for i = 1:records.numObjects
    if(i == records.numObjects + 1)
        vertList_Binary = records.vorVert(:,5) == 0;
        plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records,colorMat(plotNum,:))
%         plotNum = plotNum + 1;
    else
        objInd = i;
        enclosedBoundaries = find(records.adjMat(:,i));
        enclosingBoundaries = find(records.adjMat(i,:));
        if(i > records.numNonHoles)
            vertList_Binary = records.vorVert(:,5) == i & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
            plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records,[1,1,1])
%             plotNum = plotNum + 1;
        else
            for j = 1:length(enclosingBoundaries)
                vertList_Binary = records.vorVert(:,5) == enclosingBoundaries(j) & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
                plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records,[1,1,1]);
%                 plotNum = plotNum + 1;
            end
        end
    end
    % plotVoronoiSubGraph_vertList(dataStruct.loop.hole(i).subGraphVerts,dataStruct.loop.hole(i).binaryFilt, records,colorMat(i,:),[1,1,1].*0.5);
    % plot(records.vorVert(dataStruct.loop.hole(i).Vertices(1),1),records.vorVert(dataStruct.loop.hole(i).Vertices(1),2),'-p','MarkerFaceColor',[1,1,1],'MarkerSize',12)
end
plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);

hold off;
drawnow;

%%PLOT7
figure('color',[0,0,0]);
subplot('position',[0,0,1,1])
axis off;
axis equal
%xlim(plotXlim);
%ylim(plotYlim);
%numProfiles = length(dataStruct.loop.object);
hold on;
for i = 1:records.numObjects
    % plotVoronoiSubGraph_vertList(dataStruct.loop.hole(i).subGraphVerts,dataStruct.loop.hole(i).binaryFilt, records,colorMat(i,:),[1,1,1].*0.5);
    objInd = i;
    enclosedBoundaries = find(records.adjMat(:,i));
    enclosingBoundaries = find(records.adjMat(i,:));
    if(i > records.numNonHoles)
        
        for j = 1:length(enclosingBoundaries)
            vertList_Binary = records.vorVert(:,4) == enclosingBoundaries(j) & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
            plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary,  records, [1,1,1],0.75.*[1,1,1]);
        end
    else
        vertList_Binary = records.vorVert(:,4) == i & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
        plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records, [1,1,1],0.75.*[1,1,1])
    end
    % plotVoronoiSubGraph_vertList(dataStruct.loop.object(i).subGraphVerts,dataStruct.loop.object(i).binaryFilt, records,colorMat(i,:),[1,1,1].*0.5);
    % plot(records.vorVert(dataStruct.loop.object(i).Vertices(1),1),records.vorVert(dataStruct.loop.object(i).Vertices(1),2),'-p','MarkerFaceColor',[1,1,1],'MarkerSize',12)
    
    % plot(records.vorVert(dataStruct.loop.hole(i).Vertices(1),1),records.vorVert(dataStruct.loop.hole(i).Vertices(1),2),'-p','MarkerFaceColor',[1,1,1],'MarkerSize',12)
end
plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);
%for i = 1:numProfiles
%    plotFromEdgeList(dataStruct.loop.object(i).EL,records,[0,1,1]);
%end
hold off;
drawnow;

%%PLOT 8
figure('color',[0,0,0]);
subplot('position',[0,0,1,1])
axis off;
axis equal
%xlim(plotXlim);
%ylim(plotYlim);
colorMat = jet(records.numObjects);
% numProfiles = length(dataStruct.loop.object);
hold on;
for i = 1:records.numObjects
    objInd = i;
    enclosedBoundaries = find(records.adjMat(:,i));
    enclosingBoundaries = find(records.adjMat(i,:));
    if(i > records.numNonHoles)
        for j = 1:length(enclosingBoundaries)
            vertList_Binary = records.vorVert(:,4) == enclosingBoundaries(j) & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
            plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary, records,  colorMat(i,:),0.75.*colorMat(i,:));
        end
    else
        vertList_Binary = records.vorVert(:,4) == i & (records.vorVert(:,13) == i | records.vorVert(:,14) == i | records.vorVert(:,15) == i);
        plotVoronoiSubGraph_vertList(records.vorVert(vertList_Binary,:),vertList_Binary,  records, colorMat(i,:),0.75.*colorMat(i,:));
    end
%     plotVoronoiSubGraph_vertList(dataStruct.loop.object(i).subGraphVerts,dataStruct.loop.object(i).binaryFilt, records,colorMat(dataStruct.loop.object(i).color,:),colorMat(dataStruct.loop.object(i).color,:).*0.5);
%     plotFromEdgeList(dataStruct.loop.object(i).EL,records,[1,1,1]);
%     plot(records.vorVert(dataStruct.loop.object(i).Vertices(1),1),records.vorVert(dataStruct.loop.object(i).Vertices(1),2),'-p','MarkerFaceColor',[1,1,1],'MarkerSize',12)
end
plotOutline_Post(records,2,records.numNonHoles,colorMat);
for i = 1:length(dataStruct.loop)
    plotFromEdgeList(dataStruct.loop.object(i).EL,records,[1,1,1]);
end
hold off;
drawnow;

% objectPlace = 1;
% objectCycle = 1;
% figure('color',[1,1,1],'Position',[0,10,1920,960])
% numProfiles = length(dataStruct.loop);
% subplot('Position',[0,0,1/4,1],'XTick',[],'YTick',[],'Color',[0,0,0]);
% figure
% axis equal
% axis off
% plotOutline_Post(records,1,records.numNonHoles,[1,0,0],[0,1,0]);
% numInObjectProfiles = length(dataStruct.loop.object);
% colorMat = jet(numInObjectProfiles);
%
% hold on;
% for i = 1:numInObjectProfiles
% plotVoronoiSubGraph_vertList(dataStruct.loop.object(i).subGraphVerts,dataStruct.loop.object(i).binaryFilt, records,colorMat(i,:),colorMat(i,:).*0.5+[1,1,1].*0.5);
% plot(records.vorVert(dataStruct.loop.object(i).Vertices(1),1),records.vorVert(dataStruct.loop.object(i).Vertices(1),2),'-p','MarkerFaceColor',colorMat(i,:),'MarkerSize',12)
% end
% hold off;
%
% subplot('Position',[1/4,1/12,1/4,10/12],'Color',[1,1,1]);
% title('Dist vs Rad')
%%PLOT 9
figure;
hold on;
colorMat = jet(records.numObjects);

for i = 1:1
    plot([dataStruct.loop.object(i).distance;records.halfEdge(dataStruct.loop.object(i).EL(end),5) + dataStruct.loop.object(i).distance(end)],[dataStruct.loop.object(i).radius;dataStruct.loop.object(i).radius(end)], 'Color',colorMat(i,:));
    ylabel('Radius (Pixels)')
    xlabel('Cumulative Arc Length on Path (Pixels)')
end
hold off;
drawnow;

figure;
hold on;
colorMat = jet(records.numObjects);
gausFilt = gausswin(20);
for i = 1:1
    plot([dataStruct.loop.object(i).distance;records.halfEdge(dataStruct.loop.object(i).EL(end),5) + dataStruct.loop.object(i).distance(end)],imfilter([dataStruct.loop.object(i).radius;dataStruct.loop.object(i).radius(end)] ,gausFilt, 'circular'), 'Color',colorMat(i,:));
    ylabel('Radius (Pixels)')
    xlabel('CONV Cumulative Arc Length on Path (Pixels)')
end
hold off;
drawnow;

%%PLOT 10
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 1:1
    histogram(dataStruct.loop.object(i).radius,60)
    ylabel('Frequency')
    xlabel('Radius Range (Pixels)')
end
hold off;
drawnow;

%%PLOT 11
% subplot('Position',[2/4,1/12,1/4,10/12],'Color',[1,1,1]);
% title('Bound Prof')
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 1:1
    plot([dataStruct.loop.object(i).boundaryProfile], 'Color',colorMat(i,:));
    ylabel('Distance to Internal Cycle');
    xlabel('Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

figure;
hold on;
colorMat = jet(records.numObjects);
gausFilt = gausswin(20);
for i = 1:1
    plot(imfilter([dataStruct.loop.object(i).boundaryProfile] ,gausFilt, 'circular'), 'Color',colorMat(i,:));
    ylabel('Distance to Internal Cycle');
    xlabel('CONV Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

%%PLOT 12
figure;
hold on;
% colorMat = jet(records.numObjects);
for i = 1:1
    histogram(dataStruct.loop.object(i).boundaryProfile,60)
    ylabel('Frequency')
    xlabel('Range of Distance to Internal Cycle from Boundary (Pixels)')
end
hold off;

%%PLOT 13
% subplot('Position',[2/4,1/12,1/4,10/12],'Color',[1,1,1]);
% title('Bound Prof')
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 1:1
    plot([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)], 'Color',colorMat(i,:));
    ylabel('Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node');
    xlabel('Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

figure;
hold on;
colorMat = jet(records.numObjects);
gausFit = gausswin(20);
for i = 1:1
    plot(imfilter([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)] ,gausFilt, 'circular'), 'Color',colorMat(i,:));
    ylabel('Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node');
    xlabel('CONV Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

%%PLOT 14
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 1:1
    histogram([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)],60)
    ylabel('Frequency')
    xlabel('Range of Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node (Pixels)')
end
hold off;
drawnow;

figure;
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    plot([dataStruct.loop.object(i).distance;records.halfEdge(dataStruct.loop.object(i).EL(end),5) + dataStruct.loop.object(i).distance(end)],[dataStruct.loop.object(i).radius;dataStruct.loop.object(i).radius(end)], 'Color',colorMat(1,:));
    ylabel('Radius (Pixels)')
    xlabel('Hole Cumulative Arc Length on Path (Pixels)')
end
hold off;
drawnow;

figure;
hold on;
gausFilt = gausswin(20);
colorMat = jet(records.numObjects);
for i = 19:19
    plot([dataStruct.loop.object(i).distance;records.halfEdge(dataStruct.loop.object(i).EL(end),5) + dataStruct.loop.object(i).distance(end)],imfilter([dataStruct.loop.object(i).radius;dataStruct.loop.object(i).radius(end)],gausFilt, 'circular'), 'Color',colorMat(1,:));
    ylabel('Radius (Pixels)')
    xlabel('CONV Hole Cumulative Arc Length on Path (Pixels)')
end
hold off;
drawnow;

%%PLOT 10
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    histogram(dataStruct.loop.object(i).radius,60)
    ylabel('Frequency')
    xlabel('Hole Radius Range (Pixels)')
end
hold off;
drawnow;

%%PLOT 11
% subplot('Position',[2/4,1/12,1/4,10/12],'Color',[1,1,1]);
% title('Bound Prof')
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    plot([dataStruct.loop.object(i).boundaryProfile], 'Color',colorMat(1,:));
    ylabel('Distance to Internal Cycle');
    xlabel('Hole Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

figure;
hold on;
gausFilt = gausswin(20);
colorMat = jet(records.numObjects);
for i = 19:19
    plot(imfilter([dataStruct.loop.object(i).boundaryProfile],gausFilt, 'circular'), 'Color',colorMat(1,:));
    ylabel('Distance to Internal Cycle');
    xlabel('CONV Hole Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

%%PLOT 12
figure;
hold on;
% colorMat = jet(records.numObjects);
for i = 19:19
    histogram(dataStruct.loop.object(i).boundaryProfile,60)
    ylabel('Frequency')
    xlabel('Hole Range of Distance to Internal Cycle from Boundary (Pixels)')
end
hold off;



%%PLOT 13
% subplot('Position',[2/4,1/12,1/4,10/12],'Color',[1,1,1]);
% title('Bound Prof')
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    plot([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)], 'Color',colorMat(1,:));
    ylabel('Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node');
    xlabel('Hole Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;

figure;
gausFilt = gausswin(20);
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    plot(imfilter([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)],gausFilt, 'circular'),'Color',colorMat(1,:));
    ylabel('Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node');
    xlabel('CONVHole Cumulative Arc Length on Circumference (Pixels)');
end
hold off;
drawnow;
%%PLOT 14
figure;
hold on;
colorMat = jet(records.numObjects);
for i = 19:19
    histogram([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)],60)
    ylabel('Frequency')
    xlabel('Hole Range of Ratio of Distance of Boundary to Nearest Cycle and Radius of Nearest Cycle Node (Pixels)')
end
hold off;
drawnow;


% subplot('Position',[3/4,1/12,1/4,10/12],'Color',[1,1,1]);
% figure;
% title('Ratio')
% hold on;
% for i = 1:numInObjectProfiles
% plot([dataStruct.loop.object(i).boundaryProfile./records.vorVert(dataStruct.loop.object(i).boundaryToCycleNode,3)], 'Color',colorMat(i,:));
% end
% hold off;
