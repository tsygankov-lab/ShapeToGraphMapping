#include "../Records/halfEdgeRecords.hpp"
#include "../precisionChecks.hpp"
#ifdef _DEBUG
#include <exception>
class SetOriginOnCompleteEdge : public std::exception {
  virtual const char *what() const throw() {
    return "setOrigin was called for a completed edge pair.";
  }
} setOriginCompEdge;
class SetOriginOnPinnedEdge : public std::exception {
  virtual const char *what() const throw() {
    return "setOrigin was called for am already completed half edge.  While "
           "this is not a fatal error, it could indicate a failure elsewhere "
           "in the algorithm";
  }
} setOriginPinnedEdge;
#endif  // _DEBUG

void vorVert::addEdge(halfEdge *edge) {
  // edges.push_back(edge); delay until finalize is called
  edge->setOrigin(this);
}

void vorVert::setPTRIDs() {
  edgeIDs.reserve(edges.size());
  faceIDs.reserve(faces.size());
  for (auto &e : edges) {
    edgeIDs.emplace_back(e->getID());
  }
  for (auto &f : faces) {
    faceIDs.emplace_back(f->id);
  }
}

void vorFace::setPTRIDs() {
  edgeIDs.reserve(edges.size());
  neighborIDs.reserve(neighbors.size());
  vertIDs.reserve(vertices.size());

  for (auto &e : edges) {
    edgeIDs.emplace_back(e->getID());
  }
  for (auto &n : neighbors) {
    neighborIDs.emplace_back(n->id);
  }
  for (auto &v : vertices) {
    vertIDs.emplace_back(v->getID());
  }
}

void halfEdge::finalizeEdge() {
  // As opposed to invalidating.  Call at runtime termination on infinite edges
  // or when edge is completed
  adjacentFace->edges.push_back(this);
  adjacentFace->neighbors.push_back(twin->adjacentFace);
  origin->faces.push_back(adjacentFace);
  origin->edges.push_back(this);
  adjacentFace->vertices.push_back(origin);
}

arrXY halfEdge::computeIntersect(double rad, bool allowShortcuts) {
  auto obj1 = adjacentFace->siteObject;
  auto obj2 = twin->adjacentFace->siteObject;

  // for object at center
  if (obj1->objType == VERTEX && obj2->objType == VERTEX &&
      obj1->pos == obj1->cent) {
    return vorGeo::ellipseCircle(*static_cast<vertexEvent *>(obj2), rad, 1);
  }
  if (obj1->objType == VERTEX && obj2->objType == VERTEX &&
      obj2->pos == obj2->cent) {
    return vorGeo::ellipseCircle(*static_cast<vertexEvent *>(obj1), rad, 0);
  }

  // one is a point, one is a line
  if ((obj1->objType == LINE) != (obj2->objType == LINE)) {
    lineEvent *pLine;
    vertexEvent *pPoint;
    bool LEFT(false);
    if (obj1->objType == LINE) {
      pLine = static_cast<lineEvent *>(obj1);
      pPoint = static_cast<vertexEvent *>(obj2);
      LEFT = false;
    } else {
      pLine = static_cast<lineEvent *>(obj2);
      pPoint = static_cast<vertexEvent *>(obj1);
      LEFT = true;
    }
    auto line = *pLine;
    auto point = *pPoint;

    // degen
    if (!point.isProcessed) {
      if (line.isLeftEP(pPoint))
        return vorGeo::degenLine(line, rad, true);
      else
        return vorGeo::degenLine(line, rad, false);
    }
    if (line.isEP(pPoint)) return vorGeo::endpointLine(point, line, rad);
    return vorGeo::parbolaEllipse(line, point, rad, LEFT);
  }

  // two liness
  if (obj1->objType == LINE && obj2->objType == LINE)
    return vorGeo::dualParabola(*static_cast<lineEvent *>(obj1),
                                *static_cast<lineEvent *>(obj2), rad);

  // two points
  return vorGeo::dualEllipse(*static_cast<vertexEvent *>(obj1),
                             *static_cast<vertexEvent *>(obj2), rad,
                             allowShortcuts);
}

void halfEdge::addTwin(halfEdge *edgeTwin) {
  twin = edgeTwin;
  twin->twin = this;
  // adjacentFace->neighbors.push_back(twin->adjacentFace);
  // twin->adjacentFace->neighbors.push_back(adjacentFace);
}

void halfEdge::setOrigin(vorVert *vertex) {
  if (COMPLETE_EDGE) {
#ifdef _DEBUG
    throw setOriginCompEdge;
#endif  // _DEBUG
    return;
  }
  if (VERTEX_SET) {
#ifdef _DEBUG
#ifdef _STRICT
    throw setOriginPinnedEdge;
#endif
#endif
    /*Non-fatal error*/
    twin->setOrigin(vertex);
    twin->VERTEX_SET = true;
    COMPLETE_EDGE = twin->COMPLETE_EDGE = true;
    if (COMPLETE_EDGE) {
      this->finalizeEdge();
      twin->finalizeEdge();
    }
    return;
  }
  origin = vertex;
  VERTEX_SET = true;
  COMPLETE_EDGE = twin->COMPLETE_EDGE = VERTEX_SET && twin->VERTEX_SET;
  if (COMPLETE_EDGE) {
    this->finalizeEdge();
    twin->finalizeEdge();
  }
  return;
}

// At Origin Only
arrXY halfEdge::getDirection() {
  if (dir == arrXY({0.0, 0.0})) {
    auto obj1 = adjacentFace->siteObject;
    auto obj2 = twin->adjacentFace->siteObject;
    if (edgeType == 0 || edgeType == 100) {
      vertexEvent *ep1 = nullptr;
      vertexEvent *ep2 = nullptr;
      // dir is the perpendicular bisector to the line. Direction depends on if
      // the left or right object is the endpoint
      if (obj1->objType == LINE) {
        ep1 = static_cast<vertexEvent *>(obj2);
        ep2 = static_cast<lineEvent *>(obj1)->getOtherEP(ep1);
        dir = {-1.0 * (ep2->pos[1] - ep1->pos[1]), (ep2->pos[0] - ep1->pos[0])};
      } else {
        ep2 = static_cast<vertexEvent *>(obj1);
        ep1 = static_cast<lineEvent *>(obj2)->getOtherEP(ep2);
        dir = {-1.0 * (ep2->pos[1] - ep1->pos[1]), (ep2->pos[0] - ep1->pos[0])};
      }

      if (!_ALMOST_ZERO(dir[0], std::max(ep1->maxPos(), ep2->maxPos())) ||
          !_ALMOST_ZERO(dir[1], std::max(ep1->maxPos(), ep2->maxPos()))) {
        dir = vorGeo::normalize(dir);
      } else {
        dir[0] = 0.0;
        dir[1] = 0.0;
      }
    } else {
      bool obj1Line = obj1->objType == LINE;
      bool obj2Line = obj2->objType == LINE;
      arrXY to;
      arrXY from;
      if (!obj1Line || !obj2Line) {  // false if both are lines
        if (obj1Line || obj2Line) {  // true if one is a line (but not both)
          lineEvent *line;
          vertexEvent *point;
          if (obj1Line) {
            line = static_cast<lineEvent *>(obj1);
            point = static_cast<vertexEvent *>(obj2);
            to = vorGeo::findClosestPoint(line->ABC, origin->pos);
            from = point->pos;
          } else {
            line = static_cast<lineEvent *>(obj2);
            point = static_cast<vertexEvent *>(obj1);
            to = point->pos;
            from = vorGeo::findClosestPoint(line->ABC, origin->pos);
          }
        } else {
          to = obj1->pos;
          from = obj2->pos;
        }
        // This function works with destination then origin, technically
        auto lABC = vorGeo::points2Line_AB(from, to);

        if (!_ALMOST_ZERO(lABC[0], std::max(obj1->maxPos(), obj2->maxPos())) ||
            !_ALMOST_ZERO(lABC[1], std::max(obj1->maxPos(), obj2->maxPos()))) {
          dir = vorGeo::normalize(arrXY{{lABC[0], lABC[1]}});
        } else {
          dir[0] = 0.0;
          dir[1] = 0.0;
          // std::fill(dir.begin(), dir.end(), 0.0);
        }
      } else {
        auto lineA = static_cast<lineEvent *>(obj1);
        auto lineB = static_cast<lineEvent *>(obj2);

        auto to = vorGeo::findClosestPoint(lineA->ABC, origin->pos);
        auto from = vorGeo::findClosestPoint(lineB->ABC, origin->pos);
        if (vorGeo::dist(from, to) < std::sqrt(_EPSILON)) {
          to = vorGeo::findClosestPoint(lineA->ABC, twin->origin->pos);
          from = vorGeo::findClosestPoint(lineB->ABC, twin->origin->pos);
        }
        auto lABC =
            vorGeo::points2Line_AB(from, to);  // refactor target.  Remove 'C'

        if (!_ALMOST_ZERO(lABC[0], std::max(obj1->maxPos(), obj2->maxPos())) ||
            !_ALMOST_ZERO(lABC[1], std::max(obj1->maxPos(), obj2->maxPos()))) {
          dir = vorGeo::normalize(arrXY{{lABC[0], lABC[1]}});
        } else {
          std::fill(dir.begin(), dir.end(), 0.0);
        }
      }
    }
  }
  return dir;
}

double halfEdge::getDistance() {
  if (dist == -1.0) {
    auto vertA = origin->pos;
    auto vertB = twin->origin->pos;
    if (edgeType != 2 && edgeType != 102) {
      dist = vorGeo::dist(vertA, vertB);
      twin->dist = dist;
    } else {
      auto obj1 = adjacentFace->siteObject;
      auto obj2 = twin->adjacentFace->siteObject;
      lineEvent *line;
      vertexEvent *point;
      if (obj1->objType == 2) {
        line = static_cast<lineEvent *>(obj1);
        point = static_cast<vertexEvent *>(obj2);
      } else {
        line = static_cast<lineEvent *>(obj2);
        point = static_cast<vertexEvent *>(obj1);
      }
      auto symABC = vorGeo::perpendicularBisector2D(line->ABC, point->pos);
      auto intXY = vorGeo::Intersect2d(symABC, line->ABC);
      auto sign1 = vorGeo::checkLeftOf(point->pos, intXY, vertA, 10000);
      auto sign2 = vorGeo::checkLeftOf(point->pos, intXY, vertB, 10000);
      auto p1 = sign1 * vorGeo::perpDistancePoint2Line(symABC, vertA);
      auto p2 = sign2 * vorGeo::perpDistancePoint2Line(symABC, vertB);
      auto f = vorGeo::perpDistancePoint2Line(line->ABC, point->pos) / 2;
      auto h1 = p1 / 2;
      auto h2 = p2 / 2;
      auto q1 = sqrt(f * f + h1 * h1);
      auto q2 = sqrt(f * f + h2 * h2);

      dist = std::abs((h1 * q1 - h2 * q2) / f + f * log((h1 + q1) / (h2 + q2)));
      twin->dist = dist;
    }
  }
  return dist;
}

arrXY halfEdge::getControlPoint() {
  if (edgeType != 2 || _ALMOST_ZERO(getDistance(), 1000))
    return arrXY{0.0, 0.0};

  auto obj1 = adjacentFace->siteObject;
  auto obj2 = twin->adjacentFace->siteObject;
  lineEvent *line;
  vertexEvent *point;
  if (obj1->objType == LINE) {
    line = static_cast<lineEvent *>(obj1);
    point = static_cast<vertexEvent *>(obj2);
  } else {
    line = static_cast<lineEvent *>(obj2);
    point = static_cast<vertexEvent *>(obj1);
  }
  auto vertA = origin->pos;
  auto vertB = twin->origin->pos;

  auto rotPoint = vorGeo::rotate_CW(point->pos, line->dir);
  auto rotS1 = vorGeo::rotate_CW(vertA, line->dir);
  auto rotS2 = vorGeo::rotate_CW(vertB, line->dir);

  auto p = rotPoint[1] - line->infRad;
  auto vertX = rotPoint[0];
  auto slopeS1 = (2 * rotS1[0] - 2 * vertX) / (2 * p);
  auto slopeS2 = (2 * rotS2[0] - 2 * vertX) / (2 * p);
  auto intercept1 = rotS1[1] - slopeS1 * rotS1[0];
  auto intercept2 = rotS2[1] - slopeS2 * rotS2[0];

  arrXY rotXY;
  rotXY[0] = (intercept2 - intercept1) / (slopeS1 - slopeS2);
  rotXY[1] = rotXY[0] * slopeS1 + intercept1;
  return vorGeo::rotate_CCW(rotXY, line->dir);
}
/* Unsure if used
void addedTwin(halfEdge* edgeTwin) {
twin = edgeTwin;
adjacentFace->neighbor
}
*/
#ifdef _DEBUG
std::string halfEdge::toString() {
  return adjacentFace->toString() + std::string("|") +
         twin->adjacentFace->toString();
}

std::string vorFace::toString() { return siteObject->toString(); }

std::string vorVert::toString() {
  std::string outString = std::string("POS: ") + std::to_string(pos[0]) +
                          std::string(", ") + std::to_string(pos[1]) +
                          std::string(" FROM: ");
  for (auto SE : sites) {
    outString += std::to_string(SE->objectIndex) + std::string(", ");
  }
  return outString;
}
#endif
