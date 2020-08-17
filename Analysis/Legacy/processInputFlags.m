function settingsList = processInputFlags(vertexCoor, EL, vararg)
%%Refactor target.  A bit bloated now!
numArg = length(vararg);
settingsList.DrawImage = 0;
settingsList.DisconnectedEdgesPresent = 1;
settingsList.AXISWIDTH = [nan,nan,nan,nan];
settingsList.DrawRejectedIntercepts = 0;
settingsList.DrawArcs = 0;
settingsList.DrawArcEllipseResolution = 50;
settingsList.DrawArcParabolaResolution = 50;
settingsList.DrawEventLogIDatVertex = 0;
settingsList.DrawImageAnimationAxisUpperRight = 0;
settingsList.DrawImageHideEdgesWithNoVoronoiVertex = 0;
settingsList.ForceVertexEventsOnStraightLines = 0;
settingsList.DrawImageEL = 1;
settingsList.ObjectLengthMatrix = [];
settingsList.MultiLayer = 0;
settingsList.DrawInfiniteBisectors = 0;
settingsList.DisplayNextToPointer = 0;
settingsList.DrawImageAnimationStyle = 0;
settingsList.DrawImageAnimationSteps = 5;
settingsList.DrawImageAnimationDistance = 1;
settingsList.DrawImageAnimationAxis = 0;
settingsList.VoronoiEdgeColor = [0,0.6,0.8];
settingsList.VoronoiImplicitEdgeColor = [0,0.8,0.5];
settingsList.VoronoiInfiniteEdgeColor = [0,0.2,0.8];
settingsList.VoronoiVertexColor = [1,1,1];
settingsList.DrawEdgeListColor = [1,1,1];
settingsList.DrawBackgroundColor = [0,0,0];
settingsList.DrawImageAnimationLimitMaximumAxis = 1;
settingsList.DrawFutureCircleEvents = 1;
settingsList.DrawCircleResolution = 50;
settingsList.DrawRBTTree = 0;
settingsList.DrawSEQTree = 0;
settingsList.DrawInfiniteVoronoiEdges = 1;
settingsList.VoronoiNullifiedEdgeColor = [0,0.2,0.8];
settingsList.ImageMask = [];
settingsList.nullifyVertices = 0;
settingsList.LogImageResolutionScaleFactor = '-r200';
settingsList.IterationNumber =1;
settingsList.LogImage = 0;
settingsList.LogImagePath = nan;
settingsList.LogImageName = 'Output';
settingsList.figureHandle = nan;
settingsList.axesHandle = nan;
settingsList.ReturnFullOutputInfo = 1;
settingsList.DrawImageAnimationStopAtLastPoint = 1;
settingsList.LineThickness = 0.5;
settingsList.Center = [0,0];
% settingsList.numColors = 1;
    settingsList.numColors = 0;
    settingsList.vertColorList = zeros(size(vertexCoor,1),1);
    settingsList.edgeColoredList = zeros(size(EL,1),1);
%settingsList.vertColorList = ones(size(vertexCoor,1),1);
% settingsList.edgeColoredList = ones(size(EL,1),1);
settingsList.DEBUGTreeVerificationAfterIteration = 0;
% settingsList.vertColorList = repmat(-1,size(vertexCoor,1),1);
settingsList.LogDebug = 0;
settingsList.LogFileHandle = '';
settingsList.ValidateAllCircleEvents = 0;
settingsList.ExceptionOnValidationFailure = 0;
settingsList.vertexOverrideFaceID = 0;
settingsList.edgeOverrideFaceID = 0;
settingsList.vertexFaceIDList = zeros(size(vertexCoor,1),1);
settingsList.edgeFaceIDList = zeros(size(EL,1),2);
settingsList.verifyInputValidity = 0; 
settingsList.autoCreateVoronoiEdgeOnLines = 0;
settingsList.imageStruct = [];
try
    for i = 1:2:numArg
        switch vararg{i}
            case 'ImageStruct'
                settingsList.imageStruct = vararg{i+1};
        	case 'CreateHalfEdgeOnLineInput'
        		settingsList.autoCreateVoronoiEdgeOnLines{i+1} = vararg{i+1};
                warning('To Be Implemented');
        	case 'FaceIDVector'
        		if(size(vararg{i+1},1) == 1 && vararg{i+1} == -1)
        			settingsList.vertexOverrideFaceID = -1; %%This only really works if the endpoint is not shared....
        		else
        		if(length(vararg{i+1}) ~= size(vertexCoor,1))
        			warning('The FaceIDVector must have the same number of inputs as vertices.  Do not add IDs')
        		else
        			settingsList.vertexOverrideFaceID = 1;
        			settingsList.vertexFaceIDList = vararg{i+1};
        		end
        	end
        	case 'EdgeFaceIDVector'
        		if(size(vararg{i+1},1 == 1) && vararg{i+1} == -1)
        			settingsList.edgeOverrideFaceID = -1;
        		else
	        		if(length(vararg{i+1}) ~= size(EL,1))
	        			warning('The FaceIDVector for edges must match the number of edges.')
	        		else
	        			if(size(vararg{i+1},2) == 2)
	        				settingsList.edgeOverrideFaceID = 2;
	  						settingsList.edgeFaceIDList = vararg{i+1};
	  					elseif(size(vararg{i+1},1) == 1)
	  						settingsList.edgeOverrideFaceID = 1;
	  						settingsList.edgeFaceIDList = vararg{i+1};
						else
							warning('The edge list vector must be nx1 (reverse edge has a negative value) or nx2 (independent assignment of each edge face');
						end
	        		end
        		end
        	case 'CheckEdgeIntersects'
        		settingsList.verifyInputValidity = vararg{i+1};
        		warning('Auto edge checking to be implemented')
            case 'ExceptionOnValidationFailure'
                settingsList.ExceptionOnValidationFailure = vararg{i+1};
            case 'ValidateAllCircleEvents'
                settingsList.ValidateAllCircleEvents = vararg{i+1};
            case 'LogDebug'
                settingsList.LogDebug = vararg{i+1};
            case 'LogFileHandle'
                settingsList.LogFileHandle = vararg{i+1};
            case 'Center'
                settingsList.Center = vararg{i+1};
            case 'DrawImage'
                if(isnumeric(vararg{i+1}))
                    settingsList.DrawImage = vararg{i+1};
                else
                    warning('Draw Image requires a number 0 or 1');
                end
            case 'DisconnectedEdgesPresent'
                settingsList.DisconnectedEdgesPresent = vararg{i+1};
            case 'DrawAxisSize'
                if(length(vararg{i+1} == 4))
                    settingsList.AXISWIDTH = vararg{i+1};
                else
                    warning('Axis Width needs 4 values [x1,x2,y1,y2]');
                end
                
            case 'DrawRejectedIntercepts'
                if(isnumeric(vararg{i+1}))
                    settingsList.DrawRejectedIntercepts = vararg{i+1};
                else
                    warning('DrawRejectedIntercepts requires a numeric argument');
                end
            case 'DrawArcs'
                if(isnumeric(vararg{i+1}))
                    
                    settingsList.DrawArcs = vararg{i+1};
                else
                    warning('DrawArcs requires a numeric argument');
                end
            case 'DrawArcEllipseResolution'
                settingsList.DrawArcEllipseResolution = vararg{i+1};
            case 'DrawArcParabolaResolution'
                settingsList.DrawArcParabolaResolution = vararg{i+1};
            case 'DrawEventLogIDatVertex'
                settingsList.DrawEventLogIDatVertex = vararg{i+1};
            case 'DrawImageAnimationStyle'
                settingsList.DrawImageAnimationStyle = vararg{i+1};
            case 'DrawImageAnimationSteps'
                settingsList.DrawImageAnimationSteps = vararg{i+1};
            case 'DrawImageAnimationDistance'
                settingsList.DrawImageAnimationDistance = vararg{i+1};
            case 'DrawImageAnimationAxis'
                settingsList.DrawImageAnimationAxis = vararg{i+1};
            case 'VoronoiEdgeColor'
                if(length(vararg{i+1} == 3))
                    
                    settingsList.VoronoiEdgeColor = vararg{i+1};
                else
                    warning('Colors must be a 3 value array');
                end
            case 'VoronoiImplicitEdgeColor'
                if(length(vararg{i+1} == 3))
                    
                    settingsList.VoronoiImplicitEdgeColor = vararg{i+1};
                else
                    warning('Colors must be a 3 value array');
                end
            case 'VoronoiVertexColor'
                if(length(vararg{i+1} == 3))
                    
                    settingsList.VoronoiVertexColor = vararg{i+1};
                else
                    warning('Colors must be a 3 value array');
                end
            case 'DrawEdgeListColor'
                if(length(vararg{i+1} == 3))
                    
                    settingsList.DrawEdgeListColor = vararg{i+1};
                else
                    warning('Colors must be a 3 value array');
                end
            case 'DrawBackgroundColor'
                if(length(vararg{i+1} == 3))
                    settingsList.DrawBackgroundColor = vararg{i+1};
                else
                    warning('Colors must be a 3 value array');
                end
            case 'LogImage'
                settingsList.LogImage = vararg{i+1};
            case 'LogImagePath'
                settingsList.LogImagePath = vararg{i+1};
            case 'LogImageName'
                settingsList.LogImageName = vararg{i+1};
            case 'ReturnFullOutputInfo'
                settingsList.ReturnFullOutputInfo = vararg{i+1};
            case 'DrawImageAnimationAxisUpperRight'
                settingsList.DrawImageAnimationAxisUpperRight = vararg{i+1};
            case 'DrawImageAnimationStopAtLastPoint'
                settingsList.DrawImageAnimationStopAtLastPoint = vararg{i+1};
            case 'DrawImageAnimationLimitMaximumAxis'
                settingsList.DrawImageAnimationLimitMaximumAxis = vararg{i+1};
            case 'DrawImageAnimationLimitInterpolateAxisToFinalSetAxis'
                settingsList.DrawImageAnimationLimitInterpolateAxisToFinalSetAxis = vararg{i+1};
            case 'DrawFutureCircleEvents' 
                settingsList.DrawFutureCircleEvents = vararg{i+1};
            case 'DrawCircleResolution'
                settingsList.DrawCircleResolution = vararg{i+1};
            case 'DrawInfiniteVoronoiEdges'
                settingsList.DrawInfiniteVoronoiEdges = vararg{i+1};
            case 'VoronoiInfiniteEdgeColor'
                settingsList.VoronoiInfiniteEdgeColor = vararg{i+1};
            case 'DrawImageHideEdgesWithNoVoronoiVertex'
                settingsList.DrawImageHideEdgesWithNoVoronoiVertex = vararg{i+1};
            case 'ForceVertexEventsOnStraightLines'
                settingsList.ForceVertexEventsOnStraightLines = vararg{i+1};
            case 'DrawImageEL'
                settingsList.DrawImageEL = vararg{i+1};
            case 'ObjectLengthMatrix'
                settingsList.ObjectLengthMatrix = vararg{i+1};
                settingsList.MultiLayer = 1;
            case 'DrawInfiniteBisectors'
                settingsList.DrawInfiniteBisectors = vararg{i+1};
            case 'ImageMask'
                settingsList.ImageMask = vararg{i+1};
                settingsList.nullifyVertices = 1;
            case 'VoronoiNullifiedEdgeColor'
                 settingsList.VoronoiNullifiedEdgeColor = vararg{i+1};
            case 'LogImageResolutionScaleFactor'
                settingsList.LogImageResolutionScaleFactor = vararg{i+1};
            case 'DrawSEQTree'
                settingsList.DrawSEQTree = vararg{i+1};
            case 'DrawRBTTree' 
                settingsList.DrawRBTTree = vararg{i+1};
            case 'DEBUGTreeVerificationAfterIteration'
                settingsList.DEBUGTreeVerificationAfterIteration = vararg{i+1};
            case 'vertexColorList'
                if(size(vararg{i+1}) ~= size(vertexCoor,1))
                    warning(['Vertex Color list expected a vector of size ' num2str(size(vertexCoor,1)) ' but received a vector of size ' num2str(size(vararg{i+1})) '.  There must be one color for each vertex.']);
                else
                    settingsList.vertColorList = vararg{i+1};
                    settingsList.DisconnectedEdgesPresent = 0;
                end
            otherwise
                warning([vararg(i) ' Argument Unknown']);
        end
    end
catch ME
    warning('Something went wrong when processing your arguments - using defaults')
end
if(settingsList.LogDebug && isempty(settingsList.LogFileHandle))
    warning('Logging enabled but no file handle has been given. The output will be directed to the command window.  Note that messages may not be displayed immediately in some setups');
end

if(settingsList.DisconnectedEdgesPresent)
    vertColoredList = zeros(size(vertexCoor,1),1);
    edgeColoredList = zeros(size(EL,1),1);
    colors = 0;
    for i = 1:size(vertexCoor,1)
        if(~vertColoredList(i))
            colors = colors + 1;
            queue = zeros(size(vertexCoor,1),1);
            lastIndex = 0;
            vertColoredList(i) = colors;
            if(~isempty(EL))
            edgesLeft = EL(:,1) == i;
            edgesRight =  EL(:,2) ==  i;
            edgeColoredList([edgesLeft,edgesRight]) = colors;
            newObjects = unique([EL(edgesRight, 2), EL(edgesLeft,1)]);
            if(~isempty(newObjects))
                queue(lastIndex+1:length(newObjects)) = newObjects(:);
                lastIndex = length(newObjects);
                j = 1;
                while(queue(j)~=0)
                    vertColoredList(queue(j)) = colors;
                    edgesLeft = EL(:,1) == queue(j);
                    edgesRight = EL(:,2) ==  queue(j);
                    edgeColoredList([edgesLeft,edgesRight]) = colors;
                    newObjectsQueue = unique([EL(EL(:,1) == queue(j), 2), EL(EL(:,2) ==  queue(j)),1]);
                    for k = 1:length(newObjectsQueue)
                       if(~vertColoredList(newObjectsQueue(k)))
                           queue(lastIndex + 1) = newObjectsQueue(k);
                       end
                    end
                    j=j+1;
                end
            end
            end
        end
    end
    settingsList.numColors = colors;
    settingsList.vertColorList = vertColoredList;
    settingsList.edgeColoredList = edgeColoredList;
end
if(settingsList.DrawImage)
    if(isnan(settingsList.AXISWIDTH(1)))
        xMin = min(vertexCoor(:,1));
        xMax = max(vertexCoor(:,1));
        xWidth = xMax - xMin;
        yMin = min(vertexCoor(:,2));
        yMax = max(vertexCoor(:,2));
        yHeight = yMax - yMin;
        if(xWidth/yHeight < 0.5)
            xCent = (xMin + xMax)/2;
            xMin = xCent - yHeight/4;
            xMax = xCent + yHeight/4;
            xWidth = yHeight/2;
        elseif(xWidth/yHeight > 2.0)
            yCent = (yMin + yMax)/2;
            yMin = yCent - xWidth/4;
            yMax = yCent + xWidth/4;
            yHeight = xWidth/2;
        end
       
        %         if(settingsList.DrawImageAnimationAxisUpperRight == 0)
        settingsList.AXISWIDTH = [xMin - 0.4*xWidth,xMax+0.4*xWidth,yMin - 0.2*yHeight, yMax + 0.2*yHeight];
        %         else
        %                     settingsList.AXISWIDTH = [0,xMax+0.2*xWidth,0, yMax + 0.2*yHeight];
        
        %         end
    end
    axisInputWidth = settingsList.AXISWIDTH(2) - settingsList.AXISWIDTH(1);
    axisInputHeight = settingsList.AXISWIDTH(4) - settingsList.AXISWIDTH(3);
    scalar = 1;
    if(settingsList.DrawRBTTree)
        scalar = scalar + 0.5;
    end
    if(settingsList.DrawSEQTree)
        scalar = scalar + 0.5;
    end
    if(settingsList.DrawImageAnimationAxis == 0 || settingsList.DrawImageAnimationLimitInterpolateAxisToFinalSetAxis)
        if(axisInputWidth > axisInputHeight)
            figWidth = 960*scalar;
            figSpace = 1/scalar;
            figHeight = figWidth/scalar * axisInputHeight/axisInputWidth;
            figWidthInch = 9.6*scalar;
            figHeightInch = figWidthInch/scalar * axisInputHeight/axisInputWidth;
        else
            figHeight = 960;
            figWidth = 1920; %figHeight*axisInputWidth/axisInputHeight;%figHeight * axisInputWidth/axisInputHeight*2;
            figSpace = (960 * axisInputWidth/axisInputHeight)/figWidth;
            figHeightInch = 9.6;
            figWidthInch = 19.2;%*scalar;%figHeightInch * axisInputWidth/axisInputHeight*2;
        end
    else
        figWidth = 960*scalar;
        figHeight = 960;
        figWidthInch = 9.6*scalar;
        figHeightInch = 9.6;
        figSpace = (960 * axisInputWidth/axisInputHeight)/figWidth;
    end
    radElements = [sqrt((settingsList.AXISWIDTH(1) -  settingsList.Center(1))^2 + (settingsList.AXISWIDTH(3)- settingsList.Center(2))^2), ...
        sqrt((settingsList.AXISWIDTH(1) -  settingsList.Center(1))^2 + (settingsList.AXISWIDTH(4)- settingsList.Center(2))^2), ...
        sqrt((settingsList.AXISWIDTH(2) -  settingsList.Center(1))^2 + (settingsList.AXISWIDTH(3)- settingsList.Center(2))^2), ...
        sqrt((settingsList.AXISWIDTH(2) -  settingsList.Center(1))^2 + (settingsList.AXISWIDTH(4)- settingsList.Center(2))^2)];
    settingsList.DrawImageAnimationDampener = 1/3;
    settingsList.INITAXISWIDTH = settingsList.AXISWIDTH;
    settingsList.DrawImageAnimationRadiusLimit = max(radElements);
        settingsList.AxisMaxRadWidener =  0;%settingsList.DrawImageAnimationRadiusLimit^(1/4);
    if(settingsList.DrawImageAnimationAxisUpperRight)
        settingsList.LimittingRadius = min([radElements(2),radElements(4)]);
    else
        settingsList.LimittingRadius = settingsList.DrawImageAnimationRadiusLimit;
    end
    settingsList.DrawImageAnimationRadiusLimit = settingsList.DrawImageAnimationRadiusLimit;
    %Have user set resolution of figure...
    settingsList.figureHandle = figure('units','pixel','visible','off','position',[0,1000-figHeight,figWidth,figHeight],'color',settingsList.DrawBackgroundColor,'defaultaxesposition',[0,0,1,1],'InvertHardCopy', 'off','PaperSize', [figWidthInch,figHeightInch]);
%     settingsList.axesHandle = axes(settingsList.figureHandle,'color',settingsList.DrawBackgroundColor);
    set(settingsList.figureHandle, 'Visible', 'off');
%     set(gcf, 'color', settingsList.DrawBackgroundColor);
%     set(gca, 'color', settingsList.DrawBackgroundColor);
%     set(gcf, 'InvertHardCopy', 'off');
    setappdata(settingsList.figureHandle,'LegendColorbarManualSpace',1);
    setappdata(settingsList.figureHandle,'LegendColorbarReclaimSpace',1);
    treeSpace = 1-figSpace;
    if(settingsList.DrawRBTTree && settingsList.DrawSEQTree)
        treeSpace = treeSpace/2;
    end
    settingsList.plotAxisHandle = subplot('Position',[0,0,figSpace,1],'Color',settingsList.DrawBackgroundColor,'XTick',[],'YTick',[]);
    setappdata(settingsList.plotAxisHandle,'LegendColorbarManualSpace',1);
    setappdata(settingsList.plotAxisHandle,'LegendColorbarReclaimSpace',1);    
%     axis off;
    axis equal;
    axis ij;
    if(settingsList.DrawRBTTree)
    settingsList.treeAxisHandle = subplot('Position',[figSpace,0,treeSpace,1],'Color',settingsList.DrawBackgroundColor,'XTick',[],'YTick',[]);
    setappdata(settingsList.treeAxisHandle,'LegendColorbarManualSpace',1);
    setappdata(settingsList.treeAxisHandle,'LegendColorbarReclaimSpace',1); 
%     axis off;
    end
    if(settingsList.DrawSEQTree)
    settingsList.seqAxisHandle = subplot('Position',[1-treeSpace,0,treeSpace,1],'Color',settingsList.DrawBackgroundColor,'XTick',[],'YTick',[]);
    setappdata(settingsList.seqAxisHandle,'LegendColorbarManualSpace',1);
    setappdata(settingsList.seqAxisHandle,'LegendColorbarReclaimSpace',1);     
%     axis off;
    end
    whitebg(settingsList.figureHandle,settingsList.DrawBackgroundColor);
end
if(settingsList.LogImage)
    if(isnan(settingsList.LogImagePath))
        settingsList.LogImagePath = uigetdir;
    end
    if(~exist(settingsList.LogImagePath))
        try
            [Validate] = mkdir(settings.LogImagePath);
            if(~Validate)
                warning('Cannot make directory, disabling logging feature');
                settingsList.LogImage = 0;
            end
        catch
            warning('Cannot make directory, disabling logging feature');
            settingsList.LogImage = 0;
        end
    end
end

