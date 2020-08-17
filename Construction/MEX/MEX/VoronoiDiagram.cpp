// Disables Vector bound checking (Visual C++)
//#define _SECURE_SCL 0

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <vector>

#include "DataTypes/siteEvent.hpp"
#include "Math/basicMathAndGeometry.hpp"
#include "Queue/SEQTree.hpp"
#include "Records/halfEdgeRecords.hpp"
#include "Search/BFS.hpp"
#include "Tree/RBT.hpp"

#ifndef _GCC_49_COMP
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#endif
#ifdef _OMP
#include <omp.h>
#endif  // _OMP
#ifndef _SKIP_CHECKS
#include <exception>
class VorFaceIsEmpty : public std::exception {
  virtual const char* what() const throw() {
    return "A Voronoi Polygon has no Vertices Associated with it";
  }
} vorFaceIsEmpty;
#endif
#ifndef MATLAB_MEX_FILE

//#include "ThirdParty\cxxopts.hpp"
typedef struct ELVertProc {
  std::vector<arrXY> vertCoor;
  std::vector<std::array<int, 2>> EL;
} inputList;
/*
Format from file
##Comments
PARAM_LIST_NAME={comma delimited list};
PARAM_NAME=...
*/
inputList loadVecFromFile(const char* file) {
  inputList outVal;
  std::ifstream vecFile;
  vecFile.open(file);
  if (!vecFile) {
    std::cerr << "Can not open file" << file << std::endl;
    exit(1);
  }
  std::string line;
  std::string VERTEXLIST = "VertexList";
  std::string EDGELIST = "EL";
  if (vecFile.is_open()) {
    while (vecFile.peek() == ',' || vecFile.peek() == ' ' ||
           vecFile.peek() == '}' || vecFile.peek() == ';' ||
           vecFile.peek() == '\n' || vecFile.peek() == '\t' ||
           vecFile.peek() == ']' || vecFile.peek() == '[') {
      vecFile.ignore();
    }
    while (std::getline(vecFile, line, '=')) {
      if (VERTEXLIST.compare(0, VERTEXLIST.size(), line, 0,
                             VERTEXLIST.size()) == 0) {
        double a, b;
        std::string arguments;
        std::string curVal;
        std::getline(vecFile, arguments, ']');
        std::istringstream argumentParser(arguments);
        while (argumentParser.peek() == '{' || argumentParser.peek() == ' ' ||
               argumentParser.peek() == '\n' || argumentParser.peek() == '\t' ||
               argumentParser.peek() == ']' || argumentParser.peek() == '[') {
          argumentParser.ignore();
        }
        while (argumentParser >> a) {
          while (argumentParser.peek() == ',' || argumentParser.peek() == ' ' ||
                 argumentParser.peek() == '}' || argumentParser.peek() == ';' ||
                 argumentParser.peek() == '\n' ||
                 argumentParser.peek() == '\t' ||
                 argumentParser.peek() == ']' || argumentParser.peek() == '[') {
            argumentParser.ignore();
          }
          argumentParser >> b;
          outVal.vertCoor.push_back(arrXY{a, b});
          while (argumentParser.peek() == ',' || argumentParser.peek() == ' ' ||
                 argumentParser.peek() == '}' || argumentParser.peek() == ';' ||
                 argumentParser.peek() == '\n' ||
                 argumentParser.peek() == '\t' ||
                 argumentParser.peek() == ']' || argumentParser.peek() == '[') {
            argumentParser.ignore();
          }
        }
        std::getline(vecFile, arguments, ';');
      } else if (EDGELIST.compare(0, EDGELIST.size(), line, 0,
                                  EDGELIST.size()) == 0) {
        int a, b;
        std::string arguments;
        std::string curVal;
        std::getline(vecFile, arguments, ']');
        std::istringstream argumentParser(arguments);
        while (argumentParser.peek() == '{' || argumentParser.peek() == ' ' ||
               argumentParser.peek() == '\n' || argumentParser.peek() == '\t' ||
               argumentParser.peek() == ']' || argumentParser.peek() == '[') {
          argumentParser.ignore();
        }
        while (argumentParser >> a) {
          while (argumentParser.peek() == ',' || argumentParser.peek() == ' ' ||
                 argumentParser.peek() == '}' || argumentParser.peek() == ';' ||
                 argumentParser.peek() == '\n' ||
                 argumentParser.peek() == '\t' ||
                 argumentParser.peek() == ']' || argumentParser.peek() == '[') {
            argumentParser.ignore();
          }
          argumentParser >> b;
          outVal.EL.push_back(std::array<int, 2>{a, b});
          while (argumentParser.peek() == ',' || argumentParser.peek() == ' ' ||
                 argumentParser.peek() == '}' || argumentParser.peek() == ';' ||
                 argumentParser.peek() == '\n' ||
                 argumentParser.peek() == '\t' ||
                 argumentParser.peek() == ']' || argumentParser.peek() == '[') {
            argumentParser.ignore();
          }
        }
        std::getline(vecFile, arguments, ';');
      }
      while (vecFile.peek() == ',' || vecFile.peek() == ' ' ||
             vecFile.peek() == '}' || vecFile.peek() == ';' ||
             vecFile.peek() == '\n' || vecFile.peek() == '\t' ||
             vecFile.peek() == ']' || vecFile.peek() == '[') {
        vecFile.ignore();
      }

      // auto curLine = std::getline(vecFile, line, '=');
      // outVal.vertCoor.push_back(std::vector<double>({ a,b }));
    }
  }
  vecFile.close();
  return outVal;
}

inline double fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

// halfEdgeRecords voronoiDiagram(std::vector<std::vector<double>> vertexCoor,
// std::vector<std::vector<uint64_t>> EL, std::vector<double> cent) {
//}
// Entry Point

void initializeQueue(vorRBT::RBTree& beachTree, std::vector<arrXY>& vertexCoor,
                     std::vector<std::array<int, 2>>& EL) {
  // std::vector<vertexEvent> vertList;
  // vertList.reserve(vertexCoor.size());
  // Does not currently support colors
  beachTree.VertexContainer.reserve(vertexCoor.size());
  beachTree.LineContainer.reserve(EL.size() * 2);
  long objectID = -1;
  for (auto vert : vertexCoor) {
    beachTree.VertexContainer.emplace_back(vert, beachTree.cent, ++objectID,
                                           0l);
    beachTree.queue.add(&beachTree.VertexContainer.back());
    beachTree.records.createFace(&beachTree.VertexContainer.back(), -1);
  }
  /*
          typedef struct {
          vecDBL closeXY;
          vecDBL closeXY_Trunc;
          int truncFlag;
  }closestPoint_Out;
  */
  // lineEvent(vecDBL pos, vecDBL infPos, vecDBL cent, vertexEvent* EP1,
  // vertexEvent* EP2, long objectIndex, long eventLog) : siteEvent(pos, cent,
  // objectIndex, LINE, eventLog), infPos(infPos) {
  for (auto edge : EL) {
    auto vertA = &beachTree.VertexContainer.at(edge[0]);
    auto vertB = &beachTree.VertexContainer.at(edge[1]);
    auto cpOut =
        vorGeo::closestPoint_TRUNC(vertA->pos, vertB->pos, beachTree.cent);

    beachTree.LineContainer.emplace_back(cpOut.closeXY_Trunc, cpOut.closeXY,
                                         beachTree.cent, vertA, vertB,
                                         ++objectID, 0l);
    lineEvent& lineObj = beachTree.LineContainer.back();
    // vertA->setEndpointAsLineEvent(lineObj);
    beachTree.LineContainer.emplace_back(lineObj);
    lineEvent& lineObj_Twin = beachTree.LineContainer.back();
    lineObj_Twin.UPPER = false;
    lineObj_Twin.twin = &lineObj;
    lineObj_Twin.objectIndex = ++objectID;
    lineObj.twin = &lineObj_Twin;

    if (cpOut.truncFlag == 1) {
      vertA->setEndpointAsLineEvent(lineObj);
    } else if (cpOut.truncFlag == 2) {
      vertB->setEndpointAsLineEvent(lineObj);
    } else if (cpOut.truncFlag == 0) {
      // Should proably add the lower line here, but program was initially
      // written with this being the upper line
      beachTree.queue.add(&lineObj);
    }
    // Color and faceID settings will go here
    beachTree.records.createFace(&lineObj, vertA->voronoiFace->color);
    beachTree.records.createFace(&lineObj_Twin, vertB->voronoiFace->color);
    // ObjectID incrimented twice here
  }
}

int main(int argc, char* argv[]) {
  // point generation
  for (int i = 0; i < argc; i++) {
    std::cout << "ARGUMENT " << i << ": " << argv[i] << std::endl;
  }
  std::vector<arrXY> vertexCoor;
  auto EL = std::vector<std::array<int, 2>>();

  size_t numEvents = 0;
  srand(time(0));
  if (argc == 1) {
    size_t numEvents = 10000;
    vertexCoor.reserve(numEvents);
    for (int i = 0; i < numEvents; i++) {
      vertexCoor.push_back(arrXY({fRand(-100, 100), fRand(-100, 100)}));
      // auto tmp = vertexCoor.back();
      // std::cout << tmp[0] << "  " << tmp[1] << std::endl;
    }
  } else {
    char fileRead[] = "-in";
    if (strncmp(argv[1], fileRead, 4) == 0) {
      auto outVal = loadVecFromFile(argv[2]);
      vertexCoor = outVal.vertCoor;
      EL = outVal.EL;
    }
  }
  auto start = std::chrono::system_clock::now();

  // vertexCoor.push_back(std::vector<double>({ 1.4,5.3 }));
  // vertexCoor.push_back(std::vector<double>({ 7.7,4.2 }));
  // vertexCoor.push_back(std::vector<double>({ 2.2,9.2 }));
  // vertexCoor.push_back(std::vector<double>({ 8.3,9.3 }));
  // vertexCoor.push_back(std::vector<double>({ 2.0,3.9 }));

  // Setup - would normally call voronoiDiagram here
  auto cent = arrXY({0.0, 0.0});
  auto queue = vorQueue::heapQueue((vertexCoor.size() + 2 * EL.size()) / 2);
  auto records = halfEdgeRecords(vertexCoor.size(), EL.size());
  auto nodeBinSize = (vertexCoor.size() + 2 * EL.size()) / 20 > 128
                         ? (vertexCoor.size() + 2 * EL.size()) / 20
                         : 128;
  auto degenBinSize = EL.size() / 100 > 128 ? EL.size() / 100 : 128;
  auto circBinSize = (vertexCoor.size() + EL.size()) / 80 > 128
                         ? (vertexCoor.size() + EL.size()) / 80
                         : 128;
  auto beachTree = vorRBT::RBTree(cent, queue, records, nodeBinSize,
                                  degenBinSize, circBinSize);

  initializeQueue(beachTree, vertexCoor, EL);
  double lastRad = 0;
  while (!queue.isempty()) {
    // if (beachTree.NodeContainer.size() >= 17 &&
    // beachTree.NodeContainer.at(16).get()->nodeIndex != 16) 	std::cout <<
    //"SOMETHING HAPPENNED"; beachTree.dataValidator(); Iteration four, crap
    // gets in queue->root.  Figure it out
    beachTree.eventLog++;
#ifdef _DEBUG
    // std::cout << "ITERATION " << beachTree.eventLog << ": ";
#endif  // _DEBUG
        // beachTree.dataValidator();
        // queue.validateData();
    auto next = queue.poll();
    lastRad = next->rad;
    // queue.validateData();
    // beachTree.dataValidator();
    if (next->objType == VERTEX) {
      beachTree.handleVertexEvent(static_cast<vertexEvent*>(next));
    } else if (next->objType == LINE) {
      beachTree.handleLineEvent(static_cast<lineEvent*>(next));
    } else if (next->objType == CIRCLEEVENT) {
      beachTree.handleCircleEvent(static_cast<circleEvent*>(next));
    }
    // beachTree.print2DUtil(beachTree.root, 10);
#ifdef _DEBUG
    // std::cout << beachTree.printLeaves() << std::endl;
#endif  // _DEBUG

    // else {
    //	std::cout << "???";
    //}
    // beachTree.dataValidator();
    // queue.validateData();
    // beachTree.print2DUtil(beachTree.root, 0);
  }
#ifdef _DEBUG
  // int iterTest = 0;
  // for (auto& e : beachTree.NodeContainer) {
  //	std::cout << "ID " << iterTest++ << ": " << e.toString() << " MY ID: "
  //<< e.getID() << std::endl;
  //}
  // iterTest = 0;
  // auto testVec = beachTree.NodeContainer.extractObjVector();
  // for (auto& e : testVec) {
  //	std::cout << "ID " << iterTest++ << ": " << e.toString() << " MY ID: "
  //<< e.getID() << std::endl;
  //}
  // beachTree.NodeContainer.setIDsToFinalLocation();
  // for (auto& e : beachTree.NodeContainer) {
  //	std::cout << "ID " << iterTest++ << ": " << e.toString() << " MY ID: "
  //<< e.getID() << std::endl;
  //}
//	iterTest = 0;
//	for (auto& e : records.Vertices) {
//		std::cout << "ID " << iterTest++ << ": " << e.toString() << " MY
// ID: " << e.getID() << std::endl;
//	}
#endif
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> TotalTime = end - start;
  beachTree.attachInfiniteBisectors(lastRad * 1.5);
  std::cout << "C++ Voronoi Run Time " << TotalTime.count() << std::endl;
  // beachTree.records.DEBUG_dispContents();
  return 0;
}
#endif  // !MATLAB_MEX_FILE

#ifdef MATLAB_MEX_FILE
#include "mex.h"
// Merge updates to degenContainers when home
// Arg 1: Vert
// Arg 2: EL
// Arg 3: Cent
// Arg 4: Color
// Arg 5: vertFaceIDs (Empty -> Auto Assign from Edge)
// Arg 6: edgeFaceIDs (Empty -> Auto Assign from Vert) Both empty -> ignore
// Arg 7: numObjects
// Arg 8: labelMat

typedef struct matlabInputs {
  double* vertCoor;
  double* EL;
  double* cent;
  double* vertFaceIDs;
  double* edgeFaceIDs;
  double* maxFaceID;
  double* color;
  double* numObjects;
  double* labelMat;
  double* xTor;
  double* yTor;
  double* searchFlag;
  double* scaleFactor;

  bool toroidalMode = false;
  int edgeFaceIDMode = 0;
  long numVerts = 0;
  long numEdges = 0;
  double sf = 0;
} matlabInputs;

void initializeQueue(vorRBT::RBTree& beachTree, matlabInputs inp) {
  // std::vector<vertexEvent> vertList;
  // vertList.reserve(vertexCoor.size());
  // Does not currently support colors

  // Update to have matlab and python use same interface outside of input
  // function (IE - update this)
#ifndef _TOROIDAL
  beachTree.reserveVertexContainer(inp.numVerts);
  beachTree.reserveLineContainer(inp.numEdges * 2);
#else
  beachTree.reserveVertexContainer(9 * inp.numVerts);
  beachTree.reserveLineContainer(9 * inp.numEdges * 2);
#endif
  long objectID = -1;
  /*
  for (int i = 0; i < inp.numVerts; i++) {
    beachTree.VertexContainer.emplace_back(
        arrXY{inp.vertCoor[i], inp.vertCoor[i + inp.numVerts]}, beachTree.cent,
        ++objectID, 0l);
    beachTree.queue.add(&beachTree.VertexContainer.back());
    auto Face = beachTree.records.createFace(&beachTree.VertexContainer.back(),
                                             inp.color ? inp.color[i] : -1l);
    if (!inp.vertFaceIDs && !inp.edgeFaceIDs)
      Face->faceIndex = Face->id;
    else if (inp.vertFaceIDs)
      Face->faceIndex = inp.vertFaceIDs[i];
  }*/
  for (int i = 0; i < inp.numVerts; i++) {
    auto& newVert = beachTree.addAndReturn_Vertex(
        arrXY{inp.vertCoor[i], inp.vertCoor[i + inp.numVerts]}, beachTree.cent,
        ++objectID, 0l);
    beachTree.queue.add(
        &newVert);  // Ideally this should be abstracted so queue can change
    auto Face =
        beachTree.records.createFace(&newVert, inp.color ? inp.color[i] : -1l);
    if (!inp.vertFaceIDs && !inp.edgeFaceIDs)
      Face->faceIndex = Face->id;
    else if (inp.vertFaceIDs)
      Face->faceIndex = inp.vertFaceIDs[i];
  }

  /*
  typedef struct {
  vecDBL closeXY;
  vecDBL closeXY_Trunc;
  int truncFlag;
  }closestPoint_Out;
  */
  // lineEvent(vecDBL pos, vecDBL infPos, vecDBL cent, vertexEvent* EP1,
  // vertexEvent* EP2, long objectIndex, long eventLog) : siteEvent(pos, cent,
  // objectIndex, LINE, eventLog), infPos(infPos) {
  for (int i = 0; i < inp.numEdges; i++) {
    long vertAind = inp.EL[i] - 1;
    long vertBind = inp.EL[i + inp.numEdges] - 1;
    auto vertA = &beachTree.getVertex(vertAind);
    auto vertB = &beachTree.getVertex(vertBind);
    auto cpOut =
        vorGeo::closestPoint_TRUNC(vertA->pos, vertB->pos, beachTree.cent);

    // beachTree.LineContainer.emplace_back(cpOut.closeXY_Trunc, cpOut.closeXY,
    //                                     beachTree.cent, vertA, vertB,
    //                                     ++objectID, 0l);
    // lineEvent& lineObj = beachTree.LineContainer.back();
    //// vertA->setEndpointAsLineEvent(lineObj);
    // beachTree.LineContainer.emplace_back(lineObj);
    // lineEvent& lineObj_Twin = beachTree.LineContainer.back();
    // lineObj_Twin.UPPER = false;
    // lineObj_Twin.twin = &lineObj;
    // lineObj_Twin.objectIndex = ++objectID;
    // lineObj.twin = &lineObj_Twin;
    auto& lineObj = beachTree.addAndReturn_Line(cpOut.closeXY_Trunc,
                                                cpOut.closeXY, beachTree.cent,
                                                vertA, vertB, ++objectID, 0l);
    auto& lineObj_Twin = beachTree.addAndReturn_Line(lineObj);

    lineObj_Twin.UPPER = false;
    lineObj_Twin.twin = &lineObj;
    lineObj_Twin.objectIndex = ++objectID;
    lineObj.twin = &lineObj_Twin;
    if (cpOut.truncFlag == 1) {
      vertA->setEndpointAsLineEvent(lineObj);
    } else if (cpOut.truncFlag == 2) {
      vertB->setEndpointAsLineEvent(lineObj);
    } else if (cpOut.truncFlag == 0) {
      // Should proably add the lower line here, but program was initially
      // written with this being the upper line
      beachTree.queue.add(&lineObj);
    }
    // Color and faceID settings will go here
    auto faceA =
        beachTree.records.createFace(&lineObj, vertA->voronoiFace->color);
    auto faceB =
        beachTree.records.createFace(&lineObj_Twin, vertB->voronoiFace->color);
    if (inp.edgeFaceIDMode == 1) {
      faceA->faceIndex = inp.edgeFaceIDs[i];
      faceB->faceIndex = inp.edgeFaceIDs[i];
    } else if (inp.edgeFaceIDMode == 2) {
      faceA->faceIndex = inp.edgeFaceIDs[i];
      faceB->faceIndex = inp.edgeFaceIDs[i + inp.numEdges];
    } else if (inp.edgeFaceIDMode == 0 && inp.vertFaceIDs) {
      faceA->faceIndex = inp.vertFaceIDs[vertAind];
      faceB->faceIndex = inp.vertFaceIDs[vertBind];
    }
    if (inp.edgeFaceIDMode && !inp.vertFaceIDs) {
      vertA->voronoiFace->faceIndex = faceA->faceIndex;
      vertB->voronoiFace->faceIndex = faceB->faceIndex;
    }
    // ObjectID incrimented twice here
  }
#ifdef _TOROIDAL
  if (inp.toroidalMode) {
    auto xs = inp.xTor[0];
    auto ys = inp.yTor[0];
    std::array<double, 8> shiftX{xs, -xs, 0, 0, xs, xs, -xs, -xs};
    std::array<double, 8> shiftY{0, 0, ys, -ys, ys, -ys, ys, -ys};
    for (int reg = 0; reg < 8; ++reg) {
      // This will fail if a mirrored vert overlaps with an original vert... but
      // that would already have been an error
      for (int i = 0; i < inp.numVerts; i++) {
        auto& newVert beachTree.addAndReturn_Vertex(
            arrXY{inp.vertCoor[i] + shiftX[reg],
                  inp.vertCoor[i + inp.numVerts] + shiftY[reg]},
            beachTree.cent, ++objectID, 0l);
        beachTree.queue.add(newVert);
        auto Face = beachTree.records.createFace(
            newVert, inp.color ? inp.color[i] : -1l);
        if (!inp.vertFaceIDs && !inp.edgeFaceIDs)
          Face->faceIndex = Face->id;
        else if (inp.vertFaceIDs)
          Face->faceIndex = inp.vertFaceIDs[i];
      }
      /*
      typedef struct {
      vecDBL closeXY;
      vecDBL closeXY_Trunc;
      int truncFlag;
      }closestPoint_Out;
      */
      // lineEvent(vecDBL pos, vecDBL infPos, vecDBL cent, vertexEvent* EP1,
      // vertexEvent* EP2, long objectIndex, long eventLog) : siteEvent(pos,
      // cent, objectIndex, LINE, eventLog), infPos(infPos) {
      for (int i = 0; i < inp.numEdges; i++) {
        long vertAind = inp.EL[i] - 1 + (reg + 1) * inp.numVerts;
        long vertBind = inp.EL[i + inp.numEdges] - 1 + (reg + 1) * inp.numVerts;
        auto vertA = &beachTree.getVertex(vertAind);
        auto vertB = &beachTree.getVertex(vertBind);
        auto cpOut =
            vorGeo::closestPoint_TRUNC(vertA->pos, vertB->pos, beachTree.cent);

        lineEvent& lineObj = beachTree.addAndReturn_Line(
            cpOut.closeXY_Trunc, cpOut.closeXY, beachTree.cent, vertA, vertB,
            ++objectID, 0l);
        // vertA->setEndpointAsLineEvent(lineObj);
        lineEvent& lineObj_Twin = beachTree.addAndReturn_Line(lineObj);
        lineObj_Twin.UPPER = false;
        lineObj_Twin.twin = &lineObj;
        lineObj_Twin.objectIndex = ++objectID;
        lineObj.twin = &lineObj_Twin;

        if (cpOut.truncFlag == 1) {
          vertA->setEndpointAsLineEvent(lineObj);
        } else if (cpOut.truncFlag == 2) {
          vertB->setEndpointAsLineEvent(lineObj);
        } else if (cpOut.truncFlag == 0) {
          // Should proably add the lower line here, but program was initially
          // written with this being the upper line
          beachTree.queue.add(&lineObj);
        }
        // Color and faceID settings will go here
        auto faceA =
            beachTree.records.createFace(&lineObj, vertA->voronoiFace->color);
        auto faceB = beachTree.records.createFace(&lineObj_Twin,
                                                  vertB->voronoiFace->color);
        if (inp.edgeFaceIDMode == 1) {
          faceA->faceIndex = inp.edgeFaceIDs[i];
          faceB->faceIndex = inp.edgeFaceIDs[i];
        } else if (inp.edgeFaceIDMode == 2) {
          faceA->faceIndex = inp.edgeFaceIDs[i];
          faceB->faceIndex = inp.edgeFaceIDs[i + inp.numEdges];
        } else if (inp.edgeFaceIDMode == 0 && inp.vertFaceIDs) {
          faceA->faceIndex = inp.vertFaceIDs[vertAind];
          faceB->faceIndex = inp.vertFaceIDs[vertBind];
        }
        if (inp.edgeFaceIDMode && !inp.vertFaceIDs) {
          vertA->voronoiFace->faceIndex = faceA->faceIndex;
          vertB->voronoiFace->faceIndex = faceB->faceIndex;
        }
        // ObjectID incrimented twice here
      }
    }
  }
#endif
}

double voronoiLoop(vorRBT::RBTree& beachTree, vorQueue::heapQueue& queue) {
  double lastRad;
  while (!queue.isempty()) {
    auto next = queue.poll();
    lastRad = next->rad;
    ++beachTree.eventLog;
#ifdef _DEBUG
    // std::cout << "ITERATION " << beachTree.eventLog << ": ";
#endif  // _DEBUG
    if (next->objType == VERTEX) {
      beachTree.handleVertexEvent(static_cast<vertexEvent*>(next));
    } else if (next->objType == LINE) {
      beachTree.handleLineEvent(static_cast<lineEvent*>(next));
    } else if (next->objType == CIRCLEEVENT) {
      beachTree.handleCircleEvent(static_cast<circleEvent*>(next));
    }
#ifdef _DEBUG
    // std::cout << beachTree.printLeaves() << std::endl;
#endif  // _DEBUG
  }
  return lastRad;
}
#ifdef _TOROIDAL
void voronoiLoop_Torus(vorRBT::RBTree& beachTree, vorQueue::heapQueue& queue) {
  while (!queue.isempty() &&
         (beachTree.remainingNonMirrored > 0 || !beachTree.canEarlyTerminate)) {
    auto next = queue.poll();
    ++beachTree.eventLog;
#ifdef _DEBUG
    // std::cout << "ITERATION " << beachTree.eventLog << ": ";
#endif  // _DEBUG
    if (next->objType == VERTEX) {
      beachTree.handleVertexEvent(static_cast<vertexEvent*>(next));
    } else if (next->objType == LINE) {
      beachTree.handleLineEvent(static_cast<lineEvent*>(next));
    } else if (next->objType == CIRCLEEVENT) {
      beachTree.handleCircleEvent(static_cast<circleEvent*>(next));
    }
#ifdef _DEBUG
    // std::cout << beachTree.printLeaves() << std::endl;
#endif  // _DEBUG
  }
}
#endif

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
  try {
    // Matlab preprocessing
    if (nrhs > 13) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:nargin",
          "Too many Arguments! Arguments are Vertex Coordinates, Edge "
          "Connection List, cent, (For Tracking Groups of Objects), Vert "
          "FaceIDs, EdgeFaceIDs, maxFaceID, (for Image Analysis) Vert Colors, "
          "Number of Isolated Objects, Image Label Matrix, Toroidal window "
          "[Xmin, Xmax], Toroidal Window [Ymin, Ymax], "
          "labelFromRegionSearchFlag",
          "scaleFactor");
    }
    if (nlhs < 5 || nlhs > 6) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:nargin",
          "Voronoi needs 5 or 6 output arguments (records.input, "
          "records.verts, "
          "records.edges, records.facesFull, (opt) records.faces)");
    }
    // if (nlh) {
    //	mexErrMsgIdAndTxt("MATLAB:Voronoi:nargout", "Voronoi only returns one
    // argument (Records Struct)");
    //}
    matlabInputs inp;
    // Matlab treats all these objects as doubles
    inp.vertCoor = mxGetPr(prhs[0]);
    inp.EL = nrhs > 1 && !mxIsEmpty(prhs[1]) ? mxGetPr(prhs[1]) : nullptr;
    inp.cent = nrhs > 2 && !mxIsEmpty(prhs[2]) ? mxGetPr(prhs[2]) : nullptr;
    inp.vertFaceIDs =
        nrhs > 3 && !mxIsEmpty(prhs[3]) ? mxGetPr(prhs[3]) : nullptr;
    inp.edgeFaceIDs =
        nrhs > 4 && !mxIsEmpty(prhs[4]) ? mxGetPr(prhs[4]) : nullptr;
    inp.maxFaceID =
        nrhs > 5 && !mxIsEmpty(prhs[5]) ? mxGetPr(prhs[5]) : nullptr;
    inp.color = nrhs > 6 && !mxIsEmpty(prhs[6]) ? mxGetPr(prhs[6]) : nullptr;
    inp.numObjects =
        nrhs > 7 && !mxIsEmpty(prhs[7]) ? mxGetPr(prhs[7]) : nullptr;
    inp.labelMat = nrhs > 8 && !mxIsEmpty(prhs[8]) ? mxGetPr(prhs[8]) : nullptr;
    inp.xTor = nrhs > 9 && !mxIsEmpty(prhs[9]) ? mxGetPr(prhs[9]) : nullptr;
    inp.yTor = nrhs > 10 && !mxIsEmpty(prhs[10]) ? mxGetPr(prhs[10]) : nullptr;
    inp.searchFlag =
        nrhs > 11 && !mxIsEmpty(prhs[11]) ? mxGetPr(prhs[11]) : nullptr;
    inp.scaleFactor =
        nrhs > 12 && !mxIsEmpty(prhs[12]) ? mxGetPr(prhs[12]) : nullptr;

    inp.numVerts = mxGetM(prhs[0]);
    inp.numEdges = inp.EL ? mxGetM(prhs[1]) : 0;
    inp.sf = inp.scaleFactor ? *inp.scaleFactor / 2.0 : 1.0;
    arrXY center{0.0, 0.0};
    if (inp.cent) {
      center[0] = inp.cent[0];
      center[1] = inp.cent[1];
    }
    if (inp.vertFaceIDs && mxGetM(prhs[3]) != inp.numVerts) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:vertIDLength",
          "The vertID vector did not have as many rows as the vertCoor vector");
    }
    if (inp.edgeFaceIDs && mxGetM(prhs[4]) != inp.numEdges) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:edgeIDLength",
          "The edgeID vector did not have as many rows as the EL vector");
    }
    if (inp.color && mxGetM(prhs[6]) != inp.numVerts) {
      mexErrMsgIdAndTxt(
          "MATLAB:Voronoi:colorLength",
          "The color vector did not have as many rows as the vertCoor vector");
    }

    if (inp.xTor && inp.yTor) {
#ifndef _TOROIDAL
      mexErrMsgIdAndTxt("MATLAB:Voronoi:versionError",
                        "The Voronoi code was not compiled with support for "
                        "Toroidal Surfaces");
#endif  // !_TOROIDAL
      inp.toroidalMode = true;
    }

    if (inp.edgeFaceIDs && mxGetN(prhs[4]) == 2) {
      inp.edgeFaceIDMode = 2;
    } else if (inp.edgeFaceIDs && mxGetN(prhs[4]) == 1) {
      inp.edgeFaceIDMode = 1;
    }
    // Voronoi Setup
#ifndef _TOROIDAL
    auto&& queue = vorQueue::heapQueue((inp.numVerts + 2 * inp.numEdges) / 2);
    auto records = halfEdgeRecords(inp.numVerts, inp.numEdges);
    auto nodeBinSize = (inp.numVerts + 2 * inp.numEdges) / 20 > 128
                           ? (inp.numVerts + 2 * inp.numEdges) / 20
                           : 128;
    auto degenBinSize = inp.numEdges / 100 > 128 ? inp.numEdges / 100 : 128;
    auto circBinSize = (inp.numVerts + inp.numEdges) / 80 > 128
                           ? (inp.numVerts + inp.numEdges) / 80
                           : 128;
    auto&& beachTree = vorRBT::RBTree(center, queue, records, nodeBinSize,
                                      degenBinSize, circBinSize);
#else
    auto queue =
        vorQueue::heapQueue((9 * inp.numVerts + 9 * 2 * inp.numEdges) / 2);
    auto records = halfEdgeRecords(9 * inp.numVerts, 9 * inp.numEdges);
    auto nodeBinSize = 9 * (inp.numVerts + 2 * inp.numEdges) / 20 > 128
                           ? 9 * (inp.numVerts + 2 * inp.numEdges) / 20
                           : 128;
    auto degenBinSize =
        9 * inp.numEdges / 100 > 128 ? 9 * inp.numEdges / 100 : 128;
    auto circBinSize = 9 * (inp.numVerts + inp.numEdges) / 80 > 128
                           ? 9 * (inp.numVerts + inp.numEdges) / 80
                           : 128;
    auto numNonMirrored = inp.numVerts + 2 * inp.numEdges;
    auto beachTree = vorRBT::RBTree(center, queue, records, numNonMirrored,
                                    nodeBinSize, degenBinSize, circBinSize);
#endif

    initializeQueue(beachTree, inp);

    // Voronoi Execution
    // double lastRad = 0;
#ifndef _TOROIDAL
    double lastRad = voronoiLoop(beachTree, queue);
    beachTree.attachInfiniteBisectors(lastRad * 1.5);
#else
    //
    voronoiLoop_Torus(beachTree, queue);

#endif  //_TOROIDAL

    // Records Cleanup and Matlab Outputting
    // auto halfEdgeNumber = records.HalfEdges.numElements;
    auto vorVertNumber = records.Vertices.numElements;
    auto faceNumber = inp.numVerts + 2 * inp.numEdges;  // records.Faces.size();
    // Input Field
    auto inputsSize = inp.numVerts + inp.numEdges * 2;
    plhs[0] = mxCreateDoubleMatrix(inputsSize, 5, mxREAL);
    auto inputsField = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(inp.numEdges * 2, 9, mxREAL);
    auto inputsField_Supl = mxGetPr(plhs[1]);

    // adding input verts
#pragma omp parallel for
    for (auto i = 0; i < inp.numVerts; i++) {
      auto vert = beachTree.records.inputVertexContainer[i];
      inputsField[i] = 1;
      inputsField[i + 1 * inputsSize] = vert.voronoiFace->color;
      inputsField[i + 2 * inputsSize] = vert.pos[0];
      inputsField[i + 3 * inputsSize] = vert.pos[1];
      inputsField[i + 4 * inputsSize] = vert.voronoiFace->faceIndex;
    }
    // plhs[0] = inputsField_MX;
    // plhs[1] = inputsField_Supl_MX;
    // Adding input edges
    if (inp.numEdges > 0) {
#pragma omp parallel for
      for (std::size_t i = 0; i < inp.numEdges * 2;
           i++) {  // Just put twins one after another so objectID is
                   // preserved... Modify matlab for consistency
        auto edge = beachTree.records.inputLineContainer[i];
        auto ind = i + inp.numVerts;
        inputsField[ind] = 0;
        inputsField[ind + 1 * inputsSize] = edge.voronoiFace->color;
        inputsField[ind + 2 * inputsSize] = edge.endPoints[0]->objectIndex + 1;
        inputsField[ind + 3 * inputsSize] =
            edge.endPoints[1]->objectIndex + 1;  //+1 for matlab indexing
        inputsField[ind + 4 * inputsSize] = edge.voronoiFace->faceIndex;

        inputsField_Supl[i] = edge.dir[0];
        inputsField_Supl[i + 1 * inp.numEdges] = edge.dir[1];
        inputsField_Supl[i + 2 * inp.numEdges] = edge.infRad;
        inputsField_Supl[i + 3 * inp.numEdges] = edge.ABC[0];
        inputsField_Supl[i + 4 * inp.numEdges] = edge.ABC[1];
        inputsField_Supl[i + 5 * inp.numEdges] = edge.ABC[2];
        inputsField_Supl[i + 6 * inp.numEdges] = edge.magnitude;
        inputsField_Supl[i + 7 * inp.numEdges] =
            !edge.UPPER;  // the twin is the lower edge...
        inputsField_Supl[i + 8 * inp.numEdges] = edge.UPPER ? i + 1 : i - 1;
      }
    }
    // HalfEdge Field
    auto halfEdge_Vec_Ref = records.HalfEdges.extractObjVector_SetIDs();
    auto halfEdgeNumber = halfEdge_Vec_Ref.size();
    const char* fnames_halfEdge[] = {"twinID", "edgeType",     "origin",
                                     "dist",   "dir",          "obj",
                                     "color",  "controlPoint", "faceID"};
    auto twinID_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    auto edgeType_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    auto origin_MX = mxCreateDoubleMatrix(halfEdgeNumber, 2, mxREAL);
    auto dist_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    auto dir_MX = mxCreateDoubleMatrix(halfEdgeNumber, 2, mxREAL);
    auto obj_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    auto color_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    auto controlPoint_MX = mxCreateDoubleMatrix(halfEdgeNumber, 2, mxREAL);
    auto faceID_MX = mxCreateDoubleMatrix(halfEdgeNumber, 1, mxREAL);
    plhs[2] = mxCreateStructMatrix(1, 1, 9, fnames_halfEdge);

    auto twinID = mxGetPr(twinID_MX);
    auto edgeType = mxGetPr(edgeType_MX);
    auto origin = mxGetPr(origin_MX);
    auto dist = mxGetPr(dist_MX);
    auto dir = mxGetPr(dir_MX);
    auto obj = mxGetPr(obj_MX);
    auto color = mxGetPr(color_MX);
    auto controlPoint = mxGetPr(controlPoint_MX);
    auto faceID = mxGetPr(faceID_MX);

#pragma omp parallel for
    for (int i = 0; i < halfEdge_Vec_Ref.size(); ++i) {
      auto& e = halfEdge_Vec_Ref[i];
      dist[i] = e.getDistance();
      auto dirEdge = e.getDirection();
      auto contPoint = e.getControlPoint();

      dir[i] = dirEdge[0];
      dir[i + halfEdgeNumber] = dirEdge[1];

      controlPoint[i] = contPoint[0];
      controlPoint[i + halfEdgeNumber] = contPoint[1];

      twinID[i] = e.twin->getID() + 1;
      edgeType[i] = e.edgeType;

      origin[i] = e.origin->getID() + 1;
      origin[i + halfEdgeNumber] = e.twin->origin->getID() + 1;

      obj[i] = e.adjacentFace->siteObject->objectIndex + 1;
      color[i] = e.color;
      faceID[i] = e.adjacentFace->faceIndex;
    }
    mxSetFieldByNumber(plhs[2], 0, 0, twinID_MX);
    mxSetFieldByNumber(plhs[2], 0, 1, edgeType_MX);
    mxSetFieldByNumber(plhs[2], 0, 2, origin_MX);
    mxSetFieldByNumber(plhs[2], 0, 3, dist_MX);
    mxSetFieldByNumber(plhs[2], 0, 4, dir_MX);
    mxSetFieldByNumber(plhs[2], 0, 5, obj_MX);
    mxSetFieldByNumber(plhs[2], 0, 6, color_MX);
    mxSetFieldByNumber(plhs[2], 0, 7, controlPoint_MX);
    mxSetFieldByNumber(plhs[2], 0, 8, faceID_MX);

    // Vert Field
    auto vorVert_Vec_Ref = records.Vertices.extractObjVector_SetIDs();
    const char* fnames_vorVerts[] = {
        "pos",    "rad",        "borderRegions", "vertexCoorID", "locationType",
        "degree", "edgeIDList", "color",         "infinite"};
    auto pos_MX = mxCreateDoubleMatrix(vorVertNumber, 2, mxREAL);
    auto rad_MX = mxCreateDoubleMatrix(vorVertNumber, 1, mxREAL);
    auto borderRegions_MX = mxCreateDoubleMatrix(vorVertNumber, 2, mxREAL);
    auto vertexCoorID_MX = mxCreateDoubleMatrix(vorVertNumber, 1, mxREAL);
    auto locationType_MX = mxCreateDoubleMatrix(vorVertNumber, 1, mxREAL);
    auto degree_MX = mxCreateDoubleMatrix(vorVertNumber, 1, mxREAL);
    auto edgeIDList_MX = mxCreateDoubleMatrix(vorVertNumber, 4, mxREAL);
    auto color_V_MX = mxCreateDoubleMatrix(vorVertNumber, 3, mxREAL);
    auto infinite_MX = mxCreateDoubleMatrix(vorVertNumber, 1, mxREAL);

    plhs[3] = mxCreateStructMatrix(1, 1, 9, fnames_vorVerts);

    auto pos = mxGetPr(pos_MX);
    auto rad = mxGetPr(rad_MX);
    auto borderRegions = mxGetPr(borderRegions_MX);
    auto vertexCoorID = mxGetPr(vertexCoorID_MX);
    auto locationType = mxGetPr(locationType_MX);
    auto edgeIDList = mxGetPr(edgeIDList_MX);
    auto color_V = mxGetPr(color_V_MX);
    auto infinite = mxGetPr(infinite_MX);
    auto degree = mxGetPr(degree_MX);

#pragma omp parallel for
    for (int i = 0; i < vorVertNumber; ++i) {
      auto& v = vorVert_Vec_Ref[i];
      for (auto colID = 0; colID < 4 && colID < v.edges.size(); ++colID) {
        edgeIDList[i + vorVertNumber * colID] =
            v.edges[colID]->getID() +
            1;  // Invalid edges never inserted?  (Oh yeah finalize edge)
      }
      double objectPart = 0;
      double backgroundPart = 0;
      double locationType_val = 0;
      if ((inp.labelMat) &&
          ((!inp.searchFlag) || (inp.searchFlag && inp.searchFlag[0] == 0))) {
        double colorOfTwin = 0.0;
        auto maxX = mxGetM(prhs[8]);  // X->Row index
        auto maxY = mxGetN(prhs[8]);  // Y->Col Index  MATLAB ROTATES
        if (v.vertexCoorID != -2) {
          for (auto e : v.edges) {
            // Likely unecessary but trying to be consistent with
            // cleanRecords.m... Get twin position
            auto posx =
                std::lround(e->twin->origin->pos[0]) -
                1;  // Cooridnates were generated based on a 1,1 origin... wow
            auto posy = std::lround(e->twin->origin->pos[1]) - 1;
            if (posx < 0 || posy < 0 || posx > maxX - 1 || posy > maxY - 1) {
              colorOfTwin = 0.0;
            } else {
              colorOfTwin = inp.labelMat[posx + posy * maxX];
            }
            if (colorOfTwin > inp.numObjects[0] || colorOfTwin == 0) {
              backgroundPart = colorOfTwin;
            } else {
              objectPart = colorOfTwin;
            }
          }
          locationType_val = 2;
        } else {
          auto posx = std::lround(v.pos[0]) - 1;
          auto posy = std::lround(v.pos[1]) - 1;
          if (posx < 0 || posy < 0 || posx >= maxX || posy >= maxY) {
            objectPart = 0;
            backgroundPart = 0;
            locationType_val = 1;
          } else {
            objectPart = inp.labelMat[posx + posy * maxX];
            backgroundPart = objectPart;
            locationType_val =
                objectPart == 0 || objectPart > inp.numObjects[0];
          }
        }
      } else {
        objectPart = 0;
        backgroundPart = 0;
        locationType_val = 1;
      }
      pos[i] = v.pos[0];
      pos[i + 1 * vorVertNumber] = v.pos[1];
      rad[i] = v.rad;
      borderRegions[i] = objectPart;
      borderRegions[i + 1 * vorVertNumber] = backgroundPart;
      locationType[i] = locationType_val;
      degree[i] = v.edges.size() > 4 ? 4 : v.edges.size();
      color_V[i] = v.colorPattern[0];
      color_V[i + 1 * vorVertNumber] = v.colorPattern[1];
      color_V[i + 2 * vorVertNumber] = v.colorPattern[2];
      infinite[i] = v.infVert;
      vertexCoorID[i] = v.vertexCoorID + 1;
    }
    mxSetFieldByNumber(plhs[3], 0, 0, pos_MX);
    mxSetFieldByNumber(plhs[3], 0, 1, rad_MX);
    mxSetFieldByNumber(plhs[3], 0, 2, borderRegions_MX);
    mxSetFieldByNumber(plhs[3], 0, 3, vertexCoorID_MX);
    mxSetFieldByNumber(plhs[3], 0, 4, locationType_MX);
    mxSetFieldByNumber(plhs[3], 0, 5, degree_MX);
    mxSetFieldByNumber(plhs[3], 0, 6, edgeIDList_MX);
    mxSetFieldByNumber(plhs[3], 0, 7, color_V_MX);
    mxSetFieldByNumber(plhs[3], 0, 8, infinite_MX);

    // plhs[3] = plhs[3];
    // FacesFull
    const char* fnames_faceFull[] = {"Vertices", "Edges",   "Neighbors",
                                     "Object",   "groupID", "Closed"};
    plhs[4] = mxCreateStructMatrix(faceNumber, 1, 6, fnames_faceFull);
    std::vector<std::vector<vorFace*>> faceCollector;  // change to unorderedmap
    if (inp.vertFaceIDs || inp.edgeFaceIDs) {
      faceCollector.resize(inp.maxFaceID[0]);
    }
    //#ifdef _OMP
    //	omp_lock_t writeLock;
    //	omp_init_lock(&writeLock);
    //#pragma omp parallel for
    // endif
    // Used to loop through records.faces.size().  Now only loops through faces
    // associated with input objects (no OOB objects).
    for (std::size_t i = 0; i < inp.numVerts + 2 * inp.numEdges; ++i) {
      auto& face = records.Faces[i];

      auto numEdges = face.edges.size();
      auto numVerts = face.vertices.size();
      auto numNeigh = face.neighbors.size();

      //#ifdef _OMP
      //		omp_set_lock(&writeLock);
      //#endif _OMP

      auto objectID_MX = mxCreateDoubleMatrix(1, 1, mxREAL);
      auto groupID_MX = mxCreateDoubleMatrix(1, 1, mxREAL);
      auto closed_MX = mxCreateDoubleMatrix(1, 1, mxREAL);
      auto faceVerts_MX = mxCreateDoubleMatrix(numVerts, 1, mxREAL);
      auto faceEdge_MX = mxCreateDoubleMatrix(numEdges, 1, mxREAL);
      auto faceNeigh_MX = mxCreateDoubleMatrix(numNeigh, 1, mxREAL);

      //#ifdef _OMP
      //		omp_unset_lock(&writeLock);
      //#endif

      auto objectID = mxGetPr(objectID_MX);
      auto groupID = mxGetPr(groupID_MX);
      auto closed = mxGetPr(closed_MX);
      auto faceVerts = mxGetPr(faceVerts_MX);
      auto faceEdge = mxGetPr(faceEdge_MX);
      auto faceNeigh = mxGetPr(faceNeigh_MX);

      objectID[0] = face.id + 1;    // 0 -> 1 indexing
      groupID[0] = face.faceIndex;  // Not changed from matlab indexing
      if (inp.vertFaceIDs || inp.edgeFaceIDs) {
        //#ifdef _OMP
        //			omp_set_lock(&writeLock);
        //#endif _OMP
        faceCollector[face.faceIndex - 1].push_back(&face);
        //#ifdef _OMP
        //			omp_unset_lock(&writeLock);
        //#endif
      }

      int iter = 0;
      for (auto e : face.edges) {
        faceVerts[iter] = e->origin->getID() + 1;
        faceEdge[iter] = e->getID() + 1;
        faceNeigh[iter] = e->adjacentFace->id + 1;
        ++iter;
      }
      if (numVerts > numEdges) {
        closed[0] = 1;
        bool foundVert = true;
        for (auto v : face.vertices) {
          for (auto e : v->edges) {
            if (e->adjacentFace == &face) {
              foundVert = false;
              break;
            }
          }
          if (foundVert) {
            faceVerts[iter] = v->getID() + 1;
            break;
          }
        }
      }
      //#ifdef _OMP
      //		omp_set_lock(&writeLock);
      //#endif _OMP
      //	char* fnames_faceFull[6] = {
      //"Vertices","Edges","Neighbors","Object","groupID","Closed" };
      mxSetFieldByNumber(plhs[4], i, 0, faceVerts_MX);
      mxSetFieldByNumber(plhs[4], i, 1, faceEdge_MX);
      mxSetFieldByNumber(plhs[4], i, 2, faceNeigh_MX);
      mxSetFieldByNumber(plhs[4], i, 3, objectID_MX);
      mxSetFieldByNumber(plhs[4], i, 4, groupID_MX);
      mxSetFieldByNumber(plhs[4], i, 5, closed_MX);
      //#ifdef _OMP
      //		omp_unset_lock(&writeLock);
      //#endif
    }
    // plhs[4] = facesFullStructMat_MX;

    if ((inp.vertFaceIDs || inp.edgeFaceIDs) && nlhs > 5) {
      const char* fnames_face[] = {
          "Vertices",          "Edges",           "Neighbors",
          "Objects",           "FaceComponents",  "Finite",
          "FaceStartingIndex", "FaceEndingIndex", "subFaces"};
      plhs[5] = mxCreateStructMatrix(inp.maxFaceID[0], 1, 9, fnames_face);
      //#ifdef _OMP
      //#pragma omp parallel for
#//endif \
    //In toroidal voronoi, can safely assume all faces are finite.  Would greatly simplify the construction below. \
    //We can additionally impose a single-polygon restriction to just make this entire process below "loop through edges"

      // This all seems overly complex. Make an input flag for 'seperated'
      // polygons (false by default) or 'infinite' polygons (true by default),
      // and make simpler loops otherwise.
      // For the disconnected polygon list, may be easier to iterate through
      // faces to build 'sets' of neighboring faces.
      // Faces still needs to be a hash map at some point
      for (std::size_t i = 0; i < faceCollector.size(); ++i) {
        auto subFaces = faceCollector[i];
        auto numFacesComp = subFaces.size();
        auto faceID = subFaces[0]->faceIndex;

        int faceIter = 0;

        std::vector<halfEdge*> edgeCollector;
        std::vector<vorVert*> vertCollector;
        std::vector<vorFace*> neighborCollector;
        //#ifdef _OMP
        //			omp_set_lock(&writeLock);
        //#endif _OMP
        auto faceComponents_MX = mxCreateDoubleMatrix(numFacesComp, 1, mxREAL);
        auto objects_MX = mxCreateDoubleMatrix(numFacesComp, 1, mxREAL);
        auto numPoly_MX = mxCreateDoubleMatrix(1, 1, mxREAL);
        // auto numPoly = mxGetPr(numPoly_MX);
        //#ifdef _OMP
        //			omp_unset_lock(&writeLock);
        //#endif
        std::vector<int> finiteVec;
        std::vector<int> faceStartingIndVec;
        std::vector<int> faceEndingIndVec;
        auto objects = mxGetPr(objects_MX);
        auto faceComponents = mxGetPr(faceComponents_MX);
        edgeCollector.reserve(numFacesComp * 4);
        vertCollector.reserve(numFacesComp * 4);
        neighborCollector.reserve(numFacesComp * 4);
        // changing from matlab strat;
        std::size_t vertCounter = 0;
        for (auto f : subFaces) {
          faceComponents[faceIter] = f->id + 1;
          objects[faceIter++] = f->id + 1;
          for (auto e : f->edges) {
            if (e->adjacentFace->faceIndex !=
                e->twin->adjacentFace->faceIndex) {
              ++vertCounter;
              // vertCollector.push_back(e->origin);
              // edgeCollector.push_back(e);
              // neighborCollector.push_back(e->adjacentFace);
            }
          }
        }
        vorVert* initVert = nullptr;
        vorVert* curVert = nullptr;

        // auto curVert = initVert;
        int numPolys = 0;
        // int numAdditions = 0;
        bool closedCycle = false;

        // if (!curVert) {
        initVert = nullptr;
        bool canExit = false;
        while (vertCollector.size() < vertCounter) {
          for (auto f : subFaces) {
            for (auto e : f->edges) {
              if (e->adjacentFace->faceIndex == faceID &&
                  e->twin->adjacentFace->faceIndex != faceID) {
                bool isValid = true;
                for (auto addE : vertCollector) {
                  if (addE == e->origin) {
                    isValid = false;
                    break;
                  }
                }
                if (isValid) {
                  initVert = e->origin;
                  canExit = true;
                  break;
                }
              }
            }
            if (canExit) break;
          }
          curVert = initVert;
          if (!initVert) break;
          ++numPolys;
          int startIndex = vertCollector.size();
          bool pathFound = false;
          auto stop = false;
          // This finds the first vertex in an object
          while (!stop || vertCollector.size() > vertCounter + 1) {
            pathFound = false;
            halfEdge* selEdge;
            for (auto e : curVert->edges) {
              if (e->adjacentFace->faceIndex != faceID &&
                  e->twin->adjacentFace->faceIndex == faceID) {
                curVert = e->twin->origin;
                selEdge = e->twin;
                pathFound = true;
                break;
              }
            }
            if (pathFound && curVert == initVert) {
              vertCollector.push_back(curVert);
              edgeCollector.push_back(selEdge);
              neighborCollector.push_back(selEdge->twin->adjacentFace);
              closedCycle = true;
              stop = true;
              break;  // Escape while
            } else if (!pathFound) {
              for (auto e : curVert->edges) {
                if (e->adjacentFace->faceIndex == faceID &&
                    e->twin->adjacentFace->faceIndex != faceID) {
                  // curVert = e->twin->origin;
                  selEdge = e;
                  break;
                }
              }
              vertCollector.push_back(curVert);
              edgeCollector.push_back(selEdge);
              neighborCollector.push_back(selEdge->twin->adjacentFace);
              stop = true;
              break;  // Escape while
            }
          }
          if (!stop) {
            break;  // never entered the loop in the first place
          }
          // The next block will find all edges from this vertex, starting from
          // the
          stop = false;
          vorVert* otherVert = edgeCollector[startIndex]->twin->origin;
          vorVert* startVert = vertCollector[startIndex];
          halfEdge* edgeSel = nullptr;
          while (!stop) {
            if (otherVert == startVert) {
              stop = true;
              break;
            }
            bool edgeFound = false;
            for (auto e : otherVert->edges) {
              if (e->adjacentFace->faceIndex == faceID &&
                  e->twin->adjacentFace->faceIndex != faceID &&
                  e != edgeCollector[startIndex]) {
                otherVert = e->twin->origin;
                edgeSel = e;
                edgeFound = true;
                break;
              }
            }
            if (!edgeFound) {
              stop = true;
              break;
            }
            vertCollector.push_back(edgeSel->origin);
            edgeCollector.push_back(edgeSel);
            neighborCollector.push_back(edgeSel->twin->adjacentFace);
          }
          if (edgeSel) {
            if (!closedCycle) {
              vertCollector.push_back(edgeSel->twin->origin);
            }
            finiteVec.push_back(closedCycle);
            faceStartingIndVec.push_back(startIndex);
            faceEndingIndVec.push_back(vertCollector.size() - 1);
          }
        }
        //}

        // auto faceVerts_MX = mxCreateDoubleMatrix(numVerts, 1, mxREAL); TBD
        // auto faceEdge_MX = mxCreateDoubleMatrix(numEdges, 1, mxREAL);
        // auto faceNeigh_MX = mxCreateDoubleMatrix(numNeigh, 1, mxREAL);

#//ifdef _OMP                                                           \
    //			omp_set_lock(&writeLock);                                      \
    //#endif _OMP                                                       \
    // auto faceComponents_MX = mxCreateDoubleMatrix(numFacesComp, 1,   \
    // mxREAL); auto objects_MX = mxCreateDoubleMatrix(numFacesComp, 1, \
    // mxREAL); auto numPoly_MX = mxCreateDoubleMatrix(1, 1, mxREAL);
        auto faceEndingIndex_MX = mxCreateDoubleMatrix(numPolys, 1, mxREAL);
        auto faceStartingIndex_MX = mxCreateDoubleMatrix(numPolys, 1, mxREAL);
        auto finite_MX = mxCreateDoubleMatrix(numPolys, 1, mxREAL);
        auto vertices_MX =
            mxCreateDoubleMatrix(vertCollector.size(), 1, mxREAL);
        auto edges_MX = mxCreateDoubleMatrix(edgeCollector.size(), 1, mxREAL);
        auto neighb_MX =
            mxCreateDoubleMatrix(neighborCollector.size(), 1, mxREAL);
        //#ifdef _OMP
        //			omp_unset_lock(&writeLock);
        //#endif
        auto finite = mxGetPr(finite_MX);
        auto faceStartingIndex = mxGetPr(faceStartingIndex_MX);
        auto faceEndingIndex = mxGetPr(faceEndingIndex_MX);
        auto numPoly = mxGetPr(numPoly_MX);
        // auto faceComponents = mxGetPr(faceComponents_MX);
        // auto objects = mxGetPr(objects_MX);
        auto vertices = mxGetPr(vertices_MX);
        auto edges = mxGetPr(edges_MX);
        auto neighb = mxGetPr(neighb_MX);

        numPoly[0] = numPolys;
#ifndef _SKIP_CHECKS
        if (finiteVec.size() == 0) throw(vorFaceIsEmpty);
#endif
        for (int iter = 0; iter < numPolys; ++iter) {
          finite[iter] = finiteVec[iter];
          faceStartingIndex[iter] = faceStartingIndVec[iter] + 1;
          faceEndingIndex[iter] = faceEndingIndVec[iter] + 1;
        }
        int iter = 0;
        for (auto v : vertCollector) {
          vertices[iter++] = v->getID() + 1;
        }
        iter = 0;
        for (auto e : edgeCollector) {
          edges[iter++] = e->getID() + 1;
        }
        iter = 0;
        for (auto n : neighborCollector) {
          neighb[iter++] = n->faceIndex;
        }

        // char* fnames_face[9] = {  "Vertices" , "Edges" , "Neighbors" ,
        // "Objects" , "FaceComponents" , "Finite" ,"FaceStartingIndex" ,
        // "FaceEndingIndex" ,"subFaces"  }; #ifdef _OMP
        //			omp_set_lock(&writeLock);
        //#endif _OMP
        mxSetFieldByNumber(plhs[5], i, 0, vertices_MX);
        mxSetFieldByNumber(plhs[5], i, 1, edges_MX);
        mxSetFieldByNumber(plhs[5], i, 2, neighb_MX);
        mxSetFieldByNumber(plhs[5], i, 3, objects_MX);
        mxSetFieldByNumber(plhs[5], i, 4, faceComponents_MX);
        mxSetFieldByNumber(plhs[5], i, 5, finite_MX);
        mxSetFieldByNumber(plhs[5], i, 6, faceStartingIndex_MX);
        mxSetFieldByNumber(plhs[5], i, 7, faceEndingIndex_MX);
        mxSetFieldByNumber(plhs[5], i, 8, numPoly_MX);
        //#ifdef _OMP
        //			omp_unset_lock(&writeLock);
        //#endif
        // auto objects = mxGetPr(objects_MX);
        // auto faceComponents = mxGetPr(faceComponents_MX);
        // auto closed = mxGetPr(closed_MX);
        // auto faceVerts = mxGetPr(faceVerts_MX);
        // auto faceEdge = mxGetPr(faceEdge_MX);
        // auto faceNeigh = mxGetPr(faceNeigh_MX);
        // char* fnames_face[9] = {  "Vertices" , "Edges" , "Neighbors"
        // ,"Objects" ,"FaceComponents" ,"Finite" , "FaceStartingIndex"
        // ,"FaceEndingIndex" , "subFaces" }; auto facesStructMat_MX =
        // mxCreateStructMatrix(faceNumber, 1, 9, fnames_face);
      }
    }
    if (inp.searchFlag && (inp.searchFlag[0] == 1 || inp.searchFlag[0] == 2)) {
      if (inp.searchFlag[0] == 2) {
        // Assign location type with a grid search. Correct for cases where the
        // pixel is on the edge of an object. Actual locations will be asigned
        // via a reachability search.
        if (!inp.labelMat) {
          mexErrMsgIdAndTxt(
              "MATLAB:Voronoi:CFATAL-LabelMat-SearchMode2",
              "An image with foreground pixels labeled 1 and background pixels "
              "labeled 0 must be passed if searchFlag is 2");
        }
        if (!inp.scaleFactor) {
          mexErrMsgIdAndTxt("MATLAB:Voronoi:CFATAL-ScaleFactor-NoLabelMat",
                            "The scalefactor must be provided (13th argument) "
                            "for searchmode==2");
        }

        double colorOfTwin = 0.0;
        auto maxX = mxGetM(prhs[8]);  // X->Row index
        auto maxY = mxGetN(
            prhs[8]);  // Y->Col Index  MATLAB ROTATES (?? Does not seem to??)
        for (int i = 0; i < vorVertNumber; ++i) {
          auto& v = vorVert_Vec_Ref[i];
          if (v.vertexCoorID != -2) {
            locationType[i] = 2;
          } else {
            auto posx = std::lround(v.pos[0]) - 1;
            auto posy = std::lround(v.pos[1]) - 1;
            bool botImEdge = posy == 0;
            bool leftImEdge = posx == 0;
            bool rightImEdge = posx >= maxX - 1;
            bool topImEdge = posy >= maxY - 1;
            if (posx < 0 || posy < 0 || posx >= maxX || posy >= maxY) {
              locationType[i] = 1;
            } else {
              double objectPart = inp.labelMat[posx + posy * maxX];
              auto adj_vposx = v.pos[0] - 1;
              auto adj_vposy = v.pos[1] - 1;
              locationType[i] =
                  (objectPart == 0 || objectPart > inp.numObjects[0]) ? 1.0
                                                                      : 0.0;

              if (botImEdge ||
                  inp.labelMat[posx + (posy - 1) * maxX] != objectPart) {
                if (adj_vposy - posy < -inp.sf) locationType[i] = 1;
              }
              if (topImEdge ||
                  inp.labelMat[posx + (posy + 1) * maxX] != objectPart) {
                if (adj_vposy - posy > inp.sf) locationType[i] = 1;
              }
              if (leftImEdge ||
                  inp.labelMat[(posx - 1) + posy * maxX] != objectPart) {
                if (adj_vposx - posx < -inp.sf) locationType[i] = 1;
              }
              if (rightImEdge ||
                  inp.labelMat[(posx + 1) + posy * maxX] != objectPart) {
                if (adj_vposx - posx > inp.sf) locationType[i] = 1;
              }
            }
          }
        }
      }
      auto counter = 0;
      for (auto& e : halfEdge_Vec_Ref) {
        e.setID(counter);
        ++counter;
      }
      for (auto& v : vorVert_Vec_Ref) {
        v.setPTRIDs();
      }
      for (auto& e : halfEdge_Vec_Ref) {
        e.setPTRIDs();
      }
      std::vector<long> vertRegionIDs;
      // auto vertEdgeStruct = records.copyVertEdgeRecords();
      // if (inp.searchFlag[0] == 1) {
      vertRegionIDs = bfsSearch_Assign(vorVert_Vec_Ref, halfEdge_Vec_Ref);
      //} else if (inp.searchFlag[0] == 2) {
      //  vertRegionIDs =
      //      bfsSearch_Assign_BG_Type(vorVert_Vec_Ref, halfEdge_Vec_Ref,
      //                               locationType);  // Is this even needed
      //                               now?
      //}                                              // Modifies locationType
      // Get regionIDs. Set all Verts to corresponding regionID.
      for (int i = 0; i < vorVertNumber; ++i) {
        if (vertRegionIDs[i] == -1) {
          long regionA = 0;
          long regionB = 0;
          auto eID_0 = vorVert_Vec_Ref[i].getEdgeID(0);
          auto vID_0 = halfEdge_Vec_Ref[halfEdge_Vec_Ref[eID_0].getTwinID()]
                           .getOriginID();
          regionA = vertRegionIDs[vID_0];
          for (auto j = 1; j < vorVert_Vec_Ref[i].getEdgeIDs().size(); ++j) {
            auto eID = vorVert_Vec_Ref[i].getEdgeID(j);
            auto vID = halfEdge_Vec_Ref[halfEdge_Vec_Ref[eID].getTwinID()]
                           .getOriginID();
            if (vertRegionIDs[vID] != regionA) {
              regionB = vertRegionIDs[vID];
              break;
            }
          }
          if (regionA == 0) {
            borderRegions[i] = regionB;
            borderRegions[i + 1 * vorVertNumber] = regionA;
          } else if (regionB == 0) {
            borderRegions[i] = regionA;
            borderRegions[i + 1 * vorVertNumber] = regionB;
          } else {
            borderRegions[i] = std::min(regionA, regionB);
            borderRegions[i + 1 * vorVertNumber] = std::max(regionA, regionB);
          }

        } else {
          borderRegions[i] = vertRegionIDs[i];
          borderRegions[i + 1 * vorVertNumber] = vertRegionIDs[i];
          locationType[i] =
              (borderRegions[i] == 0 || borderRegions[i] > inp.numObjects[0])
                  ? 1.0
                  : 0.0;
        }
      }
    }
  } catch (const std::exception& ex) {
    mexErrMsgIdAndTxt("Matlab:Voronoi:CFatal", ex.what());
  } catch (...) {
    mexErrMsgIdAndTxt("MATLAB:Voronoi:CFATAL-Unknown",
                      "An Exception was caught in the MEX file due to an "
                      "error.  Computation aborted to prevent MATLAB from "
                      "crashing.  Currently no i");
  }
}
#endif  //_MATLAB
