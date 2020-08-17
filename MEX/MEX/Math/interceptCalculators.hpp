#ifdef _MSC_VER
#pragma once
#endif  //_MSC_VER

#ifndef INTERCEPTCALCULATORS_H
#define INTERCEPTCALCULATORS_H

#include "../precisionChecks.hpp"
#include "basicMathAndGeometry.hpp"

//#include "../Tree/RBT.hpp"
//#include "../DataTypes/siteEvent.hpp"

class lineEvent;
class vertexEvent;
namespace vorGeo {
arrXY degenLine(const lineEvent &line, const double &rad, bool orientationFlag);

arrXY dualEllipse(const vertexEvent &vertA, const vertexEvent &vertB,
                  const double &rad, bool allowShortcuts = true);

arrXY dualEllipse_CloseCase(const vertexEvent &vertA, const vertexEvent &vertB,
                            const double &rad);

arrXY dualParabola(const lineEvent &lineA, const lineEvent &lineB,
                   const double &rad);

arrXY dualParabola_LLC(const lineEvent &lineA, const lineEvent &line,
                       const double &rad);

arrXY endpointLine(const vertexEvent &EP, const lineEvent &line,
                   const double &rad);

arrXY parbolaEllipse(const lineEvent &line, const vertexEvent &vert,
                     const double &rad, bool orientationFlag);

arrXY ellipseCircle(const vertexEvent &vertex, const double &rad,
                    bool vertIsSecond);
// vecDBL parabolaCircle(const lineEvent &line, const double &rad, bool
// lineIsSecond); //To be implemented
}  // namespace vorGeo

#endif
