/*Compile info...
Output Type (windows): .mexw64 (.mexa64 on linux)
Additional Include Directories: C:\Program Files\MATLAB\R2017b\extern\include
Preprocesor Definitions:		MATLAB_MEX_FILE
Additional Library Directories:	C:\Program Files\MATLAB\R2017b\extern\lib\win64\microsoft (check linux vm)
Additional Dependencies:		libmx.lib;libmex.lib;libmat.lib;
Module Definition File:			deffile

deffile Contents:
LIBRARY dijkstra_mex.cpp
EXPORTS mexFunction
*/
/*
typedef struct returnList {
	std::vector<long> reachable;
	std::vector<long> reachableTerminalPoints;
	std::vector<long> reachableAxisPoints;
}returnList;
*/
#include "BFS.hpp"
#include "mex.h"
//Inputs: number of outputs, array (of arrays) of outputs, number of inputs, array (of arrays) of inputs
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
	if (nrhs < 2 && nrhs > 5) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargin", "BFS Has Two (or Four) Inputs (Connectivity Matrix (degree, Neighbor1,dist1,edgeID1,twinID1,Neighbor2,dist,3...), start point, targets to track (movement allowed), targets to track (movement disallowed), disallowed Movement");
	}
	if (nlhs < 1 || nlhs > 4) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargout", "Dijkstra has 1 to 3 arguments (Reachable Nodes, Nodes in group A, Nodes in group B), nodes before group B");
	}

	//preparing datastructs for dijkstra
	std::vector<bfsVert> events;
	std::vector<long> axisPoints;
	std::vector<long> terminalPoints;
	//Get Matrix Dimensions (M = Rows, N = Columns)
	auto connMat = mxGetPr(prhs[0]);
	auto connNumRows = mxGetM(prhs[0]);
	auto connNumCols = mxGetN(prhs[0]);
	auto startNode = mxGetScalar(prhs[1]) - 1.0;

	//Reserving Memory for Datastructs
	events.reserve(connNumRows);

	//Preparing Root and target list List
	for (int i = 0; i < connNumRows; i++) {
		bool isTarget = false;
		bool isRoot = i == startNode;
		//Could go through ids and set up the root/target stuff after creation but this will initialize the distance correctly.  Refactor w/ setRoot function
		//Pushes the new events in order of arrival into the event matrix
		events.push_back(bfsVert(i));
		//auto tester = connMat[i];
		events[i].neighborID.reserve(connMat[i]);
		for (int j = 0; j < 2 * connMat[i]; j += 2) {
			events[i].neighborID.push_back(connMat[connNumRows*(j + 1) + i] - 1); //1->0 indexing
		}
	}
	if (nrhs > 2) {
		auto terminalList = mxGetPr(prhs[2]);
		auto numTerminal = mxGetM(prhs[2]);
		for (auto i = 0; i < numTerminal; i++) {
			events[terminalList[i] - 1].setAsTerminalPoint();
		}
	}
	if (nrhs > 3) {
		auto axisList = mxGetPr(prhs[3]);
		auto numAxis = mxGetM(prhs[3]);
		for (auto i = 0; i < numAxis; i++) {
			events[axisList[i] - 1].setAsRestrictedTarget();
		}
	}
	if (nrhs > 4) {
		auto restrictList = mxGetPr(prhs[4]);
		auto numRestrict = mxGetM(prhs[4]);
		for (auto i = 0; i < numRestrict; i++) {
			if (restrictList[i] - 1 != startNode) events[restrictList[i] - 1].setAsRestrictedNode();
		}
	}
	//In this use case we will always compute an MST from the root
	auto outList = bfsSearch(events, startNode);

	//Build output arrays:  arr[0]: dist.  arr[1]: parID+1 (0ind->1ind). arr[2]: degree, numChild, childID+1...... (size, numEvents x 1+ maxchildren)
	plhs[0] = mxCreateDoubleMatrix(outList.reachable.size(), 1, mxREAL);
	plhs[1] = mxCreateDoubleMatrix(outList.reachableTerminalPoints.size(), 1, mxREAL);
	plhs[2] = mxCreateDoubleMatrix(outList.reachableOneBeforeAxis.size(), 1, mxREAL);
	plhs[3] = mxCreateDoubleMatrix(outList.reachableAxisPoints.size(), 1, mxREAL);

	auto outPTR0 = mxGetPr(plhs[0]);
	auto outPTR1 = mxGetPr(plhs[1]);
	auto outPTR2 = mxGetPr(plhs[2]);
	auto outPTR3 = mxGetPr(plhs[3]);

	auto iter = 0;
	for (auto id : outList.reachable) {
		outPTR0[iter] = id + 1;
		++iter;
	}

	iter = 0;
	for (auto id : outList.reachableTerminalPoints) {
		outPTR1[iter] = id + 1;
		++iter;
	}

	iter = 0;
	for (auto id : outList.reachableOneBeforeAxis) {
		outPTR2[iter] = id + 1;
		++iter;
	}

	iter = 0;
	for (auto id : outList.reachableAxisPoints) {
		outPTR3[iter] = id + 1;
		++iter;
	}
}