#include "siteEvent.hpp"

vertexEvent *lineEvent::getOtherEP(vertexEvent *otherEP) {
  // Assume that you are giving a valid EP in the first place...
  if (otherEP == this->endPoints[0]) {
    return this->endPoints[1];
  } else {
    return this->endPoints[0];
  }
}

bool lineEvent::isEP(vertexEvent *EP) {
  return (EP == this->endPoints[0] || EP == this->endPoints[1]);
}

bool lineEvent::isLeftEP(vertexEvent *EP) { return (EP == this->endPoints[0]); }

const vertexEvent *lineEvent::getOtherEP(const vertexEvent *otherEP) const {
  // Assume that you are giving a valid EP in the first place...
  if (otherEP == this->endPoints[0]) {
    return this->endPoints[1];
  } else {
    return this->endPoints[0];
  }
}

const bool lineEvent::isEP(const vertexEvent *EP) const {
  return (EP == this->endPoints[0] || EP == this->endPoints[1]);
}

const bool lineEvent::isLeftEP(const vertexEvent *EP) const {
  return (EP == this->endPoints[0]);
}

lineEvent lineEvent::createLower(void) {
  lineEvent twinEvent = (*this);
  twinEvent.UPPER = false;
  twinEvent.twin = this;
  twinEvent.objectIndex = this->objectIndex + 1;
  this->twin = &twinEvent;
  return twinEvent;
}

arrXY lineEvent::getSafeCoordinates(void) const {
  return (this->endPoints[0]->pos + this->endPoints[1]->pos) / 2.0;
}