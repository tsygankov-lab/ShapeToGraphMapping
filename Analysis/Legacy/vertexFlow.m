function [AUC_limit, AUC_flow, weightedVariability] = vertexFlow(records, loopStruct)
%%Go through the pre-caclulated loop boundary profile info.
%%Traverse back up from boundary to root, storing radii and instantaneous distance
%%Determine edge weights at each stage (average radius).
%%Force to be strictly increasing (if i > i+1, i = i+1).
%%Calculate AUC
%%Normalize by Radius
r2sV = loopStruct.records2SubgraphMap_Vertices;
AUC_limit= zeros(length(loopStruct.boundaryVerts),1);
AUC_flow = zeros(length(loopStruct.boundaryVerts),1);
weightedVariability = zeros(length(loopStruct.boundaryVerts),1);
for i = 1:length(loopStruct.boundaryVerts)
    if(i == 20)
        disp('');
    end
	rad = [];
	distInc = [];
	iter =1;
	curVert = loopStruct.boundaryVerts(i);
	while(~loopStruct.isRootNode(curVert))
		nextEdge = loopStruct.parEdge(r2sV(curVert),1);
		distInc(iter) = records.edges.dist(nextEdge);
		curVert = records.edges.origin(nextEdge,2);
		rad(iter) = records.verts.rad(curVert);
        iter = iter + 1;
    end
%     radWeighted = rad;
%     radWeighted(2:end) = (rad(1:end-1) + rad(2:end))/2;
%     radWeighted(1) = rad(1)/2;
    
    weightedVariability(i) = var(rad,distInc);
	AUC_flow(i) = (sum(distInc.*rad)/sum(distInc));
	for j = length(distInc):-1:2
		if(rad(j) < rad(j-1))
			rad(j-1) = rad(j);
		end
	end
	AUC_limit(i) = (sum(distInc.*rad)/sum(distInc));
end