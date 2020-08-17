#pragma once
// Will return to this later. Deal with matlab implementation for now.
#ifndef _RECORDOBJ
#define _RECORDOBJ
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../MEX/Math/vecOverrides.hpp"
#include "../MEX/precisionChecks.hpp"
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
		}
		else {
			return (sinth +
				(double)(costh < _EPSILON) * (2.0 * (1.0 - std::abs(sinth))));
		}
		return 0;
	}
}
// Base vert and edge types.
namespace vor {

struct vert;
struct edge;

// helper functions for navigating graphs (maybe move there)

struct vert {
 private:
  std::size_t myID;
  // see if inputs need to be passed...
 public:
  std::list<std::size_t> edgeIDs;
  arrXY pos;
  std::list<edge*> edgeList;
  std::array<long, 3> colorPattern;
  bool inf;
  long vertCoorID;
  double rad;

  // May make some of these in loop
  // Assumes matlab data
  vert(double* coordinates, std::size_t ID, double rad, double color1,
       double color2, double color3, double vertCoorID, double* edgeIDMat,
       std::size_t row, std::size_t numObj)
      : pos(arrXY{{coordinates[0], coordinates[1]}}),
        myID(ID - 1),
        rad(rad),
        colorPattern({color1, color2, color3}),
        vertCoorID(vertCoorID) {
    for (std::size_t i = 0; i < 4; ++i) {
      auto index = i * numObj + row;
      if (edgeIDMat[index] == 0) break;
      edgeIDs.push_back(edgeIDMat[index] - 1);
    }
  };

  std::size_t getID() { return myID; }

  // Map - for subgraph support.  Key = myID, which is MatlabID - 1
  // If the edge does not exist, then it will not be added to the edge list!
  template <class edgeFull = edge>
  void setPTRs(std::unordered_map<std::size_t, edgeFull>& allEdges) {
    for (auto& eID : edgeIDs) {
      auto edgeTest = allEdges.find(eID);
      if (edgeTest != allEdges.end()) {
        edgeList.push_back(&(*edgeTest).second);
      }
    }
  }

  std::pair<vert*, edge*> moveCW(long color);

  std::pair<vert*, edge*> moveCCW(long color);

  // void setEdgePtrs(std::vector<edge> &edgeList)
};
struct edge {
  std::size_t myID;
  std::size_t twinID;
  std::size_t originID;
  edge* twin;
  vert* origin;
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
        inf(inf){};

  std::size_t getID() { return myID; }

  template <class vertFull = vert, class edgeFull = edge>
  void setPTRs(std::unordered_map<std::size_t, vertFull>& allVerts,
               std::unordered_map<std::size_t, edgeFull>& allEdges) {
    twin = &(*allEdges.find(twinID)).second;
    origin = &(*allVerts.find(originID)).second;
  }

  vert* getOtherEP() { return twin->origin; }

  bool isBridge() { return color == twin->color; }
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
}  // namespace vor

namespace vor {
// Below deals with creation of 'subgraphs'.
template <class vertFull = vert>
struct vertSub;
template <class edgeFull = edge>
struct edgeSub;

template <class vertSt = vertSub<vert>, class edgeSt = edgeSub<edge>>
struct treeStruct {
  std::size_t ID;
  int state;
  vertSt* parent;
  std::list<vertSt*> children;
  std::list<edgeSt*> childEdges;

  treeStruct(std::size_t rootID) : ID(rootID), state(0), parent(nullptr) {};
};

template <class vertFull = vert>
struct vertSub {
  static_assert(std::is_base_of<vert, vertFull>::value,
                "edgeSt must derive from edgeSub");

  vertFull* data;
  std::list<edgeSub*> EL;
  std::unordered_map<std::size_t, treeStructOut<vertSub>> treeStructs;
  // std::unordred_map<std::size_t,treeOut<vertSub>> -> reserve(numTips)
  // treeOut -> root ID (key), parent* vertSub, std::vector<vertSub*> child;
  vertSub(vertFull& base) : data(&base){};
  vertSub(vertFull* base) : data(base){};

  // Copy only the raw data.  Edge list will have to be updated separately.
  // vertSub(const vertSub& other) : data(other.data) {};
  vertSub(vertSub* other) : data(other->data){};

  template <class edgeSt = edgeSub<edge>>
  virtual void setPTRs(
      std::unordered_map<std::size_t, edgeSt>& subGraphEdgePtrs) {
    for (auto& eID : data->edgeIDs) {
      auto edgeTest = subGraphEdgePtrs.find(eID);
      if (edgeTest != subGraphEdgePtrs.end()) {
        EL.push_back(&(edgeTest->second));
      }
    }
  }

  void reserveNumSearches(int count) { treeStructs.reserve(count); }

  std::size_t getID() { return data->getID(); }

  double getRad() { return data->rad; }

  bool isInf() { return data->inf; }

  //template<class edgeFull = edge>
  //std::pair<vertSub*, edgeSub<edgeFull>*> moveCW(long color);

//  template<class edgeFull = edge>
//  std::pair<vertSub*, edgeSub<edgeFull>*> moveCCW(long color);
};

template <class edgeFull = edge>
struct edgeSub {
  static_assert(std::is_base_of<edge, edgeFull>::value,
                "edgeSt must derive from edgeSub");

  edgeFull* data;
  edgeSub* twin;
  vertSub* origin;

  edgeSub(edgeFull& base) : data(&base){};
  edgeSub(edgeFull* base) : data(base){};
  // edgeSub(const edgeSub& other) : data(other.data) {};
  edgeSub(edgeSub* other) : data(other->data){};

  template <class vertSt = vertSub<vert>, class edgeSt = edgeSub<edge>>
  virtual void setPTRs(
      std::unordered_map<std::size_t, vertSt>& subGraphVertPtrs,
      std::unordered_map<std::size_t, edgeSt>& subGraphEdgePtrs) {
    assert(subGraphEdgePtrs.count(data->twinID));
    assert(subGraphVertPtrs.count(data->originID));

    twin = &(subGraphEdgePtrs.find(data->twinID)->second);
    origin = &(subGraphVertPtrs.find(data->originID)->second);
  }

  std::size_t getID() { return data->getID(); }

  double getDist() { return data->dist; }

  long getColor() { return data->color; }

  bool isBridge() { return data->isBridge(); }

  edgeSub* getOtherEP() { return twin->origin; }
};

// Can use different vert and edge containers as desired.  They must implement
// getID()
/*template <class vertSt = vertSub, class edgeSt = edgeSub,
                typename std::enable_if<
                std::is_base_of<vertSub, vertSt>::value &&
                std::is_base_of<edgeSub, edgeSt>::value>::type = false>*/
template <class vertSt = vertSub<vert>, class edgeSt = edgeSub<edge>>
struct subGraph {
  static_assert(std::is_base_of<vertSub, vertSt>::value,
                "vertSt must derive from vertSub");
  static_assert(std::is_base_of<edgeSub, edgeSt>::value,
                "edgeSt must derive from edgeSub");
  subGraph* parent;
  std::list<subGraph*> children;

  int subGraphID;
  int depth;
  std::unordered_map<std::size_t, vertSt> subGraphVerts;
  std::unordered_map<std::size_t, edgeSt> subGraphEdges;

  template <class vertFull = vert, class edgeFull = edge>
  subGraph(std::vector<vertFull> vertCont, std::vector<edgeFull> edgeCont,
           int ID = 0, subGraph* parent = nullptr)
      : parent(parent),
        subGraphID(ID),
        depth(parent ? (parent->depth + 1) : 0) {
    subGraphVerts.reserve(vertCont.size());
    subGraphEdges.reserve(edgeCont.size());
    for (auto e : edgeCont) {
      subGraphEdges.emplace(e.getID(), e);
    }
    for (auto v : vertCont) {
      subGraphVerts.emplace(v.getID(), v);
    }

    // Attach edgelist ptrs for subgraph verts, edges
    setPtrs();

    if (parent) {
      parent->children.emplace_back(this);
    }
  }

  template <class vertFull = vert, class edgeFull = edge>
  subGraph(std::vector<vertFull*> vertCont, std::vector<edgeFull*> edgeCont,
           int ID = 0, subGraph* parent = nullptr)
      : parent(parent),
        subGraphID(ID),
        depth(parent ? (parent->depth + 1) : 0) {
    subGraphVerts.reserve(vertCont.size());
    subGraphEdges.reserve(edgeCont.size());
    for (auto e : edgeCont) {
      subGraphEdges.emplace(e->getID(), e);
    }
    for (auto v : vertCont) {
      subGraphVerts.emplace(v->getID(), v);
    }
    if (parent) {
      parent->children.emplace_back(this);
    }
    setPtrs();
  }

  // Maybe it would be better to bypass the vector<ptrs> here?
  subGraph(std::vector<vertSt*> vertCont, std::vector<edgeSt*> edgeCont,
           int ID = 0, subGraph* parent = nullptr)
      : parent(parent),
        subGraphID(ID),
        depth(parent ? (parent->depth + 1) : 0) {
    subGraphVerts.reserve(vertCont.size());
    subGraphEdges.reserve(edgeCont.size());
    for (auto e : edgeCont) {
      subGraphEdges.emplace(e->getID(), e);
    }
    for (auto v : vertCont) {
      subGraphVerts.emplace(v->getID(), v);
    }
    if (parent) {
      parent->children.emplace_back(this);
    }
    setPtrs();
  }

  subGraph(std::vector<vertSt*> vertCont, int ID = 0,
           subGraph* parent = nullptr)
      : parent(parent),
        subGraphID(ID),
        depth(parent ? (parent->depth + 1) : 0) {
    subGraphVerts.reserve(vertCont.size());
    subGraphEdges.reserve(3 * vertCont.size());
    for (auto v : vertCont) {
      subGraphVerts.emplace(v->getID(), v);
    }

    for (auto v : vertCont) {
      for (auto e : v->EL) {
        if (epInSubGraph(e)) subGraphEdges.emplace(e->getID, e);
      }
    }
    if (parent) {
      parent->children.emplace_back(this);
    }
    setPtrs();
  }

  void setPtrs() {
    for (auto& v : subGraphVerts) {
      v.second.setPTRs<edgeSt>(subGraphEdges);
    }
    for (auto& e : subGraphEdges) {
      e.second.setPTRs<vertSt, edgeSt>(subGraphVerts, subGraphEdges);
    }
  }

  void plannedSearches(int count) {
    for (auto v : subGraphVerts) {
      v.second.reserveNumSearches(count);
    }
  }

  bool inSubGraph(edgeSt* e) { return subGraphEdges.count(e->getID()); }
  bool epInSubGraph(edgeSt* e) {
    return (subGraphEdges.count(e->origin->getID()) > 0 &&
            subGraphEdges.count(e->getOtherEP()->getID()) > 0);
  }
  bool inSubGraph(vertSt* v) { return subGraphVerts.count(v->getID()); }

  void dijkstraSearch(vertSt* root);

  //Not using auto because the templates are messing with VS
  void dijkstraSearch(std::size_t rootID) {
	  std::pair<std::size_t, vertSt> node = subGraphVerts.find(rootID);
	  if(node.second != subGraphVerts.end()) dijkstraSearch(&(node.second));
  };
};

/*template<class vertFull = vert, class edgeFull = edge>
//std::pair<vertSub<vertFull>*, edgeSub<edgeFull>*> vertSub<vertFull>::moveCW(long color) {
  vertSub* nextVert = nullptr;
  edgeSub* nextEdge = nullptr;
  for (auto e : EL) {
    if (e->getColor() == color && e->twin->getColor() != color) {
      nextVert = e->getOtherEP();
      nextEdge = &(*e);
      break;
    }
  }
  return std::make_pair(nextVert, nextEdge);
}
template<class vertFull = vert, class edgeFull = edge>
std::pair<vertSub<vertFull>*, edgeSub<edgeFull>*> vertSub<vertFull>::moveCCW(long color) {
  vertSub* nextVert = nullptr;
  edgeSub* nextEdge = nullptr;
  for (auto e : EL) {
    if (e->getColor() != color && e->twin->getColor() == color) {
      nextVert = e->getOtherEP();
      nextEdge = e->twin;
      break;
    }
  }
  return std::make_pair(nextVert, nextEdge);
}*/
}  // namespace vor
// vertsubMAM and edgeSubMAM hold a value called 'marked' for if they have
// been reached by a major axis

namespace vor {
namespace mam {

struct vertMAM : vert {
  int _mark = 0;

  vertMAM(double* coordinates, std::size_t ID, double rad, double color1,
          double color2, double color3, double vertCoorID, double* edgeIDMat,
          std::size_t row, std::size_t numObj)
      : vert(coordinates, ID, rad, color1, color2, color3, vertCoorID,
             edgeIDMat, row, numObj){};
};

struct edgeMAM : edge {
  int _mark = 0;

  edgeMAM(std::size_t thisID, std::size_t twinID, std::size_t originID,
          int edgeType, long color, double dist, double cpx, double cpy,
          double dirx, double diry, bool isInf)
      : edge(thisID, twinID, originID, edgeType, color, dist, cpx, cpy, dirx,
             diry, isInf){};

  void setPTRs(std::unordered_map<std::size_t, vertMAM>& allVerts,
               std::unordered_map<std::size_t, edgeMAM>& allEdges) {
    edge::setPTRs<vertMAM, edgeMAM>(allVerts, allEdges);
  };
};

// namespace mam
struct vertSubMAM : vertSub<vertMAM> {
  int mark = 0;

  vertSubMAM(vertMAM& base) : vertSub(base), mark(0){};
  vertSubMAM(vertMAM* base) : vertSub(base), mark(0){};
  vertSubMAM(vertSub* other) : vertSub(other), mark(0){};
};

struct edgeSubMAM : edgeSub<edgeMAM> {
  int mark = 0;

  edgeSubMAM(edgeMAM& base) : edgeSub(base), mark(0){};
  edgeSubMAM(edgeMAM* base) : edgeSub(base), mark(0){};
  edgeSubMAM(edgeSub* other) : edgeSub(other), mark(0){};

  virtual void setPTRs(
      std::unordered_map<std::size_t, vertSubMAM>& subGraphVertPtrs,
      std::unordered_map<std::size_t, edgeSubMAM>& subGraphEdgePtrs) {
    edgeSub::setPTRs<vertSubMAM, edgeSubMAM>(subGraphVertPtrs,
                                             subGraphEdgePtrs);
  }
};

struct subGraphMAM : subGraph<vertSubMAM, edgeSubMAM> {
  std::vector<vertSubMAM*> tips;
  std::vector<vertSubMAM*> majAxTips;

  std::unordered_map<std::pair<std::size_t, std::size_t>, double>
      pairWiseDistances;  // pairwise dist between vert A and B if
                          // calculated

  std::unordered_map<std::size_t, std::pair<vertSubMAM*, double>>
      maxDistPairMap;  // Pair of max distance and other vert for vert with
                       // key
                       // A

  subGraphMAM(std::vector<vertMAM> vertCont, std::vector<edgeSubMAM> edgeCont,
              std::vector<std::size_t> tipIDs, int ID = 0,
              subGraphMAM* parent = nullptr)
      : subGraph(vertCont, edgeCont, ID, parent) {
    for (auto ind : tipIDs) {
      auto tipObj = subGraphVerts.find(ind);
      if (tipObj != subGraphVerts.end()) tips.push_back(&(tipObj->second));
    }
  };

  subGraphMAM(std::vector<vertMAM> vertCont, std::vector<edgeSubMAM> edgeCont,
              int ID = 0, subGraphMAM* parent = nullptr)
      : subGraph(vertCont, edgeCont, ID, parent) {
    if (parent) {
      for (auto prevtip : parent->tips) {
        auto tipObj = subGraphVerts.find(prevtip->getID());
        if (tipObj != subGraphVerts.end()) tips.push_back(&(tipObj->second));
      }
    }
  };

};  // namespace mam
}  // namespace mam
};  // namespace vor

struct djNodeComparator {
	inline bool operator()(const djNode* a, const djNode* b) const;
};

struct djNode {
	bool visited = false;
	bool isTarget;
	bool isRoot;
	bool enteredQueue = false;
	double dist;
	long parID;
	long vertID;
	std::vector<long> neighborID;
	std::vector<double> edgeDist;
	std::vector<long> childID;
	boost::heap::fibonacci_heap<djNode*, boost::heap::compare<djNodeComparator>>::handle_type queuePtr;
	djNode::djNode(long vertID) : visited(false), dist(std::numeric_limits<double>::infinity()), parID(-1l), vertID(vertID), queuePtr(nullptr), isTarget(false), isRoot(false), enteredQueue(false) {};

	void setAsRoot() {
		dist = 0.0;
		isRoot = true;
	}

	void setAsTarget() {
		isTarget = true;
	}

	//Now -> check if corresponds to a vertCoorID, unless root
	//void restrictEdges() {
	//	neighborID.clear();
	//	edgeDist.clear();
	//}
	//boost expects maxqueue so we define our 'lower priority' comparator as being a larger distance
	//bool operator<(const djNode &b) {
	//	return dist > b.dist; //Boost uses a max heap, so this must be greater than
	//}
};

//djNode needs to know djNodeComparator exists and has an operator() function which knows about djNode, but operator() depends on the contents of djNode... hence why this is written like this.
bool djNodeComparator::operator()(const djNode *a, const djNode *b) const {
	return a->dist > b->dist;
}
//Format: myID, myDegree indexNeighbor....
template<class vertSt, class edgeSt>
void vor::subGraph<vertSt, edgeSt>::dijkstraSearch(vertSt* root) {
	boost::heap::fibonacci_heap<djNode*, boost::heap::compare<djNodeComparator>> queue;

	for (std::pair<std::size_t, vertSt> v : subGraphVerts) {
		v.second.treeStructs.emplace(root->getID())
	}

	int targetsReached = 0;

	for (int i = 0; i < roots.size(); i++) {
		events[roots[i]].enteredQueue = true;
		events[roots[i]].queuePtr = queue.push(&events[roots[i]]);
	}
	while (!queue.empty() || (!completeTraversal && targetsReached < numTargets)) {
		auto curVert = queue.top();
		if (curVert->isTarget) {
			++targetsReached;
		}
		queue.pop();
		for (int i = 0; i < curVert->neighborID.size(); i++) {
			auto vertID = curVert->neighborID[i];
			if (!events[vertID].visited) {
				if (events[vertID].dist > curVert->dist + curVert->edgeDist[i]) {
					events[vertID].dist = curVert->dist + curVert->edgeDist[i];
					events[vertID].parID = curVert->vertID;
					if (events[vertID].enteredQueue) {
						queue.increase(events[vertID].queuePtr); //Defines 'increase' as increasing priority
					}
					else {
						events[vertID].enteredQueue = true;
						events[vertID].queuePtr = queue.push(&events[vertID]);
					}
				}
			}
		}
		curVert->visited = true;
	}
	//events is directly modified
	return;// events;
}

#endif  //_RECORDOBJ
