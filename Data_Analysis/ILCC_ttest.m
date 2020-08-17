%t-test
ILCC = image_level_cluster_count;
borderType = 1;
firstSet = 2;
secondSet = 4;
imageRange1 = (firstSet-1)*5+1:firstSet*5;
imageRange2 = (secondSet-1)*5+1:secondSet*5;
figure(111111)
bar(mean(ILCC(imageRange1,:)) - mean(ILCC(imageRange2,:)))

ILCC = image_level_cluster_count;
for i = 1:12
[h,p] = ttest2(ILCC(imageRange1,i),ILCC(imageRange2,i));
if(h)
   disp([num2str(i) ': ' num2str(p)]); 
end

end