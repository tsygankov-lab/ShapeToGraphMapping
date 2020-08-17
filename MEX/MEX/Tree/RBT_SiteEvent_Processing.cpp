#include "Node.hpp"
#include "RBT.hpp"

#include "../DataTypes/siteEvent.hpp"
#include "../Queue/SEQTree.hpp"
#include "../Records/halfEdgeRecords.hpp"
#include "../precisionChecks.hpp"

#if defined(_DEBUG) || \
    !defined(_SKIP_CHECKS)  // Toroidal has to do this check too
#include <exception>

// These exceptions were made for a potential treeValidator function.  Some are
// not yet implemented. CircleValidationFailtureOnInsert is risky.  The number
// of transformations causes lost of precision.  When the values involved are
// very large, its possible for this to be *relatively* insignificant, but may
// fail this check.  Need a better way to track expected floating point errors
class CircleValidationFailureOnInsert : public std::exception {
  virtual const char* what() const throw() {
    return "The circle should have been invalidated prior to insertion";
  }
} circValExcept_STRICT;

void validateCircle_STRICT(arrXY circXY, double rad, const siteEvent* A,
                           const siteEvent* B, const siteEvent* C) {
  auto distA = A->distToPoint_STRICT(circXY);
  auto distB = B->distToPoint_STRICT(circXY);
  auto distC = C->distToPoint_STRICT(circXY);
  auto tolFact = std::fmax(A->maxPos(), std::fmax(B->maxPos(), C->maxPos()));
  if (!_ALMOST_EQUAL(rad, distA, tolFact * 1000000000) ||
      !_ALMOST_EQUAL(rad, distB, tolFact * 1000000000) ||
      !_ALMOST_EQUAL(rad, distC, tolFact * 1000000000)) {
    // throw circValExcept_STRICT;
  }
  auto oriA = A->orientationCheck(circXY);
  auto oriB = B->orientationCheck(circXY);
  auto oriC = C->orientationCheck(circXY);
  if (!oriA || !oriB || !oriC) {
    throw circValExcept_STRICT;
  }
}

class ActiveNodeContainsNullData : public std::exception {
  virtual const char* what() const throw() {
    return "A node is listed as Active, but has no data";
  }
} nodeNullDataExcept;

class TreeOrderingValidationFailure : public std::exception {
  virtual const char* what() const throw() {
    return "When checking the tree, a node was located in the incorrect "
           "position";
  }
} nodeOrderingExcept;

class CircleEventNullQueuePtr : public std::exception {
  virtual const char* what() const throw() {
    return "A Circle event was found in the tree, but this circle is not in "
           "the Queue";
  }
} circNullSEQExcept;

class CircleFailedInvalidation : public std::exception {
  virtual const char* what() const throw() {
    return "A Circle Event is in the Queue, but should have been invalidated";
  }
} circFailedInvalidateExcept;
#endif
// vorRBT contains all classes and functions which manipulate the tree
namespace vorRBT {
Node* RBTree::buildNode(void* data, _DATATYPE dataType,
                        vorRBT::_NODECOLOR color, Node* left, Node* right,
                        Node* parent) {
  ++numNodes;
#if defined(_DEBUG) || defined(_TOROIDAL)  // Toroidal has to do this check too
  auto tmp = NodeContainer.add(data, dataType, color, left, right, parent);
  if (dataType != HALFEDGE) {  // make a node history struct for debugging. list
                               // of 'events' in each node
    auto tmpSE = static_cast<siteEvent*>(tmp->data);
    tmpSE->eventLog = eventLog;
#ifdef _TOROIDAL
    if (tmpSE->objectIndex < numNonMirrored) {
      if (!canEarlyTerminate)
        canEarlyTerminate =
            true;              // Must process one non-mirrored node before
                               // the early termination rule kicks in...
                               // in-case the center is outside of the bounds
      ++remainingNonMirrored;  // When building a node which is in the
                               // non-mirrored space, increment the count.
    }
#endif
  }
  return tmp;
#else
  return NodeContainer.add(data, dataType, color, left, right, parent);
#endif
}

inline Node* RBTree::insertRoot(void* data, _DATATYPE dataType) {
  root = RBTree::buildNode(
      data, dataType, vorRBT::BLACK);  // All other elements default to nullptr
  return root;
}

// Called internally by maintainTree_del or arc split
// Works fine if leftIntEdge is the overlap point... but not otherwise
vorRBT::Node* RBTree::findInsert(siteEvent* newEvent) {
  auto firstEdgePointer =
      getFirstEdge();  // Computes a vector from the left most intersection to
                       // the measured intersect.  Keeps track of this pointer
                       // to ensure the vector isn't drawn to self

  // All intersection points are pushed to the edge of the sweep circle.  A
  // chord is drawn from the left most intersection point to the intersection
  // point of this new element.  The orientation of the new point with respect
  // to this vector determines if you must move left or right in the tree
  auto leftIntPoint =
      firstEdgePointer->edgeNodeGetIntercept(newEvent->rad) - cent;
  leftIntPoint =
      newEvent->rad / vorGeo::norm(leftIntPoint) * leftIntPoint + cent;
  auto curNode = root;

  // Special case - the new point and the intersection point are effecitvely the
  // same.  We cannot search the tree as the orientation check will always
  // return 0 (collinear with chord).  But, since we know that these objects
  // exactly overlap, we already know where in the tree this object should be
  // inserted
  // - Failed on overlap
  if (_ALMOST_EQUAL(leftIntPoint[0], newEvent->pos[0],
                    1000 * (newEvent->rad + 1)) &&
      _ALMOST_EQUAL(leftIntPoint[1], newEvent->pos[1],
                    1000 * (newEvent->rad + 1))) {
#ifndef _UNSAFE
    auto leftDesc = firstEdgePointer->left->getRightMostChild();
    auto rightDesc = firstEdgePointer->right->getLeftMostChild();

    auto clLR =
        vorGeo::checkLeftOf(cent, static_cast<siteEvent*>(leftDesc->data)->pos,
                            newEvent->pos, 10000);
    if (clLR == 0)
      return leftDesc;  // If this point matches the right point, go down that
                        // path.  Else, use the default
    else
      return rightDesc;
      // auto crLR =
      //    vorGeo::checkLeftOf(cent,
      //    static_cast<siteEvent*>(leftDesc->data)->pos,
      //                        newEvent->pos, 10000);
#else
    curNode = firstEdgePointer->left->getRightMostChild();
    return curNode;
#endif
  }
  while (curNode->dataType == HALFEDGE) {
    // Special case - the node we are at IS the left most node.  To see which
    // child we should move to, create a chord with respect to the right most
    // edge node
    if (curNode == firstEdgePointer) {
      auto intPoint = getLastEdge()->edgeNodeGetIntercept(newEvent->rad) - cent;
      intPoint = newEvent->rad / vorGeo::norm(intPoint) * intPoint + cent;
      auto LR = vorGeo::checkLeftOf(intPoint, leftIntPoint, newEvent->pos,
                                    _SIMILARITY_THRESHOLD_VERY_FINE);
      if (LR == 0) {
#ifndef _UNSAFE
        // LR == 0 -> intPoint == leftIntPoint || newEvent->pos == one of the
        if (_ALMOST_EQUAL(intPoint[0], leftIntPoint[0],
                          _SIMILARITY_THRESHOLD_ROUGH) &&
            _ALMOST_EQUAL(intPoint[1], leftIntPoint[1],
                          _SIMILARITY_THRESHOLD_ROUGH)) {
          auto LR = vorGeo::checkLeftOf(newEvent->cent, intPoint, newEvent->pos,
                                        _SIMILARITY_THRESHOLD_VERY_FINE);
          if (LR == 0) {
            curNode = curNode->left->getRightMostChild();
          } else if (LR < 0) {
            curNode = curNode->right;
          } else if (LR > 0) {
            curNode = curNode->left;
          }
        } else {
          curNode = curNode->left->getRightMostChild();
        }
#else
        curNode = curNode->left->getRightMostChild();
#endif
      } else if (LR < 0) {
        curNode = curNode->right;
      } else if (LR > 0) {
        curNode = curNode->left;
      }
    } else {
      auto intPoint = curNode->edgeNodeGetIntercept(newEvent->rad) - cent;
      intPoint = newEvent->rad / vorGeo::norm(intPoint) * intPoint + cent;
      auto LR = vorGeo::checkLeftOf(leftIntPoint, intPoint, newEvent->pos,
                                    _SIMILARITY_THRESHOLD_VERY_FINE);
      if (LR < 0) {
        curNode = curNode->right;
      } else if (LR > 0) {
        curNode = curNode->left;
      } else if (LR == 0) {
        // As this is a circle, this can be caused by colinearity between the
        // intersection points and the new event (IE overlap with one endpoint),
        // or a bad input in which the drawn chord has a distance of *almost*
        // zero.  This attempts to verify what case this is by drawing a vector
        // from the center circle to the two points used to generate the chord

#ifndef _UNSAFE
        if (_ARRAY2_ALMOST_EQUAL(intPoint, newEvent->pos,
                                 newEvent->rad * _SIMILARITY_THRESHOLD_FINER)) {
          auto leftDesc = curNode->left->getRightMostChild();
          auto rightDesc = curNode->right->getLeftMostChild();

          auto clLR = vorGeo::checkLeftOf(
              cent, static_cast<siteEvent*>(leftDesc->data)->pos, newEvent->pos,
              _SIMILARITY_THRESHOLD_VERY_FINE);
          if (clLR == 0) {
            // the leftNode is the same node
            return leftDesc;
          } else {
            return rightDesc;
          }
        } else if (_ALMOST_EQUAL(intPoint[0], leftIntPoint[0], 2.0) &&
                   _ALMOST_EQUAL(intPoint[1], leftIntPoint[1], 2.0)) {
          auto LRCheck = vorGeo::checkLeftOf(cent, intPoint, newEvent->pos,
                                             _SIMILARITY_THRESHOLD_VERY_FINE);
          if (LRCheck > 0)
            curNode = curNode->right;
          else
            curNode = curNode->left;
        } else {
          auto LRCheck = vorGeo::checkLeftOf(cent, intPoint, newEvent->pos,
                                             _SIMILARITY_THRESHOLD_VERY_FINE);
          auto rotCheck =
              -1 * vorGeo::checkLeftOf(cent, leftIntPoint, newEvent->pos,
                                       _SIMILARITY_THRESHOLD_VERY_FINE);
          if (LRCheck * rotCheck < 0) {
            curNode = curNode->right;
          } else if (LRCheck * rotCheck > 0) {
            curNode = curNode->left;
          } else {
            curNode = curNode->left->getRightMostChild();
          }
        }
#else
        auto LRCheck =
            vorGeo::checkLeftOf(cent, intPoint, newEvent->pos, 10000);
        auto rotCheck =
            -1 * vorGeo::checkLeftOf(cent, leftIntPoint, newEvent->pos, 10000);
        if (LRCheck * rotCheck < 0) {
          curNode = curNode->right;
        } else if (LRCheck * rotCheck > 0) {
          curNode = curNode->left;
        } else {
          curNode = curNode->left->getRightMostChild();
        }
#endif
      }
    }
  }
  return curNode;
}

void RBTree::handleVertexEvent(vertexEvent* vert) {
  if (!vert->replacePointerList.empty()) {
    endPointInsert(vert);
    vert->isProcessed = true;
  } else {
    if (numNodes == 0) {
      insertRoot(vert, VERTEX);
      vert->isProcessed = true;
      if (!vert->lineSpawnEvent.empty()) {
        ++numNodes;
        auto nuVert = records.createVertex(vert->pos, 0, vert, vert, vert,
                                           eventLog, true);
        nuVert->vertexCoorID = vert->objectIndex;
        vert->vertPointer = nuVert;
        multiLineSpawner(vert, root, false);
        for (auto edge : vert->mustBePinned) {
          {
            nuVert->addEdge(edge);
          }
        }
        vert->mustBePinned.clear();
      }
      return;
    } else if (numNodes == 1) {
      vertex_splitArc(vert, root);
      vert->isProcessed = true;
      return;
    } else {
      auto treeNode = findInsert(vert);
      vertex_splitArc(vert, treeNode);
      vert->isProcessed = true;

      return;
    }
  }
}

void RBTree::handleLineEvent(lineEvent* line) {
  if (numNodes == 0)
    line_splitArc(line);
  else if (numNodes == 1)
    line_splitArc(line, root);
  else
    line_splitArc(line, findInsert(line));
  line->isProcessed = true;
  line->twin->isProcessed = true;
}

inline void RBTree::destroyCircles(Node* node) {
  for (auto& circ : node->circEventPointer) {
    if (circ->SEQptr) queue.remove(circ->SEQptr);
    CircleContainer.remove(circ);
    // circ.reset();
  }
  node->circEventPointer.clear();
}

void RBTree::vertex_splitArc(vertexEvent* vert, Node* oldNode) {
  // The created subtree is constructed to be *Somewhat* balanced at the
  // start. Diagram of subtree not in this code
  auto leftNode = buildNode(oldNode->data, oldNode->dataType, BLACK);
  auto rightNode = buildNode(oldNode->data, oldNode->dataType, BLACK);
  auto newNode = buildNode(vert, VERTEX, BLACK);

  destroyCircles(oldNode);

  if (!oldNode->getHigherNode()) {
    destroyCircles(getFirstLeaf());
  }
  if (!oldNode->getLowerNode()) {
    destroyCircles(getLastLeaf());
  }

  auto edgePair =
      records.createHalfEdgePair(static_cast<siteEvent*>(oldNode->data), vert,
                                 (oldNode->dataType == LINE) ? 2 : 1);

  auto edgeNodeB =
      buildNode(std::get<1>(edgePair), HALFEDGE, RED, newNode, rightNode);

  auto edgeNodeA = buildNode(std::get<0>(edgePair), HALFEDGE, RED, leftNode,
                             edgeNodeB, oldNode->parent);

  edgeNodeB->parent = edgeNodeA;
  if (root == oldNode) {
    root = edgeNodeA;
  } else {
    if (oldNode->parent->left == oldNode)
      oldNode->parent->left = edgeNodeA;
    else
      oldNode->parent->right = edgeNodeA;
  }

  leftNode->parent = edgeNodeA;
  newNode->parent = edgeNodeB;
  rightNode->parent = edgeNodeB;

  // Only edge nodes need balancing
  maintainTree_ins(edgeNodeA);
  maintainTree_ins(edgeNodeB);

  if (vert->lineSpawnEvent.empty()) {
    circFilterLR(leftNode, newNode, rightNode);
  } else {
    auto nuVert =
        records.createVertex(vert->pos, 0.0, vert, vert, vert, eventLog, true);
    vert->vertPointer = nuVert;
    nuVert->vertexCoorID = vert->objectIndex;

    RBTree::multiLineSpawner(vert, newNode, false);
    for (auto edge : vert->mustBePinned) {
      nuVert->addEdge(edge);
    }
  }
  deleteNode(oldNode);
}

void RBTree::line_splitArc(lineEvent* line) {
  /* oldLN and 6N do not exist on first iteration
                        e3
                       /  \
                      /    \
                     e2     e5
                     /  \    / \
                 e1   2n  e4  e6
                  /  \     /  \  /\
                oldLn 1n  3n  4n5n 6n	*/
  auto node1 = buildNode(line->twin, LINE, BLACK);

  auto degen0 = DegenContainer.add(line->endPoints[0], line);
  auto node2 = buildNode(degen0, DEGENERATE, BLACK);
  line->endPoints[0]->addReplacement(node2, *line);

  auto node3 = buildNode(line, LINE, BLACK);

  auto degen1 = DegenContainer.add(line->endPoints[1], line);
  auto node4 = buildNode(degen1, DEGENERATE, BLACK);
  line->endPoints[1]->addReplacement(node4, *line);

  auto node5 = buildNode(line->twin, LINE, BLACK);

  auto edge12 = records.createHalfEdgePair(line->twin, line->endPoints[0], 0);
  auto edge23 = records.createHalfEdgePair(line->endPoints[0], line, 0);
  auto edge34 = records.createHalfEdgePair(line, line->endPoints[1], 0);
  auto edge41 = records.createHalfEdgePair(line->endPoints[1], line->twin, 0);

  // These are 'implict edges' in that they exist within a line.  They must
  // manually be connected to the diagram upon endpoint detection
  line->endPoints[0]->mustBePinned.push_back(std::get<1>(edge12));
  line->endPoints[0]->mustBePinned.push_back(std::get<1>(edge23));
  line->endPoints[1]->mustBePinned.push_back(std::get<1>(edge34));
  line->endPoints[1]->mustBePinned.push_back(std::get<1>(edge41));

  auto nodeE2 = buildNode(std::get<0>(edge12), HALFEDGE, RED, node1, node2);
  auto nodeE4 = buildNode(std::get<0>(edge34), HALFEDGE, RED, node3, node4);
  auto nodeE5 = buildNode(std::get<0>(edge41), HALFEDGE, RED, nodeE4, node5);
  auto nodeE3 = buildNode(std::get<0>(edge23), HALFEDGE, BLACK, nodeE2, nodeE5);
  root = nodeE3;

  node1->parent = nodeE2;
  node2->parent = nodeE2;
  node3->parent = nodeE4;
  node4->parent = nodeE4;
  node5->parent = nodeE5;

  nodeE2->parent = nodeE3;
  nodeE4->parent = nodeE5;
  nodeE5->parent = nodeE3;

  maintainTree_ins(nodeE3);
  maintainTree_ins(nodeE2);
  maintainTree_ins(nodeE5);
  maintainTree_ins(nodeE4);
}

void RBTree::line_splitArc(lineEvent* line, Node* oldNode) {
  auto leftNode = buildNode(oldNode->data, oldNode->dataType, BLACK);
  auto rightNode = buildNode(oldNode->data, oldNode->dataType, BLACK);

  auto node1 = buildNode(line->twin, LINE, BLACK);

  auto degen0 = DegenContainer.add(line->endPoints[0], line);
  auto node2 = buildNode(degen0, DEGENERATE, BLACK);
  line->endPoints[0]->addReplacement(node2, *line);

  auto node3 = buildNode(line, LINE, BLACK);

  auto degen1 = DegenContainer.add(line->endPoints[1], line);
  auto node4 = buildNode(degen1, DEGENERATE, BLACK);
  line->endPoints[1]->addReplacement(node4, *line);

  auto node5 = buildNode(line->twin, LINE, BLACK);

  destroyCircles(oldNode);
  if (!oldNode->getHigherNode()) destroyCircles(getFirstLeaf());
  if (!oldNode->getLowerNode()) destroyCircles(getLastLeaf());

  auto edgeL1 =
      records.createHalfEdgePair(static_cast<siteEvent*>(oldNode->data),
                                 line->twin, oldNode->dataType == LINE ? 1 : 2);
  auto edge12 = records.createHalfEdgePair(line->twin, line->endPoints[0], 0);
  auto edge23 = records.createHalfEdgePair(line->endPoints[0], line, 0);
  auto edge34 = records.createHalfEdgePair(line, line->endPoints[1], 0);
  auto edge41 = records.createHalfEdgePair(line->endPoints[1], line->twin, 0);

  // These are 'implict edges' in that they exist within a line.  They must
  // manually be connected to the diagram upon endpoint detection
  line->endPoints[0]->mustBePinned.push_back(std::get<1>(edge12));
  line->endPoints[0]->mustBePinned.push_back(std::get<1>(edge23));
  line->endPoints[1]->mustBePinned.push_back(std::get<1>(edge34));
  line->endPoints[1]->mustBePinned.push_back(std::get<1>(edge41));

  auto nodeE1 = buildNode(std::get<0>(edgeL1), HALFEDGE, RED, leftNode, node1);
  auto nodeE2 = buildNode(std::get<0>(edge12), HALFEDGE, RED, nodeE1, node2);
  auto nodeE6 = buildNode(std::get<1>(edgeL1), HALFEDGE, RED, node5, rightNode);
  auto nodeE4 = buildNode(std::get<0>(edge34), HALFEDGE, RED, node3, node4);
  auto nodeE5 = buildNode(std::get<0>(edge41), HALFEDGE, RED, nodeE4, nodeE6);
  auto nodeE3 = buildNode(std::get<0>(edge23), HALFEDGE, RED, nodeE2, nodeE5,
                          oldNode->parent);

  if (root == oldNode)
    root = nodeE3;
  else {
    if (oldNode->parent->left == oldNode)
      oldNode->parent->left = nodeE3;
    else
      oldNode->parent->right = nodeE3;
  }

  leftNode->parent = nodeE1;
  node1->parent = nodeE1;
  node2->parent = nodeE2;
  node3->parent = nodeE4;
  node4->parent = nodeE4;
  node5->parent = nodeE6;
  rightNode->parent = nodeE6;

  nodeE1->parent = nodeE2;
  nodeE2->parent = nodeE3;
  nodeE4->parent = nodeE5;
  nodeE5->parent = nodeE3;
  nodeE6->parent = nodeE5;

  maintainTree_ins(nodeE3);
  maintainTree_ins(nodeE2);
  maintainTree_ins(nodeE5);
  maintainTree_ins(nodeE1);
  maintainTree_ins(nodeE4);
  maintainTree_ins(nodeE6);

  deleteNode(oldNode);

  circFilterL(leftNode, node1);
  circFilterR(node5, rightNode);
}

void RBTree::multiLineSpawner(vertexEvent* vert, Node* oldNode,
                              bool degenerateFlag) {
  if (degenerateFlag && vert->lineSpawnEvent.empty()) {
    oldNode->changeData(vert, VERTEX);
    circFilterLR(oldNode->getLowerNode(), oldNode, oldNode->getHigherNode());
  } else {
    auto epLeftMost = buildNode(vert, VERTEX, BLACK);
    auto& lineSpawnEvents =
        mlsHelper.lineSpawnEvents;  // reused vector for multilinespawner
    lineSpawnEvents.clear();
    auto& EPNodeList = mlsHelper.EPNodeList;
    EPNodeList.clear();

    // Queues/prepares all leaves to be inserted from left to right
    for (auto line : vert->lineSpawnEvent) {
      auto otherEP = line->getOtherEP(vert);
      if (line->isLeftEP(vert)) {
        lineSpawnEvents.push_back(buildNode(line, LINE, BLACK));
        lineSpawnEvents.push_back(
            buildNode(DegenContainer.add(otherEP, line), DEGENERATE, BLACK));
        otherEP->addReplacement(lineSpawnEvents.back(), *line);
        lineSpawnEvents.push_back(buildNode(line->twin, LINE, BLACK));
        lineSpawnEvents.push_back(buildNode(vert, VERTEX, BLACK));
        EPNodeList.push_back(lineSpawnEvents.back());
      } else {
        lineSpawnEvents.push_back(buildNode(line->twin, LINE, BLACK));
        lineSpawnEvents.push_back(
            buildNode(DegenContainer.add(otherEP, line), DEGENERATE, BLACK));
        otherEP->addReplacement(lineSpawnEvents.back(), *line);
        lineSpawnEvents.push_back(buildNode(line, LINE, BLACK));
        lineSpawnEvents.push_back(buildNode(vert, VERTEX, BLACK));
        EPNodeList.push_back(lineSpawnEvents.back());
      }
      line->isProcessed = true;
      line->twin->isProcessed = true;
    }

    auto& spawnEdgeList = mlsHelper.spawnEdgeList;
    auto& spawnNodeList = mlsHelper.spawnNodeList;
    auto& spawnEdgeNodeList = mlsHelper.spawnEdgeNodeList;
    spawnEdgeList.clear();
    spawnNodeList.clear();
    spawnEdgeNodeList.clear();

    // Below creates halfedge pairs and pair nodes.  Registers certain edges
    // as 'must be pinned,' as a circle event will not naturally pin these
    // edges
    spawnNodeList.push_back(epLeftMost);
    for (std::size_t i = 0; i < 4 * vert->lineSpawnEvent.size(); i++) {
      if (i == 0) {
        spawnEdgeList.push_back(records.createHalfEdgePair(
            vert, static_cast<siteEvent*>(lineSpawnEvents[0]->data), 0));
        vert->mustBePinned.push_back(std::get<1>(spawnEdgeList.back()));

      } else {
        spawnEdgeList.push_back(records.createHalfEdgePair(
            static_cast<siteEvent*>(lineSpawnEvents[i - 1]->data),
            static_cast<siteEvent*>(lineSpawnEvents[i]->data), 0));
      }
      spawnNodeList.push_back(
          buildNode(std::get<0>(spawnEdgeList.back()),
                    HALFEDGE));  // every other is half edge, just use that...
      spawnEdgeNodeList.push_back(
          std::make_pair(spawnNodeList.back(), spawnNodeList.size() - 1));
      spawnNodeList.push_back(lineSpawnEvents[i]);
      // auto holdStr = std::get<1>(spawnEdgeList.back())->toString();

      if (i > 0) {
        if (lineSpawnEvents[i - ((i + 1) % 2)]->dataType == DEGENERATE) {
          auto data = static_cast<degenEvent*>(
              lineSpawnEvents[i - ((i + 1) % 2)]->data);

          data->replacedByPointer->mustBePinned.push_back(
              std::get<1>(spawnEdgeList.back()));
        } else if (lineSpawnEvents[i - ((i + 1) % 2)]->dataType == VERTEX) {
          auto data = static_cast<vertexEvent*>(
              lineSpawnEvents[i - ((i + 1) % 2)]->data);
          data->mustBePinned.push_back(std::get<1>(spawnEdgeList.back()));
        }
      }
      // std::get<1>(spawnEdgeList.back())->mustBePinned = true;
    }

    auto& queue = mlsHelper.queue;
    auto& queueLowInd = mlsHelper.queueLowInd;
    auto& queueHighInd = mlsHelper.queueHighInd;
    auto& queueIndex = mlsHelper.queueIndex;
    queue.clear();
    queueLowInd.clear();
    queueHighInd.clear();
    queueIndex.clear();
    queueHighInd.push_back(0);
    queueLowInd.push_back(0);

    // This takes all the nodes made above, and creates a balanced subtree
    // with the correct ordering Converts vector -> BST with leafs in approp
    // spot. Matlab code was written in a way to avoid recursion.  Uses
    // multiple queues to simulate the binary search stuff Should rewrite in
    // more C like manner if possible std::vector<Node*> queue;
    // std::vector<size_t> queueLowInd(1), queueHighInd(1), queueIndex;
    // queueLowInd.reserve(4 * vert->lineSpawnEvent.size());
    // queueHighInd.reserve(4 * vert->lineSpawnEvent.size());
    // queueIndex.reserve(4 * vert->lineSpawnEvent.size());

    size_t index = (vert->lineSpawnEvent.size() * 2) - 1;
    queue.push_back(std::get<0>(spawnEdgeNodeList[index]));
    queueIndex.push_back(index);

    queueLowInd.push_back(0);
    queueHighInd.push_back(queueIndex[0] - 1);
    queueIndex.push_back(((queueHighInd[1] + queueLowInd[1]) / 2));
    queue.push_back(std::get<0>(spawnEdgeNodeList[queueIndex[1]]));

    queueHighInd.push_back(vert->lineSpawnEvent.size() * 4 - 1);
    queueLowInd.push_back(queueIndex[0] + 1);
    queueIndex.push_back(((queueHighInd[2] + queueLowInd[2]) / 2));
    queue.push_back(std::get<0>(spawnEdgeNodeList[queueIndex[2]]));

    queue[0]->left = queue[1];
    queue[0]->right = queue[2];
    queue[1]->parent = queue[0];
    queue[2]->parent = queue[0];

    for (std::size_t i = 1; i < vert->lineSpawnEvent.size() * 4; i++) {
      if (queueLowInd[i] + 1 > queueIndex[i]) {
        queue[i]->left =
            spawnNodeList[std::get<1>(spawnEdgeNodeList[queueIndex[i]]) - 1];
        queue[i]->left->parent = queue[i];
      } else {
        queueLowInd.push_back(queueLowInd[i]);
        queueHighInd.push_back(queueIndex[i] - 1);
        queueIndex.push_back(((queueLowInd.back() + queueHighInd.back()) / 2));
        queue.push_back(std::get<0>(spawnEdgeNodeList[queueIndex.back()]));
        queue[i]->left = queue.back();
        queue.back()->parent = queue[i];
      }

      if (queueHighInd[i] < queueIndex[i] + 1) {
        queue[i]->right =
            spawnNodeList[std::get<1>(spawnEdgeNodeList[queueIndex[i]]) + 1];
        queue[i]->right->parent = queue[i];
      } else {
        queueHighInd.push_back(queueHighInd[i]);
        queueLowInd.push_back(queueIndex[i] + 1);
        queueIndex.push_back(((queueLowInd.back() + queueHighInd.back()) / 2));
        queue.push_back(std::get<0>(spawnEdgeNodeList[queueIndex.back()]));
        queue[i]->right = queue.back();
        queue.back()->parent = queue[i];
      }
    }
    queue[0]->parent = oldNode->parent;
    if (root == oldNode)
      root = queue[0];
    else {
      if (oldNode->parent->left == oldNode)
        oldNode->parent->left = queue[0];
      else
        oldNode->parent->right = queue[0];
    }

    deleteNode(oldNode);

    for (auto node : queue) maintainTree_ins(node);

    // Circle events with endpoints being pinched out by an acute edge
    for (std::size_t i = 0; i < vert->lineSpawnEvent.size() - 1; i++) {
      int index = 4 * i + 3;
      findCircleEvents(lineSpawnEvents[index - 1], lineSpawnEvents[index],
                       lineSpawnEvents[index + 1]);
    }
    if (degenerateFlag) {
      // If we inserted a degenerate node then we know this possibility exists
      // for 'previous line - EP - next line'
      auto leftLineObj = epLeftMost->getLowerNode();
      findCircleEvents(leftLineObj, epLeftMost, lineSpawnEvents[0]);
      circFilterL(leftLineObj, epLeftMost);

      auto rightLineObj = lineSpawnEvents.back()->getHigherNode();
      findCircleEvents(lineSpawnEvents.at(lineSpawnEvents.size() - 2),
                       lineSpawnEvents.back(), rightLineObj);
      circFilterR(lineSpawnEvents.back(), rightLineObj);
    } else {
      auto leftObj = epLeftMost->getLowerNode();
      if (!leftObj) leftObj = getLastLeaf()->getLowerNode();
      circFilterL(leftObj, epLeftMost);
      findCircleEvents(leftObj, epLeftMost, lineSpawnEvents[0]);

      auto rightObj = lineSpawnEvents.back()->getHigherNode();
      if (!rightObj) rightObj = getFirstLeaf()->getHigherNode();
      circFilterR(lineSpawnEvents.back(), rightObj);
      findCircleEvents(lineSpawnEvents.at(lineSpawnEvents.size() - 2),
                       lineSpawnEvents.back(), rightObj);
    }
    // Vector -> BST
  }
  // Realistically, should always pass the if statement
}

void RBTree::endPointInsert(vertexEvent* vert) {
  vorRBT::Node* oldNode = vert->replacePointerList[0];
  vorVert* nuVert = nullptr;
  if (vert->replacePointerList.size() > 1) {
    vorRBT::Node* wrapAroundNode;
    std::tie(nuVert, wrapAroundNode) = RBTree::multiLineConvergenceHandler(
        vert, *vert->replacePointerList.begin(),
        vert->replacePointerList.back());
    nuVert->vertexCoorID = vert->objectIndex;
    if (wrapAroundNode != nullptr) {
      RBTree::destroyCircles(wrapAroundNode);
      wrapAroundNode->changeData(vert, VERTEX);
    }
  } else {
    nuVert =
        records.createVertex(vert->pos, 0.0, vert, vert, vert, eventLog, true);
    nuVert->vertexCoorID = vert->objectIndex;
  }
  vert->vertPointer = nuVert;
  if (vert->lineSpawnEvent.size() == 0) {
    DegenContainer.remove(static_cast<degenEvent*>(oldNode->data));
    oldNode->changeData(vert, VERTEX);
    auto rightNode = oldNode->getHigherNode();
    if (!rightNode)
      rightNode =
          getFirstLeaf()->getHigherNode();  // This was missing the
                                            // getHigherNode call before... wow
    auto leftNode = oldNode->getLowerNode();
    if (!leftNode) leftNode = getLastLeaf()->getLowerNode();
    circFilterLCR(leftNode, oldNode, rightNode);
  } else {
    RBTree::multiLineSpawner(vert, oldNode, true);
  }

  for (auto e : vert->mustBePinned) {
    nuVert->addEdge(e);
  }
  // for (auto faceEdge : vert->voronoiFace->edges) {
  //	if (faceEdge->mustBePinned) nuVert->addEdge(faceEdge);
  //	else if (faceEdge->twin->mustBePinned) nuVert->addEdge(faceEdge->twin);
  //}
}

std::pair<vorVert*, vorRBT::Node*> RBTree::multiLineConvergenceHandler(
    vertexEvent* data, vorRBT::Node* startNode, vorRBT::Node* endNode) {
  auto wrapAround = RBTree::getAllBetween(startNode, endNode);
  auto& nodeList = gabHelper.NodeList;
  auto nuVert =
      records.createVertex(data->pos, 0.0, data, data, data, eventLog, false);
  // pins edges to the vertex.  deletes implicit edges
  for (auto loopNode : nodeList) {
    if (loopNode->dataType == HALFEDGE) {
      auto edge = static_cast<halfEdge*>(loopNode->data);
      if (edge->edgeType != 0) {
        nuVert->addEdge(edge);
      } else {
        records.HalfEdges.remove(edge);
        if (!edge->twin->INVALID) {
          // removes the twin edge if it has not been removed already. Twins do
          // not get invalidated in all cases
          records.HalfEdges.remove(edge->twin);
        }
      }
    }
  }
  for (auto loopNode : nodeList) {
    if (loopNode->dataType != HALFEDGE) {
      RBTree::destroyCircles(loopNode);
      RBTree::maintainTree_del(loopNode, loopNode->parent);
    }
  }
  RBTree::maintainTree_del(endNode, std::get<0>(endNode->getLeftParent()));
  return std::make_pair(nuVert, wrapAround);
}

void RBTree::handleCircleEvent(circleEvent* circ) {
  circ->SEQptr = nullptr;  // No longer in queue
  auto rmNode = circ->nodeVec[1];
  auto leftNode = rmNode->getLowerNode();
  if (!leftNode) leftNode = getLastLeaf()->getLowerNode();
  auto rightNode = rmNode->getHigherNode();
  if (!rightNode) rightNode = getFirstLeaf()->getHigherNode();
#ifndef _SKIP_CHECKS  // Change to _STRICT_CHECKING
  assert(leftNode->data == circ->siteList[0]);
  assert(rightNode->data == circ->siteList[2]);
  assert(leftNode->dataType != HALFEDGE);
  assert(rmNode->dataType != HALFEDGE);
  assert(rightNode->dataType != HALFEDGE);
  validateCircle_STRICT(circ->pos, circ->circRad,
                        static_cast<siteEvent*>(leftNode->data),
                        static_cast<siteEvent*>(rmNode->data),
                        static_cast<siteEvent*>(rightNode->data));
#endif  // _DEBUG

  // nodeVec *SHOULD* be fine to use, but if there was tree corruption, this
  // may not be the case
  int loopAround = 0;
  Node* replaceLeaf = nullptr;
  Node* nodeDelete = nullptr;
  Node* nodeReplace = nullptr;
  auto EdgeDistPairL = rmNode->getLeftParent();
  auto leftEdge = std::get<0>(EdgeDistPairL);
  auto ledgeDist = std::get<1>(EdgeDistPairL);
  if (!leftEdge) {
    leftEdge = getLastEdge();
    replaceLeaf = getLastLeaf();
    loopAround = 1;
  }

  auto EdgeDistPairR = rmNode->getRightParent();
  auto rightEdge = std::get<0>(EdgeDistPairR);
  auto redgeDist = std::get<1>(EdgeDistPairR);
  if (!rightEdge) {
    rightEdge = getFirstEdge();
    replaceLeaf = getFirstLeaf();
    loopAround = 2;
  }

  if (loopAround == 2 || ledgeDist < redgeDist) {
    nodeDelete = leftEdge;
    nodeReplace = rightEdge;
  } else {  // loopAround is 0 and redgeDist >= ledgeDist, or loopAround = 1
    nodeDelete = rightEdge;
    nodeReplace = leftEdge;
  }

  // If this is not a half edge you already screwed up
  assert(leftEdge->dataType == HALFEDGE);
  auto leftEdgeData = static_cast<halfEdge*>(leftEdge->data);

  assert(rightEdge->dataType == HALFEDGE);
  auto rightEdgeData = static_cast<halfEdge*>(rightEdge->data);

  auto halfEdgePair = records.createHalfEdgePair(
      static_cast<siteEvent*>(leftNode->data),
      static_cast<siteEvent*>(rightNode->data),
      (((leftNode->dataType) == LINE) != ((rightNode->dataType) == LINE)) +
          1);  // Edge type is xor(isLineA,isLineB) + 1

  // Determining what Node is getting removed/replaced in the tree
  nodeReplace->changeData(std::get<0>(halfEdgePair), HALFEDGE);
  if (loopAround != 0) {
    destroyCircles(replaceLeaf);
    if (loopAround == 1) {
#ifdef _TOROIDAL
      if (replaceLeaf->dataType != HALFEDGE &&
          static_cast<siteEvent*>(replaceLeaf->data)->objectIndex <
              numNonMirrored &&
          !(rightNode->dataType != HALFEDGE &&
            static_cast<siteEvent*>(rightNode->data)->objectIndex <
                numNonMirrored)) {  // If this is a nonMirrored node and it is
                                    // being replaced by a mirrored node
        --remainingNonMirrored;     // will have to update the line pinch case
                                    // code with this check too
      }
#endif
      replaceLeaf->changeData(rightNode->data, rightNode->dataType);
    } else if (loopAround == 2) {
#ifdef _TOROIDAL
      if (replaceLeaf->dataType != HALFEDGE &&
          static_cast<siteEvent*>(replaceLeaf->data)->objectIndex <
              numNonMirrored &&
          !(leftNode->dataType != HALFEDGE &&
            static_cast<siteEvent*>(leftNode->data)->objectIndex <
                numNonMirrored)) {  // If this is a nonMirrored node and it is
                                    // being replaced by a mirrored node
        --remainingNonMirrored;     // will have to update the line pinch case
                                    // code with this check too
      }
#endif
      replaceLeaf->changeData(leftNode->data, leftNode->dataType);
    }
  }

  auto rmNodeData = static_cast<siteEvent*>(rmNode->data);
  maintainTree_del(rmNode, nodeDelete);

  // Setting up the voronoi vertex associated with this event
  vorVert* nuVert = nullptr;
  if (circ->_PINCHCASE && rmNodeData->vertPointer) {
    nuVert = rmNodeData->vertPointer;
    nuVert->_IMPLICIT = false;
    nuVert->vertexCoorID = rmNodeData->objectIndex;
  } else {
    nuVert = records.createVertex(circ->pos, circ->circRad, circ->siteList[0],
                                  circ->siteList[1], circ->siteList[2],
                                  circ->eventLog);
  }

  if (circ->_PINCHCASE) {
    records.HalfEdges.remove(leftEdgeData);
    records.HalfEdges.remove(leftEdgeData->twin);
    records.HalfEdges.remove(rightEdgeData);
    records.HalfEdges.remove(rightEdgeData->twin);
  } else {
    nuVert->addEdge(leftEdgeData);
    nuVert->addEdge(rightEdgeData);
  }

  // rightEdge
  nuVert->addEdge(std::get<1>(halfEdgePair));

  // Destroy old removal events
  destroyCircles(leftNode);
  destroyCircles(rightNode);

  // Destroy removal events for nodes if there is a loop around
  auto furtherLeftNode = leftNode->getLowerNode();
  if (!furtherLeftNode) {
    auto lastNode = getLastLeaf();
    destroyCircles(lastNode);
    furtherLeftNode = lastNode->getLowerNode();
  }

  auto furtherRightNode = rightNode->getHigherNode();
  if (!furtherRightNode) {
    auto firstNode = getFirstLeaf();
    destroyCircles(firstNode);
    furtherRightNode = firstNode->getHigherNode();
  }
  if (furtherLeftNode != leftNode && furtherRightNode != rightNode) {
    findCircleEvents(furtherLeftNode, leftNode, rightNode);
  }
  if (furtherRightNode != leftNode && furtherRightNode != rightNode) {
    findCircleEvents(leftNode, rightNode, furtherRightNode);
  }

  destroyCircles(rmNode);
}

#ifdef _DEBUG
void RBTree::dataValidator() {
  int index = 0;
  for (auto& vec : NodeContainer.collector) {
    for (auto& e : *vec) {
      ++index;
      if (e.getState() && !(e.data)) throw nodeNullDataExcept;
    }
  }
  return;
}
#endif  //_DEBUG
}  // namespace vorRBT
