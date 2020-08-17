%%REFACTORCHECK
function plotAllFaces_Patch(records)
figure;
hold on;
colorMat = jet(length(records.Faces));
for i = 1:length(records.Faces)
   plotFace_Patch(records, records.Faces(i), colorMat(i,:));
end