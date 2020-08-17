#include "interceptCalculators.hpp"
#include <cmath>
#include <vector>
#include "../DataTypes/siteEvent.hpp"
#include "../precisionChecks.hpp"

#ifndef _SKIP_CHECKS
#include <exception>
#include <stdexcept>
// Add a special case handler for points that are almost equal.  If so, return
// the average of the two points

// class PointOverlap : public std::runtime_error {
//  virtual const char *what() const throw() {
//    return "The computed intersect point is NOT Equidistant";
//  }
//};

// Change to runtime error
class IntersectValidationFailture : public std::exception {
  virtual const char *what() const throw() {
    return "The computed intersect point is NOT Equidistant";
  }
} intValExcept;

// Maybe accept rad as an input since computations depend on rad.
void validateIntercept(arrXY XY, const siteEvent *A, const siteEvent *B) {
  auto distA = A->distToPoint(XY);
  auto distB = B->distToPoint(XY);
  // parabellipse slightly off
  if (!_ALMOST_EQUAL(
          distA, distB,
          std::fmax(A->maxPos(), B->maxPos()) * _SIMILARITY_THRESHOLD_ROUGH)) {
    std::string classType1 = A->objType == LINE ? "L" : "P";
    std::string classType2 = B->objType == LINE ? "L" : "P";

    std::string classType1_Comp = A->toString_Comprehensive();
    std::string classType2_Comp = B->toString_Comprehensive();
    std::string ERRSTRING =
        "The computed intersect point between " + classType1 +
        std::to_string(A->objectIndex) + " and " + classType2 +
        std::to_string(B->objectIndex) +
        " is not equidistant.\n Dist A: " + std::to_string(distA) +
        " \n Dist B: " + std::to_string(distB) + " \n Intercept Location: (" +
        std::to_string(XY[0]) + ", " + std::to_string(XY[1]) +
        ")\nAdditional Object Information:\n ObjA: \n" + classType1_Comp +
        "\n ObjB: \n" + classType2_Comp;

    throw std::runtime_error(ERRSTRING);
  }

  auto oriA = A->orientationCheck(XY);
  auto oriB = B->orientationCheck(XY);
  if (!oriA || !oriB) {
    std::string classType1 = A->objType == LINE ? "L" : "P";
    std::string classType2 = B->objType == LINE ? "L" : "P";
    std::string classType1_Comp = A->toString_Comprehensive();
    std::string classType2_Comp = B->toString_Comprehensive();
    std::string ERRSTRING =
        "The computed intercept point between " + classType1 +
        std::to_string(A->objectIndex) + " and " + classType2 +
        std::to_string(B->objectIndex) +
        " fails an orientation check.\n oriA: " + std::to_string(oriA) +
        " \n oriB: " + std::to_string(oriB) + " \n Intercept Location: (" +
        std::to_string(XY[0]) + ", " + std::to_string(XY[1]) +
        ")\nAdditional Object Information:\n ObjA: \n" + classType1_Comp +
        "\n ObjB: \n" + classType2_Comp;
    throw std::runtime_error(ERRSTRING);
  }
}
#endif  //_SKIP_CHECKS

arrXY vorGeo::degenLine(const lineEvent &line, const double &rad,
                        bool orientationFlag) {
  arrXY XY;
  if (std::abs(line.rad - rad) > _EPSILON * rad) {
    if (!orientationFlag)
      XY[0] = sqrt(rad * rad -
                   line.infRad * line.infRad);  // XY.insert(XY.begin(),
                                                // sqrt(rad*rad -
                                                // line.infRad*line.infRad));
    else
      XY[0] = -sqrt(rad * rad -
                    line.infRad * line.infRad);  // XY.insert(XY.begin(),
                                                 // -sqrt(rad*rad -
                                                 // line.infRad*line.infRad));
    XY[1] = line.infRad;  // XY.insert(XY.begin() + 1, line.infRad);
    return vorGeo::rotate_CCW(XY, line.dir);
  }
  return line.pos;  // Only if condition fails
}

/*Calculates the intersection points for two ellipses which share a foci by
identifying the bisector of the
unique focus, and then finding the intersect with one of the two ellipses.
Selects the appropiate intersection
based on the fact that the desired intersection point should be clockwise of
vertA and counterclockwise of
vertB.
Optimization note:  Ellipse A is rotate to lie in the plane of the x axis.  It
should be possible at this
stage to know which of the two possible intersects we desire without actually
computing the intersect.
It will vary based on the sign of the y value of the other foci.
*/
arrXY vorGeo::dualEllipse(const vertexEvent &vertA, const vertexEvent &vertB,
                          const double &rad, bool allowShortcuts) {
  // This needs to use the regular pathway and intersect ellipse1 with the
  // bisector.  Circle event for overlapping points needs dualEllipse to be
  // exact.  Add a special case handler for if vertA_rad = vertBrad = rad, where
  // the intersect is (0,0).
  // To distinguish signs for (exact) identical points, use objectIndex.
  if (allowShortcuts &&
      _ALMOST_EQUAL(vertB.rad, rad, rad * _SIMILARITY_THRESHOLD_FINER)) {
    // Passes through center of circle.  Becomes numerically imprecise (sqrtterm
    // ~= 0)
    // Find the more general equation here.
    return vertB.pos;  // all that is needed for the output
  }
#ifndef _UNSAFE
  if (_ARRAY2_ALMOST_EQUAL(vertA.pos, vertB.pos,
                           rad * _SIMILARITY_THRESHOLD_ROUGH)) {
#ifdef _THROW_ON_OVERLAP
    // exception to be implemented
#endif
    // For consistency - change to the intercept of an ellipse with a bisector
    // defined as the ray from the center to here.  Use object index to pick
    // which arc correspond to which element.
    // Ignore above - not worth it, and no longer need this to be perfectly
    // correct
    return vorGeo::elementMean(vertA.pos, vertB.pos);  // This is fine.
    // return vorGeo::dualEllipse_CloseCase(vertA, vertB, rad);
  }
#endif

  auto cossin = (vertA.pos - vertA.cent) /
                vertA.rad;  // normalized distance matrix for rotation
  auto rotShiftA = vorGeo::rotate_CW(vertA.pos - vertA.cent, cossin);
  auto rotShiftB = vorGeo::rotate_CW(vertB.pos - vertA.cent, cossin);
  rotShiftA[0] -= 0.5 * vertA.rad;
  rotShiftB[0] -= 0.5 * vertA.rad;
  auto bisectorCrosses = vorGeo::elementMean(rotShiftA, rotShiftB);

  auto chordAB = vorGeo::points2Line_AB(rotShiftA, rotShiftB);
  auto chordBis = vorGeo::perpendicularBisector2D(chordAB, bisectorCrosses);
  arrXY intercept;
#ifdef _DEBUG
  arrXY interceptAlt;
#endif
  // vecDBL interceptB(2);
  if (std::abs(chordBis[1]) > _EPSILON_F(rad)) {
    // Worth rechecking some of this math... line  -> ellipse intersect
    // if (_ALMOST_EQUAL(vertB.rad, rad, rad * 100)) {
    // Case for where vertB's ellipse is degenerate, meaning that the sqrt
    // term will be near zero.  This becomes the intersection between the
    // bisector and the ray from the center to vertB
    // auto a = rad / 2.0;
    // auto m = -chordBis[0] / chordBis[1];  // slope of bisector of input
    // points auto z = -chordBis[2] /
    //            chordBis[1];  // Y intercept of bisector of input points
    //  auto asq = a * a;
    // auto msq = m * m;
    // auto bsqrd = (asq) - (1.0 / 4.0) * (vertA.rad * vertA.rad);
    // Square root term is zero.
    //  intercept[0] = ((-m * asq * z)) / (asq * msq + bsqrd);
    //  intercept[1] = m * intercept[0] + z;
    //  intercept[0] += 0.5 * vertA.rad;
    //#ifdef _DEBUG
    //   interceptAlt[0] = ((-m * asq * z)) / (asq * msq + bsqrd);
    //      interceptAlt[1] = m * intercept[0] + z;
    //      interceptAlt[0] += 0.5 * vertA.rad;
    //#endif

    //  } else {
    auto a = rad / 2.0;
    auto asq = a * a;
    auto m = -chordBis[0] / chordBis[1];  // slope of bisector of input points
    auto z =
        -chordBis[2] / chordBis[1];  // Y intercept of bisector of input points
    auto msq = m * m;
    auto zsq = z * z;
    auto bsqrd = (asq) - (1.0 / 4.0) * (vertA.rad * vertA.rad);

    auto radicalTerm =
        asq * asq * bsqrd * msq + asq * bsqrd * bsqrd - asq * bsqrd * zsq;
    // abs =/= std::abs?
    auto absRadicalTerm = std::abs(radicalTerm);

    auto sqrtTerm = sqrt(absRadicalTerm);
#ifdef _DEBUG
    assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG

    if (rotShiftB[1] < 0) {
      intercept[0] = ((-m * asq * z) + sqrtTerm) / (asq * msq + bsqrd);
      intercept[1] = m * intercept[0] + z;
      intercept[0] += 0.5 * vertA.rad;
#ifdef _DEBUG
      interceptAlt[0] = ((-m * asq * z) - sqrtTerm) / (asq * msq + bsqrd);
      interceptAlt[1] = m * intercept[0] + z;
      interceptAlt[0] += 0.5 * vertA.rad;
#endif
    } else {
      intercept[0] = ((-m * asq * z) - sqrtTerm) / (asq * msq + bsqrd);
      intercept[1] = m * intercept[0] + z;
      intercept[0] += 0.5 * vertA.rad;
#ifdef _DEBUG
      interceptAlt[0] = ((-m * asq * z) + sqrtTerm) / (asq * msq + bsqrd);
      interceptAlt[1] = m * intercept[0] + z;
      interceptAlt[0] += 0.5 * vertA.rad;
#endif
    }
#ifdef _DEBUG
#ifndef _SKIP_CHECKS
    auto pointAlt = vorGeo::rotate_CCW(interceptAlt, cossin) + vertA.cent;
    auto point = vorGeo::rotate_CCW(intercept, cossin) + vertA.cent;
    validateIntercept(point, &vertA, &vertB);
#endif
#endif
    // }
  } else {
    auto a = rad / 2.0;
    auto asq = a * a;
    auto bsqrd = (asq) - (1.0 / 4.0) * (vertA.rad * vertA.rad);
    auto xval = bisectorCrosses[0];
    auto sqrtTerm = sqrt(std::abs(bsqrd - bsqrd * xval * xval / asq));
#ifdef _DEBUG
    assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG
    // For the alt case, if the rotated other point is to the left, the correct
    // intersect is below.  Otherwise, it is the point on top
    if (rotShiftB[0] - rotShiftA[0] > 0) {
      intercept[0] = xval + 0.5 * vertA.rad;
      intercept[1] = sqrtTerm;
#ifdef _DEBUG
      interceptAlt[0] = xval + 0.5 * vertA.rad;
      interceptAlt[1] = -sqrtTerm;
#endif
    } else {
      intercept[0] = xval + 0.5 * vertA.rad;
      intercept[1] = -sqrtTerm;
#ifdef _DEBUG
      interceptAlt[0] = xval + 0.5 * vertA.rad;
      interceptAlt[1] = sqrtTerm;
#endif  // _DEBUG
    }
  }
#ifdef _DEBUG
  auto pointAlt = vorGeo::rotate_CCW(interceptAlt, cossin) + vertA.cent;
#endif

  auto point = vorGeo::rotate_CCW(intercept, cossin) + vertA.cent;
#ifndef _SKIP_CHECKS
  validateIntercept(point, &vertA, &vertB);
#endif
  return point;  // vorGeo::rotate_CCW(intercept, cossin) + vertA.cent;
}

arrXY vorGeo::dualEllipse_CloseCase(const vertexEvent &vertA,
                                    const vertexEvent &vertB,
                                    const double &rad) {
  // This is 99.9% the same function... but calculates a different chordBis and
  // has different rules for selecting interceptions
  arrXY intercept;
  auto cossin = (vertA.pos - vertA.cent) / vertA.rad;
  auto rotShiftA = vorGeo::rotate_CW(vertA.pos - vertA.cent, cossin);
  auto rotShiftB = vorGeo::rotate_CW(vertB.pos - vertB.cent, cossin);
  auto bisectorCrosses = vorGeo::elementMean(rotShiftA, rotShiftB);
  auto chordBis = vorGeo::points2Line(bisectorCrosses, arrXY{0.0, 0.0});
  if (std::abs(chordBis[1]) > _EPSILON_F(rad)) {
    // This branch should be the only one called.  chordBis should be the line y
    // = 0 for the most part
    if (_ALMOST_EQUAL(vertB.rad, rad, rad * 100)) {
      auto a = rad / 2.0;
      auto m = -chordBis[0] / chordBis[1];
      auto z = -chordBis[2] / chordBis[1];
      auto asq = a * a;
      auto msq = m * m;
      auto bsqrd = asq - 1.0 / 4.0 * (vertA.rad * vertA.rad);
      intercept[0] = ((-m * asq * z)) / (asq * msq + bsqrd);
      intercept[1] = m * intercept[0] + z;
      intercept[0] += 0.5 * vertA.rad;
    } else {
      auto a = rad / 2.0;
      auto asq = a * a;
      auto m = -chordBis[0] / chordBis[1];
      auto z = -chordBis[2] / chordBis[1];
      auto msq = m * m;
      auto zsq = z * z;
      auto bsqrd = (asq) - (1.0 / 4.0) * (vertA.rad * vertA.rad);
      auto sqrtTerm = std::sqrt(asq * asq * bsqrd * msq + asq * bsqrd * bsqrd -
                                asq * bsqrd * zsq);
#ifdef _DEBUG
      assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG
      if (vertA.objectIndex < vertB.objectIndex) {
        intercept[0] = ((-m * asq * z) + sqrtTerm) / (asq * msq + bsqrd);
        intercept[1] = m * intercept[0] + z;
        intercept[0] += 0.5 * vertA.rad;
      } else {
        intercept[0] = ((-m * asq * z) - sqrtTerm) / (asq * msq + bsqrd);
        intercept[1] = m * intercept[0] + z;
        intercept[0] += 0.5 * vertA.rad;
      }
    }
  } else {
    // This should never get called
    auto a = rad / 2.0;
    auto asq = a * a;
    auto bsqrd = (asq) - (1.0 / 4.0) * (vertA.rad * vertA.rad);
    auto xval = bisectorCrosses[0];
    auto sqrtTerm = sqrt(bsqrd - bsqrd * xval * xval / asq);
#ifdef _DEBUG
    assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG
    if (vertA.objectIndex < vertB.objectIndex) {
      intercept[0] = xval + 0.5 * vertA.rad;
      intercept[1] = sqrtTerm;
    } else {
      intercept[0] = xval + 0.5 * vertA.rad;
      intercept[1] = -sqrtTerm;
    }
  }
  auto point = vorGeo::rotate_CCW(intercept, cossin) + vertA.cent;
#ifndef _SKIP_CHECKS
  validateIntercept(point, &vertA, &vertB);
#endif
  return point;
}

arrXY vorGeo::dualParabola(const lineEvent &lineA, const lineEvent &lineB,
                           const double &rad) {
  // Lots of opportunities for code modification...
  auto _PARALLEL_FLAG = vorGeo::isParallel(lineA.ABC, lineB.ABC);
  arrABC bisABC{0.0, 0.0, 0.0};
  arrXY XY{0.0, 0.0};

  // HACK HACK HACK
  // This executes in the scenario where two lines which are next to each
  // other and forming an edge are degenerate, causing there parabolas to be a
  // straight line which intersects at 0,0 Realistically can only occur on the
  // first iteration Likely Better (Not horrible) method: Compute directional
  // bisector, do rad* that
  if (_ALMOST_EQUAL(lineA.rad, rad, rad) &&
      _ALMOST_EQUAL(lineB.rad, rad, rad)) {
    if (!lineA.UPPER && !lineB.UPPER) {
      if (!_PARALLEL_FLAG) {
        bisABC = vorGeo::betweenAngleBisector(lineA, lineB);
      }
      // Matlab code refers to 'matched offset,' for parallel lines connected
      // by an endpoint. In this context, I believe this cannot exist (degen
      // AND matched offset where this code actually executes)
      else {
        auto signComparator =
            (_ALMOST_ZERO(lineB.ABC[0], lineB.rad * 100))
                ? lineA.ABC[1] / lineB.ABC[1]
                : lineA.ABC[0] / lineB.ABC[0];  // now scales correctly...
        bisABC = {lineA.ABC[0], lineA.ABC[1],
                  (lineA.ABC[2] + signComparator * lineB.ABC[2]) / 2.0};
      }

      // Investigate alternative calculations that do not require these
      // checks...
      if (_ALMOST_ZERO(bisABC[1], std::max(lineA.maxPos(), lineB.maxPos()))) {
        XY[0] = bisABC[2] / bisABC[0];
        if (lineA.pos[0] >= lineB.pos[0]) {
          XY[0] *= -1.0;
        }
        XY[1] = 1.0;
      } else {
        if (_ALMOST_EQUAL(lineA.pos[0], lineA.cent[0], lineA.pos[0])) {
          XY[1] = lineA.pos[1];
          XY[0] = -1.0 * (XY[1] * bisABC[1] + bisABC[2]) / bisABC[0];
        } else {
          XY[0] = lineA.pos[0];
          XY[1] = -(XY[0] * bisABC[0] + bisABC[2]) / bisABC[1];
        }

        if (_ALMOST_EQUAL(XY[0], lineA.cent[0], XY[0]) &&
            _ALMOST_EQUAL(XY[1], lineA.cent[1], XY[1])) {
          auto bisABC2 = vorGeo::perpendicularBisector2D(bisABC, XY);
          if (_ALMOST_ZERO(bisABC2[1],
                           std::max(lineA.maxPos(), lineB.maxPos()))) {
            XY[0] = bisABC2[2] / bisABC2[0];
            if (lineA.pos[0] >= lineB.pos[0]) {
              XY[0] *= -1.0;
            }
            XY[1] = 1.0;
          } else {
            if (_ALMOST_EQUAL(lineA.pos[0], lineA.cent[0], lineA.maxPos())) {
              XY[1] = lineA.pos[1];
              XY[0] = -(XY[1] * bisABC2[1] + bisABC2[2]) / bisABC2[0];
            } else {
              XY[0] = lineA.pos[0];
              XY[1] = -(XY[0] * bisABC2[0] + bisABC2[2]) / bisABC2[1];
            }
          }
        }
      }
    } else {
      XY = lineB.isEP(lineA.endPoints[1]) ? lineA.endPoints[1]->pos
                                          : lineA.endPoints[0]->pos;
      // XY = lineA.endPoints[1]->pos;
    }
#ifndef _SKIP_CHECKS
    validateIntercept(XY, &lineA, &lineB);
#endif
    return XY;
  }
  // Real code starts here

  // Can reduce some of these calculations by calculating things based on dir
  // rather than ABC
  auto rotABCA = vorGeo::rotate_CW(
      lineA.ABC, lineA.dir);  // Only reads for two values of lineA.ABC...
  auto rotABCB = vorGeo::rotate_CW(lineB.ABC, lineA.dir);

  auto rotPosA = vorGeo::rotate_CW(lineA.pos, lineA.dir);
  auto rotPosB = vorGeo::rotate_CW(lineB.pos, lineA.dir);
  rotABCA[2] = -1.0 * (rotABCA[0] * rotPosA[0] + rotABCA[1] * rotPosA[1]);
  rotABCB[2] = -1.0 * (rotABCB[0] * rotPosB[0] + rotABCB[1] * rotPosB[1]);
  // rotABCA.push_back(-1.0*(rotABCA[0] * rotPosA[0] + rotABCA[1] *
  // rotPosA[1]));
  // rotABCB.push_back(-1.0*(rotABCB[0] * rotPosB[0] + rotABCB[1] *
  // rotPosB[1])); //Sets the 'C' element of this vector

  if (!_PARALLEL_FLAG) {
    auto intXY = vorGeo::Intersect2d(rotABCA, rotABCB);
    auto rotDirA = vorGeo::rotate_CW(lineA.dir, lineA.dir);  //...huh
    auto rotDirB = vorGeo::rotate_CW(lineB.dir, lineA.dir);
    if (lineA.UPPER == lineB.UPPER) {
      bisABC[1] = -(rotDirB[1] + rotDirA[1]);
      bisABC[0] = -(rotDirB[0] + rotDirA[0]);
    } else {
      bisABC[0] = -(rotDirB[1] + rotDirA[1]);
      bisABC[1] = (rotDirB[0] + rotDirA[0]);
    }
    bisABC[2] = -(bisABC[0] * intXY[0] + bisABC[1] * intXY[1]);
  } else {
    auto signComparator =
        (_ALMOST_ZERO(rotABCB[0], lineB.maxPos()))
            ? rotABCA[1] / rotABCB[1]
            : rotABCA[0] / rotABCB[0];  // now scales correctly...
    bisABC[0] = rotABCA[0];
    bisABC[1] = rotABCA[1];
    bisABC[2] = (rotABCA[2] + signComparator * rotABCB[2]) / 2.0;
  }
  auto focus = vorGeo::rotate_CW(lineA.cent, lineA.dir);

  auto directrixHeight(lineA.infRad + focus[1]);

  if (!lineA.UPPER) {
    directrixHeight -= rad;
  } else {
    directrixHeight += rad;
  }

  auto p = focus[1] - directrixHeight;
  auto vertY = (focus[1] + directrixHeight) / 2.0;

  if (_ALMOST_ZERO(p, rad)) {
    auto pABC = vorGeo::perpendicularBisector2D(lineA.ABC, lineA.pos);
    if (!_PARALLEL_FLAG) {
      bisABC = vorGeo::betweenAngleBisector(lineA, lineB);
    } else {
      auto signComparator =
          (_ALMOST_ZERO(lineB.ABC[0], lineB.rad * 100))
              ? lineA.ABC[1] / lineB.ABC[1]
              : lineA.ABC[0] / lineB.ABC[0];  // now scales correctly...

      bisABC[0] = lineA.ABC[0];
      bisABC[1] = lineA.ABC[1];
      bisABC[2] = (lineA.ABC[2] + signComparator * (lineB.ABC[2])) / 2.0;
    }
    auto point = vorGeo::Intersect2d(pABC, bisABC);

#ifndef _SKIP_CHECKS
    auto distA = lineA.distToPoint(point);
    auto distB = lineB.distToPoint(point);
    auto distDiff = distA - distB;
#ifdef _DEBUG
    auto altPointTest = vorGeo::dualParabola_LLC(lineA, lineB, rad);
    auto altDistA = lineA.distToPoint(altPointTest);
    auto altDistB = lineB.distToPoint(altPointTest);
#endif

    validateIntercept(point, &lineA, &lineB);
#endif
    return point;  // vorGeo::Intersect2d(pABC, bisABC);
  } else {
    // REFACTOR TARGET
    if (_ALMOST_ZERO(bisABC[1], pow(2.0, 26))) {
      // 2^26 = sqrt(eps)
      XY[0] = -1.0 * bisABC[2] / bisABC[0];
      XY[1] = pow((XY[0] - focus[0]), 2.0) / (2.0 * p) + vertY;
      auto point = vorGeo::rotate_CCW(XY, lineA.dir);

#ifndef _SKIP_CHECKS
      validateIntercept(point, &lineA, &lineB);
#endif

      return point;  // vorGeo::rotate_CCW(XY, lineA.dir);
    } else {
      auto qa = 1.0 / (2.0 * p);  // This number gets ugly at large radii!!
      auto qb = -(focus[0]) / p + bisABC[0] / bisABC[1];
      auto qc =
          vertY + (bisABC[2] / bisABC[1]) + (focus[0] * focus[0]) / (2 * p);

      auto sqrtTerm = sqrt(qb * qb - 4.0 * qa * qc);
#ifdef _DEBUG
      assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG
      XY[0] = (-qb + sqrtTerm) / (2.0 * qa);
      XY[1] = -(bisABC[0] * XY[0] + bisABC[2]) / bisABC[1];
      auto point = vorGeo::rotate_CCW(XY, lineA.dir);

#ifndef _SKIP_CHECKS
#ifdef _ALT_LLC_TEST
      auto altPointTest = vorGeo::dualParabola_LLC(
          lineA, lineB, rad);  // also check dist to sweep circle...

      auto distA = lineA.distToPoint(point);
      auto distB = lineB.distToPoint(point);
      auto distC = rad - vorGeo::dist(point, lineA.cent);
      auto altDistA = lineA.distToPoint(altPointTest);
      auto altDistB = lineB.distToPoint(altPointTest);
      auto altDistC = rad - vorGeo::dist(altPointTest, lineA.cent);
      auto distDiff = distA - distB;
      auto distDiff_Ar = distA - distC;
      auto distDiff_Br = distB - distC;
      auto altDistDiff = altDistA - altDistB;
      auto altDistDiff_Ar = altDistA - altDistC;
      auto altDistDiff_Br = altDistB - altDistC;
      auto diffPoints = vorGeo::dist(point, altPointTest);
#endif
      validateIntercept(point, &lineA, &lineB);
#endif
      return point;  // vorGeo::rotate_CCW(XY, lineA.dir);
    }
  }
}

arrXY vorGeo::dualParabola_LLC(const lineEvent &lineA, const lineEvent &lineB,
                               const double &rad) {
  // Must be non-parallel
  if (!vorGeo::isParallel(lineA.ABC, lineB.ABC)) {
    // Twin lines *should* have their dir changed, but this is not the case
    auto lineA_norm = lineA.UPPER
                          ? arrXY{lineA.dir[1], -lineA.dir[0]}
                          : arrXY{-lineA.dir[1], lineA.dir[0]};  // dir is unit
    auto lineB_norm = lineB.UPPER
                          ? arrXY{lineB.dir[1], -lineB.dir[0]}
                          : arrXY{-lineB.dir[1], lineB.dir[0]};  // dir is unit

    auto lineA_circTan =
        lineA_norm * rad + lineA.cent;  // risk of error accum in rad and dir
    auto lineB_circTan = lineB_norm * rad + lineA.cent;
    auto XY_A = lineA.infPos;
    auto XY_B = lineB.infPos;
    auto XY_C = lineA.cent;
    auto XY_D =
        vorGeo::Intersect2d(lineA.ABC,
                            lineB.ABC);  // Intersection of the two lines
    auto XY_E = vorGeo::Intersect2d(
        lineA_circTan, lineA.dir, lineB_circTan,
        lineB.dir);  // Intersection of the lines when tangent to sweep cricle

    auto L_ED =
        XY_E - XY_D;  // From line-line intersect -> tangent line intersect
    auto L_CD = XY_C - XY_D;  // Cent to line intersection (0 if lines intersect
                              // at origin, > rad if outside of it)

    auto a =
        L_ED[0] * L_ED[0] +
        L_ED[1] * L_ED[1];  // Will be zero when lines are both tangent to the
                            // circle and you are checking for an intersect with
                            // their 'upper' components (non sensical). Diameter
                            // of sweep circle when spawning in (IIRC)

    auto bBy2 = L_ED[0] * L_CD[0] +
                L_ED[1] * L_CD[1];  // Cross product finds if it intersects
    auto c = L_CD[0] * L_CD[0] + L_CD[1] * L_CD[1] -
             rad * rad;  // negative when lines intersect inside
                         // the circle, postive otherwise

    auto pBy2 = bBy2 / a;
    auto q = c / a;  // Must negate for lower lines (at least if they go outside
                     // the circle)?
    auto disc = pBy2 * pBy2 - q;  // Grows when sweep circle expands
#ifdef _DEBUG
    assert(disc >= 0);
#endif  // DEBUG
    auto tmpSqrt = std::sqrt(disc);
    auto deScaleFactor1 =
        -pBy2 + tmpSqrt;  // Has to do with the side the ED line lies on wrt CD
    auto deScaleFactor2 = -pBy2 - tmpSqrt;
    auto p = XY_D - L_ED * deScaleFactor1;
    auto L_PC =
        vorGeo::points2Line(p, XY_C);  // for UL and UU so far. Has to do with

    auto p_lowerAlt1 = XY_D + L_ED * deScaleFactor1;
    auto point_lowerAlt1 =
        vorGeo::Intersect2d(vorGeo::points2Line(p_lowerAlt1, XY_C),
                            vorGeo::betweenAngleBisector(lineA, lineB));
    auto p_lowerAlt2 = XY_D - L_ED * deScaleFactor2;  // Lower lower
    auto point_lowerAlt2 = vorGeo::Intersect2d(
        vorGeo::points2Line(p_lowerAlt2, XY_C),
        vorGeo::betweenAngleBisector(lineA, lineB));  // for LL intercepts?
    auto p_lowerAlt3 = XY_D + L_ED * deScaleFactor2;
    auto point_lowerAlt3 =
        vorGeo::Intersect2d(vorGeo::points2Line(p_lowerAlt3, XY_C),
                            vorGeo::betweenAngleBisector(lineA, lineB));

    auto point =
        vorGeo::Intersect2d(L_PC, vorGeo::betweenAngleBisector(lineA, lineB));
    return point;
  } else {
    return arrXY{0.0, 0.0};
  }
}
arrXY vorGeo::endpointLine(const vertexEvent &EP, const lineEvent &line,
                           const double &rad) {
  arrXY XY{0.0, 0.0};
  if (!_ALMOST_EQUAL(EP.rad, rad, rad)) {
    auto rotPoint = vorGeo::rotate_CW(EP.pos, line.dir);
    auto rotFocus = vorGeo::rotate_CW(line.cent, line.dir);

    auto directrixHeight = line.infRad + rotFocus[1];
    if (!line.UPPER) {
      directrixHeight -= rad;
    } else {
      directrixHeight += rad;
    }

    if (!_ALMOST_ZERO(directrixHeight, rad)) {
      // Below are constants to a solved equation for the normal hitting the
      // parabola
      auto h2 = rotFocus[0];
      auto k2 = (rotFocus[1] + directrixHeight) / 2.0;
      auto p2 = rotFocus[1] - directrixHeight;
      auto invP2 = 1.0 / p2;  // Different way?

      XY[0] = rotPoint[0];
      XY[1] = (0.5 * invP2) * (XY[0] * XY[0]) - (invP2 * h2 * XY[0]) +
              (0.5 * invP2 * (h2 * h2)) + k2;
      auto point = vorGeo::rotate_CCW(XY, line.dir);

#ifndef _SKIP_CHECKS
      validateIntercept(point, &EP, &line);
#endif
      return point;  // vorGeo::rotate_CCW(XY, line.dir);
    }
  }
#ifndef _SKIP_CHECKS
  validateIntercept(EP.pos, &EP, &line);
#endif
  return EP.pos;
}

arrXY vorGeo::parbolaEllipse(const lineEvent &line, const vertexEvent &vert,
                             const double &rad, bool orientationFlag) {
  auto quadSign(orientationFlag ? 1.0 : -1.0);

  // Directrix height after rotation = line.infRad...

  auto rotFocusPoint = vorGeo::rotate_CW(vert.pos, line.dir);
  auto rotFocusCent = vorGeo::rotate_CW(vert.cent, line.dir);

  auto h1 = rotFocusPoint[0];
  auto k1 = (rotFocusPoint[1] + line.infRad + rotFocusCent[1]) / 2.0;

  auto p1 =
      rotFocusPoint[1] -
      (line.infRad +
       rotFocusCent[1]);  // cannot be zero - otherwise it would call EP-Line
  auto invP1 = 1.0 / p1;

  auto directrixBHeight = line.infRad + rotFocusCent[1];
  if (!line.UPPER) {
    directrixBHeight -= rad;
  } else {
    directrixBHeight += rad;
  }
  if (!_ALMOST_ZERO(directrixBHeight - rotFocusCent[1], rad)) {
    auto h2 = rotFocusCent[0];
    auto k2 = (rotFocusCent[1] + directrixBHeight) / 2.0;
    auto p2 = rotFocusCent[1] - directrixBHeight;
    auto invP2 = 1.0 / p2;

    auto qa = 0.5 * invP1 - 0.5 * invP2;
    auto qb = h2 * invP2 - h1 * invP1;
    auto qc = (0.5 * invP1 * h1 * h1) + (k1) - (0.5 * invP2 * h2 * h2) - (k2);
    // abs() is here because this square-root term can become slightly negative
    // from floating point round off if the radius of the point = the sweep
    // circle radius.
    auto sqrtTerm = sqrt(std::abs(qb * qb - 4 * qa * qc));
#ifdef _DEBUG
    assert(!std::isnan(sqrtTerm));
#endif  // _DEBUG
    auto x1 = (-qb + quadSign * sqrtTerm) / (2.0 * qa);
    auto y1 = (0.5 * invP1) * (x1 * x1) - (invP1 * h1 * x1) +
              (0.5 * invP1 * h1 * h1) + (k1);
    auto point = vorGeo::rotate_CCW(arrXY({x1, y1}), line.dir);

#ifndef _SKIP_CHECKS
    validateIntercept(point, &line, &vert);
#endif
    return point;  // vorGeo::rotate_CCW(arrXY({ x1, y1 }), line.dir);
  } else {
    auto point = vorGeo::rotate_CCW(arrXY({0.0, (0.5 * h1 * h1 * invP1) + k1}),
                                    line.dir);
#ifndef _SKIP_CHECKS

    validateIntercept(point, &line, &vert);
#endif
    return point;  // vorGeo::rotate_CCW(arrXY({ 0.0, (0.5 * h1 * h1 * invP1)
                   // + k1 }),
                   //           line.dir);
  }
}

arrXY vorGeo::ellipseCircle(const vertexEvent &vertex, const double &rad,
                            bool vertIsSecond) {
  auto cossin = (vertex.pos - vertex.cent) / vertex.rad;

  auto rotPos = vorGeo::rotate_CW(vertex.pos - vertex.cent, cossin);

  auto x = 0.5 * rotPos[0];
  auto halfRad = rad / 2;
  auto y1 = sqrt((halfRad * halfRad) - (x * x));
  auto y2 = -y1;

  arrXY interceptA = vorGeo::rotate_CCW(arrXY({x, y1}), cossin);
  arrXY interceptB = vorGeo::rotate_CCW(arrXY({x, y2}), cossin);

  // interceptA clockwise to vertex
  auto validate =
      vorGeo::checkLeftOf(vertex.cent, vertex.pos, interceptA, 10000 * rad);

  if (validate < 0) {
    if (vertIsSecond)
      return interceptB;
    else
      return interceptA;
  } else if (validate > 0) {
    if (vertIsSecond)
      return interceptA;
    else
      return interceptB;
  } else {
    // This should only occur - if ever, when rad = vertex.rad
    return vertex.pos;
  }
}

// Not needed
/*vecDBL vorGeo::parabolaCircle(const lineEvent &line, const double &rad, bool
lineIsSecond) {
        return vecDBL({ 0.0,0.0 });
        //To be implemented
}*/
