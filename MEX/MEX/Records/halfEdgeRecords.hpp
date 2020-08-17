#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER
// F/unctions have a setPTRIDs function which will create a vector<size_t>
// storing the ultimate index of any voronoi vertex, halfEdge, or voronoiFace
// If needed, the original siteEvent IDs will match with the faceIDs.
#ifndef HALFEDGERECORDS_H
#define HALFEDGERECORDS_H

#include <iostream>
#include <memory>
#include <string>
#include "../DataTypes/siteEvent.hpp"
#include "../Math/interceptCalculators.hpp"

#include "../Containers/vectorPageAllocator.h"

#ifdef _BUFFERED_VEC_OPT
#include "../Containers//buffered_vec.hpp"
#endif
// Make a new container with a fixed sized array and a vector.  If the container
// goes over the limit, copy all elements to the vector.

//#define _EPSILON std::numeric_limits<double>::epsilon()
struct vorVert;
struct halfEdge;
struct vorFace;

// For python -> call function

struct vorFace {
 private:
  // Pointers are invalidated the second you try to move away from this
  // datastruct.  These vectors may not be needed if, instead, the ID of these
  // vertices is adjusted such that they equal their final location in some
  // vector.  An output object can then construct itself on these objects, and
  // store the IDs of neighboring edges.
  bool ptrsValid = true;
  std::vector<size_t> edgeIDs;
  std::vector<size_t> neighborIDs;
  std::vector<size_t> vertIDs;
  // std::size_t siteObjectID; Matches id

 public:
  siteEvent *siteObject;
  // Change allocator to store up to 6 with the object itself
#ifdef _BUFFERED_VEC_OPT
  vorContainer::buffered_vec<vorFace *, 16> neighbors;
  vorContainer::buffered_vec<halfEdge *, 16> edges;
  vorContainer::buffered_vec<vorVert *, 16> vertices;

#else
  std::vector<vorFace *> neighbors;
  std::vector<halfEdge *> edges;
  std::vector<vorVert *> vertices;
#endif
  long color;
  long id;
  long faceIndex;

  vorFace(siteEvent *siteObj, long colorID)
      : siteObject(siteObj), color(colorID), id(siteObj->objectIndex) {
    siteObj->voronoiFace = this;
#ifndef _BUFFERED_VEC_OPT
    neighbors.reserve(16);
    edges.reserve(16);
    vertices.reserve(16);
#endif
  }
  vorFace() : siteObject(nullptr){};
  void reconstruct(std::vector<size_t> edgeIDs, std::vector<size_t> neighborIDs,
                   std::vector<size_t> vertIDs, long color, long id,
                   long faceIndex) {
    this->edgeIDs = edgeIDs;
    this->neighborIDs = neighborIDs;
    this->vertIDs = vertIDs;
    this->color = color;
    this->id = id;
    this->faceIndex = faceIndex;
  };
  long getColor() { return color; }
  void setPTRIDs();

  // pybinds
  auto getNeighborIDs() const -> decltype(neighborIDs) { return neighborIDs; };
  auto getEdgeIDs() const -> decltype(edgeIDs) { return edgeIDs; };
  auto getVertIDs() const -> decltype(vertIDs) { return vertIDs; };
  // auto getInputID() -> decltype(siteObjectID) {return siteObjectID;}
  // auto getNeigbors() -> decltype(neighbors) {return neighbors;} //pybind11
  // overide this method auto getEdges() -> decltype(edges) {return edges;} auto
  // getVertices() -> decltype(vertices) {return vertices;}
  std::string toString();
};

struct vorVert {
 private:
  size_t internalID;

  std::vector<size_t> edgeIDs;
  std::vector<size_t> faceIDs;

 public:
  arrXY pos;
  // change halfedges, vorFaces to store up to 4 (or 3) pointers with the object
  std::array<siteEvent *, 3> sites;
#ifdef _BUFFERED_VEC_OPT
  vorContainer::buffered_vec<halfEdge *, 4> edges;
  vorContainer::buffered_vec<vorFace *, 4> faces;
#else
  std::vector<halfEdge *> edges;
  std::vector<vorFace *> faces;
#endif
  std::array<long, 3> colorPattern{{-1, -1, -1}};
  size_t id;
  long vertexCoorID = -2;
  bool infVert = false;
  bool _IMPLICIT;
  double rad;
  long eventLog;
  bool ACTIVE = true;
  vorVert(arrXY coordinates, size_t IDnum, double rad, siteEvent *obj1,
          siteEvent *obj2, siteEvent *obj3, long eventLog, bool implicit)
      : pos(coordinates),
        sites{obj1, obj2, obj3},
        colorPattern{obj1->voronoiFace->color, obj2->voronoiFace->color,
                     obj3->voronoiFace->color},
        id(IDnum),
        internalID(IDnum),
        _IMPLICIT(implicit),
        rad(rad),
        eventLog(eventLog) {
#ifndef _BUFFERED_VEC_OPT
    edges.reserve(4);  // should be max
    faces.reserve(4);
#endif
    // vorVerts cannot be invalidated
    /*this->pos = coordinates;
    this->id = IDnum;
    this->rad = rad;
    this->colorPattern = { obj1.color, obj2.color, obj3.color };
    */
  }
  vorVert(){};
  void reconstruct(size_t internalID, std::vector<size_t> edgeIDs,
                   std::vector<size_t> faceIDs, arrXY pos,
                   std::array<long, 3> colorPattern, long vertexCoorID,
                   bool infVert, bool _IMPLICIT, double rad, long eventLog) {
    this->internalID = internalID;
    this->edgeIDs = edgeIDs;
    this->faceIDs = faceIDs;
    this->pos = pos;
    this->colorPattern = colorPattern;
    this->vertexCoorID = vertexCoorID;
    this->infVert = infVert;
    this->_IMPLICIT = _IMPLICIT;
    this->rad = rad;
    this->eventLog = eventLog;
  }

  void setPTRIDs();

  std::string toString();

  void addEdge(halfEdge *edge);

  void setID(std::size_t nuID) { internalID = nuID; }

  void disable(void) {
    ACTIVE = false;
    // data = nullptr;
  }
  bool getState() { return ACTIVE; }
  std::size_t getID(void) const { return internalID; }  // pybind
  // Sets the data to default values
  // pos(coordinates), colorPattern({ obj1->color, obj2->color, obj3->color }),
  // id(IDnum), _IMPLICIT(implicit), rad(rad), eventLog(eventLog)
  // std::vector<long> colorPattern = { -1,-1,-1 };

  void setNew(arrXY coordinates, size_t IDnum, double rad, siteEvent *obj1,
              siteEvent *obj2, siteEvent *obj3, long eventLog, bool implicit) {
    edges.clear();
    // edges.shrink_to_fit();
    faces.clear();
    colorPattern = {obj1->voronoiFace->color, obj2->voronoiFace->color,
                    obj3->voronoiFace->color};
    pos = coordinates;
    id = IDnum;
    _IMPLICIT = implicit;
    this->rad = rad;
    this->eventLog = eventLog;
    ACTIVE = true;
  }

  // bind to python
  auto getEdgeIDs() const -> decltype(edgeIDs) { return edgeIDs; };
  auto getFaceIDs() const -> decltype(faceIDs) { return faceIDs; };

  std::size_t getEdgeID(std::size_t ind) { return edgeIDs.at(ind); }
  std::size_t getFaceID(std::size_t ind) { return faceIDs.at(ind); }
  // template<class Container>
  // auto getEdges(Container container) -> halfEdge {return edges;}
  // auto getFaces() -> decltype(faces) {return faces;}

  auto getDegree() -> int { return edgeIDs.size(); }
};

struct halfEdge {
 private:
  size_t internalID;
  size_t twinID;
  size_t originID;
  size_t twinOriginID;
  size_t adjacentFaceID;

 public:
  halfEdge *twin;
  vorVert *origin;
  vorFace *adjacentFace;
  int edgeType;
  size_t id;
  long color;
  double dist = -1.0;
  arrXY controlPoint{{0, 0}};
  bool mustBePinned = false;
  bool VERTEX_SET = false;
  bool COMPLETE_EDGE = false;
  bool INVALID = false;
  bool INFINITE = false;
  arrXY dir{{0.0, 0.0}};
  double distance = 0.0;
  halfEdge(vorFace *adjFace, int edgeType, size_t edgeID)
      : twin(nullptr),
        origin(nullptr),
        adjacentFace(adjFace),
        edgeType(edgeType),
        id(edgeID),
        color(adjFace->color) {}

  halfEdge() : twin(nullptr), origin(nullptr), adjacentFace(nullptr){};
  // void addOrigin() Unknown function in code????
  void setPTRIDs() {
    twinID = twin->getID();
    originID = origin->getID();
    twinOriginID = twin->origin->getID();
    adjacentFaceID = adjacentFace->id;
  }

  std::string toString();

  void finalizeEdge();

  arrXY computeIntersect(double rad, bool allowShortcuts = true);

  void addTwin(halfEdge *edgeTwin);

  void setOrigin(vorVert *vertex);

  // At Origin Only
  arrXY getDirection();

  double getDistance();

  arrXY getControlPoint();
  /* Unsure if used
  void addedTwin(halfEdge* edgeTwin) {
  twin = edgeTwin;
  adjacentFace->neighbor
  }
  */

  void setID(std::size_t nuID) { internalID = nuID; }

  void disable(void) {
    INVALID = true;
    // assert(!origin);
    // for (auto it = origin->edges.begin(); it != origin->edges.end(); ++it) {
    //	if (this == *it) {
    //		origin->edges.erase(it);
    //		break;
    //	}
    //}
  }
  bool getState() { return !INVALID && COMPLETE_EDGE; }

  // bind to python
  std::size_t getID(void) const { return internalID; }
  // Sets the data to default values
  void setNew(vorFace *adjFace, int edgeType, size_t edgeID) {
    controlPoint = {0, 0};
    mustBePinned = false;
    VERTEX_SET = false;
    COMPLETE_EDGE = false;
    INVALID = false;
    dir = {0.0, 0.0};
    distance = -1.0;
    dist = -1.0;  // Why is this here?
    twin = nullptr;
    origin = nullptr;
    adjacentFace = adjFace;
    this->edgeType = edgeType;
    id = edgeID;
    color = adjFace->color;
  }
  void reconstruct(size_t internalID, size_t twinID, size_t originID,
                   size_t twinOriginID, size_t adjacentFaceID, int edgeType,
                   long color, double dist, arrXY controlPoint, bool INFINITE,
                   arrXY dir) {
    this->internalID = internalID;
    this->twinID = twinID;
    this->originID = originID;
    this->twinOriginID = twinOriginID;
    this->adjacentFaceID = adjacentFaceID;
    this->edgeType = edgeType;
    this->color = color;
    this->dist = dist;
    this->controlPoint = controlPoint;
    this->dir = dir;
    this->id = internalID;
  }
  // functions to bind to python
  auto getTwinID() const -> decltype(twinID) { return twinID; }
  auto getOriginID() const -> decltype(originID) { return originID; }
  auto getTwinOriginID() const -> decltype(twinOriginID) {
    return twinOriginID;
  }
  auto getFaceID() const -> decltype(adjacentFaceID) { return adjacentFaceID; }

  std::tuple<std::size_t, std::size_t> getELPair() const {
    return std::tuple<std::size_t, std::size_t>(this->getOriginID(),
                                                this->getTwinOriginID());
  }
  // template<typename Container> //Container with function .at()
  // auto getTwin(Container container) -> decltype(container.at(twinID)) {return
  // container.at(twinID);} template<typename Container> //Container with
  // function .at() auto getOrigin(Container container) ->
  // decltype(container.at(originID)) {return container.at(originID);}
  // template<typename Container>
  // auto getFace(Container container) -> decltype(container.at(adjacentFaceID))
  // {return container.at(adjacentFace);}
};

struct halfEdgeRecords {
 private:
  std::vector<vorVert>
      verticesClean;  // Filled at the end with a seperate function.
  std::vector<halfEdge> halfEdgesClean;

 public:
  // Stores pointers as underlying objects will point to each other.
  // Do not want to have to deal with invalidation of pointers.
  // Do not do a lot of accessing besides dumping out at the end.
  // When half edge records goes out of scope, all objects are deleted
  std::size_t vertexCountTracker = 0;
  std::size_t halfEdgeTracker = 0;
  vorContainer::vectorPageAllocator<vorVert> Vertices;
  vorContainer::vectorPageAllocator<halfEdge> HalfEdges;

  std::vector<vertexEvent>
      inputVertexContainer;  // refactor -> store in halfEdgeRecords
  std::vector<lineEvent> inputLineContainer;  // see above

  // std::vector<std::unique_ptr<vorVert>> Vertices;
  // std::vector<std::unique_ptr<halfEdge>> HalfEdges;
  std::vector<vorFace> Faces;

  halfEdgeRecords(){};

  halfEdgeRecords(long numInputVert, long numInputEdge)
      : Vertices(numInputVert + numInputEdge * 4),
        HalfEdges(8 * numInputEdge + 2 * numInputVert) {
    // this->Vertices.reserve(numInputVert + numInputEdge);
    // this->HalfEdges.reserve((numInputEdge + numInputVert) * 4);
    this->Faces.reserve(
        numInputVert +
        numInputEdge *
            2);  // This will reserve enough and will not need modification
  }

  void reconstruct(std::vector<vorVert> verticesClean,
                   std::vector<halfEdge> halfEdgesClean,
                   std::vector<vertexEvent> inputVertexContainer,
                   std::vector<lineEvent> inputLineContainer,
                   std::vector<vorFace> Faces) {
    this->verticesClean.swap(
        verticesClean);  // Probably can't use move constructor here
    this->halfEdgesClean.swap(halfEdgesClean);
    this->inputVertexContainer.swap(inputVertexContainer);
    this->inputLineContainer.swap(inputLineContainer);
    this->Faces.swap(Faces);
  }

  halfEdge *createHalfEdge(siteEvent *adjFace, int edgeType) {
    return HalfEdges.add(adjFace->voronoiFace, edgeType, halfEdgeTracker++);
    // HalfEdges.back().get(); //Returns a bare pointer to be stored by the twin
    // edge.
    // Specific implementations may be moved here.
  }

  std::pair<halfEdge *, halfEdge *> createHalfEdgePair(siteEvent *obj1,
                                                       siteEvent *obj2,
                                                       int edgeType) {
    auto leftEdge = createHalfEdge(obj1, edgeType);
    auto rightEdge = createHalfEdge(obj2, edgeType);
    leftEdge->addTwin(rightEdge);
    return std::make_pair(leftEdge, rightEdge);
  }

  vorVert *createVertex(arrXY coordinates, double rad, siteEvent *obj1,
                        siteEvent *obj2, siteEvent *obj3, long eventLog,
                        bool implicitOnly = false) {
    return Vertices.add(coordinates, vertexCountTracker++, rad, obj1, obj2,
                        obj3, eventLog, implicitOnly);
  }

  vorFace *createFace(siteEvent *siteObject, long color) {
    Faces.emplace_back(siteObject, color);
    return &Faces.back();
  }

  void setFinalIDs() {
    // Vertices.setIDsToFinalLocation(); //Vertices cannot be removed
    HalfEdges.setIDsToFinalLocation();
  }

  void finalizeRecordValues() {
    for (auto &e : this->HalfEdges) {
      e.getDistance();
      e.getDirection();
      e.getControlPoint();
    }
  }

  std::vector<halfEdge *> DEBUG_getHalfEdgePtrVector() {
    std::vector<halfEdge *> out;
    out.reserve(this->HalfEdges.numElements);
    for (int i = 0; i < this->HalfEdges.numElements; ++i) {
      auto he = this->HalfEdges.get(i);
      if (!he->INVALID && !he->twin->INVALID)
        out.push_back(this->HalfEdges.get(i));
    }
    return out;
  }

  void moveVertsAndEdgesToVector() {
    // HalfEdges.setIDsToFinalLocation();  // Sets their id to ultimate array
    // index
    verticesClean.reserve(Vertices.numElements);    // reserve space in vector
    halfEdgesClean.reserve(HalfEdges.numElements);  // reserve space in vector
    auto eID = 0;
    for (auto &e : this->HalfEdges) {
      e.setID(eID++);
    }

    for (auto e : this->HalfEdges) {
      halfEdgesClean.emplace_back(e);  // copies everything
    }
    for (auto v : this->Vertices) {
      verticesClean.emplace_back(v);
    }
    for (auto &e : halfEdgesClean) {
      e.setPTRIDs();  // ptrs in new container reach into old container
    }
    for (auto &v : verticesClean) {
      v.setPTRIDs();
    }
    for (auto &f : Faces) {
      f.setPTRIDs();
    }
    HalfEdges
        .clear();  // destroy original copies after moving things to a vector
    Vertices.clear();
  }

  // Below -> functions to bind to python
  std::vector<vorVert> &getVertices() { return this->verticesClean; }
  std::vector<halfEdge> &getEdges() { return this->halfEdgesClean; }
  std::vector<vorFace> &getFaces() { return this->Faces; }

  std::vector<vorVert> getVerticesCopy() const { return this->verticesClean; }
  std::vector<halfEdge> getEdgesCopy() const { return this->halfEdgesClean; }

  vorVert *getVertex(std::size_t id) { return &verticesClean.at(id); }
  halfEdge *getEdge(std::size_t id) { return &halfEdgesClean.at(id); }
  vorFace *getFace(std::size_t id) { return &Faces.at(id); }

  bool inputID_IsVertex(std::size_t ind) {
    return ind < inputVertexContainer.size();
  }

  siteEvent *getInputEvent(std::size_t ind) {
    if (inputID_IsVertex(ind)) {
      return &inputVertexContainer.at(ind);
    } else {
      return &inputLineContainer.at(ind - inputVertexContainer.size());
    }
  }

  vertexEvent *getVertexEvent(std::size_t ind) {
    return &inputVertexContainer.at(ind);
  }

  lineEvent *getLineEvent(std::size_t ind) {
    // Expects general index directly from siteEvent -> id
    return &inputLineContainer.at(ind - inputVertexContainer.size());
  }

  std::vector<std::tuple<std::size_t, std::size_t>> getEL() {
    std::vector<std::tuple<std::size_t, std::size_t>> outList;
    outList.reserve(this->halfEdgesClean.size());
    for (const auto &e : halfEdgesClean) {
      outList.push_back(e.getELPair());
    }
    return outList;
  }

  std::tuple<std::size_t, std::size_t> edgeToEL(std::size_t edgeID) {
    return getEdge(edgeID)->getELPair();
  }
// void convertPointersToIDs() {
//}
#ifdef _DEBUG
// The below code broke at some point... it is no longer important
/*void DEBUG_dispContents(void) {
  int runCount = 0;
  for (auto &vec : Vertices.collector) {
    for (auto &vert : *vec.get()) {
      std::cout << "VERTEX " << runCount++ << ": " << vert.toString()
                << std::endl;
      for (auto &vec : Vertices.collector) {
        for (auto &vert : *vec.get()) {
          std::cout << "VERTEX " << runCount++ << ": " << vert.toString();
          for (auto &vec : HalfEdges.collector) {
            std::cout << "VERTEX " << std : ++ : << o ": " << vert.toString()
                      << "VERTEX "
                      << runCount++
                      << ": "
                      << vert.toString() std::cout
                      << "HALFEDGE "
                      << runCount++
                      << ": "
                      << he.toString()
                      << std::endl;
          }
        }
        runCount = 0;
        for (auto &face : Faces) {
          std::cout << "FACE " << runCount++ << ": " << face.toString()
                    << std::endl;
        }
      }
    }
  }
} */
#endif
};

#endif
