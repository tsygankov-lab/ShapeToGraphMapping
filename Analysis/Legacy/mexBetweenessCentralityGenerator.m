clear all
V.pos = coder.typeof(0,[inf,2]);
V.rad = coder.typeof(0,[inf,1]);
V.borderRegions = coder.typeof(0,[inf,2]);
V.vertexCoorID = coder.typeof(0,[inf,1]);
V.locationType = coder.typeof(0,[inf,1]);
V.degree = coder.typeof(0,[inf,1]);
V.edgeIDList = coder.typeof(0,[inf,4]);
V.color = coder.typeof(0,[inf,3]);
V.infinite = coder.typeof(0,[inf,1]);
V.length = coder.typeof(0,[1,1]);

         E.twinID = coder.typeof(0,[inf,1]);
         E.edgeType = coder.typeof(0,[inf,1]);
         E.origin = coder.typeof(0,[inf,2]);
         E.dist = coder.typeof(0,[inf,1]);
         E.dir = coder.typeof(0,[inf,2]);
         E.obj= coder.typeof(0,[inf,1]);
         E.color= coder.typeof(0,[inf,1]);
         E.controlPoint = coder.typeof(0,[inf,2]);
         E.faceID = coder.typeof(0,[inf,1]);
         E.length = coder.typeof(0,[1,1]);
         
         color = coder.typeof(0,[1,1]);
         vertFilterList = coder.typeof(true,[inf,1]);
         location = coder.typeof(0,[1,1]);
         r2sV = coder.typeof(0,[inf,1]);
         s2rV = coder.typeof(0,[inf,1]);
         nonLeafVerts = coder.typeof(true,[inf,1]);
         
codegen mexBetweenessCentrality -args {V,E,color,vertFilterList,location,r2sV,s2rV,nonLeafVerts}