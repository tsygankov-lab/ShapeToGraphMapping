function [boundaryVertCollection] = internalNodeToBoundary(records, loopStruct, boundaryPointIdx,vertListGen)
%%Go through the pre-caclulated loop boundary profile info.
%%Traverse back up from boundary to root, storing radii and instantaneous distance
%%Determine edge weights at each stage (average radius).
%%Force to be strictly increasing (if i > i+1, i = i+1).
%%Calculate AUC
%%Normalize by Radius
singleChild = loopStruct.isRootNode(boundaryPointIdx);
r2sV = loopStruct.records2SubgraphMap_Vertices;

childEdge = loopStruct.subGraphChildEdge;
boundaryVertCollection = zeros(20,1);
% radList = zeros(20,1);
% distList = zeros(20,1);
% lastVertBelowThresh = 0;
% lastVertBelowThresh_ListID = 0;
childVisited = false(size(childEdge));
vertVisitted = false(records.verts.length,1);
itercount = 0;
boundaryCount = 0;
curVert = boundaryPointIdx; %loopStruct.boundaryVerts(boundaryPointIdx);
prevIntNode = curVert;
hold on;
if(singleChild)
    childVisited(r2sV(curVert),1) = true;
    curVert = vertListGen(end-1);
end 
if(records.verts.vertexCoorID(curVert) ~= -1)
    boundaryVertCollection = curVert;
    return;
else
    while(true) %Break condition is back where you started and can only visit parent
        %plot(records.verts.pos(curVert,1),records.verts.pos(curVert,2),'go')
        %drawnow;
        if(curVert == boundaryPointIdx)
            disp('');
        end
        if(curVert == boundaryPointIdx && childVisited(r2sV(curVert),1) && (singleChild || childVisited(r2sV(curVert),2)))
            boundaryVertCollection(boundaryCount+1:end) = [];
            return;
        end
        if(records.verts.vertexCoorID(curVert) ~= -1)
            boundaryCount = boundaryCount + 1;
            boundaryVertCollection(boundaryCount) = curVert;
            curVert = prevIntNode;
        else
            if(childEdge(r2sV(curVert),1) ~= 0 && ~childVisited(r2sV(curVert),1))
                nextEdge = childEdge(r2sV(curVert),1);
                childVisited(r2sV(curVert),1) = true;
                vertVisitted(curVert) = true;
                prevIntNode = curVert;
                curVert = records.edges.origin(nextEdge,2);
            elseif(childVisited(r2sV(curVert),1) && childEdge(r2sV(curVert),2) ~= 0 && ~childVisited(r2sV(curVert),2))
                nextEdge = childEdge(r2sV(curVert),2);
                childVisited(r2sV(curVert),2) = true;
                vertVisitted(curVert) = true;
                prevIntNode = curVert;
                curVert = records.edges.origin(nextEdge,2);
            else
                nextEdge = loopStruct.parEdge(r2sV(curVert),1);
                prevIntNode = curVert;
                curVert = records.edges.origin(nextEdge,2);
            end
        end
        itercount = itercount + 1;
    end
end

% end