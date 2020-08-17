%%Plots all input edges. Will not plot isolated points
%Will make interaction with the diagram oddly slow
%Inputs:
%   records structure (output from Voronoi_DT
%   An [r,g,b] array or a color character code. Colors all edges with this
%   color value.
%   Line params - a Cell array consisting of all options which the line
%   function can use
%Outputs:
%   None
function plotOutline_Simple(records, colorMat,lineParams)
    if(isempty(lineParams))
        lineParams = {'LineWidth',1};
    end
	if(nargin < 2)
		colorMat = [0.5,0.5,0.5];
	end
	        EL = records.inputs(records.inputs(:,1)==0,3:4);
% 	        vertexCoor = records.inputs(records.inputs(:,1)==1,3:4);
	        
	        xPlot = nan(size(EL,1),3);
	        yPlot = nan(size(EL,1),3);
	        xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
	        yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
	        
	        line(xPlot',yPlot','Color',colorMat, lineParams{:});
	

end
