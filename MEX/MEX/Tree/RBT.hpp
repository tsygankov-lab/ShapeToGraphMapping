#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef RBT
#define RBT

//#include "vorHeader.hpp" //Maybe remove and place in c file...

// Review what we actually use... remove the ones we don't
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

#include "../Containers/vectorPageAllocator.h"
#include "../DataTypes/siteEvent.hpp"
#include "../Math/basicMathAndGeometry.hpp"
#include "../Math/circleCalculators.hpp"
#include "../Math/vecOverrides.hpp"
#include "../Queue/SEQTree.hpp"
#include "../precisionChecks.hpp"

#include "Node.hpp"
// class AttemptToDeleteNullNode : public std::exception {
//  virtual const char *what() const throw() {
//    return "Program attempted to delete a node, but the node pointer was
//    null";
//  }
//} nullNodeDelete;

class AttemptToDeleteNullNodeData : public std::exception {
  virtual const char *what() const throw() {
    return "Program deleted a node which contained null data (Node has been "
           "deleted already).  This often happens with invalid inputs (IE "
           "intersecting lines).  This exception cannot be disabled with "
           "_SKIP_CHECKS.";
  }
};

namespace vorQueue {
class heapQueue;
}
struct halfEdgeRecords;
struct vorVert;

// vorRBT contains all functions and structures which manipulate the tree.  The
// tree is effectively a map of the edges in the tree, which is used to sort the
// arcs of the beachfront in a clockwise ordering. Internal nodes are halfEdges.
// Leaves are siteEvents
namespace vorRBT {

// This is the primary structure of the Voronoi Diagram which processes inputs
// (popped out from a queue) in order to find all voronoi vertices with nlogn
// complexity.  This is done by knowing all possible 'nearest' left and right
// neighbors at any time.
class RBTree {
 private:
  // Reusable vectors for internal calculations.  If we ever implemented
  // parallel sweep circles, they would use seperate RBTree instances, so this
  // is okay.
  typedef struct {
    std::vector<vorRBT::Node *> NodeList;
  } gabStore;
  typedef struct {
    std::vector<Node *> lineSpawnEvents;
    std::vector<Node *> EPNodeList;
    std::vector<std::pair<halfEdge *, halfEdge *>> spawnEdgeList;
    std::vector<Node *> spawnNodeList;
    std::vector<std::pair<Node *, std::size_t>> spawnEdgeNodeList;
    std::vector<Node *> queue;
    std::vector<size_t> queueLowInd;
    std::vector<size_t> queueHighInd;
    std::vector<size_t> queueIndex;
  } mlsStore;
  mlsStore mlsHelper;
  gabStore gabHelper;

 public:
  // VectorPage'Allocator' is a container of multiple 'vectors' (more
  // accurately, arrays, as they will never realloc).  This allows the Node
  // objects, and other objects with an unpredictable size requirement
  // (degenNode) to have a dynamically resizable container which does not
  // invalidate pointers.  When the container overflows, it creates a new vector
  // of blocksize.
  vorContainer::vectorPageAllocator<Node> NodeContainer;
  vorContainer::vectorPageAllocator<degenEvent> DegenContainer;
  vorContainer::vectorPageAllocator<circleEvent> CircleContainer;
  // std::vector<vertexEvent> VertexContainer; //refactor -> store in
  // halfEdgeRecords std::vector<lineEvent> LineContainer; //see above

  // Mostly a debug feature.  Iterates by one everytime a new object is
  // processed from the queue.  This is stored in created objects
  long eventLog = 0;
  Node *root;
  long numNodes;
  arrXY cent;  // Usually stored by the object, but may make more sense to use
               // with the tree
  double lastRad = 0;
  // For Toroidal Surfaces
#ifdef _TOROIDAL
  bool toroidalMode = false;
  bool canEarlyTerminate = false;
  long remainingNonMirrored = 0;
  long numNonMirrored;
#endif
  // Has to insert and remove objects from queue, so it holds a reference to an
  // externally prepared queue
  vorQueue::heapQueue &queue;

  // Records stores the output data.  This is created externally, and stored by
  // reference
  halfEdgeRecords &records;

  // Constructor needs the center of this sweep circle, the Queue and Records
  // struct, and optional parameters to tune how frequently memory is allocated
#ifndef _TOROIDAL
  RBTree(arrXY cent, vorQueue::heapQueue &queueSource,
         halfEdgeRecords &recordStruct, int blockReserveSize = 1000,
         int degenBlockReserveSize = 50, int circBlockReserveSize = 100)
      : NodeContainer(blockReserveSize),
        DegenContainer(degenBlockReserveSize),
        CircleContainer(circBlockReserveSize),
        eventLog(0),
        root(nullptr),
        numNodes(0),
        cent(cent),
        queue(queueSource),
        records(recordStruct) {
    gabHelper.NodeList.reserve(16);
    mlsHelper.lineSpawnEvents.reserve(16);
    mlsHelper.EPNodeList.reserve(16);
    mlsHelper.spawnEdgeList.reserve(16);
    mlsHelper.spawnNodeList.reserve(16);
    mlsHelper.spawnEdgeNodeList.reserve(16);
    mlsHelper.queue.reserve(16);
    mlsHelper.queueLowInd.reserve(16);
    mlsHelper.queueHighInd.reserve(16);
    mlsHelper.queueIndex.reserve(16);
  };
  RBTree(const RBTree &) = delete;
#else
  RBTree(arrXY cent, vorQueue::heapQueue &queueSource,
         halfEdgeRecords &recordStruct, long numNonMirroredNodes,
         int blockReserveSize = 1000, int degenBlockReserveSize = 50,
         int circBlockReserveSize = 100)
      : NodeContainer(blockReserveSize),
        DegenContainer(degenBlockReserveSize),
        CircleContainer(circBlockReserveSize),
        eventLog(0),
        root(nullptr),
        numNodes(0),
        cent(cent),
        queue(queueSource),
        records(recordStruct),
        numNonMirrored(numNonMirroredNodes) {
    gabHelper.NodeList.reserve(16);
    mlsHelper.lineSpawnEvents.reserve(16);
    mlsHelper.EPNodeList.reserve(16);
    mlsHelper.spawnEdgeList.reserve(16);
    mlsHelper.spawnNodeList.reserve(16);
    mlsHelper.spawnEdgeNodeList.reserve(16);
    mlsHelper.queue.reserve(16);
    mlsHelper.queueLowInd.reserve(16);
    mlsHelper.queueHighInd.reserve(16);
    mlsHelper.queueIndex.reserve(16);
  };
#endif
  // As the node memory is managed by the red black tree, buildNode is used to
  // access the 'constructor' for Node
  Node *buildNode(void *data, _DATATYPE dataType, _NODECOLOR color = RED,
                  Node *left = nullptr, Node *right = nullptr,
                  Node *parent = nullptr);

  // Removes Nodes from the tree.  Also removes degen events if those are
  // removed
  void deleteNode(Node *node) {
//#ifndef UNSAFE  TO BE IMPLEMENTED
//    if (!node) throw(nullNodeDelete);
//    if (!node->data) throw(nullNodeDataDelete);
//#endif
#ifdef _TOROIDAL
    if (node->dataType != HALFEDGE &&
        static_cast<siteEvent *>(node->data)->objectIndex < numNonMirrored) {
      --remainingNonMirrored;
    }
#endif
    if (!node->data) {
      throw(AttemptToDeleteNullNodeData());
    }
    if (node->dataType == DEGENERATE) {
      static_cast<degenEvent *>(node->data)->eventLog = eventLog;  // debug
      DegenContainer.remove(static_cast<degenEvent *>(node->data));
    }
    NodeContainer.remove(node);
    --numNodes;
  };

  // For the first insert only.  Constructs a node which becomes the root
  Node *insertRoot(void *data, _DATATYPE dataType);

  // Searches through the redblack tree to find which 'arc' the new event lies
  // above.  Internal node to the red black trees store voronoi edges, which
  // corresponds to the intersects between two arcs.  The arcs at the
  // 'beachfront' do not necessarily correspond to the angle of inserted
  // elements, as elements closer to the sweep circle are 'closest' to a smaller
  // portion of the circle compared to a point at the center
  vorRBT::Node *findInsert(siteEvent *newEvent);

  // When a node is deleted, destroy circles makes deletes and removes from
  // queue all circle events which depend on this element
  void destroyCircles(Node *node);

  // Handle____Event process elements from the queue, and call subfunctions
  // which adds new nodes (for lines and verts) or remove nodes (For circle
  // events).
  void handleCircleEvent(circleEvent *circ);  // Most of runtime

  void handleLineEvent(lineEvent *line);

  void handleVertexEvent(vertexEvent *vert);

  // Helper functions for handleVertexEvent and handleLineEvent.
  void vertex_splitArc(vertexEvent *vert, Node *oldNode);

  void line_splitArc(lineEvent *line);  // For when the tree is empty

  void line_splitArc(lineEvent *line, Node *oldNode);

  void endPointInsert(vertexEvent *vert);

  // Called by vertex_splitarc or endPointInsert if a processed vertex is also
  // the 'start' of one or more lines
  void multiLineSpawner(vertexEvent *vert, Node *oldNode, bool degenerateFlag);

  void reserveLineContainer(std::size_t count) {
    this->records.inputLineContainer.reserve(count);
  }

  void reserveVertexContainer(std::size_t count) {
    this->records.inputVertexContainer.reserve(count);
  }

  template <typename... Ts>
  void addVertex(Ts &&... args) {
    this->records.inputVertexContainer.emplace_back(std::forward<Ts>(args)...);
    // Forwards arguments to inputVertexContainer. If they are not correct for
    // the constructor, then the constructor throws
  }

  template <typename... Ts>
  vertexEvent &addAndReturn_Vertex(Ts &&... args) {
    addVertex(std::forward<Ts>(args)...);
    return this->records.inputVertexContainer.back();
  }

  vertexEvent &getVertex(std::size_t ind) {
    return this->records.inputVertexContainer.at(ind);
  }

  template <typename... Ts>
  void addLine(Ts &&... args) {
    this->records.inputLineContainer.emplace_back(std::forward<Ts>(args)...);
    // Forwards arguments to inputVertexContainer. If they are not correct for
    // the constructor, then the constructor throws
  }

  template <typename... Ts>
  lineEvent &addAndReturn_Line(Ts &&... args) {
    this->addLine(std::forward<Ts>(args)...);
    return this->records.inputLineContainer.back();
  }

  lineEvent &getLine(std::size_t ind) {
    return this->records.inputLineContainer.at(ind);
  }

  void registerInputLinePair(vertexEvent *vertA, vertexEvent *vertB,
                             std::size_t objectID) {
    auto cpOut = vorGeo::closestPoint_TRUNC(vertA->pos, vertB->pos, this->cent);

    // beachTree.LineContainer.emplace_back(cpOut.closeXY_Trunc, cpOut.closeXY,
    //                                     beachTree.cent, vertA, vertB,
    //                                     ++objectID, 0l);
    auto lineObj =
        this->addAndReturn_Line(cpOut.closeXY_Trunc, cpOut.closeXY, this->cent,
                                vertA, vertB, objectID, 0l);
    // lineEvent& lineObj = beachTree.LineContainer.back();
    // vertA->setEndpointAsLineEvent(lineObj);
    // beachTree.LineContainer.emplace_back(lineObj);
    // lineEvent& lineObj_Twin = beachTree.LineContainer.back();
    auto lineObj_Twin = this->addAndReturn_Line(lineObj);

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
      this->queue.add(&lineObj);
    }
    // Color and faceID settings will go here
    auto faceA = this->records.createFace(&lineObj, vertA->voronoiFace->color);
    auto faceB =
        this->records.createFace(&lineObj_Twin, vertB->voronoiFace->color);
  }

  // Called by endPointInsert when a processed vertex must terminate two or more
  // lines. When degenerate events are registered, a pointer to the node
  // containing said event is stored within the vertex object.  These are sorted
  // such that the first degenEvent is the 'left most' and the last degenEvent
  // is the 'right most.'  This function finds ALL nodes between these two
  // nodes, removes them from the tree, and pins their edges to the voronoi
  // vertex which will exist on top of the endpoint.  This will violate the
  // assumption that 'all voronoi vertices have a degree of three.'  It is
  // possible, and possibly preferrible, to 'split' these vertices in such a way
  // that each vertex has a degree of 3 (one or two edges of which connect to
  // other split vertices).  If there are any errors in the tree ordering, this
  // will very likely lead to null pointer dereferences.  the pair contains the
  // voronoiVertex which these edges have been paired to, and the 'wraparound'
  // node if the collection of nodes wraps around the right/left side of the
  // tree
  std::pair<vorVert *, vorRBT::Node *> multiLineConvergenceHandler(
      vertexEvent *data, Node *startNode, Node *endNode);

  // Standard RBT insert routine
  void maintainTree_ins(Node *newNode);

  // Deletions always occur in pairs of a deleted 'leaf' and a deleted 'edge'
  // (and the edges are what we're really sorting in these trees).
  // Maintaintree_del will remove these elements from the tree, and shift things
  // around to balance the tree.  deletionHandler_Init is the helper function
  // which performs the traditional RBT routines
  void maintainTree_del(Node *deletedArc, Node *deletedEdge);

  void deletionHandler_Init(Node *node, bool isLeftChild);

  // Rotations actually move the nodes - some objects store pointers to the
  // containers, so we cannot just change the data
  void leftRot(Node *node) {
    Node *rChild = node->right;
    if (rChild) {
      Node *rlChild = rChild->left;
      node->right = rlChild;
      if (rlChild) {
        rlChild->parent = node;
      }
      rChild->left = node;
      rChild->parent = node->parent;
      node->parent = rChild;  // Executed regardless
      if (root == node) {
        root = rChild;
      } else {
        if (rChild->parent->left == node) {
          rChild->parent->left = rChild;
        } else {
          rChild->parent->right = rChild;
        }
      }
    }
  };

  void rightRot(Node *node) {
    Node *lChild = node->left;
    if (lChild != nullptr) {
      Node *lrChild = lChild->right;
      node->left = lrChild;
      if (lrChild) {
        lrChild->parent = node;
      }
      lChild->right = node;
      lChild->parent = node->parent;
      node->parent = lChild;  // Executed regardless
      if (root == node) {
        root = lChild;
      } else {
        if (lChild->parent->left == node) {
          lChild->parent->left = lChild;
        } else {
          lChild->parent->right = lChild;
        }
      }
    }
  };

  // Search functions.  treeEntries_... are mostly for debugging
  Node *getAllBetween(Node *leftNode, Node *rightNode);

  Node *getFirstLeaf(void);

  Node *getLastLeaf(void);

  Node *getFirstEdge(void);

  Node *getLastEdge(void);

  std::vector<Node *> treeEntries_All();

  std::vector<Node *> treeEntries_Leaf();

  std::vector<Node *> treeEntries_Edge();

  // circFilter L, R, LR, and LRC searches for potential circle events given
  // pairs of nodes, and passes them to checker functions.  L, R, and C
  // indicates the potential centers for removed circles.  filterL and filterR
  // should be inlined
  void circFilterLR(Node *left, Node *cent, Node *right);

  void circFilterL(Node *left, Node *cent);

  void circFilterR(Node *cent, Node *right);

  void circFilterLCR(Node *left, Node *cent, Node *right);

  // findCircleEvents takes three nodes, and passes the data contained by these
  // nodes to the correct functions to determine if 1) these can form a circle
  // event and 2) what this circle would be. PPP, LPP, LLP, LLL indicate the
  // number and type of elements involved in this computation.
  void findCircleEvents(Node *left, Node *cent, Node *right);

  void circleFilterPPP(std::array<vertexEvent *, 3> vertVec,
                       std::array<Node *, 3> nodeVec);

  void circleFilterLPP(std::array<vertexEvent *, 2> vertVec, lineEvent *lineVec,
                       std::array<Node *, 3> nodeVec);

  void circleFilterLLP(vertexEvent *vertVec, std::array<lineEvent *, 2> lineVec,
                       std::array<Node *, 3> nodeVec);

  void circleFilterLLL(std::array<lineEvent *, 3> lineVec,
                       std::array<Node *, 3> nodeVec);

  // Takes the x, y, and rad of a circle, the list of nodes involved, and if
  // this is a 'pinch event' between two converging lines, and constructs and
  // adds a circle to the queue
  void registerCircle(vorGeo::circFlags circ,
                      std::array<vorRBT::Node *, 3> nodeVec);

  // Helper function to determine if a line and another line or point can
  // reasonably form a circle event.  This is determine by considering the
  // 'side' of the line(s) and position with respect to the other element.  This
  // is equivalent to determining if a pair of points form a right turn in
  // fortune's algorithm
  bool circleEventLPXValidator(const lineEvent &line, const vertexEvent &point);

  bool circleEventLLXValidator(const lineEvent &line1, const lineEvent &line2,
                               const int &sharedEPFlag);
  bool circleEventLLXValidator_NoShared(const lineEvent &line1,
                                        const lineEvent &line2, bool l2Left);

  void DEBUG_runIteration() {
    if (!this->queue.isempty()) {
      auto next = this->queue.poll();
      this->lastRad = next->rad;
      this->eventLog += 1;
      if (next->objType == VERTEX) {
        this->handleVertexEvent(static_cast<vertexEvent *>(next));
      } else if (next->objType == LINE) {
        this->handleLineEvent(static_cast<lineEvent *>(next));
      } else if (next->objType == CIRCLEEVENT) {
        this->handleCircleEvent(static_cast<circleEvent *>(next));
      }
    }
  }

  void DEBUG_runNIterations(int n) {
    for (int i = 0; i < n; ++i) {
      this->DEBUG_runIteration();
    }
  }

  void DEBUG_runForDistance(double dist) {
    auto curDist = this->lastRad;
    auto endDist = curDist + dist;
    while (curDist < endDist && !this->queue.isempty() &&
           this->getNextRad() < endDist) {
      DEBUG_runIteration();
      curDist = this->lastRad;
    }
    this->lastRad = endDist;
  }

  void DEBUG_finishVoronoi() {
    while (!this->queue.isempty()) {
      DEBUG_runIteration();
    }
    this->attachInfiniteBisectors(lastRad * 1.5);

    this->records
        .finalizeRecordValues();  // halfEdges use ptrs to set their dist,
                                  // dir, and control point. To do afterwards,
                                  // halfEdges would need access to the record
                                  // structure (doable)
    this->records.moveVertsAndEdgesToVector();
  }

  double getNextRad() {
    if (!this->queue.isempty()) {
      return this->queue.peek()->rad;
    }
    return lastRad;
  }

  double getLastRad() { return lastRad; }

#ifdef _DEBUG
  void print2DUtil(Node *root, int space) {
    if (space > 100) {
      throw std::runtime_error("Infinite Loop");
    }
    // Base case
    if (root == NULL) return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    if (root->right == root) throw std::runtime_error("Infinite Loop");
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    std::cout << "\n";                                  // printf("\n");
    for (int i = 10; i < space; i++) std::cout << " ";  // (" ");
    if (root->color == BLACK)
      std::cout << "B-" << root->toString()
                << "\n";  // ("%s\n", root->toString());
    else
      std::cout << "R-" << root->toString() << "\n";

    // Process left child
    if (root->left == root) throw std::runtime_error("Infinite Loop");
    print2DUtil(root->left, space);
  }

  std::string printLeaves(void) {
    auto nextNode = getFirstLeaf();
    std::string returnOut = std::string("LEAF NODES: ") + nextNode->toString();
    while (nextNode = nextNode->getHigherNode()) {
      returnOut += std::string(", ") + nextNode->toString();
    }
    return returnOut;
  }
#endif

  // Post processing.  If any elements remain in the tree, they extend off
  // infinitely.  This creates new vertices to 'pin' these bisectors to,
  // normally set at 1.5 * the radius of the sweep circle
  void attachInfiniteBisectors(double rad) {
    auto edgeNodes = treeEntries_Edge();
    for (auto &e : edgeNodes) {
      auto XY = e->edgeNodeGetIntercept(rad);
      auto edge = static_cast<halfEdge *>(e->data);
      auto edgeColora = edge->adjacentFace->siteObject;
      auto edgeColorb = edge->twin->adjacentFace->siteObject;

      auto nuVert = records.createVertex(XY, 0, edgeColora, edgeColorb,
                                         edgeColora, eventLog, false);
      nuVert->infVert = true;
      nuVert->addEdge(edge);
      edge->INFINITE = true;
      edge->twin->INFINITE = true;
    }
  }

  // debug
  void dataValidator(void);
};
}  // namespace vorRBT

#endif
