%% plotOutline - Plots region outlines (For use with Images)
%  plotOutline(records)
%  lineHandle = plotOutline(records)
%  lineHandle = plotOutline(records,'Options',...)
%  lineHandle = plotOutline(records,regionID,'Options',...)
%  lineHandle = plotOutline(records,cycleInfo,'Options',...)
%  lineHandle = plotOutline(records,'regionInfo',regionID,'Options',...)
%  lineHandle = plotOutline(records,'regionInfo',cycleInfo,'Options',...)
%Required Inputs:
%   records: Voronoi records structure
%Optional Inputs:
%   'regionInfo' (default, [])
%       regionID - plots the outline for the specified region
%       cycleInfo - plots the outline using the cycleInfo struct from
%           getCycleInfo
%       Empty or unspecified - Plots All Outlines
%   
%   Any valid parameter to 'line' can be passed as a option
%Outputs:
%   lineHandle - The handle object to the plot.
function lineHandle = plotOutline(records, varargin)

p = inputParser;
p.KeepUnmatched = true;

addOptional(p,'regionInfo',[])

parse(p,varargin{:})
inp = p.Results;

% Plot by regionID
if(~isempty(inp.regionInfo) && isnumeric(inp.regionInfo))
    colorFilt = inp.regionInfo;
    inputFilt = records.inputs(:,2) == colorFilt;
    inputRed = records.inputs(inputFilt,:);
    
    EL = inputRed(inputRed(:,1)==0,3:4);
    EL_t = EL(1:2:end-1,:); %Edges are duplicated as they are treated as half edges
    EL = EL_t;
    
    xPlot = nan(size(EL,1),3);
    yPlot = nan(size(EL,1),3);
    xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
    yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
    
    lineHandle = line(xPlot',yPlot',p.Unmatched);
    
    
else % regionInfo passed or no id specified...
    CYCLEINFO_FLAG = false;
    cycleInfo = [];
    %Have to verify what was passed was not a cycle info since argument is
    %optional
    if(isstruct(inp.regionInfo)) %we know we have a cycle info as it was specified with a flag
        CYCLEINFO_FLAG = true;
        cycleInfo = inp.regionInfo;
    elseif(~isempty(varargin)) %see if first varargin matched a cycleinfo pattern
        inparg = varargin{1};
        if(isstruct(inparg))
            if(isfield(inparg,'Vertices'))
                CYCLEINFO_FLAG = true;
                
                cycleInfo = inparg;
                args = {};
                if(length(varargin) > 1)
                    args = varargin(2:end);
                end
                parse(p,args{:}); %re-parse
            end
        end
    end
    if(CYCLEINFO_FLAG) %a cycleinfo was passed
        xPlot = [cycleInfo.boundaryVertexCoor(:,1);cycleInfo.boundaryVertexCoor(1,1)];
        yPlot = [cycleInfo.boundaryVertexCoor(:,2);cycleInfo.boundaryVertexCoor(1,2)];
        lineHandle = line(xPlot',yPlot',p.Unmatched);
    else %no cycleinfo was passed
        %Plot all outlines
        EL = records.inputs(records.inputs(:,1)==0,3:4);
        EL_t = EL(1:2:end-1,:); %Edges are duplicated as they are treated as half edges
        EL = EL_t;
        
        xPlot = nan(size(EL,1),3);
        yPlot = nan(size(EL,1),3);
        xPlot(1:end,:) = [records.inputs(EL(:,1),3),records.inputs(EL(:,2),3),nan(size(EL(:,1)))];
        yPlot(1:end,:) = [records.inputs(EL(:,1),4),records.inputs(EL(:,2),4),nan(size(EL(:,1)))];
        
        lineHandle = line(xPlot',yPlot',p.Unmatched);
    end
end

end

% if(nargin < 5 || isempty(pointParams))
%     pointParams = {'Marker','.'};
% end
% if(nargin > 5 && ~isempty(pointParams))
%     VProc = false(size(records.inputs,1),1);
%     VProc(V) = true;
%     VProc(EL(:,1)) = false;
%     VProc(EL(:,2)) = false;
%     vClear = records.inputs(VProc,3:4);
%     xPlot = nan(size(vClear,1),2);
%     yPlot = nan(size(vClear,1),2);
%     xPlot(1:end,:) = [vClear(:,1),nan(size(vClear,1))];
%     yPlot(1:end,:) = [vClear(:,2),nan(size(vClear,1))];
%     line(xPlot',yPlot','Color',colorMatObject(:), pointParams{:});
% end
% if(resetHoldState)
%     hold off;
% end


