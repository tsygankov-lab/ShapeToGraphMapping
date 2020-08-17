#include "Node.hpp"
#include "RBT.hpp"

using namespace vorRBT;

// These are mostly traditional red black tree cleanup operations.  Consider
// splitting the cases into seperate functions and inlining for readability

void RBTree::maintainTree_ins(Node *newNode) {
  if (newNode == nullptr) return;  // Why would you call this
  Node *parNode = newNode->parent;
  if (parNode == nullptr) {
    newNode->color = BLACK;
  } else {
    if (parNode->color == RED) {
      auto uncleNode = newNode->getUncle();
      auto gpNode =
          newNode->getGrandParent();  // If uncle is valid so is gpNode
      if (uncleNode && uncleNode->color == RED) {
        parNode->color = BLACK;
        uncleNode->color = BLACK;
        gpNode->color = RED;
        maintainTree_ins(gpNode);
      } else {  // newNode->parent is not null.  gpNode could be. Case 4
        if (gpNode && newNode == newNode->parent->right &&
            newNode->parent == gpNode->left) {
          leftRot(parNode);
          newNode = newNode->left;  // Could be null?
        } else if (gpNode && newNode == newNode->parent->left &&
                   newNode->parent == gpNode->right) {
          rightRot(parNode);
          newNode = newNode->right;
        }

        newNode->parent->color = BLACK;
        if (gpNode) {
          gpNode->color = RED;
          if (newNode == newNode->parent->left) {
            rightRot(gpNode);
          } else {
            leftRot(gpNode);
          }
        }
      }
    }
  }
}

void RBTree::maintainTree_del(Node *deletedArc, Node *deletedEdge) {
  if (deletedArc->parent != deletedEdge) {
    auto deletedArcParent = deletedArc->parent;  // Refactor target
    auto delParentParent =
        deletedArcParent
            ->parent;  // Can't be null, deleted Edge must be above deleted arc
    auto delParentSyb = deletedArcParent->right;  // See above
    auto isLeftChild = false;
    if (delParentParent->left == deletedArcParent) {
      delParentParent->left = delParentSyb;
      delParentSyb->parent = delParentParent;
      isLeftChild = true;
    } else {
      delParentParent->right = delParentSyb;
      delParentSyb->parent = delParentParent;
    }
    deletedEdge->changeData(deletedArcParent->data, deletedArcParent->dataType);
    // deletedEdge->data = deletedArcParent->data;
    // deletedEdge->dataType = deletedArcParent->dataType;
    deletionHandler_Init(delParentSyb, isLeftChild);
    RBTree::deleteNode(deletedArcParent);
  } else {
    auto siblingNode = deletedArc->getSibling();  // Shouldn't be null
    if (siblingNode == nullptr) {
      if (deletedEdge->parent == nullptr) {
        deletionHandler_Init(deletedEdge, false);
      } else {
        deletionHandler_Init(deletedEdge,
                             deletedEdge == deletedEdge->parent->left);
        if (deletedEdge == deletedEdge->parent->left) {
          deletedEdge->parent->left = siblingNode;
        } else {
          deletedEdge->parent->right = siblingNode;
        }
      }
    } else {
      siblingNode->parent = deletedEdge->parent;
      if (deletedEdge->color == BLACK) {
        if (siblingNode->color == RED) {
          siblingNode->color = BLACK;
          if (root == deletedEdge) {
            root = siblingNode;
          } else {  // delEdge->parent is not null if not the root
            if (deletedEdge == deletedEdge->parent->left) {
              siblingNode->parent->left = siblingNode;
            } else {
              siblingNode->parent->right = siblingNode;
            }
          }
        } else {
          if (root == deletedEdge) {
            root = siblingNode;
            deletionHandler_Init(siblingNode, false);
          } else {
            if (deletedEdge == deletedEdge->parent->left) {
              siblingNode->parent->left = siblingNode;
              deletionHandler_Init(siblingNode, true);
            } else {
              siblingNode->parent->right = siblingNode;
              deletionHandler_Init(siblingNode, false);
            }
          }
        }
      } else {  // deletedEdge is NOT the root if it is here
        if (deletedEdge->parent && deletedEdge == deletedEdge->parent->left) {
          siblingNode->parent->left = siblingNode;
        } else {
          siblingNode->parent->right = siblingNode;
        }
      }
    }
    RBTree::deleteNode(deletedEdge);
  }
  RBTree::deleteNode(deletedArc);
}

void RBTree::deletionHandler_Init(Node *node, bool isLeftChild) {
  if (node->parent == nullptr) {
    root = node;
    node->color = BLACK;
  } else {
    auto sNode = node->getSibling();
    if (sNode && sNode->color == RED) {
      node->parent->color = RED;
      sNode->color = BLACK;
      if (isLeftChild) {
        leftRot(node->parent);
      } else {
        rightRot(node->parent);
      }
      sNode = node->getSibling();
    }  // If parent is black, and if the sybling and it's children are black
       // (null == black)
    if (node->parent->color == BLACK &&
        (!sNode || (sNode->color == BLACK &&
                    (!sNode->left || sNode->left->color == BLACK) &&
                    (!sNode->right || sNode->right->color == BLACK)))) {
      if (sNode && sNode->dataType == HALFEDGE) {
        sNode->color = RED;
      }
      if (node->parent->parent)
        deletionHandler_Init(node->parent,
                             node->parent->parent->left == node->parent);
      else
        deletionHandler_Init(node->parent, false);
    } else if (node->parent->color == RED &&
               (!sNode || (sNode->color == BLACK &&
                           (!sNode->left || sNode->left->color == BLACK) &&
                           (!sNode->right || sNode->right->color == BLACK)))) {
      if (sNode && sNode->dataType == HALFEDGE) {
        sNode->color = RED;
      }
      node->parent->color = BLACK;
    } else {
      // This could be !snode || technically but the following relies on sNode
      // existing
      if (sNode && sNode->color == BLACK) {
        if (isLeftChild && (!sNode->right || sNode->right->color == BLACK) &&
            (sNode->left && sNode->left->color == RED)) {
          sNode->color = RED;          // must exist for left to be red
          sNode->left->color = BLACK;  // Must exist to be red
          rightRot(sNode);
          sNode = node->getSibling();
        } else if (!isLeftChild &&
                   (!sNode->left || sNode->left->color == BLACK) &&
                   (sNode->right && sNode->right->color == RED)) {
          sNode->color = RED;
          sNode->right->color = BLACK;
          leftRot(sNode);
          sNode = node->getSibling();
        }
      }
      if (sNode) {
        sNode->color = node->parent->color;
        node->parent->color = BLACK;
        if (isLeftChild) {
          if (sNode->right) sNode->right->color = BLACK;
          leftRot(node->parent);
        } else {
          if (sNode->left) sNode->left->color = BLACK;
          rightRot(node->parent);
        }
      }
    }
  }
}
