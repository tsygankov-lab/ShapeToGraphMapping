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

#include "dijkstra.hpp"
#include "mex.h"
//Inputs: number of outputs, array (of arrays) of outputs, number of inputs, array (of arrays) of inputs
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
	try {
		if (nrhs != 3 && nrhs != 4) {
			mexErrMsgIdAndTxt("MATLAB:dijkstra:nargin", "dijkstra Has Three (or Four) Inputs (Connectivity Matrix (degree, Neighbor1,dist1,edgeID1,twinID1,Neighbor2,dist,3...), root list, target list, restricted-Movement List (opt))");
		}
		if (nlhs < 1 || nlhs > 3) {
			mexErrMsgIdAndTxt("MATLAB:dijkstra:nargout", "Dijkstra has 1 to 3 arguments (Dist, parents, children)");
		}

		//preparing datastructs for dijkstra
		std::vector<djNode> events;
		std::vector<long> roots;
		std::vector<long> targets;
		//Get Matrix Dimensions (M = Rows, N = Columns)
		auto connMat = mxGetPr(prhs[0]);
		auto connNumRows = mxGetM(prhs[0]);
		auto connNumCols = mxGetN(prhs[0]);
		auto rootNumRows = mxGetM(prhs[1]);
		auto rootList = mxGetPr(prhs[1]);

		auto noTargets = mxIsEmpty(prhs[2]);
		auto targetNumRows = noTargets ? 0 : mxGetM(prhs[2]); //There will be 1 row even if vector is empty...
		auto targetNumCols = noTargets ? 0 : mxGetN(prhs[2]);
		auto targetList = mxGetPr(prhs[2]);
		double* restrictionList;
		size_t numRestrict = 0;

		//Reserving Memory for Datastructs
		events.reserve(connNumRows);
		roots.reserve(rootNumRows);
		targets.reserve(targetNumRows);

		//Preparing Root and target list List
		for (int i = 0; i < rootNumRows; i++) {
			roots.push_back(rootList[i] - 1); //1->0 indexing
		}
		for (int i = 0; i < targetNumRows; i++) {
			targets.push_back(targetList[i] - 1); //1->0 indexing
		}
		for (int i = 0; i < connNumRows; i++) {
			bool isTarget = false;
			bool isRoot = false;
			//Could go through ids and set up the root/target stuff after creation but this will initialize the distance correctly.  Refactor w/ setRoot function
			//Pushes the new events in order of arrival into the event matrix
			events.push_back(djNode(i));
			//auto tester = connMat[i];
			events[i].neighborID.reserve(connMat[i]);
			events[i].edgeDist.reserve(connMat[i]);
			for (int j = 0; j < 2 * connMat[i]; j += 2) {
				events[i].neighborID.push_back(connMat[connNumRows*(j + 1) + i] - 1); //1->0 indexing
				events[i].edgeDist.push_back(connMat[connNumRows*(j + 2) + i]);
			}
		}
		for (auto id : roots) {
			events[id].setAsRoot();
		}
		if (nrhs == 4) {
			auto restrictionList = mxGetPr(prhs[3]);
			auto numRestrict = mxGetM(prhs[3]);
			for (auto i = 0; i < numRestrict; i++) {
				if(!events[restrictionList[i]-1].isRoot) events[restrictionList[i] - 1].restrictEdges();
			}
		}


		for (auto id : targets) {
			events[id].setAsTarget();
		}
		//In this use case we will always compute an MST from the root
		dijkstraSearch(events, roots, targets.size(), 1);

		//Setting up child connections
		for (auto e : events) {
			if (e.parID != -1l) events[e.parID].childID.push_back(e.vertID);
		}

		size_t maxChildren = 0;
		for (auto e : events) {
			if (e.childID.size() > maxChildren) {
				maxChildren = e.childID.size();
			}
		}
		//Build output arrays:  arr[0]: dist.  arr[1]: parID+1 (0ind->1ind). arr[2]: degree, numChild, childID+1...... (size, numEvents x 1+ maxchildren)
		plhs[0] = mxCreateDoubleMatrix(connNumRows, 1, mxREAL);
		plhs[1] = mxCreateDoubleMatrix(connNumRows, 1, mxREAL);
		plhs[2] = mxCreateDoubleMatrix(connNumRows, 1 + maxChildren, mxREAL);
		auto outPTR0 = mxGetPr(plhs[0]);
		auto outPTR1 = mxGetPr(plhs[1]);
		auto outPTR2 = mxGetPr(plhs[2]);

		for (auto i = 0; i < events.size(); i++) {
			outPTR0[i] = events[i].dist;
			outPTR1[i] = events[i].parID + 1;
			outPTR2[i] = events[i].childID.size();
			for (auto j = 0; j < events[i].childID.size(); j++) {
				outPTR2[connNumRows * (1 + j) + i] = events[i].childID[j] + 1;
			}
		}
	}
	catch (const std::exception& ex) {
		mexErrMsgIdAndTxt("MATLAB:dijkstra:Generic", ex.what());
		plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
		plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
		plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
	}
}