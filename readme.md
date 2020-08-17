ShapeToGraphMapping code for publication -

This repository contains both the code for Voronoi graph construction and feature extraction, and code for boundary clustering as presented in the paper.

\----------------------------------------------------------------
1) EDGE EXTRACTION 
[vertexList, edgeList, imageStruct] = multiLayerBorder(image,0.99)
This code accepts a binary image (image) and traces the borders between the black and white boundaries of pixels. This prepares the input for Voronoi diagram generation
If working with a label image, please see information on multiLayerBorder_LABEL

2) DIAGRAM CONSTRUCTION
[records]= Voronoi_DT[vertexList, EL, ‘ImageStruct’,imageStruct)

Uses the information from multiLayerBorder to construct a voronoi diagram on a set of input edges. Information about the Voronoi diagram will be stored in records.
Records has five key fields, each of which has a set of it’s own fields
	.Inputs – an nx5 array of information about all inputs
	.edgeSup – an nx9 array with additional info about input edges.
.verts – a structure with multiple fields. Contains information about output vertices.
.edges – a structure with multiple fields. Contains information about output edges in the diagram.
.facesFull – contains information about the Voronoi cell surrounding each input
For more information about the records structure, see the section on records.

3) BRIDGE EXTRACTION
[dataStruct] = processRecords(records)
This process identifies all bridges, defined as vertices and half edges which exactly bisects two objects.  Requires the processed output array and creates a structure with a field .bridges which holds information about the vertices and edges on this bridge.

4) LOOP EXTRACTION
[dataStruct] = extractCycles(records, dataStruct)
This process uses information from the records_ARRAY from cleanRecords and dataStruct from bridge extraction to find all global cycles inside each object with a hole.  This adds fields .loop.object.* and .loop.hole.*, which each have fields .acyclic(n), .enclosed(n), and .enclosing(n), which provides the boundary profiles along with points on the cycle in each region. Information about a specific boundary can be extracted by calling getCycleInfo(dataStruct, color)


