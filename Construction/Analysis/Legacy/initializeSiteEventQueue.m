function [SiteList, records] = initializeSiteEventQueue(vertexCoor, EL, center, siteEventQueue,settingsList)

numEdge = size(EL,1);
%Initializing the Priority Queue
%isAssigned = zeros(length(vertexCoor),1);
SiteList = cell(numEdge + size(vertexCoor,1),1); %Net possible events
%doNotAdd = zeros(numEdge + size(vertexCoor,1),1);

objectID = 1;
faceID = 1; %Redundant?

records = struct('Vertex',[],'Face',[],'Edge',[],'VertexInserted',zeros(size(vertexCoor,1),1));
records.Face = cell(1,length(vertexCoor) + 2*numEdge);
records.numVertex = 0;
records.maxOID = 0;
records.numEdges.type0 = 0;
records.numEdges.type1 = 0;
records.numEdges.type2 = 0;
records.numEdges.typeN1 = 0;
records.numEdges.typeinf0 = 0;
records.numEdges.typeinf1 = 0;
records.numEdges.typeinf2 = 0;
records.numEdges.typeinfN1 = 0;

faceIDList = zeros(numEdge + size(vertexCoor,1),1);

%Processes points
for i = 1:length(vertexCoor)
    %eventType = 1; %Isolated vertex
    SiteList{objectID} = siteVertex(vertexCoor(i,1), vertexCoor(i,2),center(1),center(2),objectID);
    if(settingsList.vertexOverrideFaceID == 1) %%If -1 that is checked at edge creation...
        SiteList{objectID}.inputFlagID = settingsList.vertexFaceIDList(i);
        faceIDList(objectID)  = settingsList.vertexFaceIDList(i);
    else
        SiteList{objectID}.inputFlagID = faceID;
        faceIDList(objectID)  = faceID;%settingsList.vertexFaceIDList(i);
    end
    siteEventQueue.add(SiteList{objectID});
    SiteList{objectID}.color = settingsList.vertColorList(i);
    records.Face{objectID} = vorFace(objectID,SiteList{objectID});
    objectID = objectID + 1;
    faceID = faceID + 1;
end

%%EDGES LATER
for i = 1:numEdge
    [closeX,closeY,closeXAbs,closeYAbs,truncFlag] = closestPoint(vertexCoor(EL(i,1),1),vertexCoor(EL(i,1),2),vertexCoor(EL(i,2),1),vertexCoor(EL(i,2),2),center(1),center(2));
    %lineType = 11; %Normal Line;
    if(truncFlag == 1) %if the closest point to the line is an endpoint
        lineEvent = siteEdge(closeX,closeY,closeXAbs,closeYAbs,center(1),center(2),SiteList{EL(i,1)},SiteList{EL(i,2)},objectID); %Assigns the line the closest point to the line segment, closest point to the line in general, the center of the sweep circle, the type of line event it is, and two endpoints
        SiteList{EL(i,1)}.setEndpointAsLineEvent(lineEvent);
        % lineEvent.objectIndex = objectID;
        lineEvent.LOWERobjectID = objectID + 1;
        lineEvent.faceIndex = faceID;
        SiteList{objectID} = lineEvent;
        SiteList{objectID}.color = settingsList.vertColorList(EL(i,1));
        SiteList{objectID+1} = lineEvent.createLOWER();
        SiteList{objectID+1}.color = settingsList.vertColorList(EL(i,2));
    elseif(truncFlag == 2) %if the closest point to the line is an endpoint
        lineEvent = siteEdge(closeX,closeY,closeXAbs,closeYAbs,center(1),center(2),SiteList{EL(i,1)},SiteList{EL(i,2)},objectID); %Assigns the line the closest point to the line segment, closest point to the line in general, the center of the sweep circle, the type of line event it is, and two endpoints
        SiteList{EL(i,2)}.setEndpointAsLineEvent(lineEvent);
        % lineEvent.objectIndex = objectID;
        lineEvent.LOWERobjectID = objectID + 1;
        lineEvent.faceIndex = faceID;
        SiteList{objectID} = lineEvent;
        SiteList{objectID+1} = lineEvent.createLOWER();
                SiteList{objectID}.color = settingsList.vertColorList(EL(i,1));
                SiteList{objectID+1}.color = settingsList.vertColorList(EL(i,2));
    else
        lineEvent = siteEdge(closeX,closeY,closeXAbs,closeYAbs,center(1),center(2),SiteList{EL(i,1)},SiteList{EL(i,2)},objectID);
        % lineEvent.objectIndex = objectID;
        lineEvent.LOWERobjectID = objectID + 1;
        lineEvent.faceIndex = faceID;
        SiteList{objectID} = lineEvent;
        SiteList{objectID+1} = lineEvent.createLOWER();
        siteEventQueue.add(lineEvent);
                        SiteList{objectID}.color = settingsList.vertColorList(EL(i,1));
                SiteList{objectID+1}.color = settingsList.vertColorList(EL(i,2));
    end
    if(settingsList.edgeOverrideFaceID == -1)
        SiteList{objectID}.inputFlagID = settingsList.vertexFaceIDList(EL(i,1));
        SiteList{objectID+1}.inputFlagID = settingsList.vertexFaceIDList(EL(i,2));
                        faceIDList(objectID)  = settingsList.vertexFaceIDList(EL(i,1));%settingsList.vertexFaceIDList(i);
        faceIDList(objectID+1)  = settingsList.vertexFaceIDList(EL(i,2));%settingsList.vertexFaceIDList(i);
    elseif(settingsList.edgeOverrideFaceID == 1)
        SiteList{objectID}.inputFlagID = settingsList.edgeFaceIDList(i);
        SiteList{objectID+1}.inputFlagID = -settingsList.edgeFaceIDList(i);
                faceIDList(objectID)  = settingsList.edgeFaceIDList(i);%settingsList.vertexFaceIDList(i);
        faceIDList(objectID+1)  = -settingsList.edgeFaceIDList(i);%settingsList.vertexFaceIDList(i);
    elseif(settingsList.edgeOverrideFaceID == 2)
        SiteList{objectID}.inputFlagID = settingsList.edgeFaceIDList(i,1);
        SiteList{objectID+1}.inputFlagID = settingsList.edgeFaceIDList(i,2);
        faceIDList(objectID)  = settingsList.edgeFaceIDList(i,1);%settingsList.vertexFaceIDList(i);
        faceIDList(objectID+1)  = settingsList.edgeFaceIDList(i,2);%settingsList.vertexFaceIDList(i);
    else
        SiteList{objectID}.inputFlagID = faceID;
        SiteList{objectID+1}.inputFlagID = -faceID;
        faceIDList(objectID)  = faceID;%settingsList.vertexFaceIDList(i);
        faceIDList(objectID+1)  = -faceID;%settingsList.vertexFaceIDList(i);

    end

    if(settingsList.vertexOverrideFaceID == -1)
        SiteList{EL(i,1)}.inputFlagID = SiteList{objectID}.inputFlagID;
        SiteList{EL(i,2)}.inputFlagID = SiteList{objectID+1}.inputFlagID;
        faceIDList(EL(i,1))  = SiteList{objectID}.inputFlagID;%settingsList.vertexFaceIDList(i);
        faceIDList(EL(i,2))  = SiteList{objectID+1}.inputFlagID;%settingsList.vertexFaceIDList(i);
    end
    records.Face{objectID} = vorFace(objectID,SiteList{objectID});
    records.Face{objectID+1} = vorFace(objectID+1,SiteList{objectID+1}); %%SiteClass{oid+1} does not exist yet.
    
    faceID = faceID + 1;
    objectID = objectID + 2; %Events DegenL/R, Upper, Lower.  Degen Account for. Needs 2 points for U/L
end

records.faceIDs = unique(faceIDList);
records.maxOID = objectID-1;
