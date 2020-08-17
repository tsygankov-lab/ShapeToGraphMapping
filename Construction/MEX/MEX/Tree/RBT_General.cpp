#include "Node.hpp"
#include "RBT.hpp"

using namespace vorRBT;
// The functions below search and return single nodes or collections of nodes

// Gets all Node* between the left and right nodes.  Can wrap around the list if
// necessary.
// When the list must be wrapped around, wrapAroundNode will point towards the
// first leaf
// after wrapping around the list.  Else it is null
// Pattern:  Start at leftNode, move up and to the right.  Add this node.
// Descend down right. Descend from this point down and to the left until the
// bottom is reached.  Add node.  Repeat

// To prevent realloc, the vector is stored by the tree in a private variable.
Node *RBTree::getAllBetween(Node *leftNode, Node *rightNode) {
  Node *wrapAroundNode = nullptr;
  auto &nodeCollector = gabHelper.NodeList;
  nodeCollector.clear();
  // std::vector<Node*> nodeCollector;
  while (leftNode != rightNode) {
    leftNode =
        std::get<0>(leftNode->getRightParent());  // Right parent is 'parent for
                                                  // which I am at some point a
                                                  // left child' (left child <->
                                                  // right parent... possibly
                                                  // something to refactor)
    if (!leftNode) {
      leftNode = getFirstEdge();
      wrapAroundNode = getFirstLeaf();
    }
    nodeCollector.push_back(leftNode);
    leftNode = leftNode->right;
    if (leftNode == rightNode) {
      return wrapAroundNode;
    } else {
      while (leftNode->left) {
        leftNode = leftNode->left;
      }
      if (leftNode != rightNode) {
        nodeCollector.push_back(leftNode);
      }
    }
  }
  // We have exitted the loop after reaching at our target
  return wrapAroundNode;
}

Node *RBTree::getFirstLeaf() {
  if (root == nullptr) {
    return root;
  }
  Node *cur = root;
  while (cur->left && cur->dataType != VERTEX) {
    cur = cur->left;
  }  // Second check arguably redundant
  return cur;
}

Node *RBTree::getLastLeaf() {
  if (root == nullptr) {
    return root;
  }
  Node *cur = root;
  while (cur->right && ((cur->dataType) != VERTEX)) {
    cur = cur->right;
  }
  return cur;
}

Node *RBTree::getFirstEdge() { return getFirstLeaf()->parent; }

Node *RBTree::getLastEdge() { return getLastLeaf()->parent; }

std::vector<Node *> RBTree::treeEntries_All() {
  std::vector<Node *> nodeCollector;
  Node *leftNode = getFirstLeaf();
  Node *rightNode = getLastLeaf();
  nodeCollector.push_back(leftNode);
  while (leftNode != rightNode) {
    leftNode =
        std::get<0>(leftNode->getRightParent());  // Right parent is 'parent for
                                                  // which I am at some point a
                                                  // left child' (left child <->
                                                  // right parent... possibly
                                                  // something to refactor)
    nodeCollector.push_back(leftNode);
    leftNode = leftNode->right;
    if (leftNode == rightNode) {
      nodeCollector.push_back(leftNode);
      return nodeCollector;
    } else {
      while (leftNode->left) {
        leftNode = leftNode->left;
      }
      nodeCollector.push_back(leftNode);
    }
  }
  return nodeCollector;
}

// Could likely trim but this call is mostly debugging...
std::vector<Node *> RBTree::treeEntries_Leaf() {
  std::vector<Node *> nodeCollector;
  Node *leftNode = getFirstLeaf();
  Node *rightNode = getLastLeaf();
  nodeCollector.push_back(leftNode);
  while (leftNode != rightNode) {
    leftNode =
        std::get<0>(leftNode->getRightParent());  // Right parent is 'parent for
                                                  // which I am at some point a
                                                  // left child' (left child <->
                                                  // right parent... possibly
                                                  // something to refactor)
    if (leftNode->dataType != HALFEDGE) {
      nodeCollector.push_back(leftNode);
    }
    leftNode = leftNode->right;
    if (leftNode == rightNode) {
      if (leftNode->dataType != HALFEDGE) {
        nodeCollector.push_back(leftNode);
      }
      return nodeCollector;
    } else {
      while (leftNode->left) {
        leftNode = leftNode->left;
      }
      if (leftNode->dataType != HALFEDGE) {
        nodeCollector.push_back(leftNode);
      }
    }
  }
  return nodeCollector;
}

std::vector<Node *> RBTree::treeEntries_Edge() {
  std::vector<Node *> nodeCollector;
  Node *leftNode = getFirstLeaf();
  Node *rightNode = getLastLeaf();
  while (leftNode != rightNode) {
    leftNode =
        std::get<0>(leftNode->getRightParent());  // Right parent is 'parent for
                                                  // which I am at some point a
                                                  // left child' (left child <->
                                                  // right parent... possibly
                                                  // something to refactor)
    if (leftNode->dataType == HALFEDGE) {
      nodeCollector.push_back(leftNode);
    }
    leftNode = leftNode->right;
    if (leftNode == rightNode) {
      if (leftNode->dataType == HALFEDGE) {
        nodeCollector.push_back(leftNode);
      }
      return nodeCollector;
    } else {
      while (leftNode->left) {
        leftNode = leftNode->left;
      }
      if (leftNode->dataType == HALFEDGE) {
        nodeCollector.push_back(leftNode);
      }
    }
  }
  return nodeCollector;
}
