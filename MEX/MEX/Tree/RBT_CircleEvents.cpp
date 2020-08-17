#include "../Queue/SEQTree.hpp"
#include "Node.hpp"
#include "RBT.hpp"

// Used to filter the inputted nodes to determine which circle functions to
// call.  Does not compute circles A union of ptrs or variants may be better
// than the array setup
namespace vorRBT {
// Searching for circle events
void RBTree::circFilterLCR(Node *left, Node *cent, Node *right) {
  circFilterL(left, cent);
  findCircleEvents(left, cent, right);
  circFilterR(cent, right);
}

void RBTree::circFilterLR(Node *left, Node *cent, Node *right) {
  circFilterL(left, cent);
  circFilterR(cent, right);
}

void RBTree::circFilterL(Node *left, Node *cent) {
  auto furtherNode = left->getLowerNode();
  if (!furtherNode) {
    auto lastNode = getLastLeaf();
    furtherNode = lastNode->getLowerNode();
    if (furtherNode->data != cent->data) {
      findCircleEvents(furtherNode, left, cent);
    }
  } else {
    findCircleEvents(furtherNode, left, cent);
  }
}

void RBTree::circFilterR(Node *cent, Node *right) {
  auto furtherNode = right->getHigherNode();
  if (!furtherNode) {
    auto lastNode = getFirstLeaf();
    furtherNode = lastNode->getHigherNode();
    if (furtherNode->data != cent->data) {
      findCircleEvents(cent, right, furtherNode);
    }
  } else {
    findCircleEvents(cent, right, furtherNode);
  }
}

// Entry Point
void RBTree::findCircleEvents(Node *left, Node *cent, Node *right) {
  auto nodeVec = std::array<Node *, 3>({left, cent, right});
  auto obj1 = static_cast<siteEvent *>(left->data);
  auto obj2 = static_cast<siteEvent *>(cent->data);
  auto obj3 = static_cast<siteEvent *>(right->data);

  if (obj1->objectIndex == obj2->objectIndex ||
      obj2->objectIndex == obj3->objectIndex ||
      obj3->objectIndex == obj1->objectIndex)
    return;
  else {
    if ((obj1->objType != DEGENERATE) && (obj2->objType != DEGENERATE) &&
        (obj3->objType != DEGENERATE)) {
      auto numLines = (obj1->objType == LINE) + (obj2->objType == LINE) +
                      (obj3->objType == LINE);
      if (numLines == 0) {
        std::array<vertexEvent *, 3> vertVec{static_cast<vertexEvent *>(obj1),
                                             static_cast<vertexEvent *>(obj2),
                                             static_cast<vertexEvent *>(obj3)};
        circleFilterPPP(vertVec, nodeVec);
      } else if (numLines == 3) {
        std::array<lineEvent *, 3> lineVec{static_cast<lineEvent *>(obj1),
                                           static_cast<lineEvent *>(obj2),
                                           static_cast<lineEvent *>(obj3)};
        circleFilterLLL(lineVec, nodeVec);
      } else if (numLines == 1) {
        lineEvent *lineVec(nullptr);
        std::array<vertexEvent *, 2> vertVec;
        if (obj1->objType == LINE) {
          lineVec = static_cast<lineEvent *>(obj1);
          vertVec[0] = static_cast<vertexEvent *>(obj2);
          vertVec[1] = static_cast<vertexEvent *>(obj3);
        } else if (obj2->objType == LINE) {
          lineVec = static_cast<lineEvent *>(obj2);
          vertVec[0] = static_cast<vertexEvent *>(obj1);
          vertVec[1] = static_cast<vertexEvent *>(obj3);
        } else if (obj3->objType == LINE) {
          lineVec = static_cast<lineEvent *>(obj3);
          vertVec[0] = static_cast<vertexEvent *>(obj1);
          vertVec[1] = static_cast<vertexEvent *>(obj2);
        }
        circleFilterLPP(vertVec, lineVec, nodeVec);
      } else if (numLines == 2) {
        vertexEvent *vertVec(nullptr);
        std::array<lineEvent *, 2> lineVec;
        if (obj1->objType != LINE) {
          vertVec = static_cast<vertexEvent *>(obj1);
          lineVec[0] = static_cast<lineEvent *>(obj2);
          lineVec[1] = static_cast<lineEvent *>(obj3);
        } else if (obj2->objType != LINE) {
          vertVec = static_cast<vertexEvent *>(obj2);
          lineVec[0] = static_cast<lineEvent *>(obj1);
          lineVec[1] = static_cast<lineEvent *>(obj3);
        } else if (obj3->objType != LINE) {
          vertVec = static_cast<vertexEvent *>(obj3);
          lineVec[0] = static_cast<lineEvent *>(obj1);
          lineVec[1] = static_cast<lineEvent *>(obj2);
        }
        circleFilterLLP(vertVec, lineVec, nodeVec);
      }
    }
  }
}

// Filter helpers
bool RBTree::circleEventLPXValidator(const lineEvent &line,
                                     const vertexEvent &point) {
  int above = line.UPPER ? 1 : -1;
  return (above * vorGeo::checkLeftOf(line.endPoints[0]->pos,
                                      line.endPoints[1]->pos, point.pos,
                                      _SIMILARITY_THRESHOLD_VERY_FINE)) > 0;
}

// Indices have been altered, should pass the non-shared EP.  -1 checks both

bool RBTree::circleEventLLXValidator(const lineEvent &line1,
                                     const lineEvent &line2,
                                     const int &sharedEPFlag) {
  int above = line1.UPPER ? 1 : -1;
  if (sharedEPFlag == -1) {
    auto valid = (above * vorGeo::checkLeftOf(
                              line1.endPoints[0]->pos, line1.endPoints[1]->pos,
                              line2.endPoints[0]->pos,
                              _SIMILARITY_THRESHOLD_VERY_FINE)) > 0;
    if (!valid) {
      valid = (above * vorGeo::checkLeftOf(
                           line1.endPoints[0]->pos, line1.endPoints[1]->pos,
                           line2.endPoints[1]->pos,
                           _SIMILARITY_THRESHOLD_VERY_FINE)) > 0;
    }
    return valid;
  } else {
    // int testIndex = (sharedEPFlag == 2) ? 0 : 1; //This is something I should
    // review....
    return (above * vorGeo::checkLeftOf(line1.endPoints[0]->pos,
                                        line1.endPoints[1]->pos,
                                        line2.endPoints[sharedEPFlag]->pos,
                                        _SIMILARITY_THRESHOLD_VERY_FINE)) > 0;
  }
}

// Per-type filters
void RBTree::circleFilterPPP(std::array<vertexEvent *, 3> vertVec,
                             std::array<vorRBT::Node *, 3> nodeVec) {
  // Allowing collinear points to pass this check, as it's possbile points are
  // colinear due to being very close in spaces
  // In the long run, worth looking into a variable precision library.
  auto turnDir =
      vorGeo::checkLeftOf(vertVec[0]->pos, vertVec[1]->pos, vertVec[2]->pos,
                          _SIMILARITY_THRESHOLD_VERY_FINE);
  if (turnDir > 0) {
    auto circ =
        vorCirc::circlePPP(*vertVec.at(0), *vertVec.at(1), *vertVec.at(2));
    if (circ.isValid) {
      RBTree::registerCircle(circ, nodeVec);
    }
  }
#ifndef _UNSAFE
  else if (turnDir == 0) {
    auto circ = vorCirc::circlePPP_CloseFilter(*vertVec.at(0), *vertVec.at(1),
                                               *vertVec.at(2));
    if (circ.isValid) {
      RBTree::registerCircle(circ, nodeVec);
    }
  }
#endif
  return;
}  // namespace vorRBT

void RBTree::circleFilterLPP(std::array<vertexEvent *, 2> vertVec,
                             lineEvent *line,
                             std::array<vorRBT::Node *, 3> nodeVec) {
  auto p0EP(line->isEP(vertVec[0]));
  auto p1EP(line->isEP(vertVec[1]));
  vorGeo::circFlags circ;
  if (!(p0EP && p1EP)) {
    if (p0EP) {
      auto checkA(circleEventLPXValidator(*line, *vertVec[1]));
      auto twistCheck(false);
      if (line == nodeVec[0]->data)
        twistCheck =
            vorGeo::checkLeftOf(line->endPoints[line->UPPER ? 0 : 1]->pos,
                                vertVec[0]->pos, vertVec[1]->pos,
                                _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (line == nodeVec[1]->data)
        twistCheck = vorGeo::checkLeftOf(
                         vertVec[0]->pos, vorGeo::getClosest(vertVec[1], line),
                         vertVec[1]->pos, _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (line == nodeVec[2]->data)
        twistCheck =
            vorGeo::checkLeftOf(vertVec[0]->pos, vertVec[1]->pos,
                                line->endPoints[line->UPPER ? 1 : 0]->pos,
                                _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (checkA && twistCheck) {
        circ = vorCirc::circleLP(*line, *vertVec[1], *vertVec[0]);
        registerCircle(circ, nodeVec);
      }
    } else if (p1EP) {
      auto checkA(circleEventLPXValidator(*line, *vertVec[0]));
      auto twistCheck(false);
      if (line == nodeVec[0]->data)
        twistCheck =
            vorGeo::checkLeftOf(line->endPoints[line->UPPER ? 0 : 1]->pos,
                                vertVec[0]->pos, vertVec[1]->pos,
                                _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (line == nodeVec[1]->data)
        twistCheck = vorGeo::checkLeftOf(
                         vertVec[0]->pos, vorGeo::getClosest(vertVec[1], line),
                         vertVec[1]->pos, _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (line == nodeVec[2]->data)
        twistCheck =
            vorGeo::checkLeftOf(vertVec[0]->pos, vertVec[1]->pos,
                                line->endPoints[line->UPPER ? 1 : 0]->pos,
                                _SIMILARITY_THRESHOLD_VERY_FINE) >= 0;
      if (checkA && twistCheck) {
        circ = vorCirc::circleLP(*line, *vertVec[0], *vertVec[1]);
        registerCircle(circ, nodeVec);
      }
    } else {
      // Review the definition of 'valid'
      auto p1 = vorGeo::getClosest_Generic(
          static_cast<siteEvent *>(nodeVec[1]->data),
          static_cast<siteEvent *>(nodeVec[0]->data));
      auto p2 = vorGeo::getClosest_Generic(
          static_cast<siteEvent *>(nodeVec[0]->data),
          static_cast<siteEvent *>(nodeVec[1]->data));
      auto p3 = vorGeo::getClosest_Generic(
          static_cast<siteEvent *>(nodeVec[1]->data),
          static_cast<siteEvent *>(nodeVec[2]->data));
      auto checkA(circleEventLPXValidator(*line, *vertVec[0]));
      auto checkB(circleEventLPXValidator(*line, *vertVec[1]));

      int lineIndex = 0;
      if (nodeVec[1]->data == line) {
        lineIndex = 1;
      } else if (nodeVec[2]->data == line) {
        lineIndex = 2;
      }
      // If statement was: vorGeo::checkLeftOf(p1, p2, p3,
      // _SIMILARITY_THRESHOLD_VERY_FINE) >0
      if (checkA && checkB) {
        // if (vorGeo::checkLeftOf(p1, p2, p3, _SIMILARITY_THRESHOLD_VERY_FINE)
        // >
        //    0) {
        circ = vorCirc::circleLPP(*line, *vertVec[0], *vertVec[1], lineIndex);
        if (circ.isValid) registerCircle(circ, nodeVec);
      }
    }
  }
}

// This may need a different validation strategy for when the endpoint is on one
// of the lines. Unsure on the best way to implement. Need to think it over.
void RBTree::circleFilterLLP(vertexEvent *vertVec,
                             std::array<lineEvent *, 2> lineVec,
                             std::array<vorRBT::Node *, 3> nodeVec) {
  auto pointIsLine0EP = lineVec.at(0)->isEP(vertVec);
  auto pointIsLine1EP = lineVec.at(1)->isEP(vertVec);
  if (pointIsLine0EP && pointIsLine1EP) {
    auto nonSharedID = lineVec.at(1)->endPoints[0] == vertVec ? 1 : 0;
    auto isValid1 = RBTree::circleEventLLXValidator(
        *lineVec.at(0), *lineVec.at(1), nonSharedID);
    nonSharedID = lineVec.at(0)->endPoints[0] == vertVec ? 1 : 0;
    auto isValid2 = RBTree::circleEventLLXValidator(
        *lineVec.at(1), *lineVec.at(0), nonSharedID);
    if (isValid1 && isValid2) {
      auto circInfo =
          vorCirc::circleLL(*lineVec.at(0), *lineVec.at(1), *vertVec);
      if (circInfo.isValid) RBTree::registerCircle(circInfo, nodeVec);
    }
    return;
  } else if (pointIsLine0EP || pointIsLine1EP) {
    auto isValid1 =
        RBTree::circleEventLLXValidator(*lineVec.at(0), *lineVec.at(1), -1);
    auto isValid2 =
        RBTree::circleEventLLXValidator(*lineVec.at(1), *lineVec.at(0), -1);
    if (isValid1 && isValid2) {
      // if pointIsLine1EP, line = line1, indpline = line0.  if
      // pointisLine0EP, line = line0, indpLine = line1
      auto circInfo = vorCirc::circleLL(*lineVec.at(pointIsLine1EP),
                                        *lineVec.at(pointIsLine0EP), *vertVec);
      if (circInfo.isValid) RBTree::registerCircle(circInfo, nodeVec);
    }
    return;
  } else {
    auto isValid1 =
        RBTree::circleEventLLXValidator(*lineVec.at(0), *lineVec.at(1), -1);
    auto isValid2 =
        RBTree::circleEventLLXValidator(*lineVec.at(1), *lineVec.at(0), -1);
    if (isValid1 && isValid2) {
      auto isValid3 = circleEventLPXValidator(*lineVec.at(0), *vertVec);
      // Seeing if this check is needed still...
      // auto isValid4 = circleEventLPXValidator(*lineVec.at(1), *vertVec);

      if (isValid3) {
        std::array<int, 3> pointList;
        // Ordering of elements based on their original ordering.  Needed to
        // internally validate results
        pointList[0] = (lineVec.at(0) == nodeVec.at(0)->data
                            ? 0
                            : (lineVec.at(0) == nodeVec.at(1)->data ? 1 : 2));
        pointList[1] = (lineVec.at(1) == nodeVec.at(0)->data
                            ? 0
                            : (lineVec.at(1) == nodeVec.at(1)->data ? 1 : 2));
        pointList[2] = (vertVec == nodeVec.at(0)->data
                            ? 0
                            : (vertVec == nodeVec.at(1)->data ? 1 : 2));
        auto circInfo = vorCirc::circleLLP(*lineVec.at(0), *lineVec.at(1),
                                           *vertVec, pointList);
        if (circInfo.isValid) RBTree::registerCircle(circInfo, nodeVec);
      }
      return;
    }
  }
}

void RBTree::circleFilterLLL(std::array<lineEvent *, 3> lineVec,
                             std::array<vorRBT::Node *, 3> nodeVec) {
  if (lineVec.at(0)->twin == lineVec.at(1) ||
      lineVec.at(2)->twin == lineVec.at(1)) {
    return;
  }
  // else...
  auto isValid01 =
      RBTree::circleEventLLXValidator(*lineVec.at(0), *lineVec.at(1), -1);
  auto isValid10 =
      RBTree::circleEventLLXValidator(*lineVec.at(1), *lineVec.at(0), -1);

  if (isValid01 && isValid10) {
    auto isValid12 =
        RBTree::circleEventLLXValidator(*lineVec.at(1), *lineVec.at(2), -1);
    auto isValid21 =
        RBTree::circleEventLLXValidator(*lineVec.at(2), *lineVec.at(1), -1);
    if (isValid12 && isValid21) {
      auto posR =
          vorCirc::circleLLL(*lineVec.at(0), *lineVec.at(1), *lineVec.at(2));
      RBTree::registerCircle(posR, nodeVec);
    }
  }
  return;
}

// Register valid circle
void RBTree::registerCircle(vorGeo::circFlags circ,
                            std::array<vorRBT::Node *, 3> nodeVec) {
  std::array<siteEvent *, 3> siteList{
      static_cast<siteEvent *>(nodeVec[0]->data),
      static_cast<siteEvent *>(nodeVec[1]->data),
      static_cast<siteEvent *>(nodeVec[2]->data)};
  auto newCirc = CircleContainer.add(circ.XY, circ.R, cent, nodeVec, siteList,
                                     circ.isPinch, eventLog);
  nodeVec[1]->circEventPointer.push_back(newCirc);
  queue.add(newCirc);
}
}  // namespace vorRBT
