function adjMat = subGraph2AdjMat_SLOW(records, loopStruct)
r2sV = loopStruct.records2SubgraphMap_Vertices;
verts = find((loopStruct.binaryFilt));
filt = loopStruct.binaryFilt;
adjMat = zeros(length(verts));
for i = 1:length(verts)
    deg = records.verts.degree(verts(i));
    if(deg==4) 
        deg = 3;
    end
    for j = 1:(deg)
       if(filt(records.edges.origin(records.verts.edgeIDList(verts(i),j),2)))
           adjMat(r2sV(verts(i)),r2sV(records.edges.origin(records.verts.edgeIDList(verts(i),j),2))) = 1;
       end
    end
end