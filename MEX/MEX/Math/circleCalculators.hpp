#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef CIRCLECALCULATORS_H
#define CIRCLECALCULATORS_H

#include "../precisionChecks.hpp"
#include "basicMathAndGeometry.hpp"
#include "vecOverrides.hpp"

//#include "../DataTypes/siteEvent.hpp"
class vertexEvent;
class lineEvent;
namespace vorCirc {

vorGeo::circFlags circlePPP(const vertexEvent &p1, const vertexEvent &p2,
                            const vertexEvent &p3);
#ifndef _UNSAFE
vorGeo::circFlags circlePPP_CloseFilter(const vertexEvent &p1,
                                        const vertexEvent &p2,
                                        const vertexEvent &p3);
#endif  //  _UNSAFE

vorGeo::circFlags circleLPP(const lineEvent &line, const vertexEvent &p1,
                            const vertexEvent &p2, int lineOrderIndex);

// bool for pinch case
vorGeo::circFlags circleLLP(const lineEvent &line1, const lineEvent &line2,
                            const vertexEvent &p,
                            std::array<int, 3> inputOrientation);

vorGeo::circFlags circleLLL(const lineEvent &line1, const lineEvent &line2,
                            const lineEvent &line3);

vorGeo::circFlags circleLP(const lineEvent &line, const vertexEvent &p,
                           const vertexEvent &EP);

vorGeo::circFlags circleLL(const lineEvent &line1, const lineEvent &line2,
                           const vertexEvent &EP);
}  // namespace vorCirc
#endif
