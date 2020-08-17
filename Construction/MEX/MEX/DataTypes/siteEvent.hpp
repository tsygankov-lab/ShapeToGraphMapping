#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER
// LineEvents and VertexEvents are the only events that would need to be saved.
// Both are directly constructed into a vector/array.
// The only ptr that would need to be converted which is not trivially
// convertible
// is the vertPointer, which is a nullptr for all except for line endpoints,
// which
// have a voronoi vertex created directly ontop of them.  The pointer is used to
// ensure that a secondary vertex will not be created at this location.
// The alternative, which could be okay, is to construct multiple voronoi
// vertices
// at this location.  This would at least preserve the rule that all voronoi
// vertices
// have a degree of three (which is good for it's own reasons), but the edges
// connecting
// said vertices to each other would ultimately be meaningless, and would likely
// require
// some kind of 'hack' to work naturally with how endpoints are current allowed
// to be
// shared.
#ifndef SITEEVENT
#define SITEEVENT

//#include "../vorHeader.hpp"
#include "../Math/basicMathAndGeometry.hpp"
#include "../Math/vecOverrides.hpp"
#include "../precisionChecks.hpp"

//#include "../Records/halfEdgeRecords.hpp"
//#include "../Queue/SEQTree.hpp"
//#include "../Tree/RBT.hpp"
#include <algorithm>
#include <exception>
#include <string>
#ifdef _DEBUG

#ifdef _GCC_49_COMP
#include <sstream>
namespace std {
template <typename T>
std::string to_string(T value) {
  // create an output string stream
  std::ostringstream os;

  // throw the value into the string stream
  os << value;

  // convert the string stream into a string and return
  return os.str();
}
}  // namespace std
#endif
#endif
// Routine...
/*
if(CLASS->isCircle)
        std::static_cast<circleEvent*> &CLASS;
else if (CLASS->isEP)
        std::static_cast<vertexEvent*> &CLASS;
else if (CLASS->isLine)
        std::static_cast<lineEvent*> &CLASS;
end
switch(this->objType){
        case 0: DEGENCAST //never in list
        case 1: VERTCAST
        case 2: LINECAST
        case 100: CIRC CAST
}
*/
enum _DATATYPE { HALFEDGE, VERTEX, LINE, DEGENERATE, CIRCLEEVENT };
namespace vorQueue {
class NodeSEQ;
}
namespace vorRBT {
class Node;
}
struct vorFace;
struct vorVert;
struct halfEdge;
class siteEvent {
  std::size_t internalListID;
  std::size_t vertPointerID;

 public:
  _DATATYPE objType;

  arrXY pos;
  arrXY cent;

  long eventLog;
  long objectIndex;

  bool isProcessed = false;
  double rad;
  vorFace *voronoiFace = nullptr;
  vorVert *vertPointer = nullptr;

  vorQueue::NodeSEQ *SEQptr = nullptr;

  bool ACTIVE = true;

  // Destroys these on destruction
  // Create these on appropiate function call
  // std::unique_ptr<lineParam>  line;
  // std::unique_ptr<circParam> 	circ;

  double getKey(void) const { return rad; }
  siteEvent(){};
  // Core siteEvent object.
  siteEvent(arrXY xy, arrXY centxy, long objID, _DATATYPE type, long LogID)
      : objType(type),
        pos(xy),
        cent(centxy),
        eventLog(LogID),
        objectIndex(objID),
        rad(vorGeo::dist(pos, cent)) {}

  siteEvent(siteEvent const &other)
      : objType(other.objType),
        pos(other.pos),
        cent(other.cent),
        eventLog(other.eventLog),
        objectIndex(other.objectIndex),
        isProcessed(other.isProcessed),
        rad(other.rad),
        voronoiFace(other.voronoiFace),
        vertPointer(other.vertPointer),
        SEQptr(other.SEQptr),
        ACTIVE(other.ACTIVE){};

  void reconstruct(std::size_t internalListID, std::size_t vertPointerID,
                   _DATATYPE objType, arrXY pos, arrXY cent, long eventLog,
                   long objectIndex, double rad) {
    this->internalListID = internalListID;
    this->vertPointerID = vertPointerID;
    this->objType = objType;
    this->pos = pos;
    this->cent = cent;
    this->eventLog = eventLog;
    this->objectIndex = objectIndex;
    this->rad = rad;
  }
  // By having a virtual function, pybind11 will treat classes as
  // polymorphic
  virtual ~siteEvent() = default;

  void setPTRIDs();
  /*siteEvent& operator=(siteEvent const &other) {
          pos = other.pos;
          cent = other.cent;
          objectIndex = other.objectIndex;
          objType = other.objType;
          eventLog = other.eventLog;
          isProcessed = other.isProcessed;
          rad = other.rad;// vorGeo::dist(pos, cent);
          ACTIVE = other.ACTIVE;
          voronoiFace = other.voronoiFace;
          vertPointer = other.vertPointer;
          SEQptr = other.SEQptr;
  }*/
  std::size_t getVorVertID() const { return this->vertPointerID; }

  // void setVorVertID(std::size_t id) { this->vertPointerID = id; }
  // Will be called by degenEvent::setNew in the allocator.  Degen Events _can_
  // be deleted.
  void setNew(arrXY xy, arrXY centxy, long objID, _DATATYPE type, long LogID) {
    pos = xy;
    cent = centxy;
    objectIndex = objID;
    objType = type;
    eventLog = LogID;
    isProcessed = false;
    rad = vorGeo::dist(pos, cent);
    ACTIVE = true;
    voronoiFace = nullptr;
    vertPointer = nullptr;
    SEQptr = nullptr;
  }

  std::size_t getID(void) const { return internalListID; }

  void setID(std::size_t newID) { internalListID = newID; }

  void disable(void) { ACTIVE = false; }
  bool getState() { return ACTIVE; }

  virtual std::string toString() const {
    return std::string("ERROR UNKNOWN TYPE");
  }

  virtual std::string toString_Comprehensive() const {
    return this->toString();
  }

  virtual double distToPoint(arrXY XY) const { return vorGeo::dist(pos, XY); }

  virtual double distToPoint_STRICT(arrXY XY) const { return distToPoint(XY); }

  virtual arrXY getClosestPoint(arrXY XY) const { return this->pos; }

  virtual bool orientationCheck(arrXY XY) const { return true; }

  double maxPos() const {
    return std::fmax(std::abs(pos[0]), std::abs(pos[1]));
  }
  // Gets the extended parameter list
  // auto ... = SE -> getExtendedParameters()
};

// These could be saved
class vertexEvent : public siteEvent {
 public:
  // These don't track edges at all
  // Maybe add a std::vector<std::size_t> edgeList? Exclusively for use
  // afterwards. Do not currently have a use where this is needed...
  std::vector<std::size_t> connectedEgeList;
  //

  // Degen objects are intially set to degen.  Upon SEQ hit, degen status is
  // flipped.
  std::vector<vorRBT::Node *> replacePointerList;  // NodeRBT
  // std::vector<lineEvent*>		degenLineList; //calculatable
  // std::vector<vertexEvent*>	degenOtherEPList;
  // std::vector<std::uint8_t>	degenIsLeftEP;

  std::vector<lineEvent *> lineSpawnEvent;

  std::vector<halfEdge *> mustBePinned;
  // std::vector<vertexEvent*>	otherEPList; //calculatable
  // std::vector<std::uint8_t> 	isLeftEP;

  double numDegen;
  bool isEP = false;

  vertexEvent() : siteEvent(){};

  vertexEvent(arrXY pos, arrXY cent, long objID, long LogID)
      : siteEvent(pos, cent, objID, VERTEX, LogID), isEP(false){};

  // debuggers
  vertexEvent(arrXY pos, arrXY cent)
      : siteEvent(pos, cent, 0, VERTEX, 0), isEP(false){};

  void reconstruct(std::size_t internalListID, std::size_t vertPointerID,
                   _DATATYPE objType, arrXY pos, arrXY cent, long eventLog,
                   long objectIndex, double rad,
                   std::vector<size_t> connectedEdgeList, bool isEP) {
    siteEvent::reconstruct(internalListID, vertPointerID, objType, pos, cent,
                           eventLog, objectIndex, rad);
    this->connectedEgeList = connectedEdgeList;
    this->isEP = isEP;
  }
  /*vertexEvent(vertexEvent const &other) : siteEvent(other) {
          *this = other;
  }*/

  /*vertexEvent& operator=(vertexEvent const &other) {
          pos = other.pos;
          cent = other.cent;
          objectIndex = other.objectIndex;
          objType = other.objType;
          eventLog = other.eventLog;
          isProcessed = other.isProcessed;
          rad = other.rad;// vorGeo::dist(pos, cent);
          ACTIVE = other.ACTIVE;
          voronoiFace = other.voronoiFace;
          vertPointer = other.vertPointer;
          SEQptr = other.SEQptr;
  }*/
  // Not really a context where this should need to be called
  void setNew(arrXY pos, arrXY cent, long objID, long LogID) {
    siteEvent::setNew(pos, cent, objID, VERTEX, LogID);
    lineSpawnEvent.clear();
    replacePointerList.clear();
    isEP = false;
  }

  // vertexEvent(vecDBL &pos) : siteEvent(pos, vecDBL({ 0.0,0.0 }), 0, VERTEX,
  // 0), isEP(false) {
  //};
  // lineObj not modified immediately, but stored for later
  void setEndpointAsLineEvent(lineEvent &lineObj);

  void registerEdgeID(std::size_t ind) { connectedEgeList.emplace_back(ind); }

  // degenObjNode is the node containing the degenerate node.
  // lineObj is a reference to the line creating this degenerate.
  void addReplacement(vorRBT::Node *degenObjNode, lineEvent &lineObj);

  std::string toString() const {
    if (isEP)
      return std::string("EP") + std::to_string(objectIndex);
    else
      return std::string("V") + std::to_string(objectIndex);
  }

  virtual std::string toString_Comprehensive() const {
    std::string COMPREHENSIVE = this->toString();
    COMPREHENSIVE += ":\nXY: (" + std::to_string(this->pos[0]) + ", " +
                     std::to_string(this->pos[1]) + ")";
    return COMPREHENSIVE;
  }
};

// These could be saved
class lineEvent : public siteEvent {
  std::array<std::size_t, 2> endPointIDs;
  // dir and EP ordering should account for UPPER vs LOWER
  // Correcting the constructor would be a massive undertaking due to other code
  // accounting for this. getDir and getLeftEP vs getRightEP which do account
  // for upper/lower can relieve this

  // Setting each endpoints 'edgeID list' will add the output of 'getLeftEP'.
 public:
  arrABC ABC;
  arrXY dir;
  arrXY infPos;

  double infRad;
  double magnitude;

  bool centerAligned;
  bool UPPER;

  // Why was this here?
  // std::vector<lineEvent*> circlePointer;
  lineEvent *twin;
  // twinID = objectIndex + UPPER - !UPPER;
  std::array<vertexEvent *, 2> endPoints;
  lineEvent() : siteEvent(), twin(nullptr){};

  lineEvent(arrXY pos, arrXY infPos, arrXY cent, vertexEvent *EP1,
            vertexEvent *EP2, long objectIndex, long eventLog)
      : siteEvent(pos, cent, objectIndex, LINE, eventLog), infPos(infPos) {
    // siteEvent(pos, cent, objectIndex, 2, eventLog);

    infRad = vorGeo::dist(infPos, cent);
    int ep1LeftEP2 = vorGeo::checkLeftOf(cent, EP1->pos, EP2->pos, 10000);
    this->centerAligned = false;
    if (ep1LeftEP2 == 0) {
      this->centerAligned = true;
      if (EP1->rad < EP2->rad) {
        endPoints[0] = EP1;
        endPoints[1] = EP2;
        this->ABC = vorGeo::points2Line(EP1->pos, EP2->pos);
      } else {
        endPoints[0] = EP2;
        endPoints[1] = EP1;
        this->ABC = vorGeo::points2Line(EP2->pos, EP1->pos);
      }
    } else if (ep1LeftEP2 == -1) {
      endPoints[0] = EP1;
      endPoints[1] = EP2;
      this->ABC = vorGeo::points2Line(EP1->pos, EP2->pos);
    } else {
      // ep1LeftEP2 == 1
      endPoints[0] = EP2;
      endPoints[1] = EP1;
      this->ABC = vorGeo::points2Line(EP2->pos, EP1->pos);
    }
    this->magnitude =
        sqrt(ABC[0] * ABC[0] + ABC[1] * ABC[1]);  // vorGeo::norm(this->ABC);
    this->dir = {this->ABC[1] / magnitude, -this->ABC[0] / magnitude};
    EP1->isEP = true;
    EP2->isEP = true;
    this->UPPER = true;
  }

  // twin and circlePointers not copied
  lineEvent(const lineEvent &other)
      : siteEvent(other),
        ABC(other.ABC),
        dir(other.dir),
        infPos(other.infPos),
        infRad(other.infRad),
        magnitude(other.magnitude),
        centerAligned(other.centerAligned),
        UPPER(other.UPPER),
        endPoints(other.endPoints),
        endPointIDs(other.endPointIDs){};

  void reconstruct(std::size_t internalListID,
                              std::size_t vertPointerID, _DATATYPE objType,
                              arrXY pos, arrXY cent, long eventLog,
                              long objectIndex, double rad,
                              std::array<std::size_t, 2> endPointIDs,
                              arrABC ABC, arrXY dir, arrXY infPos,
                              double infRad, double magnitude,
                              bool centerAligned, bool UPPER) {
    siteEvent::reconstruct(internalListID, vertPointerID, objType, pos, cent,
                           eventLog, objectIndex, rad);
    this->endPointIDs = endPointIDs;
    this->ABC = ABC;
    this->dir = dir;
    this->infPos = infPos;
    this->infRad = infRad;
    this->magnitude = magnitude;
    this->centerAligned = centerAligned;
    this->UPPER = UPPER;
  }

  std::size_t getLeftEPID() {
    return this->UPPER ? endPointIDs[1] : endPointIDs[0];
  }
  std::size_t getRightEPID() {
    return this->UPPER ? endPointIDs[0] : endPointIDs[1];
  }

  std::array<size_t, 2> getEPIDs() const {
    return this->endPointIDs; };
  // Flips for UPPER lines
  // Check
  arrXY getDir() {
    return this->UPPER ? arrXY{-this->dir[1], -this->dir[0]} : this->dir;
  }
  // vecDBL ABC;
  // vecDBL dir;
  // vecDBL infPos;

  // double infRad;
  // double magnitude;

  // bool centerAligned;
  // bool UPPER;

  // std::vector<lineEvent*> circlePointer;
  // lineEvent* twin;

  // std::vector<vertexEvent*> endPoints;
  // Not really a context where this should need to be called.  Allows
  // compatibility with container if needed
  void setNew(arrXY pos, arrXY infPos, arrXY cent, vertexEvent *EP1,
              vertexEvent *EP2, long objectIndex, long eventLog) {
    // circlePointer.clear();
    siteEvent::setNew(pos, cent, objectIndex, LINE, eventLog);
    this->infPos = infPos;
    this->centerAligned = false;
    this->infRad = vorGeo::dist(infPos, cent);
    // from above
    int ep1LeftEP2 = vorGeo::checkLeftOf(cent, EP1->pos, EP2->pos, 10000);
    if (ep1LeftEP2 == 0) {
      this->centerAligned = true;
      if (EP1->rad < EP2->rad) {
        endPoints[0] = EP1;
        endPoints[1] = EP2;
        this->ABC = vorGeo::points2Line(EP1->pos, EP2->pos);
      } else {
        endPoints[0] = EP2;
        endPoints[1] = EP1;
        this->ABC = vorGeo::points2Line(EP2->pos, EP1->pos);
      }
    } else if (ep1LeftEP2 == -1) {
      endPoints[0] = EP1;
      endPoints[1] = EP2;
      this->ABC = vorGeo::points2Line(EP1->pos, EP2->pos);
    } else {
      // ep1LeftEP2 == 1
      endPoints[0] = EP2;
      endPoints[1] = EP1;
      this->ABC = vorGeo::points2Line(EP2->pos, EP1->pos);
    }
    this->magnitude = vorGeo::norm(arrXY({ABC[0], ABC[1]}));
    this->dir = {this->ABC[0] / (-magnitude), this->ABC[1] / magnitude};
    EP1->isEP = true;
    EP2->isEP = true;
    this->UPPER = true;
    endPointIDs[0] = endPoints[0]->objectIndex;
    endPointIDs[1] = endPoints[1]->objectIndex;
  }

  double maxPos() const {
    return std::fmax(endPoints[0]->maxPos(), endPoints[1]->maxPos());
  }

  lineEvent(lineEvent *twinObj)
      : siteEvent(twinObj->pos, twinObj->cent, twinObj->objectIndex, LINE,
                  twinObj->eventLog){};

  vertexEvent *getOtherEP(vertexEvent *otherEP);  // add ID version

  bool isEP(vertexEvent *EP);  // add ID version

  bool isLeftEP(vertexEvent *EP);  // add ID version

  const bool isEP(const vertexEvent *EP) const;  // add ID version

  const bool isLeftEP(const vertexEvent *EP) const;  // add ID version

  const vertexEvent *getOtherEP(const vertexEvent *otherEP) const;

  lineEvent createLower(void);

  arrXY getSafeCoordinates(void) const;

  std::string toString() const {
    if (UPPER)
      return std::string("UL") + std::to_string(objectIndex);
    else
      return std::string("LL") + std::to_string(objectIndex);
  }

  virtual std::string toString_Comprehensive() const {
    std::string COMPREHENSIVE = this->toString();
    COMPREHENSIVE +=
        ":\n\tEP1 Info:\n" + this->endPoints[0]->toString_Comprehensive() +
        "\nEP2 Info:\n" + this->endPoints[1]->toString_Comprehensive();
    return COMPREHENSIVE;
  }
  virtual double distToPoint(arrXY XY) const {
    auto closestPoint =
        vorGeo::closestPoint_TRUNC(endPoints[0]->pos, endPoints[1]->pos, XY);
    // For line segments, they are treated as infinite lines until both
    // endpoints have been processed, so this function should check with the
    // perpendicular distance to said line.  Its okay to check with truncated
    // distances too, but only on circle event confirmation.
    return vorGeo::dist(closestPoint.closeXY, XY);
  }

  virtual double distToPoint_STRICT(arrXY XY) const {
    auto closestPoint =
        vorGeo::closestPoint_TRUNC(endPoints[0]->pos, endPoints[1]->pos, XY);
    // For line segments, they are treated as infinite lines until both
    // endpoints have been processed, so this function should check with the
    // perpendicular distance to said line.  Its okay to check with truncated
    // distances too, but only on circle event confirmation.
    return vorGeo::dist(closestPoint.closeXY_Trunc, XY);
  }

  virtual arrXY getClosestPoint(arrXY XY) const {
    return vorGeo::findClosestPoint(this->ABC, XY);
  }

  virtual bool orientationCheck(arrXY XY) const {
    if (UPPER) {
      return vorGeo::checkLeftOf(endPoints[0]->pos, endPoints[1]->pos, XY) >= 0;
    } else {
      return vorGeo::checkLeftOf(endPoints[0]->pos, endPoints[1]->pos, XY) <= 0;
    }
  }

  double betweenEP(const arrXY &XY) const {
    // 0.0->1.0 is inbetween the line.  <0.0 implies it is to the 'left' of EP1.
    // >1.0 implies it is to the 'right' of EP2.  Assumes dist of line > 0.0. If
    // this is not the case, it will return NaN (0/0).
    const arrXY &ep1 = this->endPoints[0]->pos;
    const arrXY &ep2 = this->endPoints[1]->pos;
    arrXY p(ep2 - ep1);
    auto value = ((XY[0] - ep1[0]) * p[0] + (XY[1] - ep1[1]) * p[1]) /
                 (p[0] * p[0] + p[1] * p[1]);  // this->magnitude;
    return value;

    //
  }
  // check if getPosFromEP is used
};

// These never need to be saved
class degenEvent : public siteEvent {
 public:
  vertexEvent *replacedByPointer;
  lineEvent *linePointer;
  degenEvent(vertexEvent *endPointPointer, lineEvent *lineObj)
      : siteEvent(endPointPointer->pos, endPointPointer->cent,
                  endPointPointer->objectIndex, DEGENERATE,
                  endPointPointer->eventLog),
        replacedByPointer(endPointPointer),
        linePointer(lineObj) {
    siteEvent::voronoiFace = endPointPointer->voronoiFace;
  }

  void setNew(vertexEvent *endPointPointer, lineEvent *lineObj) {
    siteEvent::setNew(endPointPointer->pos, endPointPointer->cent,
                      endPointPointer->objectIndex, DEGENERATE,
                      endPointPointer->eventLog);
    siteEvent::voronoiFace = endPointPointer->voronoiFace;
    replacedByPointer = endPointPointer;
    linePointer = lineObj;
  }
  std::string toString() const {
    return std::string("D") + std::to_string(objectIndex);
  }
};

// These never need to be saved
class circleEvent : public siteEvent {
 public:
  // May want to make the circle events use the same allocator method
  double circRad;
  bool _PINCHCASE;

  std::array<vorRBT::Node *, 3> nodeVec;
  std::array<siteEvent *, 3> siteList;

  circleEvent(arrXY circXY, double cRad, arrXY cent,
              std::array<vorRBT::Node *, 3> nodeList,
              std::array<siteEvent *, 3> sites, bool pinchFlag, long eventLog)
      : siteEvent(circXY, cent, -1, CIRCLEEVENT, eventLog),
        circRad(cRad),
        _PINCHCASE(pinchFlag),
        nodeVec(nodeList),
        siteList(sites) {
    rad += circRad;  // must be added to give the correct circle
  }

  void setNew(arrXY circXY, double cRad, arrXY cent,
              std::array<vorRBT::Node *, 3> nodeList,
              std::array<siteEvent *, 3> sites, bool pinchFlag, long eventLog) {
    siteEvent::setNew(circXY, cent, -1, CIRCLEEVENT, eventLog);
    circRad = cRad;
    rad += circRad;
    _PINCHCASE = pinchFlag;
    nodeVec = nodeList;
    siteList = sites;
  }
  // std::string toString() const {
  //	return nodeVec.at(0)->toString() + std::string("/") +
  // nodeVec.at(1)->toString() + std::string("\\") + nodeVec.at(2)->toString();
  //}
};
#endif
