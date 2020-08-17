#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef SEQTREE
#define SEQTREE
#include <memory>
#include <stack>
#include <string>
#include <vector>
#ifndef _GCC_49_COMP
#include <fstream>
#endif
#include "../Containers/vectorPageAllocator.h"
#include "../DataTypes/siteEvent.hpp"
// Add prepare heap and heapify for O(n) insertion
// Prepare heap takes inputs and builds a nodeContainer.  Heapify constructs an
// initial heap
// We swap data pointers... maybe make search operations simple (x/2) operations
// on the NodeContainer Vector
namespace vorQueue {
class NodeSEQ {
 public:
  // Consider converting to std::unique_ptr<NodeSEQ>
  // Not necessary since operations are basic enough.
  NodeSEQ *left;
  NodeSEQ *right;
  NodeSEQ *parent;

  std::vector<NodeSEQ>::size_type nodeID;

  siteEvent *data;
  bool ACTIVE;
  NodeSEQ(void)
      : left(nullptr),
        right(nullptr),
        parent(nullptr),
        nodeID(0),
        data(nullptr),
        ACTIVE(false) {
    // Null Node
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    data = nullptr;
  }

  NodeSEQ(siteEvent *siteData)
      : left(nullptr),
        right(nullptr),
        parent(nullptr),
        nodeID(0),
        data(siteData),
        ACTIVE(true) {
    siteData->SEQptr = this;
  }

  void setNew(siteEvent *siteData) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = siteData;
    this->ACTIVE = true;
    siteData->SEQptr = this;
  }

  void setNew(void) {
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->data = nullptr;
    this->ACTIVE = true;
  }

  void disable(void) {
    ACTIVE = false;
    data = nullptr;
  }
  bool getState() { return ACTIVE; }

  std::vector<NodeSEQ>::size_type getID() { return nodeID; }

  void setID(std::vector<NodeSEQ>::size_type ID) { nodeID = ID; }

  bool greaterThan(NodeSEQ *n2) { return (this->getKey() > n2->getKey()); }

  double getKey(void) { return data->rad; }

  void swap(NodeSEQ *n2) {
    auto tData = this->data;
    this->data = n2->data;
    n2->data = tData;
    this->data->SEQptr = this;
    n2->data->SEQptr = n2;
  }

  void assignChild(NodeSEQ *child) {
    if (left == nullptr)
      left = child;
    else
      right = child;
    child->parent = this;
  }

  NodeSEQ *smallerChild(void) {
    bool leftNull = this->left == nullptr;
    bool rightNull = this->right == nullptr;
    if (leftNull && rightNull) {
      return nullptr;
    } else if (leftNull && !rightNull) {
      return this->right;
    } else if (rightNull && !leftNull) {
      return this->left;
    } else {
      if (this->left->greaterThan(this->right)) {
        return this->right;
      } else {
        return this->left;
      }
    }
  }
};
// template<class T>
// HeapQueue Implementation for the site event class
class heapQueue {
 public:
  NodeSEQ *root;
  NodeSEQ *lastNode;
  // std::vector<std::unique_ptr<NodeSEQ>> NodeContainer;
  // std::stack<std::vector<NodeSEQ>::size_type> NodeRecycleInd;
  vorContainer::vectorPageAllocator<NodeSEQ> NodeContainer;
  // std::ofstream logStream;

  long numNodes;

  bool _LOGGING = false;
  bool _VERBOSE = false;
  heapQueue(int blockPageSize = 1000)
      : root(nullptr),
        lastNode(nullptr),
        NodeContainer(blockPageSize),
        numNodes(0) {}

  heapQueue(const heapQueue &) = delete;
  void setRoot(NodeSEQ *nodeObj) { nodeObj->parent = nullptr; }

  NodeSEQ *add(siteEvent *siteEvent);
  void deleteNode(NodeSEQ *node);
  void downHeap(NodeSEQ *nodeObj);
  void upHeap(NodeSEQ *nodeObj);
  bool isempty(void) { return numNodes == 0; };
  siteEvent *peek(void) { return root->data; };
  siteEvent *poll(void);
  siteEvent *remove(NodeSEQ *rmNode);
  NodeSEQ *findLeftLeaf(NodeSEQ *curentNode, bool isRightChild);
  NodeSEQ *findLeaf(NodeSEQ *prevNode, bool descending);  // Change to loop?
  NodeSEQ *findRightMostLeaf(void);  // Argument is this->root

  // void logToFile(std::string info);
  // void startLogging(const char* path);
  //	void endLogging(void);

  // void outputTree(NodeSEQ* node, int indent = 0);

  void validateData(void);
};
}  // namespace vorQueue
#endif  // !SEQTREE
