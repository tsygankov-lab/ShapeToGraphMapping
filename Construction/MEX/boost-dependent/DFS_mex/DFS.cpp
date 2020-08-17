#include "mex.h"
#include "DFS.hpp"
//Change to accept entire object graph, and then mark vertices which are not in the subgraph as 'boundary regions'
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
	//try{
	if (nrhs < 4 || nrhs > 6) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargin", "DFS Has 4-5 Inputs (Connectivity Matrix (degree, Neighbor1,dist1,twinID1,Neighbor2,dist,3...), NxMaxDegree EdgeID Matrix, NEdges x 2 DirMatrix, start point, targets to track (movement disallowed), regionBoundaryFlag");
	}
	if (nlhs < 1 || nlhs > 3) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargout", "DFS has 1 to 2 arguments: Reachable Terminal Nodes, Reachable Nodes, Parents");
	}

	//preparing datastructs for dijkstra
	std::vector<DFSstruct> events;
	std::vector<long> terminalPoints;
	//Get Matrix Dimensions (M = Rows, N = Columns)
	auto connMat = mxGetPr(prhs[0]);
	auto connNumRows = mxGetM(prhs[0]);
	auto connNumCols = mxGetN(prhs[0]);
	auto edgeIDMat = mxGetPr(prhs[1]);
	auto edgeIDNumRows = mxGetM(prhs[1]);
	auto edgeIDNumCols = mxGetN(prhs[1]);
	auto edgeDirMat = mxGetPr(prhs[2]);
	auto numEdges = mxGetM(prhs[2]);

	auto startNode = mxGetScalar(prhs[3]) - 1.0;

	//Reserving Memory for Datastructs
	events.reserve(connNumRows);

	//Preparing Root and target list List
	for (int i = 0; i < connNumRows; i++) {
		bool isTarget = false;
		bool isRoot = i == startNode;
		//Could go through ids and set up the root/target stuff after creation but this will initialize the distance correctly.  Refactor w/ setRoot function
		//Pushes the new events in order of arrival into the event matrix
		events.push_back(DFSstruct(i));
		//auto tester = connMat[i];
		events[i].neighborID.reserve(connMat[i]);
		auto edgeNum = 0;
		for (int j = 0; j < 2 * connMat[i]; j += 2) {
			events[i].neighborID.push_back(connMat[connNumRows*(j + 1) + i] - 1); //1->0 indexing
			long edgeID = edgeIDMat[edgeIDNumRows*edgeNum + i] - 1l;
			std::vector<double> edgeDirection({ edgeDirMat[edgeID],edgeDirMat[numEdges + edgeID] });
			events[i].childrenDir.push_back(edgeDirection);
			++edgeNum;
		}
	}

	if (nrhs > 4) {
		auto restrictList = mxGetPr(prhs[4]);
		auto numRestrict = mxGetM(prhs[4]);
		auto numRestrict2 = mxGetN(prhs[4]);
		numRestrict = numRestrict == 1 ? numRestrict2 : numRestrict;

		for (auto i = 0; i < numRestrict; i++) {
			if (restrictList[i] - 1 != startNode) events[restrictList[i] - 1].setAsTerminalPoint();
			else events[restrictList[i] - 1].isTerminal = true;
		}
	}

	if (nrhs > 5) {
		auto boundaryList = mxGetPr(prhs[5]);
		auto boundaryListCount = mxGetM(prhs[5]);
		auto boundaryListCount2 = mxGetN(prhs[5]);
		boundaryListCount = boundaryListCount == 1 ? boundaryListCount2 : boundaryListCount;
		for (auto i = 0; i < boundaryListCount; i++) {
			auto test = boundaryList[i];
			events[boundaryList[i] - 1].setAsRegionBoundary();
		}
	}
	//In this use case we will always compute an MST from the root
	auto outList = dfsSearch(events, startNode, nrhs > 5);

	//Build output arrays:  arr[0]: dist.  arr[1]: parID+1 (0ind->1ind). arr[2]: degree, numChild, childID+1...... (size, numEvents x 1+ maxchildren)
	plhs[0] = mxCreateDoubleMatrix(outList.reachableTerminalPoints.size(), 1, mxREAL);
	plhs[1] = mxCreateDoubleMatrix(outList.reachable.size(), 1, mxREAL);
	plhs[2] = mxCreateDoubleMatrix(outList.reachable.size(), 1, mxREAL);

	auto outPTR0 = mxGetPr(plhs[0]);
	auto outPTR1 = mxGetPr(plhs[1]);
	auto outPTR2 = mxGetPr(plhs[2]);

	auto iter = 0;
	for (auto id : outList.reachableTerminalPoints) {
		outPTR0[iter] = id + 1;
		++iter;
	}

	iter = 0;
	for (auto id : outList.reachable) {
		outPTR1[iter] = id + 1;
		++iter;
	}

	iter = 0;
	for (auto id : outList.reachable) {
		outPTR2[iter] = events[id].parID + 1;
		++iter;
	}
	//} catch (const std::exception& ex) {
	//	mexErrMsgIdAndTxt("MATLAB:dijkstra:Generic", ex.what());
	//	plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	//	plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
	//	plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
	//}
}