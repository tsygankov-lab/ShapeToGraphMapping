cm = jet(records.numNonHoles);
hold on;
for i = 1:records.numNonHoles
    plotVoronoiSkeleton_SingleRegion(records,i,cm(i,:));
end
