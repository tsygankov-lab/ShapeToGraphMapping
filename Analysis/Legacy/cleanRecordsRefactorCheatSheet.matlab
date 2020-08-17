records.verts = struct(...
	'pos', zeros(size(records.Vertex,2),2),... 				vorVert 1:2
	'rad', zeros(size(records.Vertex,2),1),...				vorVert 3
	'borderRegions', zeros(size(records.Vertex,2),2),...	vorVert 4:5
	'vertexCoorID', zeros(size(records.Vertex,2),1),...		vorVert 6
	'locationType', zeros(size(records.Vertex,2),1),...		vorVert 7
	'degree', zeros(size(records.Vertex,2),1),...			vorVert 8
	'edgeIDList',zeros(size(records.Vertex,2),4),...		vorVert 9:12
	'color',zeros(size(records.Vertex,2),3),...				vorVert 13:15
	'infinite',zeros(size(records.Vertex,2),1)...			vorVert 16
	);


records.edges = struct(...
	'twinID', zeros(size(records.Edge,2),2),...				halfEdge 1
	'edgeType', zeros(size(records.Edge,2),1),...			halfEdge 2
	'origin', zeros(size(records.Edge,2),2),...				halfEdge 3:4
	'dist', zeros(size(records.Edge,2),1),...				halfEdge 5
	'dir', zeros(size(records.Edge,2),2),...				halfEdge 6:7
	'obj', zeros(size(records.Edge,2),1),...				halfEdge 8
	'color', zeros(size(records.Edge,2),1),...				halfEdge 9
	'controlPoint',zeros(size(records.Edge,2),2),...		halfEdge 10:11
	'faceID',zeros(size(records.Edge,2),1)...				halfEdge 12
	);