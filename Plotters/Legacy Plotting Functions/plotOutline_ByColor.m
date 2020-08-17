function plotOutline_ByColor(records, colorFilt, colorMatObject,lineParams,pointParams)
if(nargin < 4 || isempty(lineParams))
    lineParams = {'LineWidth',1};
end

%Three args - all borders are colored by if they are an outter or inner border
%Two args - all borders are colored by looping through the colorMatObject list
%If the colorMatObj matrix does not match the size of the number of borders, a single color is drawn per edge instead
%If 1 arg - default color.
% resetHoldState = 0;
% if(ishold == 0)
%     cla;
%     resetHoldState = 1;
%     hold on;
% end
inputFilt = records.inputs(:,2) == colorFilt;
inputRed = records.inputs(inputFilt,:);
%%The first block is outdated - use plotOutline_Simple
EL = inputRed(inputRed(:,1)==0,3:4);
V = inputFilt(inputRed(:,1)~=0);
% 	        vertexCoor = records.inputs(records.inputs(:,1)==1,3:4);

xPlot = nan(size(EL,1),3);
yPlot = nan(size(EL,1),3);
xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];

line(xPlot',yPlot','Color',colorMatObject(:), lineParams{:});

% if(nargin < 5 || isempty(pointParams))
%     pointParams = {'Marker','.'};
% end
if(nargin > 5 && ~isempty(pointParams))
    VProc = false(size(records.inputs,1),1);
    VProc(V) = true;
    VProc(EL(:,1)) = false;
    VProc(EL(:,2)) = false;
    vClear = records.inputs(VProc,3:4);
    xPlot = nan(size(vClear,1),2);
    yPlot = nan(size(vClear,1),2);
    xPlot(1:end,:) = [vClear(:,1),nan(size(vClear,1))];
    yPlot(1:end,:) = [vClear(:,2),nan(size(vClear,1))];
    line(xPlot',yPlot','Color',colorMatObject(:), pointParams{:});
end
% if(resetHoldState)
%     hold off;
% end

end

