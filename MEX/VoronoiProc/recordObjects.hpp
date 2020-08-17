// Will return to this later. Deal with matlab implementation for now.
#ifndef _RECORDOBJ
#define _RECORDOBJ
#include <list>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "../MEX/Containers/buffered_vec.hpp"
#include "../MEX/Math/vecOverrides.hpp"
#include "../MEX/precisionChecks.hpp"
#include "boost/heap/fibonacci_heap.hpp"

namespace vorGeo {
double norm(const arrXY& arr2d) {
  return std::sqrt(arr2d[0] * arr2d[0] + arr2d[1] * arr2d[1]);
}
arrXY normalize(const arrXY& vec) { return vec / norm(vec); }
double angleBetween(const arrXY& dir1, const arrXY& dir2) {
  auto dir1N = normalize(dir1);
  auto dir2N = normalize(dir2);

  double sinth = dir1N[0] * dir1N[1] - dir1N[1] * dir2N[0];
  double costh = dir1N[0] * dir2N[0] - dir1N[1] * dir2N[1];

  if (sinth <= 0) {
    return (sinth -
            (double)(costh < _EPSILON) * (2.0 * (1.0 - std::abs(sinth))));
  } else {
    return (sinth +
            (double)(costh < _EPSILON) * (2.0 * (1.0 - std::abs(sinth))));
  }
  return 0;
}
}  // namespace vorGeo
// Base vert and edge types.
namespace vor {

struct vert;
struct edge;
struct subGraph;

struct vertEdgeID {
  long originID;
  long otherID;
  long edgeID;
  vertEdgeID(long vertID, long twinVertID, long edgeID)
      : originID(vertID), otherID(twinVertID), edgeID(edgeID){};

  // Can't be const... that would make the return type const vert&
  vert& getVert(std::unordered_map<long, vert>& umV) const {
    return umV.at(originID);
  }
  edge& getEdge(std::unordered_map<long, edge>& umE) const {
    return umE.at(edgeID);
  }
};
// verts/edge types
struct vert {
 private:
  std::size_t myID;
  // see if inputs need to be passed...
 public:
  std::vector<vertEdgeID> EL;  // make a vector of pairs of <vertID,edgeID>
  arrXY pos;
  // std::list<edge*> edgeList;
  std::array<long, 3> colorPattern;
  bool inf;
  long vertCoorID;
  double rad;

  // May make some of these in loop
  // Assumes matlab data
  vert(double* coordinates, std::size_t ID, double rad, long color1,
       long color2, long color3, long vertCoorID, double* edgeIDMat,
       double* originIDMat, std::size_t row, std::size_t numObjV,
       std::size_t numObjE)
      : pos(arrXY{{coordinates[0], coordinates[1]}}),
        myID(ID - 1),
        rad(rad),
        colorPattern({color1, color2, color3}),
        vertCoorID(vertCoorID) {
    for (std::size_t i = 0; i < 4; ++i) {
      auto indexE = i * numObjV + row;  // get outgoing edge.
      if (edgeIDMat[indexE] == 0) break;
      // get vertex other edge is attached to
      std::size_t indexV = edgeIDMat[indexE] - 1;
      EL.emplace_back(originIDMat[indexV] - 1,
                      originIDMat[indexV + numObjE] - 1, edgeIDMat[indexE] - 1);
    }
  };

  std::size_t getID() const noexcept { return myID; }

  bool isTerminal() const noexcept { return vertCoorID != -1; }
  // Map - for subgraph support.  Key = myID, which is MatlabID - 1
  // If the edge does not exist, then it will not be added to the edge list!

  std::pair<vert*, edge*> moveCW(long color);

  std::pair<vert*, edge*> moveCCW(long color);

  // void setEdgePtrs(std::vector<edge> &edgeList)
};
struct edge {
  std::size_t myID;
  std::size_t twinID;
  std::size_t originID;
  int edgeType;
  long color;
  double dist;
  arrXY controlPoint;
  arrXY dir;
  bool inf;
  // Constructor based Matlab Data
  edge(std::size_t thisID, std::size_t twinID, std::size_t originID,
       int edgeType, long color, double dist, double cpx, double cpy,
       double dirx, double diry, bool isInf)
      : myID(thisID - 1),
        twinID(twinID - 1),
        originID(originID - 1),
        edgeType(edgeType),
        color(color),
        dist(dist),
        controlPoint({cpx, cpy}),
        dir({dirx, diry}),
        inf(isInf){};

  std::size_t getID() const noexcept { return myID; }

  double getDist() const noexcept { return dist; }
};
std::pair<vert*, edge*> vert::moveCW(long color) {
  vert* nextVert = nullptr;
  edge* nextEdge = nullptr;
  for (auto e : edgeList) {
    if (e->color == color && e->twin->color != color) {
      nextVert = e->getOtherEP();
      nextEdge = &(*e);
      break;
    }
  }
  return std::make_pair(nextVert, nextEdge);
}
std::pair<vert*, edge*> vert::moveCCW(long color) {
  vert* nextVert = nullptr;
  edge* nextEdge = nullptr;
  for (auto e : edgeList) {
    if (e->color != color && e->twin->color == color) {
      nextVert = e->getOtherEP();
      nextEdge = e->twin;
      break;
    }
  }
  return std::make_pair(nextVert, nextEdge);
}

enum STATE { ACTIVE, QUEUE, INACTIVE };
namespace dijkstra {
// djVerts are objects created to point towards objects that hold all the
// information, and contain flags relevant to the current search;  This includes
// edge list (pair of djVert* and edge*).  The parent <djvert,edge> to this
// node, children <djvert, edge>, the distance, and the root of the search.
struct djVert;
struct djVertComparator {
  inline bool operator()(const djVert* a, const djVert* b) const;
};
struct djVert {
  vert* data;
  std::size_t rootID;
  STATE state;
  double dist;
  std::vector<std::pair<djVert*, edge*>> edgeList;
  std::pair<djVert*, edge*> parent;
  std::vector<std::pair<djVert*, edge*>> children;
  boost::heap::fibonacci_heap<
      djVert*, boost::heap::compare<djVertComparator>>::handle_type queueHandle;
  djVert(std::size_t rootID, vert* base)
      : rootID(rootID),
        data(base),
        dist(std::numeric_limits<double>::infinity()),
        state(ACTIVE){};

  bool isTerminal() const { return data->isTerminal(); }

  void setEdgeList(const subGraph* graph,
                   const std::unordered_map<std::size_t, djVert>& djVertList);

  bool isVisited() const noexcept { return state != INACTIVE; }

  bool isQueued() const noexcept { return state == QUEUE; }

  void setQueueState() noexcept { state = QUEUE; }

  void setVisitState() noexcept { state = INACTIVE; }

  std::vector<std::pair<vert*, edge*>> pathToParent();
};

bool djVertComparator::operator()(const djVert* a, const djVert* b) const {
  return a->dist > b->dist;
}
};  // namespace dijkstra
struct subGraph {
  std::size_t ID;
  std::unordered_set<std::size_t> vertInSubGraph;
  // std::unordered_set<std::size_t> edgeInSubGraph; //Optional?
  std::unordered_map<std::size_t, vert>& baseGraphVerts;
  std::unordered_map<std::size_t, edge>& baseGraphEdges;

  std::unordered_set<std::size_t>
      tipList;  // Roots for search. Could be vectors - easy enough to refactor
  std::unordered_set<std::size_t> majAxisTips;       // Roots for search
  std::unordered_set<std::size_t> majAxis;           // Final path
  std::unordered_set<std::size_t> majAxisReachable;  // Reachable from Final
                                                     // Path

  std::unordered_map<std::size_t,
                     std::unordered_map<std::size_t, dijkstra::djVert>>
      dijkstraData;
  subGraph(std::unordered_set<std::size_t> inSubGraph,
           std::unordered_map<std::size_t, vert>& baseGraphVerts,
           std::unordered_map<std::size_t, edge>& baseGraphEdges)
      : vertInSubGraph(inSubGraph),
        baseGraphVerts(baseGraphVerts),
        baseGraphEdges(baseGraphEdges){};
  subGraph(std::unordered_map<std::size_t, vert>& baseGraphVerts,
           std::unordered_map<std::size_t, edge>& baseGraphEdges)
      : baseGraphVerts(baseGraphVerts), baseGraphEdges(baseGraphEdges) {
    vertInSubGraph.reserve(baseGraphVerts.size());
    for (const auto& v : baseGraphVerts) {  // std::pair<std::size_t,vert>&
      vertInSubGraph.emplace(v.second.getID());
    }
  };
  subGraph(std::vector<std::size_t> inSubGraph,
           std::unordered_map<std::size_t, vert>& baseGraphVerts,
           std::unordered_map<std::size_t, edge>& baseGraphEdges)
      : baseGraphVerts(baseGraphVerts), baseGraphEdges(baseGraphEdges) {
    for (auto id : inSubGraph) {
      vertInSubGraph.emplace(id);
    }
  };

  bool inSubGraph(std::size_t id) const {
    return vertInSubGraph.count(id) > 0;
  };

  // getVertEP throws if the edge does not have an origin. This should not be
  // possible
  // These could be moved to vert and edge classes, but they need to be aware of
  // the subgraph calling them in the first place, as they only store indices to
  // each other

  // Edges may not have a twin if passed from matlab. These return nullptr if
  // the twin does not exist. Edges must have an origin.  This throws an
  // exception if it does not exist.
  edge* getTwin(const edge& edgeRef) const {
    auto twinEdge = baseGraphEdges.find(edgeRef.twinID);
    if (twinEdge == baseGraphEdges.end()) return nullptr;
    return &twinEdge->second;
  }
  edge* getTwin(std::size_t edgeID) const {
    return getTwin(baseGraphEdges.at(edgeID));
  }
  vert* getVertEP(const edge& edgeRef) const {
    return &baseGraphVerts.at(edgeRef.originID);
  }
  vert* getVertEP(std::size_t edgeID) const {
    return getVertEP(baseGraphEdges.at(edgeID));
  }
  vert* getOtherEP(const edge& edgeRef) const {
    auto twinEdge = baseGraphEdges.find(edgeRef.twinID);
    if (twinEdge == baseGraphEdges.end()) return nullptr;
    return getVertEP(twinEdge->second);
  }
  vert* getOtherEP(std::size_t edgeID) const {
    return getOtherEP(baseGraphEdges.at(edgeID));
  }
  bool inSubGraph(const vert& vert) const { return inSubGraph(vert.getID()); };
  // A half edge is in the subgraph if it's origin is in the subgraph.  The
  // twinEdge does not matter
  bool inSubGraph(const edge& edge) const {
    return inSubGraph(getVertEP(edge)->getID());
  }

  // This is using the definition for bridge in my program. Due to the way
  // passing edges work from matlab, if this the twin is null, it is a bridge.
  bool isBridge(const edge& edgeRef) const {
    auto twinE = getTwin(edgeRef);
    if (twinE) {
      return edgeRef.color == twinE->color;
    } else {
      return true;
    }
  }
  bool isBridge(std::size_t edgeID) const {
    return isBridge(baseGraphEdges.at(edgeID));
  }
  std::unordered_set<std::size_t> bfsInRad(std::vector<std::size_t> majAxNodes);

  void reserveSearches(std::size_t numSearches) {
    dijkstraData.reserve(numSearches);
  };

  std::unordered_map<std::size_t, dijkstra::djVert>& dijkstraSearch(
      std::size_t rootID) {
    auto prevCheck = dijkstraData.find(rootID);
    if (prevCheck == dijkstraData.end()) return prevCheck->second;

    // Setup storage structures
    auto loc = dijkstraData.emplace(rootID);
    auto& djCont =
        loc.first->second;  // pair <iter, bool> -> iter-pair <key,map> -> map
    djCont.reserve(vertInSubGraph.size());
    for (auto vID : vertInSubGraph) {
      djCont.emplace(rootID, baseGraphVerts.find(vID)->second);
    }
    for (auto& djV : djCont) {
      djV.second.setEdgeList(this, djCont);
    }

    boost::heap::fibonacci_heap<
        dijkstra::djVert*, boost::heap::compare<dijkstra::djVertComparator>>
        queue;

    while (!queue.empty()) {
      auto curVert = queue.top();
      queue.pop();
      for (auto eP : curVert->edgeList) {
        auto& djV = eP.first;  // Reference to a pointer djVert* or edge*
        auto& e = eP.second;
        if (!djV->isVisited()) {
          if (djV->dist > curVert->dist + e->dist) {
            djV->dist = curVert->dist + e->dist;
            djV->parent = eP;
            if (djV->isQueued()) {
              queue.increase(djV->queueHandle);
            } else {
              djV->setQueueState();
              djV->queueHandle = queue.push(djV);
            }
          }
        }
      }
      curVert->setVisitState();
    }

    return djCont;  // returns the reference to the container within the
                    // subgraph object, if you want to do something with this
                    // data right after
    // On termination, all djNodes in the djContainer in the subgraph will have
    // their distances to rootID set
  }
};

void dijkstra::djVert::setEdgeList(
    const subGraph* graph,
    const std::unordered_map<std::size_t, djVert>& djVertList) {
  for (auto e : data->edgeList) {
    if (graph->inSubGraph(e)) {
      edgeList.emplace_back(&(djVertList.find(e->getTwinEPID())->second), e);
    }
  }
};
}  // namespace vor
#endif
