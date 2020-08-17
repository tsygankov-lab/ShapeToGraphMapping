#DEPENDS ON DATATYPES
add_library(records STATIC halfEdgeRecords.cpp)
target_link_libraries(records datatypes)
