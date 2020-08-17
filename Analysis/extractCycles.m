function [dataStruct] = extractCycles(records, dataStruct)
LOOP_EXTRACTION_VERSION = 100; %maj.min.rev
inHoleEnclosingObject = 1;
inHoleEnclosedByObject = 1;
inHoleNoEnclosure = 1;
inObjEnclosingHole = 1;
inObjNoEnclosure = 1;
inObjEnclosedByHole = 1;

%%Loops through all objects and checks if they are either enclosed by
%%another object, or encloses another object.  If no object is enclosed,
%%falls back to classic definition of boundary profile
for i = 1:records.numObjects
    objInd = i;
    enclosedBoundaries = find(records.adjMat(:,i));
    enclosingBoundaries = find(records.adjMat(i,:));
    if(i > records.numNonHoles)
        if(~isempty(enclosingBoundaries))
            for j = 1:length(enclosingBoundaries)
                vertList_Binary = records.verts.borderRegions(:,1) == enclosingBoundaries(j) & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
                loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd,enclosingBoundaries(j),1,0);
                % 				loopStruct.pattern = [i,enclosingBoundaries(j)];
                dataStruct.loop.object.enclosing(inObjEnclosingHole) = loopStruct;
                inObjEnclosingHole = inObjEnclosingHole + 1;
            end
        end
        if(~isempty(enclosedBoundaries))
            vertList_Binary = records.verts.borderRegions(:,2) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
            loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd, objInd, 0,0);
            % 				loopStruct.pattern = [enclosedBoundaries,i];
            dataStruct.loop.hole.enclosed(inHoleEnclosedByObject) = loopStruct;
            inHoleEnclosedByObject = inHoleEnclosedByObject + 1;
        else
            vertList_Binary = records.verts.borderRegions(:,2) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
            loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd, objInd, 0,1);
            dataStruct.loop.hole.acyclic(inHoleNoEnclosure) = loopStruct;
            inHoleNoEnclosure = inHoleNoEnclosure + 1;
        end
    else
        if(~isempty(enclosingBoundaries))
            for j = 1:length(enclosingBoundaries)
                vertList_Binary = records.verts.borderRegions(:,2)  == enclosingBoundaries(j) & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
                loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd, enclosingBoundaries(j),0,0);
                dataStruct.loop.hole.enclosing(inHoleEnclosingObject) = loopStruct;
                inHoleEnclosingObject = inHoleEnclosingObject + 1;
            end
            
        end
        if(~isempty(enclosedBoundaries))
            vertList_Binary = records.verts.borderRegions(:,1) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
            loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd, objInd, 1,0);
            dataStruct.loop.object.enclosed(inObjEnclosedByHole) = loopStruct;
            inObjEnclosedByHole = inObjEnclosedByHole + 1;
        else%if(isempty(enclosingBoundaries)
            vertList_Binary = records.verts.borderRegions(:,1) == i & (records.verts.color(:,1) == i | records.verts.color(:,2) == i | records.verts.color(:,3) == i);
            loopStruct = extractSubGraphCycles(vertList_Binary, records, dataStruct, objInd, objInd, 0,1);
            dataStruct.loop.object.acyclic(inObjNoEnclosure) = loopStruct;
            inObjNoEnclosure = inObjNoEnclosure + 1;
        end
    end
end
dataStruct.loop.numInObjectEnclosingHole = inObjEnclosingHole - 1;
dataStruct.loop.numInHoleEnclosingObject = inHoleEnclosingObject - 1;
dataStruct.loop.numInObjectEnclosedByHole = inObjEnclosedByHole - 1;
dataStruct.loop.numInHoleEnclosedByObject = inHoleEnclosedByObject - 1;
dataStruct.loop.numInObjectNoEnclosure = inObjNoEnclosure - 1;
dataStruct.loop.numInHoleNoEnclosure = inHoleNoEnclosure - 1;
dataStruct.loop.LOOP_EXTRACTION_VERSION = LOOP_EXTRACTION_VERSION;
end