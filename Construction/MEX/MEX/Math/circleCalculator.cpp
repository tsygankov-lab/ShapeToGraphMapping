#include <exception>
#include "../DataTypes/siteEvent.hpp"
#include "circleCalculators.hpp"
// Add a special case for if two points are too close to each other (10^-7 or
// less?).  Return the average of one of the two points and the other.
// If three points overlap, return the average of the three points or throw an
// exception. Throw an exception if _NOAPPROX.  Do not perform the check in
// _UNSAFE mode.
#ifndef _SKIP_CHECKS
class CircleEventValidationFailure : public std::exception {
  virtual const char *what() const throw() {
    return "The registered circle is NOT Equidistant";
  }
} circValExcept;

class CircleEventValidationFailureOrientation : public std::exception {
  virtual const char *what() const throw() {
    return "A registered circle has failed an orientation check";
  }
} circValOriExcept;
// Add orientation checks
void validateCircle(vorGeo::circFlags circ, const siteEvent *A,
                    const siteEvent *B, const siteEvent *C) {
  auto distA = A->distToPoint(circ.XY);
  auto distB = B->distToPoint(circ.XY);
  auto distC = C->distToPoint(circ.XY);
  // Circle event LLP seems to have precision issues (10^-10(?) digit)

  auto oriA = A->orientationCheck(circ.XY);
  auto oriB = B->orientationCheck(circ.XY);
  auto oriC = C->orientationCheck(circ.XY);
  auto tolFact = std::fmax(A->maxPos(), std::fmax(B->maxPos(), C->maxPos()));
  if (!_ALMOST_EQUAL(circ.R, distA, tolFact * 1000000000) ||
      !_ALMOST_EQUAL(circ.R, distB, tolFact * 1000000000) ||
      !_ALMOST_EQUAL(circ.R, distC, tolFact * 1000000000)) {
    throw circValExcept;
  }
  if (!oriA || !oriB || !oriC) {
    throw circValOriExcept;
  }
}
#endif

namespace vorCirc {
vorGeo::circFlags circlePPP(const vertexEvent &p1, const vertexEvent &p2,
                            const vertexEvent &p3) {
  auto circ = vorGeo::pointsToCircle(p1.pos, p2.pos, p3.pos, p1.cent);
#ifndef _SKIP_CHECKS
  validateCircle(circ, &p1, &p2, &p3);
#endif  //
  return circ;
}  // namespace vorCirc
#ifndef _UNSAFE
vorGeo::circFlags circlePPP_CloseFilter(const vertexEvent &p1,
                                        const vertexEvent &p2,
                                        const vertexEvent &p3) {
  vorGeo::circFlags circ;
  auto maxElement = _MAXVAL_3xARRXY(p1.pos, p2.pos, p3.pos) + 0.0001;
  bool p12close = _ARRAY2_ALMOST_EQUAL(
      p1.pos, p2.pos, maxElement * _SIMILARITY_THRESHOLD_ROUGH);
  bool p23close = _ARRAY2_ALMOST_EQUAL(
      p2.pos, p3.pos, maxElement * _SIMILARITY_THRESHOLD_ROUGH);
  bool p13close = _ARRAY2_ALMOST_EQUAL(
      p1.pos, p3.pos, maxElement * _SIMILARITY_THRESHOLD_ROUGH);
  if (p12close && p23close) {
    circ.XY = vorGeo::elementMean(p1.pos, vorGeo::elementMean(p1.pos, p2.pos));
    circ.R = vorGeo::dist(circ.XY, p1.pos);
    circ.isPinch = false;
    circ.isValid = true;
    return circ;
  } else {
    if (p12close) {
      auto vecFromCent = p1.pos - p1.cent;
      arrXY p1Adj;
      // arrXY p2Adj;
      if (p1.objectIndex < p2.objectIndex) {
        p1Adj[0] = p1.pos[0] - vecFromCent[1];  // lefter point
        p1Adj[1] = p1.pos[1] + vecFromCent[0];
        // p2Adj[0] = p2.pos[0] + vecFromCent[1];  // rigther point
        // p2Adj[1] = p2.pos[1] - vecFromCent[0];
      } else {
        p1Adj[0] = p1.pos[0] + vecFromCent[1];
        p1Adj[1] = p1.pos[1] - vecFromCent[0];
      }
      // Same twist check for degenerate cases
      if (vorGeo::checkLeftOf(p1Adj, p2.pos, p3.pos,
                              maxElement * _SIMILARITY_THRESHOLD_VERY_FINE) >
          0) {
        return vorGeo::pointsToCircle_CloseCase(p1.pos, p2.pos, p3.pos, p1.cent,
                                                maxElement);
      }
    } else if (p23close) {
      auto vecFromCent = p2.pos - p2.cent;
      arrXY p2Adj;
      if (p2.objectIndex < p3.objectIndex) {
        p2Adj[0] = p2.pos[0] - vecFromCent[1];  // lefter point
        p2Adj[1] = p2.pos[1] + vecFromCent[0];
        // p2Adj[0] = p2.pos[0] + vecFromCent[1];  // rigther point
        // p2Adj[1] = p2.pos[1] - vecFromCent[0];
      } else {
        p2Adj[0] = p2.pos[0] + vecFromCent[1];
        p2Adj[1] = p2.pos[1] - vecFromCent[0];
      }
      if (vorGeo::checkLeftOf(p1.pos, p2Adj, p3.pos,
                              maxElement * _SIMILARITY_THRESHOLD_VERY_FINE) >
          0) {
        return vorGeo::pointsToCircle_CloseCase(p2.pos, p3.pos, p1.pos, p1.cent,
                                                maxElement);
      }
    } else if (p13close) {
      auto vecFromCent = p1.pos - p1.cent;
      arrXY p1Adj;
      // arrXY p2Adj;
      if (p1.objectIndex < p3.objectIndex) {
        p1Adj[0] = p1.pos[0] - vecFromCent[1];  // lefter point
        p1Adj[1] = p1.pos[1] + vecFromCent[0];
        // p2Adj[0] = p2.pos[0] + vecFromCent[1];  // rigther point
        // p2Adj[1] = p2.pos[1] - vecFromCent[0];
      } else {
        p1Adj[0] = p1.pos[0] + vecFromCent[1];
        p1Adj[1] = p1.pos[1] - vecFromCent[0];
      }
      // Same twist check for degenerate cases
      if (vorGeo::checkLeftOf(p1Adj, p2.pos, p3.pos,
                              maxElement * _SIMILARITY_THRESHOLD_VERY_FINE) >
          0) {
        return vorGeo::pointsToCircle_CloseCase(p1.pos, p3.pos, p2.pos, p1.cent,
                                                maxElement);
      }
    }
    circ.XY = {0.0, 0.0};
    circ.R = 0;
    circ.isValid = false;
    circ.isPinch = false;
    return circ;
  }
}
#endif  // _UNSAFE

// Must be ordering aware
vorGeo::circFlags circleLPP(const lineEvent &line, const vertexEvent &p1,
                            const vertexEvent &p2, int lineOrderIndex) {
  auto mABC = vorGeo::points2Line(p1.pos, p2.pos);
  auto tolScaleFactor =
      std::max(p1.maxPos(), std::max(line.maxPos(), p2.maxPos()));
  // Above cannot be zero - that would imply two points exist on top of one
  // another
  // Case: chord is parallel to line.  Find the third point by intersecting
  // the perpbis of the chord and the line
  if (vorGeo::isParallel(line.ABC, mABC, tolScaleFactor)) {
    auto avgP = (p1.pos + p2.pos) / 2.0;
    auto pmABC = vorGeo::perpendicularBisector2D(mABC, avgP);
    auto intXY = vorGeo::Intersect2d(line.ABC, pmABC);
    auto circ = vorGeo::pointsToCircle(intXY, p1.pos, p2.pos, p1.cent);

#ifndef _SKIP_CHECKS
    validateCircle(circ, &p1, &p2, &line);
#endif

    return circ;  // vorGeo::pointsToCircle(intXY, p1.pos, p2.pos, p1.cent);
  } else {
    auto g = vorGeo::Intersect2d(line.ABC, mABC);
    auto dGP1 = vorGeo::dist(g, p1.pos);
    auto dGP2 = vorGeo::dist(g, p2.pos);

    auto dGT = sqrt(dGP1 * dGP2);

    auto t1 = g + dGT * line.dir;
    auto t2 = g - dGT * line.dir;
    int twistCheck = 0;
    // Figure out if there is a better pattern for this.
    if (lineOrderIndex == 0)
      twistCheck = vorGeo::checkLeftOf(t1, p1.pos, p2.pos, 10000);
    if (lineOrderIndex == 1)
      twistCheck = vorGeo::checkLeftOf(p1.pos, t1, p2.pos, 10000);
    if (lineOrderIndex == 2)
      twistCheck = vorGeo::checkLeftOf(p1.pos, p2.pos, t1, 10000);
    if (twistCheck > 0) {
      auto circ = vorGeo::pointsToCircle(t1, p1.pos, p2.pos, p1.cent);
      circ.isValid = true;
#ifndef _SKIP_CHECKS
      validateCircle(circ, &p1, &p2, &line);
#endif  //
      return circ;
    } else {
      twistCheck = 0;
      if (lineOrderIndex == 0)
        twistCheck = vorGeo::checkLeftOf(t2, p1.pos, p2.pos, 10000);
      if (lineOrderIndex == 1)
        twistCheck = vorGeo::checkLeftOf(p1.pos, t2, p2.pos, 10000);
      if (lineOrderIndex == 2)
        twistCheck = vorGeo::checkLeftOf(p1.pos, p2.pos, t2, 10000);
      auto circ = vorGeo::pointsToCircle(t2, p1.pos, p2.pos, p1.cent);
      circ.isValid = false;
      if (twistCheck > 0) {
        circ.isValid = true;
#ifndef _SKIP_CHECKS
        validateCircle(circ, &p1, &p2, &line);
#endif  //
      }
      return circ;
    }
  }
}

// Needs to know ordering for the test
vorGeo::circFlags circleLLP(const lineEvent &line1, const lineEvent &line2,
                            const vertexEvent &p,
                            std::array<int, 3> inputOrientation) {
  if (line1.isEP(&p) && line2.isEP(&p)) {
    vorGeo::circFlags circ;
    circ.XY = {p.pos[0], p.pos[1]};
    circ.R = 0;
    circ.isPinch = true;
    circ.isValid = true;
#ifndef _SKIP_CHECKS
    validateCircle(circ, &line1, &line2, &p);
#endif            //
    return circ;  // std::make_pair(arrXYR({p.pos[0], p.pos[1], 0.0}), true);
  } else {
    auto tolScale =
        2 * std::max(line1.maxPos(), std::max(line2.maxPos(), p.maxPos()));
    arrABC uAngBis;
    // This computation is wrong?
    // if (vorGeo::isParallel(line1.ABC, line2.ABC, tolScale)) {
    //   if (line1.UPPER == line2.UPPER) {
    //     uAngBis[0] = line1.dir[0];
    //     uAngBis[1] = -line1.dir[1];
    //   } else {
    //     uAngBis[0] = -line1.dir[1];
    //     uAngBis[1] = line1.dir[0];
    //   }
    //   auto sampEP = line1.endPoints[0]->pos;
    //   auto closeP = vorGeo::findClosestPoint(line2.ABC, sampEP);
    //   auto passesThru = (sampEP + closeP) / 2.0;
    //   uAngBis[2] = -(uAngBis[0] * passesThru[0] + uAngBis[1] *
    //   passesThru[1]);
    // } else {
    //   uAngBis = vorGeo::betweenAngleBisector(line1, line2);
    // }
    uAngBis = vorGeo::betweenAngleBisector(line1, line2);
    auto pABC = vorGeo::perpendicularBisector2D(uAngBis, p.pos);
    auto bisXY = vorGeo::Intersect2d(uAngBis, pABC);
    auto g = vorGeo::Intersect2d(line1.ABC, pABC);

    auto diff = bisXY - p.pos;
    auto q = p.pos + 2.0 * diff;

    auto dGP = vorGeo::dist(g, p.pos);
    auto dGQ = vorGeo::dist(g, q);
    auto dGT = sqrt(dGP * dGQ);

    auto t1 = g + dGT * line1.dir;

    auto pABCt1 = vorGeo::perpendicularBisector2D(line1.ABC, t1);
    auto circXY = vorGeo::Intersect2d(uAngBis, pABCt1);

    auto closeL2 = vorGeo::findClosestPoint(line2.ABC, circXY);

    // Review this at some point... It works, but...
    std::array<arrXY, 3> pointList;
    // the 'Twist' depends on the ordering of the initial objects
    pointList[inputOrientation[0]] = t1;
    pointList[inputOrientation[1]] = closeL2;
    pointList[inputOrientation[2]] = p.pos;

    auto validator =
        vorGeo::checkLeftOf(pointList[0], pointList[1], pointList[2], 10000);

    if (validator > 0) {
      vorGeo::circFlags circ;
      circ.XY = circXY;
      circ.R = vorGeo::dist(circXY, p.pos);
      circ.isValid =
          line1.orientationCheck(circ.XY) && line2.orientationCheck(circ.XY);
      // If the circle is correctly oriented to
      // both lines, then the tangent points on
      // the lines are also correctly oriented
      // (unless something with the math is wrong)
      circ.isPinch = false;
#ifndef _SKIP_CHECKS
      if (circ.isValid) validateCircle(circ, &line1, &line2, &p);
#endif  //
      return circ;
    } else {
      vorGeo::circFlags circ;

      auto t2 = g - dGT * line1.dir;
      auto pABCt2 = vorGeo::perpendicularBisector2D(line1.ABC, t2);
      circ.XY = vorGeo::Intersect2d(uAngBis, pABCt2);
      circ.R = vorGeo::dist(circ.XY, p.pos);
      circ.isPinch = false;
      circ.isValid =
          line1.orientationCheck(circ.XY) && line2.orientationCheck(circ.XY);
      // Need to do betweenEP here for line2?

#ifndef _SKIP_CHECKS
      if (circ.isValid) validateCircle(circ, &line1, &line2, &p);
#endif  //
      return circ;
    }
  }
}

vorGeo::circFlags circleLLL(const lineEvent &line1, const lineEvent &line2,
                            const lineEvent &line3) {
  vorGeo::circFlags circ;
  auto bisABC1 = vorGeo::betweenAngleBisector(
      line1, line2);  // now checks parallel status before intersection
  auto bisABC2 = vorGeo::betweenAngleBisector(line2, line3);
  circ.XY = vorGeo::Intersect2d(bisABC1, bisABC2);
  circ.R = vorGeo::perpDistancePoint2Line(line1.ABC, circ.XY);
  circ.isValid = true;
  circ.isPinch = false;
#ifndef _SKIP_CHECKS
  validateCircle(circ, &line1, &line2, &line3);
#endif  // _DEBUG
  return circ;
}

vorGeo::circFlags circleLP(const lineEvent &line, const vertexEvent &p,
                           const vertexEvent &EP) {
  vorGeo::circFlags circ;

  auto pABC = vorGeo::perpendicularBisector2D(line.ABC, EP.pos);

  auto mpXY = (EP.pos + p.pos) / 2.0;

  // perp bisector of the chord p->EP
  auto bisABC = vorGeo::perpendicularBisector2D(
      arrXY{-(p.pos[1] - EP.pos[1]), p.pos[0] - EP.pos[0]}, mpXY);

  if (vorGeo::isParallel(bisABC, pABC)) {
    // If this is true, the function should never have been called.  Still can
    // be calculated
    circ.XY = mpXY;
    circ.R = vorGeo::dist(mpXY, EP.pos);
    circ.isPinch = false;
    circ.isValid = true;
#ifndef _SKIP_CHECKS
    validateCircle(circ, &line, &p, &EP);
#endif  //
    return circ;
  } else {
    circ.XY = vorGeo::Intersect2d(pABC, bisABC);
    circ.R = vorGeo::dist(circ.XY, EP.pos);
    circ.isPinch = false;
    circ.isValid = true;
#ifndef _SKIP_CHECKS
    validateCircle(circ, &line, &p, &EP);
#endif  //
    return circ;
  }
}

// First line is the line w/ the EP.  Second is the independent line
vorGeo::circFlags circleLL(const lineEvent &line, const lineEvent &indpLine,
                           const vertexEvent &EP) {
  // Note: This assumes that the circle event lies along the normal to the
  // line at the endpoint. This is because the only true vertex-creating
  // circle events lie along this position.  However, this function will still
  // return a circle even if the above case is not true.  These false circle
  // events get filtered later.
  vorGeo::circFlags circ;
  if (line.isEP(&EP) && indpLine.isEP(&EP)) {
    circ.XY = EP.pos;
    circ.R = 0.0;
    circ.isPinch = true;
    circ.isValid = true;
#ifndef _SKIP_CHECKS
    validateCircle(circ, &line, &indpLine, &EP);
#endif  //
    return circ;
  } else {
    auto pABC = vorGeo::perpendicularBisector2D(line.ABC, EP.pos);
    // EP.maxPos() can be 0
    if (vorGeo::isParallel(line.ABC, indpLine.ABC, 2 * (EP.maxPos() + 1))) {
      auto intXY = vorGeo::Intersect2d(pABC, indpLine.ABC);
      circ.XY = (intXY + EP.pos) / 2.0;
      circ.R = vorGeo::dist(circ.XY, EP.pos);
      circ.isPinch = false;
      circ.isValid = true;
#ifndef _SKIP_CHECKS
      validateCircle(circ, &line, &indpLine, &EP);
#endif  //
      return circ;
    } else {
      auto bisABC = vorGeo::betweenAngleBisector(line, indpLine);
      circ.XY = vorGeo::Intersect2d(pABC, bisABC);
      circ.R = vorGeo::dist(circ.XY, EP.pos);
      circ.isPinch = false;

      // Will explain the tolerance below - accumulation of round-off errors can
      // cause the selected circle location to be slightly off of where it
      // should be ideally. Occurs due to vertex peturbation in images when
      // lines are otherwise perfectly vertical or horizontal auto tolScale =
      // _EPSILON
      // * indpLine.magnitude * 50000000;

      auto btwEP = indpLine.betweenEP(circ.XY);
      circ.isValid = line.orientationCheck(circ.XY) &&
                     indpLine.orientationCheck(circ.XY) && btwEP >= -(.01) &&
                     btwEP <= 1 + .01;

      // btwEP gives the ratio of the distance to the projected point from EP1
      // over the distance to EP2 from EP1.  For many circle events in images,
      // where edges have right-angled orientations and unit lengths, the circle
      // point should project down on EP2.  Some edges are slightly peturbed to
      // ensure no two points are overlapping.  The accumulation of floating
      // point error when normalizing by their slightly lower distance,
      // computing the slightly off-angle bisector, and so on causes the circle
      // event to be placed slightly off (with small error).  The projection of
      // said circle event will then project down to a point usually 0.5%
      // further than the edge of the line, even if it should be a valid circle
      // event (I think the FP error is in the projection calculation). This
      // should still get detected as a valid pseudoLP circle event, but this
      // does not seem to occur - and this should be investigated (maybe the
      // center line must get eliminated first?).  Need to severely review the
      // need for btwEP and potentially remove it. It is currently needed for
      // some arbritrary Voronoi diagrams (should it be, line should get cut off
      // at the endpoint?), but having a strict filter breaks true diagrams due
      // to small errors.

      // if ((btwEP < 0.0 && btwEP > -1.0) || (btwEP > 1.0 && btwEP < 2.0)) {
      //  auto testThing = indpLine.betweenEP(circ.XY);
      //  auto debuggertrigger = 2 + 2;
      //}
      // Likely faster to just never create a false circle event rather than
      // letting it be invalidated later...

      // Ensures that the circle event defined
      // from the two tangent points lies on the
      // correct side of both lines. betweenEP furhter
      // ensures that the circle event lies 'under' the line

      // Could be done in advance?  Check betweenEP in the circle filter
      // function?

#ifndef _SKIP_CHECKS
      if (circ.isValid) validateCircle(circ, &line, &indpLine, &EP);
#endif  //
      return circ;
    }
  }
}
}  // namespace vorCirc
