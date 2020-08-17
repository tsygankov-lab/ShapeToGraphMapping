#ifdef MATLAB_MEX_FILE
#include "subGraphSearch.hpp"
#include <exception>
#include <unordered_map>
#include <vector>
#include "mex.h"

// Inputs:
// Store vertex/edge data in unordered map indexed by global id?
// ...) binary vertex filter vector (Search through all vertices and filter
// using the color/location flag) 1) records
// ... - searches through vertices, finds one with a a valid color
// pair (uneeded?)
// 2) color - sub region color, used to select valid edges
// 3) location - Used with color to find valid vertices
// 4) inObject- Used to correctly index the location
// 5) nonCycleFlag - uses different rule to pick the start point
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  try {
    // Matlab preprocessing
    if (nrhs > 4) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:nargin",
          "Too many Arguments! Arguments are Vertex Coordinates, Edge "
          "Connection List, cent, (For Tracking Groups of Objects), Vert "
          "FaceIDs, EdgeFaceIDs, maxFaceID, (for Image Analysis) Vert Colors, "
          "Number of Isolated Objects, Image Label Matrix, Toroidal window "
          "[Xmin, Xmax], Toroidal Window [Ymin, Ymax] ");
    }
    if (nlhs < 4) {
      mexErrMsgIdAndTxt("MATLAB:Voronoi:nargin", "Arguments: ");
    }
    // Read inputs into the appropiate structure
    // Pass to subgraph function

  } catch (const std::exception& ex) {
    mexErrMsgIdAndTxt("Matlab:Voronoi:CFatal", ex.what());
  } catch (...) {
    mexErrMsgIdAndTxt("MATLAB:Voronoi:CFATAL-Unknown",
                      "An Exception was caught in the MEX file due to an "
                      "error.  Computation aborted to prevent MATLAB from "
                      "crashing.  Currently no i");
  }
}
#endif
