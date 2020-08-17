#DEPENDS ON DATATYPE
add_library(queue STATIC NodeSEQ.cpp)
target_link_libraries(queue datatypes)
