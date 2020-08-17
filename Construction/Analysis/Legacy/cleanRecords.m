function records_Array = cleanRecords(records, vertexCoor, EL, voronoiSettings)
%vorVert- [x, y, r, inObjectColor, inBackgroundColor, inputVertexID, 0/1/2 hole/object/border, numberOfEdges, edge1ID, edge2ID, edge3ID, edge4ID, color1,color2,color3, infiniteVert]
%halfEdge- [Twin, edgeType, originVertID, twinVertID, distanceMeasure, dirX, dirY, adjacentInputObject, color,bezier1,bezier2, inputFlagID]
%edgeSup- [dirX, dirY,infRad, A, B, C, mag, isTwin, twinEdgeIndex]
%input- [isVert, color, x, y, inputFlagID]
%Input ordering 
IMAGEMODE = 1;
if(isempty(voronoiSettings.imageStruct))
IMAGEMODE = 0;
voronoiSettings.imageStruct.numObjects = 0;
voronoiSettings.imageStruct.numNonHoles = 0;
voronoiSettings.imageStruct.adjMat = [];
voronoiSettings.imageStruct.pixelIndOffset = [];
voronoiSettings.imageStruct.imageMask = [];
voronoiSettings.imageStruct.labelMat = [];
end
numVerts = size(vertexCoor,1);
numEdges = size(EL, 1);
records_Array.CLEANRECORDS_VERNUMBER = 200;
records_Array.fromImage = IMAGEMODE;
records_Array.numObjects = voronoiSettings.imageStruct.numObjects;
records_Array.numNonHoles = voronoiSettings.imageStruct.numNonHoles;
records_Array.adjMat = voronoiSettings.imageStruct.adjMat;
records_Array.pixelIndOffset = voronoiSettings.imageStruct.pixelIndOffset;
records_Array.vertexCoor = vertexCoor;
records_Array.EL = EL;
records_Array.imageMask = voronoiSettings.imageStruct.imageMask;

maxX = size(voronoiSettings.imageStruct.labelMat,1);
maxY = size(voronoiSettings.imageStruct.labelMat,2);
inputList = zeros(numVerts + numEdges*2,5);
objectIndexToInputs = zeros(size(records.inputObjects,1),1);
twinEdgeInserted = zeros(size(records.inputObjects,1),1,'uint8');
edgeListSupplemental = zeros(numEdges*2,9);
index = 0;
numVertsIN = 0;
numEdgesIN = 0;
for i = 1:size(records.inputObjects,1)
    if(~twinEdgeInserted(i))
        obj = records.inputObjects{i};
        if(~obj.isLine)
            index = index + 1;
            inputList(index,:) = [1,obj.color,obj.pos(1),obj.pos(2),obj.inputFlagID];
            twinEdgeInserted(i) = 1;
            objectIndexToInputs(i) = index;
            numVertsIN = numVertsIN + 1;
        else
            index = index + 1;
            inputList(index,:) = [0,obj.color,objectIndexToInputs(obj.endPoints(1).objectIndex),objectIndexToInputs(obj.endPoints(2).objectIndex),obj.inputFlagID];
            twinEdgeInserted(i) = 1;
            twinEdgeInserted(i+1) = 1; %The twin edge is always one index higher
            objectIndexToInputs(i) = index;
            %objectIndexToInputs(i+1) = index;
            edgeListSupplemental(index-numVerts,:) = [obj.dirX, obj.dirY, obj.infRad, obj.A, obj.B, obj.C, obj.magnitude, 0, index + numEdges - numVerts];
            numEdgesIN = numEdgesIN + 1;
        end
    elseif(twinEdgeInserted(i))
        obj = records.inputObjects{i};
        if(obj.isLine) %%A vertex literally cannot be here...
            inputList(index + numEdges,:) = [0,obj.color,objectIndexToInputs(obj.endPoints(1).objectIndex),objectIndexToInputs(obj.endPoints(2).objectIndex),obj.inputFlagID];
            objectIndexToInputs(i) = index + numEdges;

            %%Ideally the direction and ABC vectors would reverse as well, but plotting functions require the old logic it seems
            edgeListSupplemental(index-numVerts+ numEdges,:) = [obj.dirX, obj.dirY, obj.infRad, obj.A, obj.B, obj.C, obj.magnitude, 1, index - numVerts];
            numEdgesIN = numEdgesIN + 1;
        end
    end
end

index = 0;
halfEdgeList = zeros(size(records.Edge,2),12);
edgeIDToIndex = zeros(size(records.Edge,2),1,'uint64');


halfEdges = struct(...
	'twinID', zeros(size(records.Edge,2),1),...
	'edgeType', zeros(size(records.Edge,2),1),...
	'origin', zeros(size(records.Edge,2),2),...
	'dist', zeros(size(records.Edge,2),1),...
	'dir', zeros(size(records.Edge,2),2),...
	'obj', zeros(size(records.Edge,2),1),...
	'color', zeros(size(records.Edge,2),1),...
	'controlPoint',zeros(size(records.Edge,2),2),...
	'faceID',zeros(size(records.Edge,2),1)...
	);

for i = 1:length(records.Edge)
    edge = records.Edge{i};
    if(~edge.INVALID)
        index = index + 1;
        offset = index - i; %Negative if a point has been skipped
        distance = edge.computeDistance;
        dirMat = edge.computeDirection;
        if(distance > sqrt(eps(max([edge.Origin.corr(1),edge.Origin.corr(2),edge.Twin.Origin.corr(1),edge.Twin.Origin.corr(2)]))))
            
            if((edge.edgeType ~= 2 && edge.edgeType ~= 102))
%                 if(distance > sqrt(eps(max([edge.Origin.corr(1),edge.Origin.corr(2),edge.Twin.Origin.corr(1),edge.Twin.Origin.corr(2)]))))
%                     dirMatOld = [edge.Twin.Origin.corr(1) - edge.Origin.corr(1), edge.Twin.Origin.corr(2) - edge.Origin.corr(2)]./distance;
%                 else
%                     dirMatOld = [0,0];
%                 end
                controlPoint = [0,0];
            else
                %%DIRECTION CALCULATION IF POINT TOUCHES A PARABOLA.  BASED ON
                %%THE TANGENT SLOPE OF THE PARABOLA AT THE VERTEX.
                %%from getBezeir_ARR
%                 distanceFlag = distance > sqrt(eps(max([edge.Origin.corr(1),edge.Origin.corr(2),edge.Twin.Origin.corr(1),edge.Twin.Origin.corr(2)])));
                obj1 = inputList(objectIndexToInputs(edge.adjacentFace.objectID),:);
                obj2 = inputList(objectIndexToInputs(edge.Twin.adjacentFace.objectID),:);
                if(obj1(1))
                    point = obj1;
                    line = edgeListSupplemental(objectIndexToInputs(edge.Twin.adjacentFace.objectID) - numVerts,:);
                else
                    point = obj2;
                    line = edgeListSupplemental(objectIndexToInputs(edge.adjacentFace.objectID) - numVerts,:);
                end
                vertA = edge.Origin.corr;
                vertB = edge.Twin.Origin.corr;
                SIN = line(2);%-line.Ax/denom;
                COS = line(1);%line.By/denom;
                rotMCW = [COS,-SIN;SIN,COS];
                rotMCCW = [COS,SIN;-SIN,COS];
                rotPoint = [point(3),point(4)]*rotMCW;
                rotS1 = [vertA(1),vertA(2)]*rotMCW;
                rotS2 = [vertB(1),vertB(2)]*rotMCW;
                
                p = rotPoint(2)-line(3);%perpDistancePoint2Line(line.Ax,line.By,line.C,point.xCorr,point.yCorr); %Dist between focus and directrix
                vertX = rotPoint(1);
                slopeS1 = (2*rotS1(1) - 2*vertX)/(2*p); %%calculates direction based on the parabolic orientation at this point
%                 if(distanceFlag && rotS1(1) < rotS2(1)) %this edge starts on the left - was this the error?
%                     dirMatOld = [1,slopeS1]./(sqrt(1+slopeS1^2))*rotMCCW;
%                 elseif(distanceFlag && rotS1(1) >= rotS2(1))
%                     dirMatOld = [-1,-slopeS1]./(sqrt(1+slopeS1^2))*rotMCCW;
%                 else
%                     dirMatOld = [0,0];
%                 end
                
                slopeS2 = (2*rotS2(1) - 2*vertX)/(2*p);
                intercept1 = rotS1(2)-slopeS1*rotS1(1);
                intercept2 = rotS2(2)-slopeS2*rotS2(1);
                xIntersect = (intercept2-intercept1)/(slopeS1-slopeS2);
                yIntersect = xIntersect*slopeS1 + intercept1;
                
                controlPoint = [xIntersect,yIntersect]*rotMCCW;
            end
        else
%             dirMatOld = [0,0];
            controlPoint = [0,0];
        end
%         edge.edgeType
%         dirMat
%         dirMatOld
        edge.CLEANRECORDS_IDCHANGED = index;
         halfEdges.twinID(index) = edge.Twin.ID + offset;
         halfEdges.edgeType(index) = edge.edgeType;
         halfEdges.origin(index,:) = [edge.Origin.id, edge.Twin.Origin.id];
         halfEdges.dist(index) = distance;
         halfEdges.dir(index,:) = dirMat;
         halfEdges.obj(index) = objectIndexToInputs(edge.adjacentFace.objectID);
         halfEdges.color(index) = edge.color;
         halfEdges.controlPoint(index,:) = controlPoint;
         halfEdges.faceID(index) = edge.adjacentFace.inputFaceID;
        halfEdgeList(index,:) = [edge.Twin.ID + offset, edge.edgeType, edge.Origin.id, edge.Twin.Origin.id, distance, dirMat(1), dirMat(2), objectIndexToInputs(edge.adjacentFace.objectID),edge.color,controlPoint(1),controlPoint(2),edge.adjacentFace.inputFaceID];
        edgeIDToIndex(i) = index;
    else
        edge.CLEANRECORDS_IDCHANGED = index;
        edgeIDToIndex(i) = index;
    end
end
halfEdgeList(index+1:end,:) = [];
         halfEdges.twinID(index+1:end) = [];
         halfEdges.edgeType(index+1:end) = [];
         halfEdges.origin(index+1:end,:) = [];
         halfEdges.dir(index+1:end,:) = [];
         halfEdges.obj(index+1:end) = [];
         halfEdges.color(index+1:end) = [];
         halfEdges.controlPoint(index+1:end,:) = [];
         halfEdges.faceID(index+1:end) = [];
halfEdges.length = index;
vorVerts = struct(...
	'pos', zeros(size(records.Vertex,2),2),...
	'rad', zeros(size(records.Vertex,2),1),...
	'borderRegions', zeros(size(records.Vertex,2),2),...
	'vertexCoorID', zeros(size(records.Vertex,2),1),...
	'locationType', zeros(size(records.Vertex,2),1),...
	'degree', zeros(size(records.Vertex,2),1),...
	'edgeIDList',zeros(size(records.Vertex,2),4),...
	'color',zeros(size(records.Vertex,2),3),...
	'infinite',zeros(size(records.Vertex,2),1)...
	);

%%Vertices cannot be invalidated
vorVertList = zeros(size(records.Vertex,2),16);
for i = 1:length(records.Vertex)
    vert = records.Vertex{i};
    edgeIDList = zeros(max([4,vert.degree]),1);
    edgeList = halfEdge.empty(min([4,vert.degree]),0);
    index = 0;
    for j = 1:vert.degree
        if(~vert.edge{j}.INVALID)
            index = index+1;
            edgeIDList(index) = edgeIDToIndex(vert.edge{j}.ID);
            edgeList(index) = vert.edge{j};
        end
    end
    if(IMAGEMODE)
    posx = round(vert.corr(1));
    posy = round(vert.corr(2));
    if(posx < 1 || posy < 1 || posx > maxX || posy > maxY)
        objectPart = 0;
        backgroundPart = 0;
        locationType = 0;
    elseif(vert.vertexCoorID ~= -1)
        objectPart = 0;
        backgroundPart = 0;
        for j = 1:length(edgeList)
            posx = round(edgeList(j).Twin.Origin.corr(1));
            posy = round(edgeList(j).Twin.Origin.corr(2));
            if(posx < 1 || posy < 1 || posx > maxX || posy > maxY)
                colorofTwin = 0;
            else
                colorofTwin = voronoiSettings.imageStruct.labelMat(posx,posy);
            end
            if(colorofTwin > voronoiSettings.imageStruct.numNonHoles || colorofTwin == 0)
                backgroundPart = colorofTwin;
            else
                objectPart = colorofTwin;
            end
        end
        locationType = 2;
    else
        objectPart = voronoiSettings.imageStruct.labelMat(posx,posy);
        backgroundPart = objectPart;
        locationType = objectPart > voronoiSettings.imageStruct.numNonHoles;
    end
    else
        objectPart = 0;
        backgroundPart = 0;
        locationType = 0;
    end
    



    %%Asociated objects can be derived from edges... may change for vertex to explicitly store these
    vert.CLEANRECORDS_IDCHANGED = i;

    %%Flowerpot has verts w/ degree > 5 - check
    vorVerts.pos(i,:) = vert.corr;
    vorVerts.rad(i) = vert.rad;
    vorVerts.borderRegions(i,:) = [objectPart,backgroundPart];
    vorVerts.vertexCoorID(i) = vert.vertexCoorID;
    vorVerts.locationType(i) = locationType;
    if(vert.degree > 4)
        vert.degree = 4;
    end
    vorVerts.degree(i) = vert.degree;
    vorVerts.edgeIDList(i,:) = edgeIDList(1:4);
    vorVerts.color(i,:) = vert.colorPattern;
    vorVerts.infinite(i) = vert.infVert;

    vorVertList(i,:) = [vert.corr(1), vert.corr(2), vert.rad, objectPart, backgroundPart, vert.vertexCoorID, locationType, vert.degree,edgeIDList(1),edgeIDList(2),edgeIDList(3),edgeIDList(4),vert.colorPattern(1),vert.colorPattern(2),vert.colorPattern(3),vert.infVert];
end
vorVerts.length = i;
FacesFull(length(records.Face),1) = struct('Vertices',[],'Edges',[],'Neighbors',[],'Object',[],'groupID',-1,'Closed',1);
FaceToGroupID = zeros(length(records.Face),1);
for i = 1:length(records.Face)
    %%Polygons for lines will be missing the edge which connects the endpoints!  Will not be fully enclosed!
    faceObj = records.Face{objectIndexToInputs(i)};
    FacesFull(i).Object = objectIndexToInputs(faceObj.objectID);
    FacesFull(i).groupID = faceObj.inputFaceID;
    FaceToGroupID(i) = FacesFull(i).groupID;
    nonInvalid = 1;
    for j = 1:length(faceObj.Edge)
        if(~(isempty(faceObj.Edge{j}) || faceObj.Edge{j}.INVALID))
            FacesFull(i).Vertices(nonInvalid) = faceObj.Edge{j}.Origin.CLEANRECORDS_IDCHANGED;
            FacesFull(i).Edges(nonInvalid) = faceObj.Edge{j}.CLEANRECORDS_IDCHANGED;
            FacesFull(i).Neighbors(nonInvalid) = objectIndexToInputs(faceObj.Edge{j}.Twin.adjacentFace.objectID);
            nonInvalid = nonInvalid + 1;
        end
    end
    if(faceObj.numVertices > faceObj.numEdges)
        for j = 1:length(faceObj.Vertices)
            if(~isempty(faceObj.Vertices{j}))
                if(~any(faceObj.Vertices{j}.CLEANRECORDS_IDCHANGED == FacesFull(i).Vertices))
                    FacesFull(i).Vertices(nonInvalid) = faceObj.Vertices{j}.CLEANRECORDS_IDCHANGED;
                    nonInvalid = nonInvalid + 1;
                end
            end
        end
    end
end
%%Ideally should use a map here, but matlab's support varies depending on version
%if(voronoiSettings.vertexOverrideFaceID ~= 0 || voronoiSettings.edgeOverrideFaceID ~= 0)
%%If a line has two infinite vertices, the endpoints will not be connected
%%by anything, so this search pattern will not work.  Will need to add fake
%%edges across every input edge for this to work (this would still be a
%%correct voronoi diagram)
    Faces = struct('Vertices',[],'Edges',[], 'Neighbors',[],'Objects',[],'FaceComponents',[],'Finite',[],'FaceStartingIndex',[],'FaceEndingIndex',[]);
    for i = 1:length(records.faceIDs)

        faceID = records.faceIDs(i);
        %%I can't tell if this is a hack or just the way it has to be done
        %%in matlab
        Faces(i).FaceComponents = find(FaceToGroupID == faceID);
        Edges = [];
        Neighbors = [];
        Vertices = [];
        nonInvalid = 1;
        totalVerts = 0;
        for j = 1:length(Faces(i).FaceComponents)
            Faces(i).Objects(j) = FacesFull(Faces(i).FaceComponents(j)).Object;
            for k = 1:length(FacesFull(Faces(i).FaceComponents(j)).Edges)
                edgeID = FacesFull(Faces(i).FaceComponents(j)).Edges(k);
                if(halfEdges.faceID(edgeID) ~= halfEdges.faceID(halfEdges.twinID(edgeID))) %Make sure the edge does not split its own polygon.  If it doesn't add it
                    Vertices(nonInvalid) = FacesFull(Faces(i).FaceComponents(j)).Vertices(k);
                    Edges(nonInvalid) = FacesFull(Faces(i).FaceComponents(j)).Edges(k);
                    Neighbors(nonInvalid) = FacesFull(FacesFull(Faces(i).FaceComponents(j)).Neighbors(k)).groupID;
                    nonInvalid = nonInvalid + 1;
                    totalVerts = totalVerts + length(FacesFull(Faces(i).FaceComponents(j)).Vertices(k));
                end
            end
        end
        if(~isempty(Vertices))
            numPolys = 0;
            numAdditions = 0;
            while(numAdditions < length(Vertices))
                if(numAdditions == 0)
                    curVert = Vertices(1);
                    initVert = Vertices(1);
                else
                   binVec = ismember(Vertices,Faces(i).Vertices);
                    filtList = Vertices(~binVec);
                    curVert = filtList(1);
                    initVert = filtList(1);
                end
                counter = 1;
                canBegin = 0;
                closedCycle = 0;
                firstIndex = numAdditions + 1;
                numPolys = numPolys + 1;
                while(~(canBegin || counter > totalVerts+1)) %Should break on valid exit.  Second statement establishes upper limit
                    pathFound = 0;
                    for v = 1:vorVerts.degree(curVert)
                        testEdge = vorVerts.edgeIDList(curVert, v);
                        testEdgeTwin = halfEdges.twinID(testEdge);
                        if(halfEdges.faceID(testEdge) ~= faceID && halfEdges.faceID(testEdgeTwin) == faceID)
                            curVert = halfEdges.origin(testEdgeTwin,1); %Reverses through vert
                            pathFound = 1;
                            break;
                        end
                    end
                    if(pathFound && curVert == initVert)
                        numAdditions = numAdditions + 1;
                        Faces(i).Vertices(numAdditions) = curVert;
                        Faces(i).Edges(numAdditions) = halfEdges.twinID(testEdge);%testEdge(1);
                        Faces(i).Neighbors(numAdditions) = halfEdges.faceID(testEdge);%testEdge(12);
                        canBegin = 1;
                        closedCycle = 1;
                        break;
                    elseif(~pathFound)
                        %%this is a non-closed polygon with infinite area, so
                        %%we must find the most clockwise vertex and first
                        %%outgoing edge.  The last vertex will be added after
                        %%the fact
    	                for v = 1:vorVerts.degree(curVert)
    	                    testEdge = vorVerts.edgeIDList(curVert, v);
    	                    testEdgeTwin = halfEdges.twinID(testEdge);
                            if(halfEdges.faceID(testEdge) == faceID && halfEdges.faceID(testEdgeTwin) ~= faceID)
                                curVert = halfEdges.origin(testEdge,1);
                                break;
                            end
                        end
                        numAdditions = numAdditions + 1;
                        Faces(i).Vertices(numAdditions) = curVert;
                        Faces(i).Edges(numAdditions) = vorVerts.edgeIDList(curVert, v);
                        Faces(i).Neighbors(numAdditions) = halfEdges.faceID(testEdgeTwin);%testEdgeTwin(12);
                        canBegin = 1;
                    end
                    counter = counter + 1;
                end
                if(~canBegin) 
                    %Debug workaround - for degenerate regions
                    break;
                end
                for k = 2:length(Edges)
                    otherVert = halfEdges.origin(Faces(i).Edges(numAdditions),2);%halfEdgeList(Faces(i).Edges(k-1),4);
                    if(otherVert == Faces(i).Vertices(firstIndex))
                        break;
                    end
                    edgeFound = 0;
                    for l = 1:vorVerts.degree(otherVert)%vorVertList(otherVert,8)
                        otherEdge = vorVerts.edgeIDList(otherVert,l);%vorVertList(otherVert,(8+l));
                        if(any(Edges == otherEdge) && ~any(Faces(i).Edges == otherEdge))
                            edgeFound = 1;
                            break;
                        end
                    end
                    if(~edgeFound) %If no edges are valid, abort
                        break;
                    end
                    numAdditions = numAdditions + 1;
                    Faces(i).Vertices(numAdditions) = otherVert;
                    Faces(i).Edges(numAdditions) = otherEdge;
                    Faces(i).Neighbors(numAdditions) = halfEdges.faceID(halfEdges.twinID(otherEdge));%halfEdgeList(halfEdgeList(otherEdge,1),12);
                end

                if(~closedCycle)
                    numAdditions = numAdditions + 1;
                    Faces(i).Vertices(numAdditions) = halfEdges.origin(otherEdge,2);%halfEdgeList(otherEdge,4); %By construction this will be the last vertex...
                end
                Faces(i).Finite(numPolys) = closedCycle;
                Faces(i).FaceStartingIndex(numPolys) = firstIndex;
                Faces(i).FaceEndingIndex(numPolys) = numAdditions;
            end
        end
        Faces(i).subFaces = numPolys;
    end
    records_Array.NumFaces = length(records.faceIDs);
    records_Array.NumRegions = length(records.Face);
    records_Array.FacesFull = FacesFull;
    records_Array.Faces = Faces;

%else
%    records_Array.Faces = FacesFull;
%end
records_Array.input = inputList;
records_Array.edgeSup = edgeListSupplemental;
records_Array.edges = halfEdges;
records_Array.verts = vorVerts;
records_Array.halfEdge = halfEdgeList; 	%legacy
records_Array.vorVert = vorVertList; 	%legacy
records_Array.numInputVerts = numVerts; 
records_Array.numInputEdges = numEdges;
%%Faces are not used at this time.  Things to consider - for line objects, do we add the line itself?