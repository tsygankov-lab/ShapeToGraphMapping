#include "../Math/basicMathAndGeometry.hpp"
#include "../Tree/Node.hpp"
#include "../Tree/RBT.hpp"
#include "siteEvent.hpp"
// Vertex event code.

void siteEvent::setPTRIDs() { vertPointerID = vertPointer->getID(); }

void vertexEvent::setEndpointAsLineEvent(lineEvent &lineObj) {
  // bool nuLineLeftEP = lineObj.isLeftEP(this);
  vertexEvent *otherEP = lineObj.getOtherEP(this);
  if (lineSpawnEvent.size() > 0) {
    for (auto lineIt = lineSpawnEvent.begin(); lineIt < lineSpawnEvent.end();
         lineIt++) {
      auto line = *lineIt;
      int ckLeftResult = vorGeo::checkLeftOf(
          this->pos, line->getOtherEP(this)->pos, otherEP->pos, 10000);
      if (ckLeftResult == 0) {
        ckLeftResult = vorGeo::checkLeftOf(
            this->cent, line->getOtherEP(this)->pos, otherEP->pos, 10000);
      }
      if (ckLeftResult > 0) {
        lineSpawnEvent.insert(lineIt, &lineObj);
        return;  // we're done
      }
    }
  }
  // Executed if object is not inserted prior
  lineSpawnEvent.push_back(&lineObj);
}

// degenObjNode is the node containing the degenerate node.
// lineObj is a reference to the line creating this degenerate.
void vertexEvent::addReplacement(vorRBT::Node *degenObjNode,
                                 lineEvent &lineObj) {
  // bool nuLineLeftEP = lineObj.isLeftEP(this);
  // vertexEvent* nuLineOtherEP = lineObj.getOtherEP(this);
  if (replacePointerList.size() > 0) {
    for (auto iter = replacePointerList.begin();
         iter < replacePointerList.end(); iter++) {
      // Not at risk of colinearity from this->pos and line->pos overlap
      auto degenEP = static_cast<degenEvent *>((*iter)->data);
      auto otherDegenEP = degenEP->linePointer->getOtherEP(this);
      if (vorGeo::checkLeftOf(this->pos, otherDegenEP->pos, lineObj.pos,
                              10000) < 0) {
        replacePointerList.insert(iter, degenObjNode);
        return;
      }
    }
  }
  replacePointerList.push_back(degenObjNode);

  isEP = true;
}
