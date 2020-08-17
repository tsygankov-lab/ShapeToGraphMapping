#include <iostream>
#include <vector>
#include "boost/heap/fibonacci_heap.hpp"
struct djNode;

struct djNodeComparator {
  inline bool operator()(const djNode *a, const djNode *b) const;
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
  boost::heap::fibonacci_heap<
      djNode *, boost::heap::compare<djNodeComparator>>::handle_type queuePtr;
  djNode::djNode(long vertID)
      : visited(false),
        dist(std::numeric_limits<double>::infinity()),
        parID(-1l),
        vertID(vertID),
        queuePtr(nullptr),
        isTarget(false),
        isRoot(false),
        enteredQueue(false){};

  void setAsRoot() {
    dist = 0.0;
    isRoot = true;
  }

  void setAsTarget() { isTarget = true; }

  void restrictEdges() {
    neighborID.clear();
    edgeDist.clear();
  }
  // boost expects maxqueue so we define our 'lower priority' comparator as
  // being a larger distance bool operator<(const djNode &b) { 	return dist >
  // b.dist; //Boost uses a max heap, so this must be greater than
  //}
};

// djNode needs to know djNodeComparator exists and has an operator() function
// which knows about djNode, but operator() depends on the contents of djNode...
// hence why this is written like this.
bool djNodeComparator::operator()(const djNode *a, const djNode *b) const {
  return a->dist > b->dist;
}
// Format: myID, myDegree indexNeighbor....
void dijkstraSearch(std::vector<djNode> &events, std::vector<long> roots,
                    size_t numTargets, bool completeTraversal) {
  boost::heap::fibonacci_heap<djNode *, boost::heap::compare<djNodeComparator>>
      queue;

  int targetsReached = 0;

  for (int i = 0; i < roots.size(); i++) {
    events[roots[i]].enteredQueue = true;
    events[roots[i]].queuePtr = queue.push(&events[roots[i]]);
  }
  while (!queue.empty() ||
         (!completeTraversal && targetsReached < numTargets)) {
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
            queue.increase(
                events[vertID]
                    .queuePtr);  // Defines 'increase' as increasing priority
          } else {
            events[vertID].enteredQueue = true;
            events[vertID].queuePtr = queue.push(&events[vertID]);
          }
        }
      }
    }
    curVert->visited = true;
  }
  // events is directly modified
  return;  // events;
}
