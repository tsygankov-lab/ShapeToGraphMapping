function [vertList, radList, distList, lastVertBelowThresh, lastVertBelowThresh_ListID] = boundaryPathToRoot(records, loopStruct, boundaryPointIdx, radThresh)
%%Go through the pre-caclulated loop boundary profile info.
%%Traverse back up from boundary to root, storing radii and instantaneous distance
%%Determine edge weights at each stage (average radius).
%%Force to be strictly increasing (if i > i+1, i = i+1).
%%Calculate AUC
%%Normalize by Radius
checkThresh = true;
if(isempty(radThresh))
    checkThresh = false;
    radThresh = 0;
end
r2sV = loopStruct.records2SubgraphMap_Vertices;
vertList = zeros(20,1);
radList = zeros(20,1);
distList = zeros(20,1);
lastVertBelowThresh = 0;
lastVertBelowThresh_ListID = 0;

iter =2;
curVert = boundaryPointIdx; %loopStruct.boundaryVerts(boundaryPointIdx);
vertList(1) = curVert;
lastVertBelowThresh = curVert;
lastVertBelowThresh_ListID = 1;
radList(1) = 0;
distList(1) = 0;
while(~loopStruct.isRootNode(curVert))
    nextEdge = loopStruct.parEdge(r2sV(curVert),1);
    distList(iter) = records.edges.dist(nextEdge);
    curVert = records.edges.origin(nextEdge,2);
    radList(iter) = records.verts.rad(curVert);
    vertList(iter) = curVert;
    if(checkThresh && radList(iter) <= radThresh)
        lastVertBelowThresh = curVert;
        lastVertBelowThresh_ListID = iter;
    end
    iter = iter + 1;
end
vertList(iter:end) = [];
radList(iter:end) = [];
distList(iter:end) = [];
% end