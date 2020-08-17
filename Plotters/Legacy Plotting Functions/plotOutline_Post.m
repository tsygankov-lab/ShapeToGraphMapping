function plotOutline_Post(records, colorMat, lineParams,pointParams)
%Three args - all borders are colored by if they are an outter or inner border
%Two args - all borders are colored by looping through the colorMatObject list
%If the colorMatObj matrix does not match the size of the number of borders, a single color is drawn per edge instead
%If 1 arg - default color.
resetHoldState = 0;
if(ishold == 0)
    cla;
    resetHoldState = 1;
    hold on;
end
if(nargin < 2 || isempty(colorMat))
    colorMat = [0,0,1];
end
if(nargin < 3 || isempty(lineParams))
    lineParams = {'LineWidth',2};
end
if(nargin < 4 || isempty(pointParams))
    pointParams = {'Marker','.'};
end
%%The first block is outdated - use plotOutline_Simple
if(size(colorMat,1) == 1)
    EL = records.inputs(records.inputs(:,1)==0,3:4);
    V = records.inputs(records.inputs(:,1)~=0,3:4);
    % 	        vertexCoor = records.inputs(records.inputs(:,1)==1,3:4);
    
    xPlot = nan(size(EL,1),3);
    yPlot = nan(size(EL,1),3);
    xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
    yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
    
    VProc = false(size(V,1),1);
    VProc(EL(:,1)) = true;
    VProc(EL(:,2)) = true;
    
    line(xPlot',yPlot','Color',colorMat(1,:), lineParams{:});
    xPlot = nan(size(V(~VProc,1),1),2);
    yPlot = nan(size(V(~VProc,2),1),2);
    xPlot(1:end,:) = [V(~VProc,1),nan(size(V(~VProc,1)))];
    yPlot(1:end,:) = [V(~VProc,2),nan(size(V(~VProc,2)))];
    line(xPlot',yPlot','Color',colorMat(1,:), pointParams{:});
elseif(size(colorMat,1) == 2)
    EL = records.inputs(records.inputs(:,1)==0 & records.inputs(:,2) <= records.numNonHoles,3:4);
    Vobj  = records.inputs(records.inputs(:,1)~=0 & records.inputs(:,2) <= records.numNonHoles,3:4);
    %         records.inputs(records.inputs(:,1)==0 & records.inputs(:,2) <= numNonHoles,3:4);
    %         vertFilt = records.inputs(:,1)==1 & records.inputs(:,2) <= numNonHoles;
    % 		vertexCoor = records.inputs( ,3:4);
    
    xPlotOBJ = nan(size(EL,1),3);
    yPlotOBJ = nan(size(EL,1),3);
    xPlotOBJ(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
    yPlotOBJ(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
    VProcOBJ = false(size(Vobj,1),1);
    VProcOBJ(EL(:,1)) = true;
    VProcOBJ(EL(:,2)) = true;
    
    EL = records.inputs(records.inputs(:,1)==0 & records.inputs(:,2) > records.numNonHoles,3:4);
    Vhole = records.inputs(records.inputs(:,1)~=0 & records.inputs(:,2) > records.numNonHoles,3:4);
    % 		vertexCoor = records.inputs(records.inputs(:,1)==1 & records.inputs(:,2) > numNonHoles ,3:4);
    
    xPlotHOLE = nan(size(EL,1),3);
    yPlotHOLE = nan(size(EL,1),3);
    xPlotHOLE (1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
    yPlotHOLE (1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
    VProcHOLE = false(size(Vhole,1),1);
    VProcHOLE(EL(:,1)) = true;
    VProcHOLE(EL(:,2)) = true;
    
    
    line(xPlotOBJ',yPlotOBJ','Color',colorMat(1,:),lineParams{:});
    line(xPlotHOLE',yPlotHOLE','Color',colorMat(2,:),lineParams{:});
    
    xPlot = nan(size(Vobj(~VProcOBJ,1),1),2);
    yPlot = nan(size(Vobj(~VProcOBJ,2),1),2);
    xPlot(1:end,:) = [Vobj(~VProcOBJ,1),nan(size(Vobj(~VProcOBJ,1)))];
    yPlot(1:end,:) = [Vobj(~VProcOBJ,2),nan(size(Vobj(~VProcOBJ,2)))];
    line(xPlot',yPlot','Color',colorMat(1,:), pointParams{:});
    
    
    xPlot = nan(size(Vhole(~VProcHOLE,1),1),2);
    yPlot = nan(size(Vhole(~VProcHOLE,2),1),2);
    xPlot(1:end,:) = [Vhole(~VProcHOLE,1),nan(size(Vhole(~VProcHOLE,1)))];
    yPlot(1:end,:) = [Vhole(~VProcHOLE,2),nan(size(Vhole(~VProcHOLE,2)))];
    line(xPlot',yPlot','Color',colorMat(2,:), pointParams{:});
elseif(size(colorMat,1) == max(records.inputs(:,2)))
    for i = 1:max(records.inputs(:,2))
        EL = records.inputs(records.inputs(:,1)==0 & records.inputs(:,2) == i,3:4);
%         V =  records.inputs(records.inputs(:,1)~=0 & records.inputs(:,2) == i,3:4);
        % 	    	vertexCoor = records.inputs(records.inputs(:,1)==1 & records.inputs(:,2) == i ,3:4);
%         VProc = false(size(V,1),1);
%         VProc(EL(:,1)) = true;
%         VProc(EL(:,2)) = true;
        
        xPlot = nan(size(EL,1),3);
        yPlot = nan(size(EL,1),3);
        xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
        yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
        
        line(xPlot',yPlot','Color',colorMat(i,:),lineParams{:});
%         xPlot = nan(size(V(~VProc,1),1),2);
%         yPlot = nan(size(V(~VProc,2),1),2);
%         xPlot(1:end,:) = [V(~VProc,1),nan(size(V(~VProc,1)))];
%         yPlot(1:end,:) = [V(~VProc,2),nan(size(V(~VProc,2)))];
%         line(xPlot',yPlot','Color',colorMat(i,:), pointParams{:});
    end
end
if(resetHoldState)
    hold off;
end

end

