// Disables Vector bound checking (Visual C++)
//#define _SECURE_SCL 0

// For Python
// Use boost python bindings
// Accepts verts, edges, and color for now
// Create finalized structures to store the finalized objects

// Figure out faceInputs with python
// Figure out out python input/out even works
// Input -> probably np.arrays

// Bindings for vertexEvent, lineEvent. Input/Output to main function

// Line constructor that accepts lines -> Have it setup the twin and set upper
// as false in constructor - we pass a pointer to the main object anyways!!!
// Don't use copy constructor...

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "DataTypes/siteEvent.hpp"
#include "Math/basicMathAndGeometry.hpp"
#include "Queue/SEQTree.hpp"
#include "Records/halfEdgeRecords.hpp"
#include "Tree/RBT.hpp"
#include "vorPyBindings.hpp"

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
  virtual const char *what() const throw() {
    return "A Voronoi Polygon has no Vertices Associated with it";
  }
} vorFaceIsEmpty;
#endif

void initializeQueue(vorRBT::RBTree &beachTree, std::vector<arrXY> &vertexCoor,
                     std::vector<std::array<std::size_t, 2>> &EL,
                     std::vector<int> color) {
#ifndef _TOROIDAL
  auto vertCount = vertexCoor.size();
  auto edgeCount = EL.size() * 2;
#else
  auto vertCount = 9 * vertexCoor.size();
  auto edgeCount = 9 * EL.size() * 2;
#endif
  beachTree.reserveVertexContainer(vertCount);
  beachTree.reserveLineContainer(edgeCount);
  long objectID = -1;
  for (int i = 0; i < vertexCoor.size(); i++) {
    auto &newVert = beachTree.addAndReturn_Vertex(
        vertexCoor.at(i), beachTree.cent, ++objectID, 0l);
    beachTree.queue.add(
        &newVert);  // Ideally this should be abstracted so queue can change
    auto Face = beachTree.records.createFace(&newVert,
                                             color.empty() ? -1 : color.at(i));
  }

  for (int i = 0; i < EL.size(); i++) {
    auto vertA = &beachTree.getVertex(EL.at(i)[0]);
    auto vertB = &beachTree.getVertex(EL.at(i)[1]);
    auto cpOut =
        vorGeo::closestPoint_TRUNC(vertA->pos, vertB->pos, beachTree.cent);

    auto &lineObj = beachTree.addAndReturn_Line(cpOut.closeXY_Trunc,
                                                cpOut.closeXY, beachTree.cent,
                                                vertA, vertB, ++objectID, 0l);
    auto &lineObj_Twin = beachTree.addAndReturn_Line(lineObj);

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
    // if (inp.edgeFaceIDMode == 1) {
    //  faceA->faceIndex = inp.edgeFaceIDs[i];
    //  faceB->faceIndex = inp.edgeFaceIDs[i];
    //} else if (inp.edgeFaceIDMode == 2) {
    //  faceA->faceIndex = inp.edgeFaceIDs[i];
    //  faceB->faceIndex = inp.edgeFaceIDs[i + inp.numEdges];
    //} else if (inp.edgeFaceIDMode == 0 && inp.vertFaceIDs) {
    //  faceA->faceIndex = inp.vertFaceIDs[vertAind];
    //  faceB->faceIndex = inp.vertFaceIDs[vertBind];
    //}
    // if (inp.edgeFaceIDMode && !inp.vertFaceIDs) {
    //  vertA->voronoiFace->faceIndex = faceA->faceIndex;
    //  vertB->voronoiFace->faceIndex = faceB->faceIndex;
    //}
    // ObjectID incrimented twice here
  }
}

double voronoiLoop(vorRBT::RBTree &beachTree, vorQueue::heapQueue &queue) {
  double lastRad;
  while (!queue.isempty()) {
    auto next = queue.poll();
    lastRad = next->rad;
    ++beachTree.eventLog;
#ifdef _DEBUG
    // std::cout << "ITERATION " << beachTree.eventLog << ": ";
#endif  // _DEBUG
    if (next->objType == VERTEX) {
      beachTree.handleVertexEvent(static_cast<vertexEvent *>(next));
    } else if (next->objType == LINE) {
      beachTree.handleLineEvent(static_cast<lineEvent *>(next));
    } else if (next->objType == CIRCLEEVENT) {
      beachTree.handleCircleEvent(static_cast<circleEvent *>(next));
    }
#ifdef _DEBUG
    // std::cout << beachTree.printLeaves() << std::endl;
#endif  // _DEBUG
  }
  return lastRad;
}
#ifdef _TOROIDAL
void voronoiLoop_Torus(vorRBT::RBTree &beachTree, vorQueue::heapQueue &queue) {
  while (!queue.isempty() &&
         (beachTree.remainingNonMirrored > 0 || !beachTree.canEarlyTerminate)) {
    auto next = queue.poll();
    ++beachTree.eventLog;
#ifdef _DEBUG
    // std::cout << "ITERATION " << beachTree.eventLog << ": ";
#endif  // _DEBUG
    if (next->objType == VERTEX) {
      beachTree.handleVertexEvent(static_cast<vertexEvent *>(next));
    } else if (next->objType == LINE) {
      beachTree.handleLineEvent(static_cast<lineEvent *>(next));
    } else if (next->objType == CIRCLEEVENT) {
      beachTree.handleCircleEvent(static_cast<circleEvent *>(next));
    }
#ifdef _DEBUG
    // std::cout << beachTree.printLeaves() << std::endl;
#endif  // _DEBUG
  }
}
#endif

// initializeQueue should move to RBTree -> Should be the parent struct of all
std::unique_ptr<DEBUG_InternalStateHolder> DEBUG_createTree(
    std::vector<arrXY> vertCoor, std::vector<std::array<std::size_t, 2>> EL,
    std::vector<int> color, arrXY center) {
  // Voronoi Setup
  py::print("Function entered");
  // py::print("VertCoor", vertCoor.at(0)[0], vertCoor.at(0)[1]);
  // for (auto e : vertCoor) py::print(e[0], e[1]);
  auto numVerts = vertCoor.size();
  auto numEdges = EL.size();
  auto queue = new vorQueue::heapQueue((numVerts + 2 * numEdges) / 2);
  auto records = new halfEdgeRecords(
      numVerts, numEdges);  // Python takes ownership.... eventually
  auto nodeBinSize = (numVerts + 2 * numEdges) / 20 > 128
                         ? (numVerts + 2 * numEdges) / 20
                         : 128;
  auto degenBinSize = numEdges / 100 > 128 ? numEdges / 100 : 128;
  auto circBinSize =
      (numVerts + numEdges) / 80 > 128 ? (numVerts + numEdges) / 80 : 128;
  auto beachTree = new vorRBT::RBTree(center, *queue, *records, nodeBinSize,
                                      degenBinSize, circBinSize);
  py::print("Initialize Queue");
  initializeQueue(*beachTree, vertCoor, EL, color);

  return std::unique_ptr<DEBUG_InternalStateHolder>(
      new DEBUG_InternalStateHolder(queue, records, beachTree));
}

std::unique_ptr<halfEdgeRecords> computeDiagram(
    std::vector<arrXY> vertCoor, std::vector<std::array<std::size_t, 2>> EL,
    std::vector<int> color, arrXY center) {
  // Voronoi Setup
  py::print("Function entered");
  // py::print("VertCoor", vertCoor.at(0)[0], vertCoor.at(0)[1]);
  // for (auto e : vertCoor) py::print(e[0], e[1]);
  auto numVerts = vertCoor.size();
  auto numEdges = EL.size();
#ifndef _TOROIDAL
  auto &&queue = vorQueue::heapQueue((numVerts + 2 * numEdges) / 2);
  auto records = std::unique_ptr<halfEdgeRecords>(
      new halfEdgeRecords(numVerts, numEdges));  // Python takes ownership....
  auto nodeBinSize = (numVerts + 2 * numEdges) / 20 > 128
                         ? (numVerts + 2 * numEdges) / 20
                         : 128;
  auto degenBinSize = numEdges / 100 > 128 ? numEdges / 100 : 128;
  auto circBinSize =
      (numVerts + numEdges) / 80 > 128 ? (numVerts + numEdges) / 80 : 128;
  auto &&beachTree = vorRBT::RBTree(center, queue, *records, nodeBinSize,
                                    degenBinSize, circBinSize);
#else
  auto &&queue = vorQueue::heapQueue((9 * numVerts + 9 * 2 * numEdges) / 2);
  auto records = halfEdgeRecords(9 * numVerts, 9 * numEdges);
  auto nodeBinSize = 9 * (numVerts + 2 * numEdges) / 20 > 128
                         ? 9 * (numVerts + 2 * numEdges) / 20
                         : 128;
  auto degenBinSize = 9 * numEdges / 100 > 128 ? 9 * numEdges / 100 : 128;
  auto circBinSize = 9 * (numVerts + numEdges) / 80 > 128
                         ? 9 * (numVerts + numEdges) / 80
                         : 128;
  auto numNonMirrored = numVerts + 2 * numEdges;
  auto beachTree = vorRBT::RBTree(center, queue, records, numNonMirrored,
                                  nodeBinSize, degenBinSize, circBinSize);
#endif
  py::print("Initialize Queue");
  initializeQueue(beachTree, vertCoor, EL, color);

  // Voronoi Execution
  // double lastRad = 0;
  py::print("Voronoi Loop");

#ifndef _TOROIDAL
  double lastRad = voronoiLoop(beachTree, queue);
  beachTree.attachInfiniteBisectors(lastRad * 1.5);
#else
  //
  voronoiLoop_Torus(beachTree, queue);

#endif
  records->finalizeRecordValues();  // halfEdges use ptrs to set their dist,
                                    // dir, and control point. To do afterwards,
                                    // halfEdges would need access to the record
                                    // structure (doable)
  records->moveVertsAndEdgesToVector();
  py::print(records->Vertices.numElements);
  py::print(records->getVertices().size());
  return records;
}
