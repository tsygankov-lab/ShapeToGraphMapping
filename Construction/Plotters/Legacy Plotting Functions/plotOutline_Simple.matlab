function plotOutline_Simple(records, colorMat)
	resetHoldState = 0;
	if(ishold == 0)
		cla;
		resetHoldState = 1;
		hold on;
	end
	if(nargin < 2)
		colorMat = [0.5,0.5,0.5]
	end
	if(~colorByObjectType)
	        EL = records.input(records.input(:,1)==0,3:4);
% 	        vertexCoor = records.input(records.input(:,1)==1,3:4);
	        
	        xPlot = nan(size(EL,1),3);
	        yPlot = nan(size(EL,1),3);
	        xPlot(1:end,:) = [records.input(EL(:,1),3),records.input(EL(:,2),3),nan(size(EL(:,1)))];
	        yPlot(1:end,:) = [records.input(EL(:,1),4),records.input(EL(:,2),4),nan(size(EL(:,1)))];
	        
	        line(xPlot',yPlot','Color',colorMat, 'LineWidth', 4);
	end
    if(resetHoldState)
    	hold off;
    end

end
