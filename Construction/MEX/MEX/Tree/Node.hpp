#pragma once
#include <memory>
#include <vector>

#include "../DataTypes/siteEvent.hpp"
#include "../Math/vecOverrides.hpp"
#include "../Records/halfEdgeRecords.hpp"

#ifdef _BUFFERED_VEC_OPT
#include "../Containers//buffered_vec.hpp"
#endif

#ifdef _STRICT_CHECKING  // Will document flags in voronoiDiagram.cpp
#include <exception>

class NodeParentChildRelationshipList : public std::exception {
  virtual const char *what() const throw() {
    return "Get Sybling was called a node which is not the root, but no "
           "sybling was found.  Tree is corrupted";
  }
} nodeSybTreeCorrupt;
#endif
namespace vorRBT {
enum _NODECOLOR { BLACK, RED };

// Redblack tree nodes which store voronoi data.  The data is held in the form
// of a void* as I do not believe it is appropiate for halfEdges and siteEvents
// to derive from the same base class, and nodes must point to other nodes
// (ruling out templates).  To circumvent this, these store an enum of the
// datatype stored in the node.  When debugging, nodes store a short std::string
// which identifies the type and ID of the object stored in the node.  Could use
// variants (?) or unions to get around the void*, especially since all elements
// will be pointers of the same size.
// Nodes constructor will be indirectly called through buildNode, which will
// manage it's memory
class Node {
 public:
  void *data;  // Can be either a siteEvent or a halfEdge.  Consider using
               // Unions or Variants
  Node *left;
  Node *right;
  Node *parent;
  bool ACTIVE;
  _NODECOLOR color;
  _DATATYPE dataType;  // Use for casting
  std::vector<Node>::size_type
      nodeIndex;  // ID used for debuggin and for indexing in the vector page
                  // allocator

  // All leaf nodes will fill this up at least once.
#ifdef _BUFFERED_VEC_OPT
  vorContainer::buffered_vec<circleEvent *, 1> circEventPointer;
#else
  std::vector<circleEvent *>
      circEventPointer;  // When a node is removed, it must destroy any other
                         // circles which depend on this node (nodes leaves
                         // correspond to arcs - circles events depend on arcs,
                         // not on individual site events)
#endif
#ifdef _DEBUG
  std::string DEBUGID;  // FOR DEBUGGING
  // Constructor for debugging also stores the debugID of the data
  Node(void *obj, _DATATYPE type, _NODECOLOR colorBool = RED,
       Node *leftPtr = nullptr, Node *rightPtr = nullptr,
       Node *parentPtr = nullptr)
      : data(obj),
        left(leftPtr),
        right(rightPtr),
        parent(parentPtr),
        ACTIVE(true),
        color(colorBool),
        dataType(type),
        nodeIndex(0),
        DEBUGID(this->toString()){};
#endif
#ifndef _DEBUG
  // Takes a pointer, the type of the pointer, the color of the node (Defaults
  // to RED), and the initial left node, right node, and parent if these are
  // known
  Node(void *obj, _DATATYPE type, _NODECOLOR colorBool = RED,
       Node *leftPtr = nullptr, Node *rightPtr = nullptr,
       Node *parentPtr = nullptr)
      : data(obj),
        left(leftPtr),
        right(rightPtr),
        parent(parentPtr),
        ACTIVE(true),
        color(colorBool),
        dataType(type),
        nodeIndex(0){};
#endif  // !_DEBUG

  // This is a function used by vectorPageAllocator to reuse data stored in a
  // node.  Essentially is the constructor
  void setNew(void *obj, _DATATYPE type, _NODECOLOR colorBool = RED,
              Node *leftPtr = nullptr, Node *rightPtr = nullptr,
              Node *parentPtr = nullptr) {
    data = obj;
    dataType = type;
    color = colorBool;
    left = leftPtr;
    right = rightPtr;
    parent = parentPtr;
    circEventPointer.clear();  // This circleEventPointer _should_ be empty if a
                               // node has been reused
    ACTIVE = true;
#ifdef _DEBUG
    DEBUGID = this->toString();
#endif
  }

  //'Swap' operation for when a vertex replaces a degenerate event
  void changeData(void *obj, _DATATYPE type) {
    data = obj;
    dataType = type;
#ifdef _DEBUG
    DEBUGID = this->toString();
#endif
  }

  // Function used by vectorPageAllocator to 'delete' a node
  void disable(void) {
    ACTIVE = false;
    data = nullptr;
  }

  // Function used by vectorPageAllocators (mostly it's iterators) to determine
  // if this node is active, or if it is reserved
  bool getState(void) { return ACTIVE; }

  // Function used by vectorPageAllocator to assign a new ID to the node.  The
  // reasons for which this is done is explained in vectorPageAllocator
  void setID(std::vector<Node>::size_type ID) { nodeIndex = ID; };

  // nothing to do...
  void setPTRIDs(){};

  std::vector<Node>::size_type getID() { return nodeIndex; };

  // When findInsert is traversing a node with a halfEdge, edgeNodeIntercept
  // will return the intersect point which it represents.  This checks to make
  // sure the data is a HALFEDGE, and then calls the computeIntersect function
  // of the halfedge
  arrXY edgeNodeGetIntercept(double rad, bool allowShortcuts = true) {
    if (this->dataType == HALFEDGE) {
      return static_cast<halfEdge *>(data)->halfEdge::computeIntersect(
          rad, allowShortcuts);
    } else
      return arrXY({0.0, 0.0});
  };

  // Traverses the tree until it finds the first parent to the 'right(left)' of
  // this node (for which this node is a left(right) descendent).  Also returns
  // the distance traversed.  Node* is nullptr if no right parents exist.  Can
  // be made recursive, but why
  std::pair<Node *, int> getRightParent(void) {
    bool isLeftChild = false;
    int dist = 0;
    Node *rightPar = this;
    while (!isLeftChild && rightPar->parent != nullptr) {
      isLeftChild = (rightPar == rightPar->parent->left);
      rightPar = rightPar->parent;
      dist++;
    }
    if (!isLeftChild) {
      return std::make_pair(nullptr, dist);
    }
    return std::make_pair(rightPar, dist);
  };

  std::pair<Node *, int> getLeftParent(void) {
    bool isRightChild = false;
    int dist = 0;
    Node *leftPar = this;
    while (!isRightChild && leftPar->parent != nullptr) {
      isRightChild = (leftPar == leftPar->parent->right);
      leftPar = leftPar->parent;
      dist++;
    }
    if (!isRightChild) {
      return std::make_pair(nullptr, dist);
    }
    return std::make_pair(leftPar, dist);
  };

  // Traverses the left (right) most branch of a node until it hits a leaf
  // (which holds no children).
  Node *getLeftMostChild(void) {
    auto curNode = this;
    while (curNode->left) {
      curNode = curNode->left;
    }
    return curNode;
  };

  Node *getRightMostChild(void) {
    auto curNode = this;
    while (curNode->right) {
      curNode = curNode->right;
    }
    return curNode;
  };

  // Returns the sybling node based on if it is the left or right child.  If it
  // is the root node, then it returns nullptr.  If it is a leaf node, it
  // returns a nullptr or throws an exception with strict checking
  Node *getSibling(void) {
    if (this->parent == nullptr)
      return nullptr;
    else if (this->parent->left == this)
      return this->parent->right;
    else if (this->parent->right == this)
      return this->parent->left;
    else {
#ifdef _STRICT_CHECKING
      throw nodeSybTreeCorrupt;
#endif
      return nullptr;  // std::cout << "Sybling not found for node.  Parent
                       // -
    }                  // child relationship lost";
  };

  // Gets the leaf to the left(right) of this node.
  Node *getLowerNode(void) {
    Node *prevNode = this;
    Node *newParent = prevNode->parent;
    if (!newParent) {
      return nullptr;
    }
    while (newParent->parent && newParent->right != prevNode) {
      prevNode = newParent;
      newParent = newParent->parent;
    }
    newParent = newParent->left;
    if (newParent == prevNode || !newParent) {
      return nullptr;
    } else {
      while (newParent->dataType != VERTEX && newParent->right) {
        newParent = newParent->right;
      }
      return newParent;
    }
  };

  Node *getHigherNode(void) {
    auto prevNode = this;
    auto newParent = prevNode->parent;
    if (!newParent) {
      return nullptr;
    }
    while (newParent->parent && newParent->left != prevNode) {
      prevNode = newParent;
      newParent = newParent->parent;
    }
    newParent = newParent->right;
    if (newParent == prevNode || !newParent) {
      return nullptr;
    } else {
      while (newParent->dataType != VERTEX && newParent->left) {
        newParent = newParent->left;
      }
      return newParent;
    }
  };

  Node *getParent(void) { return this->parent; };

  Node *getGrandParent(void) {
    if (this->parent == nullptr || this->parent->parent == nullptr) {
      return nullptr;
    }
    return this->parent->parent;
  };

  Node *getUncle(void) {
    Node *GP = this->getGrandParent();
    if (GP == nullptr) {
      return nullptr;
    }

    // GP will be null if parent is null
    if (this->parent == GP->left) {
      return GP->right;
    } else {
      return GP->left;
    }
  };

  siteEvent *getSiteEvent() {
    if (this->dataType != HALFEDGE && this->dataType != CIRCLEEVENT) {
      return static_cast<siteEvent *>(this->data);
    }
    return nullptr;
  }

  halfEdge *getHalfEdge() {
    if (this->dataType == HALFEDGE) {
      return static_cast<halfEdge *>(this->data);
    }
    return nullptr;
  }

#ifdef _DEBUG
  std::string toString(void) {
    if (dataType == VERTEX) {
      return static_cast<vertexEvent *>(data)->toString();
    } else if (dataType == LINE) {
      return static_cast<lineEvent *>(data)->toString();
    } else if (dataType == HALFEDGE) {
      return static_cast<halfEdge *>(data)->toString();
    } else if (dataType == DEGENERATE) {
      return static_cast<degenEvent *>(data)->toString();
    }
    return "";
  }
#endif
};
};  // namespace vorRBT
