%% plotInputs - Plot Point Inputs
%  plotPoints(records)
%  lineHandle = plotPoints(records)
%  lineHandle = plotPoints(records,)
%  lineHandle = plotPoints(records,'Options',...)
%  lineHandle = plotOutline(records,'ColorFilter',color,'FaceIDFilter',faceID,'InputTypeFilter',inputTypeFilter,'Options',...)
%Required Inputs:
%   records: Voronoi records structure
%Optional Inputs:
%   'ColorFilter' - The color ID of vertices to include in the plot.
%       Defaults to no filter.
%   'FaceIDFilter' - The FaceID of vertices to include in the plot.
%       Defaults to no filter *to be tested
%   'InputIdxFilter' - Filter inputs by index
%       Defaults to no filter *to be tested
%   'InputTypeFilter' - Filter to only plot lines or only plot non-endpoint
%       vertices 
%       0 - No filter (default)
%       1 - Non-Endpoint Vertices only *to be tested
%       2 - Edges only
%   Any valid parameter to 'line' can be passed as a option
%Outputs:
%   linehandle - The handle object to the plot.
%Notes:
%   Must pass 'Marker' along with a marker style for the vertex objects to
%   be visible
function lineHandle = plotInputs(records, varargin)
p = inputParser;
p.KeepUnmatched = true;
addOptional(p,'ColorFilter',[]);
addOptional(p,'FaceIDFilter',[]);
addOptional(p,'InputIdxFilter',[]);
addOptional(p,'InputTypeFilter',0)
parse(p,varargin{:})
inp = p.Results;
inputFilt = records.inputs(:,1) == 1;
vertsOnly = records.inputs(inputFilt,:);

edgeFilt = records.inputs(:,1) == 0;
endpointList = unique([records.inputs(edgeFilt,3); records.inputs(edgeFilt,4)]);
vertFilt(endpointList) = false;

fullFiltList = true(size(records.inputs,1),1);
if(~isempty(inp.ColorFilter))
    fullFiltList = fullFiltList & any(records.inputs(:,2) == inp.ColorFilter,2);
end
if(~isempty(inp.FaceIDFilter))
    fullFiltList = fullFiltList & any(records.inputs(:,5) == inp.FaceIDFilter,5);
end
if(~isempty(inp.InputIdxFilter))
   filt_t = false(size(fullFiltList));
   filt_t(inp.InputIdxFilter) = true;
   fullFiltList = fullFiltList & filt_t;
end
vertFilt = vertFilt & fullFiltList(1:length(vertFilt));

%% Edges...
if(inp.InputTypeFilter == 0 || inp.InputTypeFilter == 2)
    EL = records.inputs(records.inputs(:,1)==0 & fullFiltList,3:4);
    EL_t = EL(2:2:end,:); %Edges are duplicated as they are treated as half edges
    EL = EL_t;
    
    points_E = nan(size(EL,1)*3,2);
    points_E(1:3:end,:) = [records.inputs(EL(:,1),3), records.inputs(EL(:,1),4)];
    points_E(2:3:end,:) = [records.inputs(EL(:,2),3), records.inputs(EL(:,2),4)];
end
%% Non-Endpoint Vertices
if(inp.InputTypeFilter == 0 || inp.InputTypeFilter == 1)
    V = vertsOnly(vertFilt,3:4);
    points_V = nan(size(V,1)*2,2);
    points_V(1:2:end) = [V(:,1),V(:,2)];
end
if(inp.InputTypeFilter == 0)
    points = [points_V;points_E];
elseif(inp.InputTypeFilter == 1)
    points = points_V;
elseif(inp.InputTypeFilter == 2)
    points= points_E;
end
%% Plot
lineHandle = line(points(:,1),points(:,2),p.Unmatched);
end

