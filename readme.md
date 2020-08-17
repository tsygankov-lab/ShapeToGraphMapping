**VoronoiDiagram is an implementation of fortune's algorithm utilizing circle
sweeps rather than a traditional plane sweep. Unlike matlab's native
implementation of voronoi diagram generation, this code can accept lines as
inputs. This readme also covers the pre and post processing functions which
prepare images for diagram construction, and extract features from the
diagram.**

**This program makes extensive use of the Matlab object oriented programming
environment. For performance reasons, you should run this code on the most
recent version of Matlab possible (2017a). Version 2017a has a 50% performance
increase compared to 2016a.**

\----------------------------------------------------------------

There are five main routines which must be called in the following order. They
perform the following

**1) EDGE EXTRACTION**

**2) DIAGRAM CONSTRUCTION**

**3) DIAGRAM CLEANUP AND PROCESSING**

**4) BRIDGE EXTRACTION**

**5) LOOP EXTRACTION**

For most use cases, the user should interact with a function which automates
this process, or through a GUI. **runVoronoi** contains a template of how the
Voronoi diagram code can be interacted with.

For those who wish to modify or customize the behavior of the code, they may
need too use these commands directly.

Some extra parameters can control the behavior of the code. These parameters
will be noted on a file by file basis.

This readme has three sections: simple, detailed, and advanced. Simple gives a
brief description of a function and its core input/outputs. It will tell you the
flow of outputs between one function and inputs of another.

Detailed gives a function breakdown, additional parameters which may be
modified, and additional information on the on the constraints of each process.

Advanced goes into detail on specific topics which may be helpful for analyzing
the raw data manually. Further comments can be found in internal functions for
information on each routine

\----------------------------------------------------------------

**SIMPLE:**

**1) EDGE EXTRACTION**  
**[vertexList, edgeList, numberOfRegions, numberOfObjects, lengthOfObjects,
colorList, pixelIndexOffset, labelMatrix, adjacencyMatrix] =
multiLayerBorder(image)**

This code accepts a binary image (image) and traces the borders between the
black and white boundaries of pixels**.** This prepares the input for voronoi
diagram generation

**2) DIAGRAM CONSTRUCTION**  
**[records_raw]= VoronoiDiagram[vertexList, edgeList, 'ObjectLengthMatrix',
lengthOfObjects, 'vertexColorList', colorList, 'DisconnectedEdgesPresent', 0,
'DrawInfiniteBisectors', 1)**

Uses the information from multiLayerBorder to construct a voronoi diagram on a
set of input edges (stored in records_raw in an unproccessed state), along with
all the information provided for later analysis. Please note that matlab will
crash if one attempts to save records_raw. Please immediately call cleanRecords.

**3) DIAGRAM CLEANUP AND PROCESSING -**  
**[records_Array] = cleanRecords(records_raw, labelMat, size(vertexList,1),
size(edgeList,1), numberOfObjects, numberOfRegions, adjMat, pixelIndOffset,
vertexList, edgeList, imageMask)**

This converts and stores all information produced by VoronoiDiagram and
multiLayerBorder in a struct of arrays.

records_Array has four key fields

>   .**Input** - an array of information for all input vertices and edges

>   .**edgeSup** - an array of additional information for all input edges

>   .**halfEdge** - an array of information for all voronoi diagram edges

>   .**vorVert** - an array of information for all voronoi vertices

See the detailed section to see the contents of each index

**4) BRIDGE EXTRACTION**

[**dataStruct**] = **processRecords**(**records_ARRAY**)

This process identifies all bridges, defined as vertices and half edges which
exactly bisects two objects. Requires the processed output array and creates a
structure with a field .bridges which holds information about the vertices and
edges on this bridge.

See the detailed section for further explanation of the fields

**5) LOOP EXTRACTION**

[**dataStruct**] = **extractCycles**(**records_ARRAY**, **dataStruct**)

This process uses information from the records_ARRAY from cleanRecords and
dataStruct from bridge extraction to find all global cycles inside each object
with a hole. This adds fields .loop.object(n) and .loop.hole(n) which provides
the boundary profiles along with points on the cycle in each region.

See the detailed section for further explanation of the fields

\----------------------------------------------------------------

**DETAILED:**

**EDGE EXTRACTION:**

**[vertexList, edgeList, numberOfRegions, numberOfObjects, lengthOfObjects,
colorList, pixelIndexOffset, labelMatrix, adjacencyMatrix] =
multiLayerBorder(image,perturbationWeight)**

**NOTES:**

This code accepts an image and traces the borders between the black and white
boundaries of pixels**. The resulting vertices will be on a 'half pixel edge'
(IE, 1.5, 2.5).** The edge list will connect vertices of each object in a
counter clockwise manner. **All object (white) regions are assumed to be
8-connected, all hole regions are assumed to be 4 connected.** If the user does
not wish this to be true, then they can choose to either invert the image and
reverse the interpretation of 'holes' and 'objects' later on.

**INPUT:**

**image** is a 2d image where all non-zero pixels are assumed to be an object.
The image will be immediately thresholded under this assumption in the function.

**perturbationWeight** is a number between 0 and 1 which indicates how the
pixels on 8-connected only pixels will be modified. By default the tracing
algorithm will (correctly) place two vertices at these points. The perturbation
slightly widens this gap so that the object has no zero-width gaps internally.

All code following this assumes a weight strictly less than 1 (no perturbation)
and greater than 0 (large perturbation) is provided. Unpredictable behavior may
arise if this parameter is not in range. If unset, it defaults to 0.99, a 1%
peturbation. Please be careful to not choose weights smaller than 10\^-5, as
computational geometry techniques may be highly sensitive to floating point
errors.

For additional information on perturbation weight, see expanded notes below
**(PERTURBATION WEIGHT)**.

**OUTPUT:**

**vertexList** - an n x 2 list of all vertex coordinates. See expanded notes for
more information **(BORDER TRACING)**

**edgeList** - an n x 2 list of all vertex connections, in the format of
(vertexIndex1, vertexIndex2)

**numberOfRegions** - the number of objects and holes

**numberOfObjects** - the number of non-object regions

**lengthOfObjects** - the number of vertices associated with each object

**colorList** - the color of the border upon which each vertex lies, IE, the
object from which each vertex was generated.

**pixelIndexOffset**- an n+1 x 1 vector where n is the number of objects. the
ith+1 index represents the index of the last item in the ith object.

**labelMatrix** - from bwboundaries, returns a m x n matrix matching the
original image size where each pixel is assigned a color according to what
object/hole it was in. Background regions are labeled 0.

adjacencyMatrix - an n x n sparse matrix, where n is the number of objects,
indicating if a region encloses or is enclosed by another region.

**Currently, we find the location of voronoi vertices using the labelMat as this
is faster than calculating inPoly for all points. If you do not start with an
image, then additional functions must be provided to determine if a voronoi
vertex is in or outside a polygon.**

All this information can be used by the various functions

**VORONOI DIAGRAM CONSTRUCTION**

**[records_raw]= VoronoiDiagram[vertexList, edgeList, 'ObjectLengthMatrix',
lengthOfObjects, 'vertexColorList', colorList, 'DisconnectedEdgesPresent', 0,
'DrawInfiniteBisectors', 1)**

**NOTES:**

**All vertices not placed on the border have a maximum degree of 3. In the event
that there are four or more objects which are tagent to the circle at each
voronoi vertex, the vertex will be split with a zero distance edge connecting
the two vertices. While this could be considered an artifact, this is the
preferred mechanism for defining a voronoi diagram.**

**INPUT:**

This code computes a general voronoi diagram based on (required) **vertexCoor**
and (optional) **edgeList**. If no edge list is provided, the vertices are
assumed to not be part of an edge.

The code will execute and generate a voronoi diagram on the following
circumstances

**1) All vertices in vertexList are unique.**

**2) No edges in edge list overlap another edge EXCEPT at an endpoint.**

Please note that if the x or y components of vertices are seperated by
difference on the order of the limit of machine precision, unpredictable
behavior, or crashes, may occur when computing the voronoi diagram. See
(**NUMERICAL PRECISION**) for more information. If debugging is required,
'**DEBUGTreeVerificationAfterIteration**' 1 will scan through the internal data
structures so there are no contradictory information in the diagram - this comes
at a major so

The input above can be considered a 'standard' input for most use cases.

This sample code will compute the voronoi diagram on a set of **vertices** and
**edges**, with **colorList** and **lengthOfObjects** allowing the code to
better track which region each vertex belongs too. **DisconnectedEdgesPresent**
0 overrides default behavior in which, if no **colorList** or **object length**
is provided, the code will perform a breadth first search on the edge list to
identify connected regions. **DrawInfiniteBisectors** 1 ensures that all edges
which could be formed are completed - for more information on this, see the
expanded notes, **(HALF EDGES)**.

This code accepts a variety of inputs to display or animate plots of the diagram
in real time. The diagram for large images can be very complex, so please be
patient when plotting

**OUTPUT:**

**records_raw** - a structure containing the following core components. This is
based off the half-edge-records structure standard in computational geometry.

**THE VORONOI DIAGRAM PROCESS IS HIGHLY DYNAMIC, WHICH MAKES WORKING STRICTLY
WITH LARGE ARRAYS INCREDIBLY DIFFICULT. INTERNALLY, THIS STRUCT OF CELLS OF
OBJECTS IS USED TO ALLOW FOR DYNAMIC UPDATES TO GRAPH IN A SIMPLE,
UNDERSTANDIBLE MANNER. MATLAB'S 'POINTER' FUNCTIONALITY HOWEVER IS STILL VERY
NEW - RUNNING THE NEWEST VERSION OF MATLAB (2017a at this time) IS THEREFORE
HIGHLY RECOMMENDED.**

**ON LARGE IMAGES, ATTEMPTING TO SAVE THIS STRUCTURE WILL CRASH MATLAB. IT IS
RETURNED FOR THOSE WHO WANT TO PERFORM MANUAL ANALYSIS - BUT FOR NORMAL USE,
IMMEDIATELLY CALL CLEAN RECORDS, AND SAVE THIS RESULT.**

**UNDERSTANDING THE CONTENTS OF THIS STRUCTURED IS NOT REQUIRED FOR NORMAL USE
OF THE VORONOI DIAGRAM CODE. FOR THOSE CURIOUS, HERE ARE THE CORE STRUCTURES**

**.Vertex{n}** - a cell array containing object handles pointing towards all
voronoi vertices, which contain information on their coordinates and color,
along with pointers to voronoi faces and voronoi edges.

**.Edge{n}** - a cell array containing object handles pointing towards all
voronoi HALF EDGES, which contain the start point of the edge, the edge
distance, the voronoi face which lies to the right of the edge,

**.Face{n}** - a cell array for each input point defining the polygon of all
points which are closer to this input than all others.

.**beachTree -** an object pointer to a tree which defines all edges and
vertices which have no circle events to close their exterior arc

Interpretating this records structure requires understanding the assumptions
made to compute this diagram. Please see (Linear Voronoi Diagram Construction)
for more information

Some edges will be marked as **INVALID**. These are internal edges between
endpoints and the rest of the line that do not need to exist due to the shape of
the line. Half edges are recorded immediately when it is determined an edge
could exist. This ensures the directionality of the edges are correct. Some
edges, however, while they hypothetically exist, do not get completed due to the
assumptions made during computation (**see LINEAR VORONOI DIAGRAM
CONSTRUCTION**). This cannot be safely removed during construction of the
algorithm, but these lines are pruned during clean records. For manual
computation, these edges should be ignored. These edges are unlikely to be
completed edges.

**DIAGRAM CLEANUP AND PROCESSING**

**records_Array = cleanRecords(records_raw, labelMat, numVerts, numEdges,
numberOfObjects, numberOfRegions, adjMat, pixelIndOffset, vertexList, edgeList,
imageMask)**

**NOTES:**

This converts the raw half edge records from the voronoi diagram to a more
standard struct of arrays for saving and later processing. It also stores all
information used in the code up to this point.

**INPUT:**

**records_raw** - output of the previous voronoi diagram

**labelMat** - output of multilayerBorder

**numVerts** - number of vertices (size(vertexCoor,1))

**numEdges** - number of edges (size(EL,1))

**numberOfRegions** - Output of multilayerBorder

**numberOfObjects** - Output of multilayerBorder

**adjMat** - Output of multiLayerBorder

**pixelIndOffset** - Output of multiLayerBorder

**vertexCoor** - Original input vertex list

**edgeList** - Original edge list

**imageMask** - Original input image

**OUTPUT:**

This outputs the records array structured, which is as follows

.**numObjects** -\> **numberOfRegions**

.**numNonHoles** -\> **numberOfObjects**

.**adjMat** -\> **adjMat**

.**pixelIndOffset** -\> **pixelIndOffset**

.**vertexCoor** -\> **vertexCoor**

.**EL** -\> **edgeList**

.**imageMask** -\> **imageMask**

.**numInputVerts** -\> **numVerts**

.**numInputEdges** -\> **numEdges**

.**input**(numVerts + numEdges, 4) = [**isVert** (1/0), **color**
(0-numRegions), **xCoor** (if vert) or **vert1ID** (if edge), **yCoor** (if
vertex) or **vert2ID** (if edge)]

.**edgeSup**(numEdges, 7) = [**normalized x direction**, **normalized y
direction**, **infiniteRadius** (see **(infRad vs rad)**), **A**, **B**, **C**,
**magnitude**] (**A**, **B**, **C** refers to the standard line equation)

Note that all vertices will be listed, then all edges. For getting the 'edge
supplemental index' from the edge index, subtract by the number of vertices

.**halfEdge**(numHalfEdges,11) = [**Twin Edge Index**, **edgeType** (see **HALF
EDGE**), **origin Vertex ID**, **twin Vertex ID**, **distance**, **normalized x
direction**, **normalized y direction**, **inputObjectFaceEnclosedToRight**,
**color** (see **COLOR**), **controlPointX**, **controlPointY**] See (**HALF
EDGE**) for more explanation on these topics

.**vorVert**(numVorVerts, 19) = [**x**, **y**, **rad**, **objectColor**,
**backgroundColor** (same if not on border), **inputIndex** (-1 if not on
border), **locationType** (0/1/2 hole/object/border), **vertex Degree** (3 if
internal, 2 if infinite, 4 on some borders), **edgeID1**, **edgeID2**,
**edgeID3**, **edgeID4** (0 if edge does not exist), **vertexColor1**,
**vertexColor2**, **vertexColor3** (see **COLOR**), **isInfiniteVertex**] See
(**Voronoi Vertices**) for more information on this topic.

The voronoi faces are not explicitly stored in this structure - but can be
easily computed by for each input object ID, find all corresponding half edges
matching the ID. These edges should rotate clockwise around the object.

Internally, construction distinguishes between the sides of a line segment. This
information removed post processing. The polygonal region described by a line
segment will therefore be the region bound by the normals at the endpoints
expanding to both sides of the line until the graph is intersected.

**BRIDGE EXTRACTION:**

[**dataStruct**] = **processRecords**(**records_ARRAY**)

**NOTES:**

This process identifies all bridges, defined vertices and half edges which
exactly bisects two objects.

**INPUT:**

The inputs are simply the processed records list from cleanup records

**OUTPUT:**

dataStruct is the following structure.

**dataStruct**.**bridgeArrayIndex**(n x n) = Sparse matrix mapping the bridge
color [**objectA**, **objectB** or **objectB**, **objectA**] to an index in
.**bridges** where information on the bridge can be found. Note this only stores
one bridge per color combination. This is used later mostly to easily find a set
of valid vertices to perform cycle analysis. To find all bridges between two
objects, search through the color pattern stored by .bridge

.**bridge**.**EL** = edgeList of all edges on a continuous bridge

.**bridge**.**Vertices** = vertex list of all vertices on a continuous bridge

.**bridge**.**radius** = radius of all voronoi vertex nodes on a continuous
bridge

.**bridge**.**incDist** = Distance along each edge

.**bridge**.**dist** = Cumulative distance from the first to last vertex. The
first vertex has a distance of 0.

.**bridge**.**completeCircuit** = 1 if the bridge is a loop in itself, or 0
otherwise.

**LOOP EXTRACTION:**

[**dataStruct**] = **extractCycles**(**records_ARRAY**, **dataStruct**)

**NOTES:**

This routine finds the largest internal cycle which connects all bridges
involving an object together. It can be thought as a continuous path which is
directly bisects the border of 1 object with all other objects. By definition,
this will form a circle if one object is inside another.

This can be defined more formally as follows.

*Let G be the subgraph of all directional half edges E and vertices V connected
to E such that for all edges in E there is a voronoi face of color C.*

This finds the largest cycle in this subgraph via a depth first search, starting
at a known valid location on a bridge. This allows for the user to identify the
presence of protrusions or features along the boundary of any object or hole,
and extract geometrical features.

**INPUT:**

**records_ARRAY =** From cleanRecords

**dataStruct** = From processRecords

**OUTPUT:**

**Additional field .loop for dataStruct (dataStruct.loop)**

Fields for **dataStruct**

.**loop**.**object**(n) = array of structs for all loops which are inside an
object

.**loop**.**hole**(n) = array of structs for all loops which are inside a hole

Fields for **dataStruct**.**loop**.**object**(i) or
**dataStruct**.**loop**.**hole**(i)

>   n = number of vertices in sub graph.

>   m = number of vertices on path.

>   o = number of vertices in the sub graph on an object border

>   v = number of vertices in the full diagram.

>   **Critical:**

>   .**Vertices = m x 1** array of indices of vertices (corresponding to
>   records.vorVert) for vertices along the largest cycle

>   **EL** = m x 1 array of indices of edges (corresponding to records.halfEdge)
>   for half edges along the largest cycle

>   .**distance** = m x 1 array, defining the arc length distance from vertex 1
>   to vertex m along the path

>   .**radius** = m x 1 array of the radius defined at each vertex along the
>   path

>   .**subGraphVerts =** n x 16 array containing all records.vorVert information
>   in this region.

>   .**boundaryProfile =** o x 1 array containing the shortest path from a point
>   on the boundary to a point on the cycle

>   .**boundaryToCycleNode =** o x 1 array containing the index to the vertex in
>   records which is closest to this point on the boundary. This can be used to
>   normalize boundaryProfile by the radius at this point for direct comparison
>   with objects without cycles

>   **Additional**:

>   .**subGraphParentEdge =** n x 2 array indicating the index of the half edge
>   by which this vertex (in sub graph verts) was reached. The term parent is
>   used as most vertices will be reached by descent from a subtree whose root
>   starts on the cycle. Points can have a maximum of two parents, as the
>   maximum number of valid directional edges from a vertex on a bridge is 2,
>   which is where the graph must both start and end.

>   .**subGraphChildEdge** = n x 2 array, all child nodes which are reached by
>   descending from a vertex.

>   **.direction =** m x 2 array, defining the normalized direction vector used
>   to get to this vertex.

>   .**incrDist = m x 1 array**, defining the distance between each edge along
>   the loop

>   .**records2SubgraphMap_Vertices** = a v x 1 array, which maps each vertex v
>   in the records list to corresponding vertex m in the subgraph region. 0 if
>   it is not in the subgraph.

>   .**subGraph2RecordsMap_Vertices** = a n x 1 array which maps all vertices in
>   the subgraph to their corresponding vertex in records.

>   .**binaryFilt = a v x 1** logical array which is 1 if the vertex is in the
>   subgraph

>   .**subGraphEL** = **a n x 11** array containing all information about edges
>   in the subgraph

>   .**objectNumber =** the color of the object the subgraph is located in

>   .**color =** the color of the half edges in the subgraph

>   .**inObject =** 1 if in object, 0 if in background

>   **.subGraphLeafFilter =** an n x 1 logical matrix which is 1 if a leaf is on
>   the edge, 0 otherwise

**If everything has been run, the script plot measures will create plenty of
sample diagrams. Additional post processing techniques will automate analysis of
bridges and loops further.**

\----------------------------------------------------------------

**ADVANCED/EXPANDED NOTES**

**(PERTURBATION WEIGHT)** A weight of 1 means that the pixel will remain in its
original position. A weight of 0 means it will be set to the average of its
neighboring vertices. A weight inbetween will perform a weighted average of
these two states. Please note that all algorithms assume a weight less than 1
(IE, some perturbation) is provided. If this is not done, then the user must
manually reprocess these non-unique vertices to connect multiple edges between
them. Furthermore, post processing steps assume all vertices have at most 4
valid edges, and The border profile code restricts paths from going through a
vertex, and assumes that all pixels border on, at most, two color regions, and
assumes all vertices have a max degree of 4.

The voronoi diagram is general enough to which this perturbation is not strictly
necessary if the edges for both vertices have been combined. However, the
interpretation of the resulting diagram assumes a non-zero width at all internal
points in an object as 1) the diameter of a cell being zero at any point is
nonsensical and 2) it simplifies the assumptions involved later on in
post-processing

**(BORDER TRACING)** Order of vertexList and edgeList is counterclockwise
starting from the point on the outermost object. After all vertices on the outer
most object, it then list all vertices of the second object, and so on. When all
objects have had there vertices listed, it then lists the vertices for all 4
connected holes.

**(Linear Voronoi Diagram Construction)**

A voronoi diagram has three components

A region closest to an input point (region closest to 1)

A region closest to two input points (bisects two)

A region closest to three input points (bisect three)

... and so on.

In 2d, this becomes a polygonal face (2d area closest to an input), an edge (1d
bisector between two inputs), an a point (0d bisector between three points, the
center of the resulting enscribed circle). In higher dimensions, everything goes
up by 1.

In 3d, its a volume around all inputs, a plane bisecting two inputs, an edge
bisector groups of three inputs, and a vertex at the center of an enscribed
sphere between four inputs.

This is why you cannot have intersecting or overlapping lines. If you have two
points which overlap, A and B, what is the polygon containing all points closer
to A and B? Since this behavior is undefined, intersecting lines and overlapping
vertices are strictly prohibitted.

Some edge voronoi diagram constructors use the additional assumption that two
edges cannot share an endpoint, and slightly space all cases which this occurs.
This in the end creates something closer to a topological skeleton than a
voronoi diagram. We wanted to have voronoi vertices placed (correctly) directly
on endpoint between two connected edges, as this will allow us to treat these
points as 'leaves' descending from our interior voronoi diagram structure. If
you take additional precautions when processing endpoints, then you can create a
graph which isolates the diagram into the following regions:

Region closer to the endpoint

Region closer to line side A

Region closer to line side B

Some edges get marked as invalid internally, and are removed in cleanRecords.
This can be considered an artifact of allowing shared endpoints. The
Invalidation occurs on the following scenario.

An endpoint is detected for two different edges. Four half edges are generated.
LeftLineTop \| EP, EP \| RightLineTop, RightLineBottom\|EP, EP\|LeftLineBottom.
These are called implicit edges, or type 0 edges, which are edges between an
endpoint of a line and the rest of the line. Often you will see these at the
start parabolic arcs at concave vertices.

If the line is parallel, two of these edges will get pinned two coincident
vertices on one side of the line, and two will get pinned to two coincident
vertices on the other line. The vertices will be connected by a zero-length edge
indicating that the region closest to the endpoint is virtually non-existant.

If the line is not parallel, then there is one side in which the endpoint
creates a parabolic arc overwhich all points are closer to the endpoint compared
to the line or anything else (in which the half edges are valid), and one side
where the endpoint is closer to zero points compared to the two edges. Instead
of creating two vertices at the endpoint, one of which with a degree of two, the
edge leftLine\|RightLine is pinned to the vertex, and the implicit edges are
invalidated. In the end the vertex will have a degree of three - two implicit
half edges and 1 half edge bisecting two lines.

**(COLOR)** We describe objects having a color several times. This is how we
describe the objects which a point, half edge, or face are closest to.
MultiLayerBorder assigns each 8-connected region or 4-connected hole an index.
We use this index as a color to determine 1) Where a vertex is located (is it
inside, or is it outside of a region?) and 2) what object/hole border is a
voronoi vertex closest to?

Each half edge has 1 color. It is the color of the voronoi face which this half
edge closes on the right. If a half edge's color differs from its twin, we call
this a bridge\*.

\*There are some additional bridges that may be defined as consecutive sets of
vertices and edges of some pure color A which connect two sets of bridges
containing color A, which are otherwise disconnected. Typically we simply
include these special bridges in loops.

Each interior voronoi vertex has 3 colors. It is the color of the 3 half edges
which start from this vertex. If the 3 colors are distinct, we call this vertex
a hub.

Border vertices will have all 3 colors the same. To distinguish position, each
vertex will have a background color and object color. If a vertex is inside an
object, its background and object color will match the object. If it is inside a
hole, those two colors will match the hole. If it borders an object and a hole,
the object color and background color will match the colors of the neigbors.

A special color is the background - which indicates any non-object region not
enclosed by an object. This has an index 0. When plotting, it can be ignored
simply by finding all vertices with non-zero colors.

**(Voronoi Vertex)** A voronoi vertex is a vertex in the voronoi diagrma which
is the center of an enscribed circle between three input objects. Each vertex
stores the radius of said enscribed circle, along with the half edges starting
from this point. The vertex's color will match that of the three input objects.

Some vertices are artifically created at 1.5\*the last radius of the sweep
circle. These serve as a way to draw infinite bisectors such that they do not
cross back over the sweep circle. These vertices will have a degree of 1, and
are mostly included for completeness.

**(HALF EDGE)** You will see the term Half Edge mentioned repeatedly through the
documentation. This is because we do not store edges as simply a connection
between two points, but rather as a pair of directional half edges. Each half
edge has an origin, which is the endpoint the edge is connected to. It stores a
pointer towards (or, the index of) it's twin edge, which is the edge which
starts at the other endpoint, and points towards this half edge's origin.

The directionality of the half edges means that the voronoi polygon for each
this directional edge is located to the right of this directional edge. This is
useful for extracting voronoi polygons, or for traversing through the graph.

There are several edge types, but most commonly you will see the following:

Type0 - an implicit half edge seperating an endpoint from the rest of the line

Type1 - a half edge which is linear (bisecting a point and a point or a line and
a line)

Type2 - a half edge which is parabolic (bisecting a point and a line)

TypeN + 100 - a type 0, 1, or 2 edge which extends off infinitely and pinned at
an infinite voronoi vertex (placed at the edge of the sweep circle 1.5\*the
radius of the last processed object).

Type2 edges, due to ther curved nature, requires a little bit more information
to precisely plot. The last two entries refer to a 'control point', which is
used for constructing a bezeir curve for the parabola. The bezeir curve also
allows us to sample the parabola at even arc lengths, letting exactly calculate
the radius at specific points along the parabolic curve.

**(NUMERICAL PRECISION)**

Computational geometry techniques rely on being able to distinguish the relative
orientations of objects in nd space. Functions attempt to control floating point
errors internally, but if, for example, two vertices correctly differ in the x
direction by orders of magnitude less than 10\^-10, it is very possible that
this could cascade down the road and lead to divide by zero errors and general
instability. If you use a binary image input, then this is not a concern. If
your spacial coordinates have, for whatever reason, near-zero random noise, then
it is possible the construction will crash or fail.

Functions which are sensitive to numerical precision are:

'checkLeftOf', which must know to the most precise degree possible if point C is
to the left of directed vector A-\>B. If the differences in X and Y cooridnates
(independently) between A, B, and C are near the limits of machine precision,
the point may innappropiately be marked as co-linear.

isParallel, used to determine if a value can be computed in a simpler manner or
if having parallel lines may lead to a divide by zero error. FP error may cause
isParallel to return false, and allow for division by an incredibly small
(10\^-14 to 10\^-16) value.

Precision errors typically arive when calculating the A, B, C parameters for a
line. If two points at the start and end of the line very slightly (10\^-14th or
less) differ in Y, then A, and dirY post normalization, will be very small.

**(infRad vs Rad)**

Internally, there are two radii used for how we definte the distance of the
object from the start of the sweep circle. The radius - the distance from any
point on a line segment/vertex to the center, and the infinite radius - the
distance from any point if the line was extended infinitely towards the center.
This distinction is required to correct the correct parabolic bisector for any
input edge and the sweep circle. The reason it is used outside of the voronoi
diagram is simply to simplify plotting rotate parabolas.
