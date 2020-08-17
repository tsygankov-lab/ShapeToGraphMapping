#include "mex.h"
//Indicates how to take a 5x3 matrix and extract information in rows then cols
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
	if(nrhs != 1){
		mexErrMsgIdAndTxt("MATLAB:dijkstra:nargin","dijkstra Has Three Inputs (Connectivity Matrix (degree, Neighbor1,dist,2,dist,3...), root list, target list)");
	}
	if(nlhs != 0){
				mexErrMsgIdAndTxt("MATLAB:dijkstra:nargout","dijkstra Has One Output TBD");
	}

	auto connMat = mxGetPr(prhs[0]);
	auto connNumRows = mxGetM(prhs[0]);
	auto connNumCols = mxGetN(prhs[0]);

	for(size_t i=0;i<connNumRows;i++){
		mexPrintf("\n");

		for (size_t j = 0; j < connNumCols; j++) {
			mexPrintf("%lf, ", connMat[connNumRows*j+i]);
		}
	}
	return;
}
