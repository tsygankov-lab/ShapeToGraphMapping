%% Voronoi_DT - Constructs the Voronoi Diagram given a set of points and
%line segments. Return the records structure, which contains information
%about the Vertices, Edges, and Faces in the resulting Voronoi diagram.
%See documentation for details. 
%This is a wrapper function for the compiled Voronoi construction code,
%VoronoiMEX. The Voronoi construction code is avaliable in
%VoronoiDiagram.cpp.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Required Arguments:
%   VertexCoor (required) - nx2 matrix of vertices (x, y). Repeated
%   vertices may cause undefined behavior
%
%% General Options:
%   'EL'    
%           Default Value: []
%           Expected input: nx2 vector
%           Option to specify an nx2 edge list. Each row in the edge list 
%           includes the index of two vertices and vertexCoor which should 
%           be connected by an edge. Redundant edges or edges which 
%           intersect will lead to construction errors.
%   'Center' 
%           Default Value: [0,0]
%           Expected Input: (1,2) vector.
%           Specifies the start location of the sweep circle used during
%           Voronoi construction. This should not need to be modified for
%           most use cases. For toroidal data, the sweep circle center
%           should be placed at the center of your toroidal space.
%
%   'DebugMode'
%       `   Default Value: false
%           Expected Input: Boolean value
%           Controls whether to use the default build of the Voronoi
%           diagram, or the debug build produced by the buildScript
%           function, VoronoiMEX_DBG. With default flags, the debug build
%           will internally validate the correctness of placed vertices by
%           ensuring that all three inputs associated with a Vertex are
%           equidistant (within a certain tolerance). This will also
%           validate the correctness of each intercept. If an inconsistency
%           is found, an exception will be thrown which lists the
%           computation which failed, and the construction will be
%           terminated.
%           This option should only be enabled if an error with
%           construction has been previously noticed.
%
%% Image Analysis Options
%   'ImageStruct'
%           Default Value: []
%           Expected input: Third output from multiLayerBorder.m
%           Option to pass the 'ImageStruct' structure output by
%           multiLayerBorder.m. This will automaticaly set the input
%           options for 'Color', 'numObjects', 'numNonHoles', and
%           'labelMat'. It will also inform the script to store additional
%           information within the records structure output about the
%           image. The user can choose to override any of the options set
%           by ImageStruct by setting a non-empty value for these options.
%           See the documentation on 'records' below to see how the output
%           structure will change. 
%
%           'Color'
%                   Default Value: []
%                   Expected Input: nx1 vector which matches the size of
%                   VertexCoor.
%                   An nx1 vector, with one value for each row in
%                   VertexCoor. This groups input vertices (and edges associated
%                   with each vertex) with a 'color' value. When the
%                   Voronoi diagram identifies vertices and edges within
%                   the Voronoi diagram, it will track the colors of the
%                   input events involved. The color of an input edge will
%                   be derived by the color of it's 'first' endpoint.
%                   
%                   As part of the image processing pipeline, each
%                   continuous boundary surrounding an object (exterior
%                   boundary) or a hole (interior boundary) in a binary
%                   image will be assigned a unique color. This information
%                   will be used to find subgraphs of the Voronoi diagram
%                   nearer to a specific boundary, along with 'bridges'
%                   which bisect boundaries. 
%
%                   Color does not influence the output of 'records.Faces.'
%                   To automatically form a composite Voronoi cell based on
%                   a common identifier, see vertFaceID, edgeFaceID, and
%                   maxFaceID.
%
%           'numObjects'
%                   Default Value: []
%                   Expected Input: Integer value
%                   The number of boundaries identified in the image.
%                   Normally, this is the maximum value of 'Color.'
%           
%           'numNonHoles'
%                   Default Value: []
%                   Expected Input: Integer Value
%                   The number of 'exterior boundaries', equivalent to the
%                   number of foreground objects in the image. After
%                   computing the diagram, the algorithm will identify the
%                   location of each vertex in the image, in terms of which
%                   object they lie within. 
%
%                   Regions with exterior boundaries assigned a value of 1
%                   to 'numNonHoles' will be assumed to be foreground
%                   objects. Vertices which lie within these regions will
%                   be assigned a location type of 1. Regions with exterior
%                   boundaries assigned a value greater than 'numNonHoles'
%                   will be considered a background object (ie, a hole, or
%                   an interior boundary for another region), and be
%                   assigned a location type of 0. For more information on
%                   locationType, see the description for the output of
%                   records.
%
%           'labelMat'
%                   Default Value: []
%                   Expected Input: nxm label image, in which each index
%                   is assigned an integer value corresponding to the color
%                   of the region. This is the output of bwconncomp in
%                   multilayerborder.m. 
%
%                   This is used to efficiently identify the region a
%                   Voronoi vertex lies in. If this information is not
%                   avaliable, and grouping Voronoi vertices into 'regions'
%                   is required, see 'searchFlag' for an alternative region
%                   assignment mode.
%
%   The following settings are options tailored to specfic types of imaging
%   data (IE - Continuous contour maps and confluent label images). These
%   options should not be set when working with binary masks.
%   'scaleFactor'
%           Default Value: [], or 1
%           Expected Input: The fourth input argument to multiLayerBorder
%           This option is used when operating on label images, when two
%           distinct foreground objects can share a boundary. This
%           information is used to help determine if an output Voronoi
%           Vertex lies within the artificial 'background' region which
%           lies between two objects.
%
%           This parameter is used in very specific use cases. This
%           parameter should only be set if it is also used in
%           multiLayerBorder.m
%
%   'searchMode'
%           Default Value: [] or 0. 2 if scaleFactor and labelImage are
%           defined.
%           Expected Input: 0, 1, or 2.
%           Determines the search mode used to assigned Voronoi vertices to
%           specific regions.
%           This parameter should only need to be adjusted for very
%           specific use cases.
%
%
%           Search Mode 0: The edges and lines are those extracted from
%           multiLayerBorder and lie on the half-pixel edge between two
%           pixels. The regions are assigned by searching in a supplied
%           labelMat, in which each pixel is colored by their corresponding
%           region
%
%           SerchMode 1: The input edges and vertices do form a set of 
%           nested of polygons, but are not directly associated with an
%           image (e.g., a nested set of contours). This assigns vertices
%           into groups based on the reachability - IE, finding valid paths
%           between vertices which do not pass through a boundary. The
%           color associated with each regionID group is that of the 'left
%           most,' or outer-most boundary
%
%           SearchMode 2: The boundaries are derived from a labeled image,
%           with boundaries slightly peturbed using a ScaleFactor. An
%           initial assignment is determined by using an image for
%           non-ambiguous vertices, which is then refined with a search.
%
%% Face Grouping Options
%           If any of these parameters are set, the Voronoi diagram will
%           switch to 'Face Mode' and output an additional 'Faces' output
%           structure. See the 'records' section for information on this
%           output structure.
%
%           A 'FaceID' is an integer value from 1 to n. A composite face,
%           consisting of all faces associated with inputs with the same
%           faceID, will be created after construction and stored in the
%           'records.Faces' structure array. The index of the resulting
%           composite face will match the assigned FaceID.
%
%           'vertFaceID'
%                   Default Value: []
%                   Expected Input: an nx1 vector, the same size of
%                   VertexCoor
%                   Associates each vertex with a FaceID. If this is not
%                   specified, the faceID will be derived from 'edgeFaceID'
%                   if avaliable.
%           'edgeFaceID'
%                   Default Value: []
%                   Expected Input: an nx1 vector, the same size of EL
%                   Associates each edge with a FaceID. If this is not
%                   specified, the faceID will be derived from 'vertFaceID'
%                   if avaliable.
%           'maxFaceID'
%                   Default Value: [], or max(vertFaceID, edgeFaceID)
%                   Expected Value: Integer
%                   The largest FaceID. Should be the same or larger than
%                   the default value
%                   
%
%% Toroidal Options
%   The following options require the VoronoiMEX algorithm to have been
%   compiled in Toroidal mode. See buildScript_TEST_Torus for more
%   information
%
%       'xTor'
%               Default Value: []
%               Expected Value: Positive floating point value
%               The width of the Toroidal space
%       'yTor'
%               Default Value: []
%               Expected Value: Positive floating point value
%               The height of the Toroidal space

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% The Records Structure
%   Contains the raw information about the Voronoi graph. Contains fields
%   for the input, input edge supplemental info, output vertices, output
%   edges, output faces, and output composite faces. Each of these fields
%   is itself a structure.
%
%%       records.input
%               nx5 array - One entry for each vertex in vertex coor, two
%               entries for each edge in EL
%               Contains basic information about the input vertices and
%               edges
%               
%               Index 1: 0 if vertex, 1 if edge
%               Index 2: The color
%               Index 3, 4:
%                        If vertex: x, y coordinates
%                        If edge: Indices of the start and end vertex
%               Index 5: Face ID
%
%%       records.edgeSup
%               nx9 array - contains information about the input edges in
%               the Voronoi diagram. There are two entries for each input
%               edge. This is indexed in the same order as records.input,
%               but does not contain any of the vertices. Therefore, the
%               first index of records.edgeSup corresponds to the number of
%               input vertices + 1
%               
%               This information was typically used to draw parabolic arcs
%               spawned as the bisector between an input edge and an input
%               vertex. As the control point is now precomputed, this
%               structure should not need to be used.
%
%               Index 1, 2: 'X, Y' direction (endpoint 2 - endpoint 1)
%               Index 3:    'infRad' - The distance to the center of the
%               sweep circle if the line extended infinitely (not bound
%               between endpoints). Used for geometric/parabola
%               computations
%               Index 4, 5, 6: 'A, B, C' in standard form equation Ax + By
%               + C = -
%               Index 7: Magnitude (euclidian distance between endpoints)
%               Index 8: 0 if the 'Lower Edge' which points towards the
%               center of the sweep circle. 1 If it's the 'Upper Edge'
%               which points away from the center of the sweep circle
%               Index 9: Index of twin (*in edgeSup)
%
%%       records.verts
%               Contains multiple sub-fields, each which is a vector with
%               one row per vertex
%               
%               records.verts.pos
%                   nx2 array consisting of the (x,y) position for each
%                   vertex
%               records.verts.rad
%                   nx1 array with the radius of each voronoi vertex
%                   (distance to nearest 3 inputs)
%               records.verts.borderRegions
%                   nx2 array with information about the location of each
%                   object.
%                   For vertices which are entirely within a region and do
%                   not lie on the border, both columns will list the
%                   region the object lies in (defined by the color of it's
%                   exterior boundary)
%                   For vertices which are on the boundary between a
%                   foreground and background region, the first column will
%                   list the foreground regionID, and the second column
%                   will list the background regionID. RegionID is
%                   typically defined by the color of the exterior boundary
%                   of a region
%               records.verts.vertexCoorID
%                   nx1 array of input vertexIDs
%                   There will be a Voronoi vertex placed at the endpoint
%                   of any input llne segment. If this vertex is placed on
%                   an input vertex (a 'boundary vertex'), this vector will
%                   contain the index of this input vertex. Otherwise if it
%                   is not on an input vertex, it will have a value of -1.
%               records.verts.locationType
%                   nx1 array ocntaining information about the location of
%                   the vertex
%                   0: Vertex is in the in-graph/foreground
%                   1: Vertex is in the out-grpah/background
%                   2: Vertex is on the boundary between a foreground and
%                   background region
%               records.verts.edgeIDList
%                   nx4 array of edgeIDs
%                   Contains indices of edges which start at this vertex.
%                   Corresponds to records.edges. Most edges will have 3
%                   vertices. Some boundary verts will have 4, and some
%                   infinite/unbounded verts will have a degree of 1
%               records.verts.color
%                   nx3 array of colors
%                   Lists the colors of the 3 input objects each vertex is
%                   associated with
%               records.verts.infinite
%                   nx1 boolean
%                   Some edges in the Voronoi Diagram extend infinitely.
%                   An artificial vertex is created for plotting purposes.
%                   This value in this vector will be 1 if it is
%                   artificially created on an unbounded edge
%
%%      records.edges
%               Contains multiple fields about the output edges. Each field
%               is an array with one row per output edge.
%               
%               records.edges.twinID
%                   nx1 array of edgeIDs
%                   Each edge is represented as a directional 'half edge'.
%                   This array will provide the index to the twin half edge
%               records.edges.edgeType
%                   nx1 array of edgeTypes
%                   There are three types of edges
%                       0: Linear edge which terminates at a boundary
%                       vertex
%                       1: Linear edge (fully in-graph)
%                       2: Quadratic edge
%                   There are some additional legacy edge types which
%                   should be noted
%                       101: Infinite linear edge
%                       102: Infinite quadratic edge
%               records.edges.origin
%                   nx2 array of vertex ids
%                   Contains indices for the startpoint and endpoint for
%                   each line.
%               records.edges.dist
%                   nx1 array of distances
%                   The length of the edge (euclidian distance between
%                   endpoints for lines, arc lengths for parabolas)
%               records.edges.dir
%                   nx2 array
%                   The direction of the tangent vector to an edge at the
%                   origin
%               records.edges.obj
%                   nx1 array of inputIDs
%                   The input object corresponding to this edge. This edge
%                   is the bisector between this input object, and the
%                   input object corresponding to it's twin. This index can
%                   be used to access information in records.inputs and
%                   records.facesFull
%               records.edges.controlPoint
%                   nx2 array of coordinates
%                   x,y position of the control point, used for drawing a
%                   quadratic bezeir curve. This is the intersection of the
%                   tangent lines at the start and endpoint of the
%                   parabolas.
%               records.edges.faceID
%                   nx1 array of faceID
%                   The composite faceID of the corresponding input object.
%                   This is derived from the user supplied faceIDs
%                   Corresponds to indices in records.Faces
%
%%      records.facesFull
%               nx1 struct array, with one entry per input object
%               Contains information about the Voronoi Cell around each
%               input object. The index of these faces matches 1-to-1 with
%               records.inputs and records.edges.obj. This does not include
%               composite faces formed with the faceID arguments
%               
%               records.facesFull(i).Vertices
%                   A list of Voronoi vertices associated with a Voronoi
%                   cell, in no particular order
%               records.facesFull(i).Edges
%                   A list of Voronoi Edges associated with a Voronoi cell,
%                   in no particular order
%               records.facesFull(i).Neighbors
%                   A list of adjacent Voronoi cells. There is one entry
%                   for each edge, and entries can be repeated
%               records.facesFull(i).Object
%                   The objectID associated with each face (should match
%                   the index)
%               records.facesFull(i).groupID
%                   The composite faceID this face is associated with
%               records.facesFull(i).Closed
%                   1 if the face is finite and bounded
%                   0 if the face is infinite and unbounded.
%
%%      The following is only used if faceIDs are set
%%      records.Faces
%               nx1 struct array, with one entry per faceID (from 1 to
%               maxFaceID)
%
%               records.Faces(i).Vertices
%                   A list of Vertices associated with each composite face.
%                   Only includes Vertices on the boundary between one
%                   composite face and another. This is ordered such that
%                   each subsequent vertex is connected to the preceeding
%                   vertex by an edge
%               records.Faces(i).Edges
%                   A list of Edges associated with each composite face.
%                   Only includes Edges on the boundary between one
%                   composite face and another. This is ordered such that
%                   each subsequent edge shares a common endpoint
%               records.Faces(i).Neighbors
%                   A list of adjacent composite faces. There is one entry
%                   per entry in records.Faces(i).Edges. This is ordered
%                   such that the jth entry in neighbor corresponds to the
%                   face on the opposite side of the jth entry in Edges
%               records.Faces(i).Objects
%                   A list of input objects which the composite face is
%                   associated with. 
%               records.Faces(i).FaceComponents
%                   A list of individual Voronoi cells a composite face is
%                   associated with. This can be used to index into
%                   records.facesFull. This should match
%                   records.Faces.Objects
%               records.Faces(i).Finite
%                   1 if the face is fully bounded and finite
%                   0 if the face is unbounded
%               records.Faces(i).FaceStartingIndex
%                   If a composite face is split such that it can only be
%                   represented as multiple polygons, this will indicate
%                   the first index in Edges which is associated with each
%                   polygon. This should be avoided.
%               records.Faces(i).FaceEndingIndex
%                   If a composite face is split such that it can only be
%                   represented as multiple polygons, this will indicate
%                   the last index in Edges which is associated with each
%                   polygon. This should be avoided.
%               records.Faces(i).subFaces
%                   This indicates the number of polygons a composite face
%                   is split into. For most cases, this should be 1. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function records = Voronoi_DT(vertexCoor, varargin)
p = inputParser;
imageStructMode = false;
addOptional(p,'EL',[]);
addParameter(p,'Center',[0,0]);
% addOptional(p,'OutputFaces',false);
addParameter(p,'DebugMode',false);
addParameter(p,'Color',[]);
addParameter(p,'VertFaceID',[]);
addParameter(p,'EdgeFaceID',[]);
addParameter(p,'MaxFaceID',[]);
addParameter(p,'NumObjects',[]);
addParameter(p,'NumNonHoles',[]);
addParameter(p,'LabelMat',[]);
addParameter(p,'xTor',[]);
addParameter(p,'yTor',[]);
addParameter(p,'SearchMode',[]);
addParameter(p,'ScaleFactor',[]);
addParameter(p,'ImageStruct',[]);
parse(p, varargin{:})

inp = p.Results;
%Parsing Info
EL = inp.EL;
cent = inp.Center;
faceIDMode = false;
color = inp.Color;
vertFaceID = inp.VertFaceID;
edgeFaceID = inp.EdgeFaceID;
maxFaceID = inp.MaxFaceID;
numObjects = inp.NumObjects;
numNonHoles = inp.NumNonHoles;
labelMat = inp.LabelMat;
xTor = inp.xTor;
yTor = inp.yTor;
searchMode = inp.SearchMode;
scaleFactor = inp.ScaleFactor;

ImageStruct = inp.ImageStruct;

if(~isempty(ImageStruct))
    if(isempty(color))
        color = ImageStruct.colorList;
    end
    if(isempty(numNonHoles))
        numNonHoles = ImageStruct.numNonHoles;
    end
    if(isempty(numObjects))
        numObjects = ImageStruct.numObjects;
    end
    if(isempty(labelMat))
        labelMat = ImageStruct.labelMat;
    end
    imageStructMode = true;
end

if(~isempty(labelMat) && ~isempty(scaleFactor))
    if(isempty(searchMode))
        searchMode = 2; 
    end
end
if(~isempty(vertFaceID) || ~isempty(edgeFaceID))
    faceIDMode = true;
    if(isempty(maxFaceID))
        maxFaceID = max([vertFaceID, edgeFaceID]);
    end
end

if(inp.DebugMode)
    if (faceIDMode)
        [records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull, records.Faces] = VoronoiMEX_DBG(vertexCoor, EL, cent,vertFaceID,edgeFaceID,maxFaceID,color,numNonHoles,labelMat,xTor,yTor,searchMode,scaleFactor);
    else
        [records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull] = VoronoiMEX_DBG(vertexCoor, EL, cent,vertFaceID,edgeFaceID,maxFaceID,color,numNonHoles,labelMat,xTor,yTor,searchMode,scaleFactor);
    end
else
    if (faceIDMode)
        [records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull, records.Faces] = VoronoiMEX(vertexCoor, EL, cent,vertFaceID,edgeFaceID,maxFaceID,color,numNonHoles,labelMat,xTor,yTor,searchMode,scaleFactor);
    else
        [records.inputs, records.edgeSup, records.edges, records.verts, records.facesFull] = VoronoiMEX(vertexCoor, EL, cent,vertFaceID,edgeFaceID,maxFaceID,color,numNonHoles,labelMat,xTor,yTor,searchMode,scaleFactor);
    end
end
records.edges.length = length(records.edges.origin);
records.verts.length = length(records.verts.pos);
if(~isempty(numObjects))
    records.numObjects = numObjects;
end
if(~isempty(numNonHoles))
    records.numNonHoles = numNonHoles;
end
if(~isempty(labelMat))
    records.labelMat = labelMat;
end

if(imageStructMode)
    records.imageStruct = ImageStruct;
    records.numObjects = numObjects;
    records.numNonHoles = numNonHoles;
    records.adjMat = ImageStruct.adjMat;
    records.labeMat = labelMat;
    records.imageMask = ImageStruct.imageMask;
    records.fromImage = true;
end
records.vertexCoor = vertexCoor;
records.EL = EL;
assert(~any(records.verts.vertexCoorID == 0))