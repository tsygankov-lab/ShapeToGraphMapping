#basicMathAndGeometry.cpp -> depends on siteevents
add_library(math STATIC basicMathAndGeometry.cpp circleCalculator.cpp interceptCalculators.cpp geoTester.cpp)
target_link_libraries(math datatypes)
