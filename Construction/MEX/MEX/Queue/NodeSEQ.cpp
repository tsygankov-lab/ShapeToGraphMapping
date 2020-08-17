#include "SEQTree.hpp"
#include <iostream>
using namespace vorQueue;
// Heapqueue for siteEvent objects.
// std::vector<std::unique_ptr<NodeSEQ>> NodeContainer;
// std::queue<std::vector<NodeSEQ>::size_type> NodeRecycleInd;
NodeSEQ *heapQueue::add(siteEvent *siteObj) {
  //	if (_LOGGING) {
  //		logStream << "Adding siteEvent (ID " << siteObj->objectIndex << ",
  //rad " << siteObj->rad << ", pos " << siteObj->pos[0] << "," <<
  //siteObj->pos[1] << ") to Queue...\n\r";
  //	}
  auto newNode = NodeContainer.add(siteObj);
  /*NodeSEQ* newNode;
  if (NodeRecycleInd.empty()) {
          if (_LOGGING) {
                  logStream << "Creating new node\n\r";
          }

          NodeContainer.emplace_back(std::make_unique<NodeSEQ>(siteObj,
  NodeContainer.size()));
          newNode = NodeContainer.back().get();
  }
  else {
          auto index = NodeRecycleInd.top();
          NodeRecycleInd.pop();
          if (_LOGGING) {
                  logStream << "Recycling old nodeID" << index << "\n\r";
          }
          newNode = NodeContainer.at(index).get();
          newNode->left = nullptr;
          newNode->right = nullptr;
          newNode->parent = nullptr;
          newNode->data = siteObj;
          newNode->ACTIVE = true;
          siteObj->SEQptr = newNode;
  }*/
  if (isempty()) {
    // if (_LOGGING) {
    //	logStream << "This is a root node\n\r";
    //}
    this->numNodes++;
    this->root = newNode;
    this->lastNode = newNode;
  } else {
    // if (_LOGGING) {
    //	logStream << "Inserting into tree\n\r";
    //}
    this->numNodes++;
    NodeSEQ *newParent = findLeaf(this->lastNode, 0);
    newParent->assignChild(newNode);
    this->lastNode = newNode;
    // if (_LOGGING) outputTree(this->root, 0);
    this->upHeap(newNode);
    //	if (_LOGGING) {
    //	if (!newNode->parent) logStream << "Node became the root\n\r";
    //	else logStream << "Node has a new parent (ParID: " <<
    //newNode->parent->nodeID << ", ParRAD: " << newNode->parent->data->rad <<
    //") \n\r";
    //	}
  }
  // if (_LOGGING && _VERBOSE) outputTree(this->root);
  return newNode;
};

void heapQueue::deleteNode(NodeSEQ *node) {
  //	if (_LOGGING) {
  //		logStream << "Removing node nodeid " << node->nodeID << " rad " <<
  //node->data->rad << ", pos " << node->data->pos[0] << "," <<
  //node->data->pos[1] << "\n\r";
  //	}
  NodeContainer.remove(node);
  // node->ACTIVE = false;
  // node->data = nullptr;
  // NodeRecycleInd.push(node->nodeID);
}

void heapQueue::downHeap(NodeSEQ *nodeObj) {
  NodeSEQ *lesserChild = nodeObj->smallerChild();
  if (lesserChild != nullptr) {
    if (nodeObj->greaterThan(lesserChild)) {
      nodeObj->swap(lesserChild);
      heapQueue::downHeap(lesserChild);
    }
  }
};

void heapQueue::upHeap(NodeSEQ *nodeObj) {
  if (nodeObj->parent != nullptr) {
    if (!nodeObj->greaterThan(nodeObj->parent)) {
      nodeObj->swap(nodeObj->parent);
      heapQueue::upHeap(nodeObj->parent);
    }
  }
};

siteEvent *heapQueue::poll(void) {
  if (this->isempty()) {
    return nullptr;
  } else {
    siteEvent *data = this->root->data;
    --numNodes;
    if (this->isempty()) {
      heapQueue::deleteNode(this->root); // Destructor just needs to delete the
                                         // node class.  All the things it
                                         // points to could be valid
      this->root = nullptr;
      return data;
    } else {
      NodeSEQ *newLastNode;
      if (this->lastNode->parent->left == this->lastNode) {
        this->lastNode->parent->left = nullptr;
        newLastNode = this->heapQueue::findLeftLeaf(this->lastNode, 0);
      } else {
        this->lastNode->parent->right = nullptr;
        newLastNode = this->heapQueue::findLeftLeaf(this->lastNode, 1);
      }
      // NodeSEQ* oldLastNode = this->lastNode;

      this->root->NodeSEQ::swap(this->lastNode);
      heapQueue::deleteNode(this->lastNode);
      this->lastNode = newLastNode;
      this->heapQueue::downHeap(this->root);
    }
    //	if (_LOGGING && _VERBOSE) outputTree(this->root);
    return data;
  }
};

void heapQueue::validateData() {
  int index = 0;
  for (auto &vec : NodeContainer.collector)
    for (auto &e : *vec) {
      if (e.data &&
          (e.data->objType != VERTEX && e.data->objType != CIRCLEEVENT))
        std::cout << "???";
      ++index;
    }
  return;
}

siteEvent *heapQueue::remove(NodeSEQ *rmNode) {
  if (rmNode == nullptr) {
    return nullptr;
  }
  siteEvent *data = rmNode->data;
  if (this->root == rmNode) {
    return this->poll();
  } else {
    this->numNodes--;
    NodeSEQ *swapNode = this->lastNode;
    if (this->lastNode->parent->left == this->lastNode) {
      this->lastNode->parent->left = nullptr;
      this->lastNode = this->heapQueue::findLeftLeaf(this->lastNode, 0);
    } else {
      this->lastNode->parent->right = nullptr;
      this->lastNode = this->heapQueue::findLeftLeaf(this->lastNode, 1);
    }

    if (swapNode == rmNode) {
      heapQueue::deleteNode(rmNode);
    } else {
      bool keyCheck = swapNode->greaterThan(rmNode);
      swapNode->swap(rmNode);
      if (keyCheck) {
        this->downHeap(rmNode);
      } else {
        this->upHeap(rmNode);
      }
      heapQueue::deleteNode(swapNode);
    }
  }
  // if (_LOGGING && _VERBOSE) outputTree(this->root);
  return data;
};

NodeSEQ *heapQueue::findLeftLeaf(NodeSEQ *curNode, bool isRightChild) {
  // Uses a loop as that was what was done in matlab
  NodeSEQ *prevNode = curNode;
  curNode = curNode->parent;
  if (!isRightChild && curNode) {
    while (curNode->parent && curNode->right != prevNode) {
      prevNode = curNode;
      curNode = curNode->parent;
    }
  }
  if (isRightChild || curNode->right == nullptr || curNode->right == prevNode) {
    if (curNode->left) {
      curNode = curNode->left;
      while (curNode->right) {
        curNode = curNode->right;
      }
      while (curNode->left) {
        curNode = curNode->left;
      }
    }
  } else if (curNode->right) {
    while (curNode->right) {
      curNode = curNode->right;
    }
    while (curNode->left) {
      curNode = curNode->left;
    }
  }

  return curNode;
};

NodeSEQ *heapQueue::findLeaf(NodeSEQ *prevNode, bool descending) {
  // Going down -> left until find a node without two children
  if (descending) {
    // Going down and to the left
    if (prevNode->left == nullptr || prevNode->right == nullptr) {
      return prevNode;
    } else {
      return heapQueue::findLeaf(prevNode->left, 1);
    }
  } else {
    // Go up until you find your parent for which you (and by relation, the
    // starting node) is the left descendent OR the root
    NodeSEQ *parentNode = prevNode->parent;
    if (parentNode == nullptr) {
      // You are at the root
      if (prevNode->left == nullptr) {
        // Root is missing a left child - this is the left most leaf
        return prevNode;
      } else {
        // You were the right most node at the start.  You now need the leftmost
        // leaf (Depth grown)
        return heapQueue::findLeaf(prevNode->left, 1);
      }
    } else if (parentNode->left == prevNode) {
      // You have found your right ascendant
      if (parentNode->right == nullptr) {
        // There is no right leaf.  This is the new last neaf
        return parentNode;
      } else {
        // There is a valid branch to the right.  Go right and start descending
        return heapQueue::findLeaf(parentNode->right, 1);
      }
    } else {
      return heapQueue::findLeaf(parentNode, 0);
    } // keep ascending
  }
};

NodeSEQ *heapQueue::findRightMostLeaf(void) { // Argument is this->root
  if (this->isempty()) {
    return nullptr;
  }
  NodeSEQ *cur = this->root;
  while (cur->right != nullptr) {
    cur = cur->right;
  }
  while (cur->left != nullptr) {
    cur = cur->left;
  }
  return cur;
};

//#include <iostream>
//#include <fstream>
//#include <ctime>
// void heapQueue::startLogging(const char* path) {
// logStream.open(path, std::ostream::out);
//_LOGGING = true;
//}

// void heapQueue::endLogging(void) {
//	logStream.close();
//	_LOGGING = false;
//}
/*
#include <iomanip>
void heapQueue::outputTree(NodeSEQ* node, int indent)
{
        if (node != NULL) {
                if (node->left) outputTree(node->left, indent + 4);
                if (node->right) outputTree(node->right, indent + 4);
                if (indent) {
                        std::cout << std::setw(indent) << ' ';
                }
                std::cout << node->data->rad << "\n ";
        }
}*/