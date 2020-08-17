//#include "vorHeader.hpp"
#include "basicMathAndGeometry.hpp"
#include "../DataTypes/siteEvent.hpp"
#include "../precisionChecks.hpp"

//#include <cmath>
#include <algorithm>
#include <numeric>
// Magnitude.  sqrt(sum(vec^2))

double vorGeo::norm(const arrXY &arr2d) {
  // Innerproduct of a and a is the dot product
  return std::sqrt(arr2d[0] * arr2d[0] + arr2d[1] * arr2d[1]);
}
// Distance between two vectors.  Sqrt(sum(diff^2))
// double vorGeo::dist(const vecDBL &p1, const vecDBL &p2) {
//	return sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] -
// p2[1]));
// result.reserve(p1.size());
// result = p1 - p2;
// return sqrt(std::inner_product(result.begin(), result.end(), result.begin(),
// 0.0));
//}

// Elementwise division of vector by magnitude
arrXY vorGeo::normalize(const arrXY &vec) { return vec / norm(vec); }

// 1 if parallel.  Uses maximum value of A, B, C to determine tolerance.  2D
// only
bool vorGeo::isParallel(const arrABC &ABC1, const arrABC &ABC2) {
  double maxval = fmax(fmax(std::abs(ABC1[0]), std::abs(ABC1[1])),
                       fmax(std::abs(ABC2[0]), std::abs(ABC2[1])));
  return _ALMOST_EQUAL(ABC1[1] * ABC2[0], ABC1[0] * ABC2[1], maxval);
}

bool vorGeo::isParallel(const arrABC &ABC1, const arrABC &ABC2,
                        const double tolScale) {
  // double max = fmax(fmax(std::abs(ABC1[0]), abs(ABC1[1])),
  // fmax(std::abs(ABC2[0]), abs(ABC2[1])));
  return _ALMOST_EQUAL(ABC1[1] * ABC2[0], ABC1[0] * ABC2[1], tolScale);
}
// Orient 2d.  1 is EP3 is left of the line ep1 -> ep2.  0 if colinear.  -1
// otherwise
int vorGeo::checkLeftOf(const arrXY &ep1, const arrXY &ep2, const arrXY &ep3) {
  // assert(ep1.size() == 2 && ep2.size() == 2 && ep3.size() == 2);

  double maxVal = fmax(fmax(std::abs(ep1[0]), std::abs(ep1[1])),
                       fmax(fmax(std::abs(ep2[0]), std::abs(ep2[1])),
                            fmax(std::abs(ep3[0]), std::abs(ep3[1]))));
  double tol = (maxVal)*_EPSILON * 1000;
  double z = (ep2[0] - ep1[0]) * (ep3[1] - ep1[1]) -
             (ep2[1] - ep1[1]) * (ep3[0] - ep1[0]);
  if (z > tol) {
    return 1;
  } else if (z < -tol) {
    return -1;
  } else {
    return 0;
  }
}
int vorGeo::checkLeftOf(const arrXY &ep1, const arrXY &ep2, const arrXY &ep3,
                        const double &maxVal) {
  // assert(ep1.size() == 2 && ep2.size() == 2 && ep3.size() == 2);

  // double maxVal = fmax(fmax(std::abs(ep1[0]), abs(ep1[1])),
  // fmax(fmax(std::abs(ep2[0]), abs(ep2[1])), fmax(std::abs(ep3[0]),
  // abs(ep3[1]))));
  double tol = (maxVal)*_EPSILON;
  double z = (ep2[0] - ep1[0]) * (ep3[1] - ep1[1]) -
             (ep2[1] - ep1[1]) * (ep3[0] - ep1[0]);
  if (z > tol) {
    return 1;
  } else if (z < -tol) {
    return -1;
  } else {
    return 0;
  }
}

// 2D only - approximation that does not calculate angle linearly but enough for
// basic comparisons

double vorGeo::angleBetween(const arrXY &dir1, const arrXY &dir2) {
  auto dir1N = normalize(dir1);
  auto dir2N = normalize(dir2);

  double sinth = dir1N[0] * dir1N[1] - dir1N[1] * dir2N[0];
  double costh = dir1N[0] * dir2N[0] - dir1N[1] * dir2N[1];

  if (sinth <= 0) {
    return (sinth -
            (double)(costh < _EPSILON) * (2.0 * (1.0 - std::abs(sinth))));
  } else {
    return (sinth +
            (double)(costh < _EPSILON) * (2.0 * (1.0 - std::abs(sinth))));
  }
  return 0;
}

// 2D only

arrABC vorGeo::betweenAngleBisector(const arrABC &ABC1, const arrABC &ABC2,
                                    const arrXY &EP1, const arrXY &EP2) {
  auto intersect = Intersect2d(ABC1, ABC2);

  arrXY DL1 = {intersect[0] - EP1[0], intersect[1] - EP1[1]};
  arrXY DL2 = {intersect[0] - EP2[0], intersect[1] - EP2[1]};

  DL1 = normalize(DL1);
  DL2 = normalize(DL2);

  arrXY bisVec = DL1 + DL2;
  arrABC biABC{-bisVec[1], bisVec[0],
               -(bisVec[0] * intersect[0] + bisVec[1] * intersect[1])};
  return biABC;
}

arrABC vorGeo::betweenAngleBisector(const lineEvent &lineA,
                                    const lineEvent &lineB) {
  if (vorGeo::isParallel(lineA.ABC, lineB.ABC,
                         std::max(lineA.maxPos(), lineB.maxPos()))) {
    auto signComparator =
        (_ALMOST_ZERO(lineB.ABC[0], lineB.rad * 100))
            ? lineA.ABC[1] / lineB.ABC[1]
            : lineA.ABC[0] / lineB.ABC[0];  // now scales correctly...
    return arrABC({lineA.ABC[0], lineA.ABC[1],
                   (lineA.ABC[2] + signComparator * lineB.ABC[2]) / 2.0});
  } else {
    auto intercept = vorGeo::Intersect2d(lineA.ABC, lineB.ABC);
    arrABC bisABC{0.0, 0.0, 0.0};
    if (lineA.UPPER == lineB.UPPER) {
      bisABC[1] = -(lineA.dir[1] + lineB.dir[1]);
      bisABC[0] = -(lineA.dir[0] + lineB.dir[0]);
    } else {
      bisABC[1] = (lineA.dir[0] + lineB.dir[0]);
      bisABC[0] = -(lineA.dir[1] + lineB.dir[1]);
    }
    bisABC[2] = -(bisABC[0] * intercept[0] + bisABC[1] * intercept[1]);
    return bisABC;
  }
}

arrXY vorGeo::betweenAngleBisector_AB(const lineEvent &lineA,
                                      const lineEvent &lineB) {
  // auto interscept = vorGeo::Intersect2d(lineA.ABC, lineB.ABC);
  arrXY bisABC{0.0, 0.0};
  if (lineA.UPPER == lineB.UPPER) {
    bisABC[1] = -(lineA.dir[1] + lineB.dir[1]);
    bisABC[0] = -(lineA.dir[0] + lineB.dir[0]);
  } else {
    bisABC[1] = (lineA.dir[0] + lineB.dir[0]);
    bisABC[0] = -(lineA.dir[1] + lineB.dir[1]);
  }
  // bisABC[2] = -(bisABC[0] * interscept[0] + bisABC[1] * interscept[1]);
  return bisABC;
}
// 2D Only - Numerically unstable?
arrXY vorGeo::Intersect2d(const arrABC &ABC1, const arrABC &ABC2) {
  double denom = (ABC1[1] * ABC2[0]) - (ABC1[0] * ABC2[1]);
  double num1 = (ABC1[2] * ABC2[1] - ABC1[1] * ABC2[2]);
  double num2 = (ABC2[2] * ABC1[0] - ABC2[0] * ABC1[2]);

  // assert(std::abs(denom) > machEps);
  arrXY intersect{num1 / denom, num2 / denom};
  return intersect;
}

arrXY vorGeo::Intersect2d(const arrXY &EP1, const arrXY &dir1, const arrXY &EP2,
                          const arrXY &dir2) {
  auto d = (dir1[0] * dir2[1] - dir2[0] * dir1[1]);  // risk if almost parallel
  auto t = (dir2[1] * (EP2[0] - EP1[0]) - dir2[0] * (EP2[1] - EP1[1])) / d;
  return arrXY{EP1[0] + dir1[0] * t, EP1[1] + dir1[1] * t};
}

arrABC vorGeo::points2Line(const arrXY &EP1, const arrXY &EP2) {
  arrABC ABC;
  // ABC.reserve(3);
  ABC[0] = EP1[1] - EP2[1];
  ABC[1] = EP2[0] - EP1[0];
  ABC[2] = EP1[0] * EP2[1] - EP1[1] * EP2[0];
  return ABC;
}
// 2D
arrXY vorGeo::findClosestPoint(const arrABC &ABC, const arrXY &pos) {
  auto A = ABC.at(0);
  auto B = ABC.at(1);
  auto C = ABC.at(2);
  auto X = pos.at(0);
  auto Y = pos.at(1);
  return arrXY{(B * (B * X - A * Y) - A * C) / (A * A + B * B),
               (A * (-B * X + A * Y) - B * C) / (A * A + B * B)};
}

arrXY vorGeo::getClosest_Generic(siteEvent *S, siteEvent *T) {
  if (T->objType == VERTEX)
    return T->pos;
  else if (S->objType == VERTEX)
    return getClosest(static_cast<vertexEvent *>(S),
                      static_cast<lineEvent *>(T));
  else
    return getClosest(static_cast<lineEvent *>(S), static_cast<lineEvent *>(T));
}

arrXY vorGeo::getClosest(const void *S, const vertexEvent *T) { return T->pos; }

arrXY vorGeo::getClosest(const vertexEvent *S, const lineEvent *T) {
  return closestPoint_TRUNC(T->endPoints[0]->pos, T->endPoints[1]->pos, S->pos)
      .closeXY_Trunc;
}

arrXY vorGeo::getClosest(const lineEvent *S, const lineEvent *T) {
  auto flipSign(S->UPPER ? 1 : -1);
  auto valEP1 =
      flipSign * vorGeo::checkLeftOf(S->endPoints[0]->pos, S->endPoints[1]->pos,
                                     T->endPoints[0]->pos,
                                     _SIMILARITY_THRESHOLD_VERY_FINE);
  if (valEP1 > 0)
    return T->endPoints[1]->pos;
  else
    return T->endPoints[0]->pos;
}

/*std::vector<double> getClosestPoint(siteEvent* Source, siteEvent* Target) {//
(siteEvent* Source, siteEvent* Target) {
        if (Target->objType == VERTEX) {
                return Target->pos;
        }

        //Vert->Line
        auto lTarget = static_cast<lineEvent*>(Target);
        if (Source->objType != LINE) {
                return
std::get<0>(closestPoint_TRUNC(lTarget->endPoints[0]->pos,
lTarget->endPoints[1]->pos, Source->pos));
        }

        //Line->Line
        auto lSource = static_cast<lineEvent*>(Source);

        auto flipSign(lSource->UPPER ? 1 : -1);
        auto valEP1 = flipSign*checkLeftOf(lSource->endPoints[0]->pos,
lSource->endPoints[1]->pos, lTarget->endPoints[0]->pos);
        if (valEP1 <= 0) {
                return lTarget->endPoints[1]->pos;
        }
        else if (valEP1 > 0) {
                return lTarget->endPoints[0]->pos;
        }
        return vecDBL({ 0.0,0.0 });
        return vecDBL({ 0.0,0.0 });
}*/

arrXY vorGeo::points2Line_AB(const arrXY &EP1, const arrXY &EP2) {
  return arrXY{EP1[1] - EP2[1], EP2[0] - EP1[0]};
}

arrABC vorGeo::perpendicularBisector2D(const arrABC &ABC, const arrXY &pos) {
  return arrABC{-ABC.at(1), ABC.at(0),
                -(-ABC.at(1) * pos.at(0) + ABC.at(0) * pos.at(1))};
}
arrABC vorGeo::perpendicularBisector2D(const arrXY &ABC, const arrXY &pos) {
  return arrABC{-ABC.at(1), ABC.at(0),
                -(-ABC.at(1) * pos.at(0) + ABC.at(0) * pos.at(1))};
}

arrXY vorGeo::perpendicularBisector2D(const arrABC &ABC) {
  return arrXY{-ABC.at(1), ABC.at(0)};
}

double vorGeo::perpDistancePoint2Line(const arrABC &ABC, const arrXY &pos) {
  return std::abs(ABC[0] * pos[0] + ABC[1] * pos[1] + ABC[2]) /
         std::sqrt(ABC[0] * ABC[0] + ABC[1] * ABC[1]);
}

arrXY vorGeo::getControlPoint(const lineEvent &line, const arrXY &point,
                              const arrXY &startPos, const arrXY &endPos) {
  auto SIN = line.dir.at(1);
  auto COS = line.dir.at(0);

  auto rotPoint = rotate_CW(point, COS, SIN);
  auto rotStart = rotate_CW(startPos, COS, SIN);
  auto rotEnd = rotate_CW(endPos, COS, SIN);

  auto p = rotPoint.at(1) - line.infRad;

  auto vertX = rotPoint.at(0);

  auto slopeStart = (2 * rotStart.at(0) - 2 * vertX) / (2 * p);
  auto slopeEnd = (2 * rotEnd.at(0) - 2 * vertX) / (2 * p);

  auto interceptStart = rotStart.at(1) - slopeStart * rotStart.at(0);
  auto interceptEnd = rotEnd.at(1) - slopeEnd * rotEnd.at(0);

  auto xIntersect = (interceptEnd - interceptStart) / (slopeStart - slopeEnd);
  auto yIntersect = xIntersect * slopeStart + interceptStart;

  return rotate_CCW(arrXY{xIntersect, yIntersect}, COS, SIN);
}

// 2D until matrix class implemented...

arrXY vorGeo::rotate_CCW(const arrXY &point, const double &COS,
                         const double &SIN) {
  return arrXY{point.at(0) * COS - point.at(1) * SIN,
               point.at(0) * SIN + point.at(1) * COS};
}
arrABC vorGeo::rotate_CCW(const arrABC &point, const double &COS,
                          const double &SIN) {
  return arrABC{point.at(0) * COS - point.at(1) * SIN,
                point.at(0) * SIN + point.at(1) * COS, 0.0};
}

arrXY vorGeo::rotate_CW(const arrXY &point, const double &COS,
                        const double &SIN) {
  return arrXY{point.at(0) * COS + point.at(1) * SIN,
               -point.at(0) * SIN + point.at(1) * COS};
}
arrABC vorGeo::rotate_CW(const arrABC &point, const double &COS,
                         const double &SIN) {
  return arrABC{point.at(0) * COS + point.at(1) * SIN,
                -point.at(0) * SIN + point.at(1) * COS, 0.0};
}

arrXY vorGeo::rotate_CCW(const arrXY &point, const arrXY &dirMat) {
  return arrXY{point.at(0) * dirMat[0] - point.at(1) * dirMat[1],
               point.at(0) * dirMat[1] + point.at(1) * dirMat[0]};
}
// Did not calculate C for rotation in previous code, must not have been needed?
arrABC vorGeo::rotate_CCW(const arrABC &point, const arrXY &dirMat) {
  return arrABC{point.at(0) * dirMat[0] - point.at(1) * dirMat[1],
                point.at(0) * dirMat[1] + point.at(1) * dirMat[0], 0.0};
}

arrXY vorGeo::rotate_CW(const arrXY &point, const arrXY &dirMat) {
  return arrXY{point.at(0) * dirMat[0] + point.at(1) * dirMat[1],
               -point.at(0) * dirMat[1] + point.at(1) * dirMat[0]};
}
arrABC vorGeo::rotate_CW(const arrABC &point, const arrXY &dirMat) {
  return arrABC{point.at(0) * dirMat[0] + point.at(1) * dirMat[1],
                -point.at(0) * dirMat[1] + point.at(1) * dirMat[0], 0.0};
}
vecDBL vorGeo::elementMean(const vecDBL &a, const vecDBL &b) {
  return (a + b) / 2.0;
}
arrXY vorGeo::elementMean(const arrXY &a, const arrXY &b) {
  return arrXY(a + b) / 2.0;
}

vorGeo::closestPoint_Out_ARR vorGeo::closestPoint_TRUNC(const arrXY &ep1,
                                                        const arrXY &ep2,
                                                        const arrXY &c) {
  closestPoint_Out_ARR returnStruct;
  auto p(ep2 - ep1);
  auto u = ((c[0] - ep1[0]) * p[0] + (c[1] - ep1[1]) * p[1]) /
           (p[0] * p[0] + p[1] * p[1]);  // element wise differences
  auto trunc(u);
  returnStruct.truncFlag = 0;
  if (trunc >= 1.0) {
    trunc = 1.0;
    returnStruct.truncFlag = 2;
  } else if (trunc <= 0.0) {
    trunc = 0.0;
    returnStruct.truncFlag = 1;
  }

  returnStruct.closeXY_Trunc = ep1 + trunc * p;
  returnStruct.closeXY = ep1 + u * p;
  return returnStruct;
}

vorGeo::circFlags vorGeo::pointsToCircle(const arrXY &p1, const arrXY &p2,
                                         const arrXY &p3, const arrXY &cent) {
  /*This is the following math:
  h = [x1^2+y1^2,y1,1;x2^2+y2^2,y2,1;x3^2+y3^2,y3,1];
  k = [x1,x1^2+y1^2,1;x2,x2^2+y2^2,1;x3,x3^2+y3^2,1];
  l = [x1,y1,1;x2,y2,1;x3,y3,1];

  [x,y] = [det(h),det(k)]/(2*det(l))
  */
  vorGeo::circFlags circ;
  auto maxElement = _MAXVAL_3xARRXY(p1, p2, p3) +
                    0.0001;  // the 0.0001 ensures this is not 0...
  // moving overlap handler to circlePPP.  Other cases with lines may need to be
  // worked on independently.
  auto detL = p1[0] * (p2[1] - p3[1]) - p1[1] * (p2[0] - p3[0]) +
              (p2[0] * p3[1] - p2[1] * p3[0]);
  // zero if collinear or if points are indistinguishable.
  if (!_ALMOST_ZERO(detL, maxElement)) {
    auto p1sqsm = p1[0] * p1[0] + p1[1] * p1[1];
    auto p2sqsm = p2[0] * p2[0] + p2[1] * p2[1];
    auto p3sqsm = p3[0] * p3[0] + p3[1] * p3[1];

    auto detH = (p1sqsm) * (p2[1] - p3[1]) - (p2sqsm) * (p1[1] - p3[1]) +
                (p3sqsm) * (p1[1] - p2[1]);
    auto detK = p1[0] * (p2sqsm - p3sqsm) - p2[0] * (p1sqsm - p3sqsm) +
                p3[0] * (p1sqsm - p2sqsm);
    circ.XY[0] = detH / (2.0 * detL);
    circ.XY[1] = detK / (2.0 * detL);
    circ.R = vorGeo::dist(circ.XY, p1);
    circ.isValid = true;
    circ.isPinch = false;
    return circ;
  }
  circ.XY = {0.0, 0.0};
  circ.R = 0.0;
  circ.isPinch = false;
  circ.isValid = false;
  return circ;
}

#ifndef _UNSAFE
vorGeo::circFlags vorGeo::pointsToCircle_CloseCase(const arrXY &p1_close,
                                                   const arrXY &p2_close,
                                                   const arrXY &p3,
                                                   const arrXY &cent,
                                                   double tolOffset) {
  double tol = (tolOffset)*_SIMILARITY_THRESHOLD_FINER;
  // If tolOffset is zero, then all three points are (0,0).  isParallel will
  // return true (with min tol of '1'), and so an intersect should never be
  // computed.  If intersect2d is somehow called on parallel lines anyways,
  // arrXY will be 'nan'.  If all three points are close in space, then
  // circlePPP will handle it.

  vorGeo::circFlags circ;
  arrABC bisA;
  arrABC bisB;
  auto lineSeg = vorGeo::points2Line_AB(p1_close, p2_close);
  if (_ARRAY2_ALMOST_EQUAL(p1_close, p2_close, tol)) {
    // Points are incredibly close even with a finer precision threshold,
    bisA = vorGeo::points2Line(p1_close, cent);
    if (_ALMOST_ZERO(bisA[0], tol) && _ALMOST_ZERO(bisA[1], tol)) {
      // By some chance, if you have a pair of close points that are also at
      // the center, pretend they are split by a vertical line
      bisA[0] = 0;
      bisA[1] = 1;
      bisA[2] = 0;
    }
  } else {
    bisA = vorGeo::perpendicularBisector2D(
        lineSeg, vorGeo::elementMean(p1_close, p2_close));
  }
  bisB = vorGeo::perpendicularBisector2D(vorGeo::points2Line_AB(p2_close, p3),
                                         vorGeo::elementMean(p2_close, p3));
  if (!vorGeo::isParallel(bisA, bisB, tol + 1.0)) {
    circ.XY = vorGeo::Intersect2d(bisA, bisB);
    circ.R = vorGeo::dist(circ.XY, p1_close);
    circ.isValid = true;
    circ.isPinch = false;
    return circ;
  } else {
    circ.XY = {0.0, 0.0};
    circ.R = 0;
    circ.isValid = false;
    circ.isPinch = false;
    return circ;
  }
}
#endif
