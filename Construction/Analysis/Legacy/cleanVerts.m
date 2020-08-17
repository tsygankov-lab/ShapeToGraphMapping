function records = cleanVerts(records, labelMat)
minX = 0;
minY = 0;
maxX = size(labelMat,1);
maxY = size(labelMat,2);
for i = 1:length(records.Vertex)
   %%Assign color
   %%Go through edges
   %%IF edge is invalidated, delete it
   %%if e
end