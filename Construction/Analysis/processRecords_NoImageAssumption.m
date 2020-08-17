%Preliminary Switch
function [dataStruct] = processRecords_NoImageAssumption(records)
%%Note - a bridge can have length zero if two hubs exist on one another
numObjects = records.numObjects;
bridgeRaw = cell(numObjects);
twinRegistered = zeros(records.edges.length,1,'uint8');
loop = cell(numObjects,1);
colorsPresent = cell(numObjects+1,1);
HEL = records.edges;
VER = records.verts;
for i = 1:HEL.length
    %%Go through all half edges.  If the colors between the twin and the current edge differ, add them to the corresponding bridge
    if(HEL.color(i) ~= (HEL.color(HEL.twinID(i))))
        loop{HEL.color(i)}(end+1) = i;
        if(~twinRegistered(i))
            if(HEL.color(i) < HEL.color(HEL.twinID(i)))
                bridgeRaw{HEL.color(i), HEL.color(HEL.twinID(i))}(end+1) = i;
            else
                bridgeRaw{HEL.color(HEL.twinID(i)), HEL.color(i)}(end+1) = HEL.twinID(i);
            end
            twinRegistered(i) = 1;
            twinRegistered(HEL.twinID(i)) = 1;
        end
    end
end
for i = 1:numObjects
    inObjFilt = records.verts.borderRegions(:,1) == i | records.verts.borderRegions(:,2) == i;
    colorsPresent{i} = unique(unique(records.verts.color(inObjFilt,:)));
end
inObjFilt = records.verts.borderRegions(:,1) == 0 | records.verts.borderRegions(:,2) == 0;
colorsPresent{numObjects+1} = unique(unique(records.verts.color(inObjFilt,:)));

dataStruct.bridgeArrayIndex = zeros(size(bridgeRaw,1),size(bridgeRaw,2));
dataStruct.colorsPresent = colorsPresent;
index = 0;
for i = 1:size(bridgeRaw,1)
    for j = i:size(bridgeRaw,2)
        if(~isempty(bridgeRaw{i,j}))
            vertexRegistered = zeros(VER.length,1,'uint8');
            twinVertexRegistered = zeros(VER.length,1,'uint8');
            VertListRaw = HEL.origin(bridgeRaw{i,j},1); %ID
            vertexRegistered(VertListRaw) = 1;
            twinEdges = HEL.twinID(bridgeRaw{i,j}); %ID
            twinVertListRaw = HEL.origin(twinEdges,1); %ID
            twinVertexRegistered(twinVertListRaw) = 1;
            startVertices =  find(~twinVertexRegistered & vertexRegistered);
            if(isempty(startVertices))
                startVertices = VertListRaw(1); %Just pick one - this means that the bridge is a loop
            end
            for k = 1:size(startVertices,1)
                temp_vertList = [];
                temp_edgeList = [];
                temp_distList = [];
                temp_radList = [];
                
                temp_vertList(1) = startVertices(k);
                temp_distList(1) = 0;
                temp_radList(1) = VER.rad(startVertices(k));
                startID = startVertices(k);
                curNode = startVertices(k);
                passCondition = 1;
                indexVert = 1;
                completeCircuit = 0;
                while(passCondition)
                    passCondition = 0;
                    for deg = 1:VER.degree(curNode)
                        if(HEL.color(VER.edgeIDList(curNode,deg)) == i &&  HEL.color(HEL.twinID(VER.edgeIDList(curNode,deg))) == j) %%If the half edge with this vertex is this color AND the twin of this half edge is the other color
                            temp_edgeList(indexVert) = VER.edgeIDList(curNode,deg);
                            if(HEL.origin(VER.edgeIDList(curNode,deg),2) ~= startID) %if the twin id is not the start ID
                                indexVert = indexVert + 1;
                                temp_distList(indexVert) = HEL.dist(VER.edgeIDList(curNode,deg));%curNode.edge{deg}.computeDistance;
                                curNode = HEL.origin(VER.edgeIDList(curNode,deg),2); %%Move to the new edge
                                temp_vertList(indexVert) = curNode;
                                temp_radList(indexVert) = VER.rad(curNode);
                                passCondition = 1;
                                break;
                            else
                                completeCircuit = 1;
                            end
                        end
                    end
                end
                index = index+1;
                dataStruct.bridge(index).EL = temp_edgeList;
                dataStruct.bridge(index).Vertices = temp_vertList;
                dataStruct.bridge(index).rad = temp_radList;
                dataStruct.bridge(index).incDist = temp_distList;
                dataStruct.bridge(index).dist = cumsum(temp_distList);
                dataStruct.bridge(index).completeCircuit = completeCircuit;
                dataStruct.bridgeArrayIndex(i,j) = index;
                dataStruct.bridgeArrayIndex(j,i) = index;
            end
        end
    end
end
dataStruct.loopCell = loop;
dataStruct.bridgeArrayIndex = sparse(dataStruct.bridgeArrayIndex);

%%Loop detection
% for i = 1:numObjects
% %%Find all bridges which contain the color 'object'
% %%Start from a point on the bridge
% %%Move CCW turning left at all opertunities
% %%If hit leaf reverse
% while(curVert.ID ~= startNode.ID)
%     %%Get angle between cur direction and adj edges
%     %%Pick the left most option.
%     %%Descend down that branch (edge.Twin.Origin -> curVert)
%     %%If curVert.vertCoorIndex ~= -1.  Reverse = 1.  Go back a step.  Overwrite index in vert list.

% end
% numBridges = index;
% dataStruct.loop = loop;