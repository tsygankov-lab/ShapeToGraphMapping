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
#include "BFS_inRad.hpp"
#include "mex.h"
//Inputs: number of outputs, array (of arrays) of outputs, number of inputs, array (of arrays) of inputs
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
	if (nrhs != 4) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargin", "BFS Has Four Inputs (Connectivity Matrix (degree, Neighbor1,dist1,edgeID1,twinID1,Neighbor2,dist,3...), start points, radii, pos");
	}
	if (nlhs != 1) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargout", "Dijkstra has 1 to 3 arguments (Reachable Nodes)");
	}

	//preparing datastructs for dijkstra
	std::vector<bfsVert_inrad> events;
	std::vector<long> startIDs;
	//Get Matrix Dimensions (M = Rows, N = Columns)
	auto connMat = mxGetPr(prhs[0]);
	auto connNumRows = mxGetM(prhs[0]);
	auto connNumCols = mxGetN(prhs[0]);
	auto startNodeIDs = mxGetPr(prhs[1]);
	auto startNodeVeca = mxGetM(prhs[1]);
	auto startNodeVecb = mxGetN(prhs[1]);
	auto startNodeCounts = startNodeVeca == 1 ? startNodeVecb : startNodeVeca;

	auto radMat = mxGetPr(prhs[2]);
	auto radVecA = mxGetM(prhs[2]);
	auto radVecB = mxGetN(prhs[2]);
	auto radVecCounts = radVecA == 1 ? radVecB : radVecA;

	auto posMat = mxGetPr(prhs[3]);
	auto posVecXY = mxGetN(prhs[3]);
	auto posVecElem = mxGetM(prhs[3]);
	//Reserving Memory for Datastructs
	events.reserve(connNumRows);

	//Preparing Root and target list List
	for (int i = 0; i < connNumRows; i++) {
		bool isTarget = false;
		bool isRoot = false;
		auto radVal = radMat[i];
		//Could go through ids and set up the root/target stuff after creation but this will initialize the distance correctly.  Refactor w/ setRoot function
		//Pushes the new events in order of arrival into the event matrix
		events.push_back(bfsVert_inrad(i, posMat[i], posMat[posVecElem + i], radMat[i]));
		//auto tester = connMat[i];
		events[i].neighborID.reserve(connMat[i]);
		for (int j = 0; j < 2 * connMat[i]; j += 2) {
			events[i].neighborID.push_back(connMat[connNumRows*(j + 1) + i] - 1); //1->0 indexing
		}
	}
	for (auto i = 0; i < startNodeCounts; i++) {
		startIDs.push_back(startNodeIDs[i] - 1);
	}

	//In this use case we will always compute an MST from the root
	auto outList = bfsSearch_inRad(events, startIDs);

	//Build output arrays:  arr[0]: dist.  arr[1]: parID+1 (0ind->1ind). arr[2]: degree, numChild, childID+1...... (size, numEvents x 1+ maxchildren)
	plhs[0] = mxCreateDoubleMatrix(outList.size(), 1, mxREAL);
	auto outPTR0 = mxGetPr(plhs[0]);

	auto iter = 0;
	for (auto id : outList) {
		outPTR0[iter] = id + 1;
		++iter;
	}
}