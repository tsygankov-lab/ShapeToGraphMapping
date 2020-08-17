#Depends on TREE and MATH
add_library(datatypes STATIC lineEvent.cpp vertexEvent.cpp)
target_link_libraries(datatypes math tree)
