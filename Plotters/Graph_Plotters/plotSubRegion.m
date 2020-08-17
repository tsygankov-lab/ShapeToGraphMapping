%% plotSubRegion - Plots Subgraphs in the Voronoi Diagram
%  plotOutline(records, regionID)
%  lineHandle = plotSubRegion(records, regionID, inGraph, 'Options',...)
%  lineHandle = plotSubRegion(records, cycleInfo, 'Options',...)
%  lineHandle = plotSubRegion(records, 'regionInfo', regionID, 'inGraph',inGraph, 'Options',...)
%  lineHandle = plotSubRegion(records, 'regionInfo', cycleInfo, 'Options',...)
%Required Inputs:
%   records - Voronoi records structure
%   regionID or cycleInfo:
%       regionID - The color of the corresponding subregion. Additionally
%           will require 'inGraph' to specify the ingraph or outgraph
%           inGraph - Selects either the ingraph or outgraph for a specific
%               color
%               1 - in graph
%               0 - out graph
%       cycleInfo - The cycleInfo struct returned from getCycleInfo.
%           In-graph does not need to be specified when using cycleInfo.
%   
%   Any valid parameter to 'line' can be passed as a option
%Outputs:
%   lineHandle - The handle object to the plot.
function [lineHandle, legacy_outer_handle] = plotSubRegion(records, varargin)
lineHandle = [];
legacy_outer_handle = [];

% Legacy input handler. Match = 0 if it does not match the old format. This is used to handle old code which has not been updated to the new plotting interface
[MATCH, lineHandle, legacy_outer_handle] = legacyInputHandler(records, varargin);
if(MATCH)
    return;
end

% Parsing input
p = inputParser;
p.KeepUnmatched = true;
addRequired(p,'regionInfo');

addOptional(p,'inGraph',[]);
parse(p, varargin{:})
inp = p.Results;

if(isempty(inp.regionInfo))
    return; %Region was empty, abort without error (can happen with some cycleInfos)
end
if(isnumeric(inp.regionInfo)) %user passed a region ID number/color
    regionID = inp.regionInfo;
    graphRegion = ~inp.inGraph;
    if(isempty(graphRegion))
        error('if a boundary color is used, user must specify foreground/background subregion')
    end
    vertList_Binary = (records.verts.locationType(:,1) == graphRegion | records.verts.locationType(:,1) == 2) & (records.verts.color(:,1) == regionID | records.verts.color(:,2) == regionID | records.verts.color(:,3) == regionID);
    
else
    if(~isstruct(inp.regionInfo)) 
        error('Must pass a cycleInfo struct or a numeric boundary color value/regionID')
    end
    %user passed a cycleinfo
    vertList_Binary = inp.regionInfo.binaryFilt;
end

% Assume unmatched arguments are arguments for plotting
lineHandle = plotFromVertList(records, vertList_Binary, p.Unmatched);
end

function [MATCH, INNER, OUTER] = legacyInputHandler(records, ARGS)
%Legacy Input mode...
MATCH = false;
OUTERFLAG = false;
INNERFLAG = false;
lineSpec_INNER = {};
lineSpec_OUTER = {};
INNER = [];
OUTER = [];
if(isnumeric(ARGS{1}))
    regionID = ARGS{1};
    if(length(ARGS) > 1 && (isnumeric(ARGS{2}) && length(ARGS{2}) == 3) || (ischar(ARGS{2}) && length(ARGS{2}) == 1) || isempty(ARGS{2}))
        INNERFLAG = ~isempty(ARGS{2});
        if(INNERFLAG)
            color_inner = ARGS{2};
        end
        if(~INNERFLAG && length(ARGS) == 2)
            return;
        end
        if(length(ARGS) > 2 && (isnumeric(ARGS{3}) && length(ARGS{3}) == 3) || (ischar(ARGS{3}) && length(ARGS{3}) == 1) || isempty(ARGS{3}))
            OUTERFLAG = ~isempty(ARGS{3});
            if(OUTERFLAG)
                color_outer = ARGS{3};
            end
            if(~INNERFLAG && ~OUTERFLAG)
                return;
            end
        end
        if(length(ARGS) > 3 && iscell(ARGS{4}))
            lineSpec_INNER = ARGS{4};
        end
        if(length(ARGS) > 4 && iscell(ARGS{5}))
            lineSpec_OUTER = ARGS{5};
        end
        if(INNERFLAG)
            vertList_Binary = (records.verts.locationType(:,1) == 0 | records.verts.locationType(:,1) == 2) & (records.verts.color(:,1) == regionID | records.verts.color(:,2) == regionID | records.verts.color(:,3) == regionID);
            lineSpec_INNER = ['Color',color_inner, lineSpec_INNER];
            INNER = plotFromVertList(records, vertList_Binary, lineSpec_INNER{:});
            MATCH = true;
        end
        if(OUTERFLAG)
            vertList_Binary = (records.verts.locationType(:,1) == 0 | records.verts.locationType(:,1) == 2) & (records.verts.color(:,1) == regionID | records.verts.color(:,2) == regionID | records.verts.color(:,3) == regionID);
            lineSpec_OUTER = ['Color',color_outer, lineSpec_OUTER];
            INNER = plotFromVertList(records, vertList_Binary, lineSpec_OUTER{:});
            MATCH = true;
        end
    end
end
end