#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef MATHANDGEO
#define MATHANDGEO

// Double Floating Point Geometry Operations
// These strictly accept vector<doubles>
#include <algorithm>
#include <cmath>
#include "vecOverrides.hpp"

class lineEvent;
class vertexEvent;
class siteEvent;

namespace vorGeo {
typedef struct circFlags {
  arrXY XY;
  double R;
  bool isValid;
  bool isPinch;
} circOut;
// Magnitude.  sqrt(sum(vec^2))
double norm(const arrXY &arr2d);

// Distance between two vectors.  Sqrt(sum(diff^2))
inline double dist(const arrXY &p1, const arrXY &p2) {
  return std::sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) +
                   (p1[1] - p2[1]) * (p1[1] - p2[1]));
  // result.reserve(p1.size());
  // result = p1 - p2;
  // return sqrt(std::inner_product(result.begin(), result.end(),
  // result.begin(), 0.0));
}
// Elementwise division of vector by magnitude
arrXY normalize(const arrXY &vec);

// Checks if lines are parallel in 2d.  Can accept a tolerance parameter
bool isParallel(const arrABC &ABC1, const arrABC &ABC2);

bool isParallel(const arrABC &ABC1, const arrABC &ABC2, const double tol);

// Orient 2d.  1 is EP3 is left of the line ep1 -> ep2.  0 if colinear.  -1
// otherwise
int checkLeftOf(const arrXY &ep1, const arrXY &ep2, const arrXY &ep3);
int checkLeftOf(const arrXY &ep1, const arrXY &ep2, const arrXY &ep3,
                const double &maxVal);

// 2D only - approximation that does not calculate angle linearly but enough for
// basic comparisons
double angleBetween(const arrXY &dir1, const arrXY &dir2);

arrXY betweenAngleBisector_AB(const lineEvent &lineA, const lineEvent &lineB);
// vecDBL betweenAngleBisector_AB(const lineEvent &lineA, const lineEvent
// &lineB);

// 2D only
arrABC betweenAngleBisector(const arrABC &ABC1, const arrABC &ABC2,
                            const arrXY &EP1, const arrXY &EP2);

arrABC betweenAngleBisector(const lineEvent &ABC1, const lineEvent &ABC2);

// 2D Only
arrXY Intersect2d(const arrABC &ABC1, const arrABC &ABC2);
arrXY Intersect2d(const arrXY &EP1, const arrXY &dir1, const arrXY &EP2,
                  const arrXY &dir2);

arrABC perpendicularBisector2D(const arrABC &ABC, const arrXY &pos);
arrABC perpendicularBisector2D(const arrXY &ABC, const arrXY &pos);

arrXY perpendicularBisector2D(const arrABC &ABC);

arrABC points2Line(const arrXY &EP1, const arrXY &EP2);

double perpDistancePoint2Line(const arrABC &ABC, const arrXY &pos);

arrXY findClosestPoint(const arrABC &ABC, const arrXY &pos);

arrXY points2Line_AB(const arrXY &EP1, const arrXY &EP2);

arrXY getControlPoint(const lineEvent &line, const arrXY &point,
                      const arrXY &startPos, const arrXY &endPos);

arrXY rotate_CCW(const arrXY &point, const double &COS, const double &SIN);
arrABC rotate_CCW(const arrABC &point, const double &COS, const double &SIN);

arrXY rotate_CW(const arrXY &point, const double &COS, const double &SIN);
arrABC rotate_CW(const arrABC &point, const double &COS, const double &SIN);

arrXY rotate_CCW(const arrXY &point, const arrXY &dirMat);
arrABC rotate_CCW(const arrABC &point, const arrXY &dirMat);

arrXY rotate_CW(const arrXY &point, const arrXY &dirMat);
arrABC rotate_CW(const arrABC &point, const arrXY &dirMat);

vecDBL elementMean(const vecDBL &a, const vecDBL &b);
arrXY elementMean(const arrXY &a, const arrXY &b);
// arrABC elementMean(const arrABC &a, const arrABC &b);

arrXY getClosest_Generic(siteEvent *S, siteEvent *T);

arrXY getClosest(const void *S, const vertexEvent *T);

arrXY getClosest(const vertexEvent *S, const lineEvent *T);

arrXY getClosest(const lineEvent *S, const lineEvent *T);

// Cent is for special case handling, otherwise it's unnecessary
vorGeo::circFlags pointsToCircle(const arrXY &p1, const arrXY &p2,
                                 const arrXY &p3, const arrXY &cent);
#ifndef _UNSAFE
vorGeo::circFlags pointsToCircle_CloseCase(const arrXY &p1_close,
                                           const arrXY &p2_close,
                                           const arrXY &p3_other,
                                           const arrXY &cent, double tolOffset);
#endif
// vecDBL closestPoint_General(siteEvent* Source, siteEvent* Target);
typedef struct {
  vecDBL closeXY;
  vecDBL closeXY_Trunc;
  int truncFlag;
} closestPoint_Out;
typedef struct {
  arrXY closeXY;
  arrXY closeXY_Trunc;
  int truncFlag;
} closestPoint_Out_ARR;

closestPoint_Out closestPoint_TRUNC(const vecDBL &ep1, const vecDBL &ep2,
                                    const vecDBL &c);
closestPoint_Out_ARR closestPoint_TRUNC(const arrXY &ep1, const arrXY &ep2,
                                        const arrXY &c);
}  // namespace vorGeo
#endif
