[filename,pathname,filterindex] = uigetfile('*.tif','Choose a masked TIFF-image ');

if filename~=0
    
   image = imread([pathname filename], 1);
   if length(size(image))==3
       image=image(:,:,1);
   end
   image = cast(image, 'double');
   image(image>0)=1;
    
   [B,L]=bwboundaries(image,'noholes');
   A=regionprops(logical(image),'Area');
   Area=[A.Area];
   [~,ind]=max(Area);
   if ~isempty(ind)
       [b,~]=regbound(B{ind});
       L(L~=ind)=0; L(L==ind)=1;                                                                    
   end
   
   figure;
   colormap('jet');
   imagesc(1-image);
   hold on;
   plot([b(:,2); b(1,2)],[b(:,1); b(1,1)],'y','LineWidth',2);
   axis image;
   axis off;
end
