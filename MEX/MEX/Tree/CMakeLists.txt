#DEPENDS ON EVERYTHING
add_library(tree STATIC RBT_CircleEvents.cpp RBT_General.cpp RBT_Maintain.cpp RBT_SiteEvent_Processing.cpp)
target_link_libraries(tree math datatypes queue records)

