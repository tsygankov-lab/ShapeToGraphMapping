#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "DataTypes/siteEvent.hpp"
#include "Records/halfEdgeRecords.hpp"

std::unique_ptr<halfEdgeRecords> computeDiagram(
    std::vector<arrXY> vertCoor, std::vector<std::array<std::size_t, 2>> EL,
    std::vector<int> color, arrXY center);

struct DEBUG_InternalStateHolder {
  std::unique_ptr<vorQueue::heapQueue> queue;
  std::unique_ptr<halfEdgeRecords> records;
  std::unique_ptr<vorRBT::RBTree> tree;

  DEBUG_InternalStateHolder(vorQueue::heapQueue *que, halfEdgeRecords *rec,
                            vorRBT::RBTree *rbt)
      : queue(que), records(rec), tree(rbt){};

  vorQueue::heapQueue *getQueue() { return queue.get(); }
  halfEdgeRecords *getRecords() { return records.get(); }
  vorRBT::RBTree *getTree() { return tree.get(); }
};

std::unique_ptr<DEBUG_InternalStateHolder> DEBUG_createTree(
    std::vector<arrXY> vertCoor, std::vector<std::array<std::size_t, 2>> EL,
    std::vector<int> color, arrXY center);
// Add serialization to all classes in halfedgerecords

// To Bind
//  siteEvent.hpp
//  main functionn
//  STL containers
namespace py = pybind11;
// struct halfEdgeRecords {
//  py::array_t<std::size_t>
// halfEdgeRecords::edgeToEL_numpy(py::array_t<std::size_t> input1) {
//    py::buffer_info buf1 = input1.request();
//    if(buf1.ndim != 1)
//      throw std::runtime_error("Number of dimensions must be 1");
//
//    auto result = py::array_t<std::size_t>(2*input1.size());
//
//  }
//};
// LineEvents need some re-tinkering

// Everything ready for serialization
// Process -> py::tuple(All things needed for output)
//            object p = object();
//            p.reconstruct(.......inputs.cast<type>())

template <typename T>
void declare_VPA(py::module &m, std::string typestr) {
  using Class = vorContainer::vectorPageAllocator<T>;
  std::string pyclass_name = std::string("vectorPageAllocator") + typestr;
  py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(),
                    py::dynamic_attr())
      .def_readonly("blockSize", &Class::blockSize)
      .def_readonly("lastSpot", &Class::lastSpot)
      .def("at", &Class::get, py::return_value_policy::reference_internal)
      .def("getObjectVector", &Class::extractObjVector,
           py::return_value_policy::reference_internal);
}

PYBIND11_MODULE(vor, m) {
  m.def("computeDiagram", &computeDiagram);
  m.def("DEBUG_createTree", &DEBUG_createTree);

  py::class_<halfEdge>(m, "halfEdge")
      .def_property_readonly("ID", &halfEdge::getID)
      .def_property_readonly("twinID", &halfEdge::getTwinID)
      .def_property_readonly("EPID", &halfEdge::getOriginID)
      .def_property_readonly("twinEPID", &halfEdge::getTwinOriginID)
      .def_property_readonly("adjacentFaceID", &halfEdge::getFaceID)
      .def_readonly("edgeType", &halfEdge::edgeType)
      .def_readonly("color", &halfEdge::color)
      .def_readonly("dist", &halfEdge::dist)
      .def_readonly("controlPoint", &halfEdge::controlPoint)
      .def_readonly("dir", &halfEdge::dir)
      .def("DEBUG_computeIntersect", &halfEdge::computeIntersect)
      .def_readonly("DEBUG_getLiveTwin", &halfEdge::twin)
      .def_readonly("DEBUG_getLiveOrigin", &halfEdge::origin)
      .def_readonly("DEBUG_getLiveAdjacentFace", &halfEdge::adjacentFace)
      .def_readonly("DEBUG_LiveVertexSet", &halfEdge::VERTEX_SET)
      .def_readonly("DEBUG_LiveCompleteEdge", &halfEdge::COMPLETE_EDGE)
      .def("DEBUG_getLiveControlPoint", &halfEdge::getControlPoint)
      .def("DEBUG_getLiveDirection", &halfEdge::getDirection)
      .def_readonly("DEBUG_INVALID", &halfEdge::INVALID)
      .def(py::pickle(
          [](const halfEdge &he) {
            auto id = he.getID();
            auto twinID = he.getID();
            auto oriID = he.getOriginID();
            auto toriID = he.getTwinOriginID();
            auto fid = he.getFaceID();
            auto et = he.edgeType;
            auto col = he.color;
            auto dist = he.dist;
            auto contp = he.controlPoint;
            auto INFINITE = he.INFINITE;
            auto dir = he.dir;
            return py::make_tuple(id, twinID, oriID, toriID, fid, et, col, dist,
                                  contp, INFINITE, dir);
          },
          [](py::tuple t) {
            halfEdge obj = halfEdge();
            obj.reconstruct(t[0].cast<std::size_t>(), t[1].cast<std::size_t>(),
                            t[2].cast<std::size_t>(), t[3].cast<std::size_t>(),
                            t[4].cast<std::size_t>(), t[5].cast<int>(),
                            t[6].cast<long>(), t[7].cast<double>(),
                            t[8].cast<arrXY>(), t[9].cast<bool>(),
                            t[10].cast<arrXY>());
            return obj;
          }));

  py::class_<vorVert>(m, "vorVert")
      .def_property_readonly("ID", &vorVert::getID)
      .def_property_readonly("edgeIDs", &vorVert::getEdgeIDs)
      .def_property_readonly("faceIDs", &vorVert::getFaceIDs)
      .def_readonly("pos", &vorVert::pos)
      .def_readonly("vertexCoorID", &vorVert::vertexCoorID)
      .def_readonly("isInfinite", &vorVert::infVert)
      .def_readonly("rad", &vorVert::rad)
      .def_property_readonly("degree", &vorVert::getDegree)
      .def("getEdgeID", &vorVert::getEdgeID)
      .def("getFaceID", &vorVert::getFaceID)
      .def_readonly("DEBUG_getLiveEdges", &vorVert::edges,
                    py::return_value_policy::reference_internal)
      .def_readonly("DEBUG_getLiveFaces", &vorVert::faces,
                    py::return_value_policy::reference_internal)
      .def(py::pickle(
          [](const vorVert &vv) {
            auto id = vv.getID();
            auto edgeIDs = vv.getEdgeIDs();
            auto faceIDs = vv.getFaceIDs();  // note -> these are inputIDs
            auto pos = vv.pos;
            auto color = vv.colorPattern;
            auto vcID = vv.vertexCoorID;
            auto inf = vv.infVert;
            auto impl = vv._IMPLICIT;
            auto rad = vv.rad;
            auto eventLog = vv.eventLog;
            return py::make_tuple(id, edgeIDs, faceIDs, pos, color, vcID, inf,
                                  impl, rad, eventLog);
          },
          [](py::tuple t) {
            vorVert obj = vorVert();
            obj.reconstruct(
                t[0].cast<std::size_t>(), t[1].cast<std::vector<size_t>>(),
                t[2].cast<std::vector<size_t>>(), t[3].cast<arrXY>(),
                t[4].cast<std::array<long, 3>>(), t[5].cast<long>(),
                t[6].cast<bool>(), t[7].cast<bool>(), t[8].cast<double>(),
                t[9].cast<long>());
            return obj;
          }));

  py::class_<vorFace>(m, "vorFace")
      .def_property_readonly("edgeIDs", &vorFace::getEdgeIDs)
      .def_property_readonly("vertIDs", &vorFace::getVertIDs)
      .def_readonly("faceIndex", &vorFace::faceIndex)
      .def_readonly("color", &vorFace::color)
      .def_readonly("DEBUG_getLiveNeighbors", &vorFace::neighbors,
                    py::return_value_policy::reference_internal)
      .def_readonly("DEBUG_getLiveEdges", &vorFace::edges,
                    py::return_value_policy::reference_internal)
      .def_readonly("DEBUG_getLiveVertices", &vorFace::vertices,
                    py::return_value_policy::reference_internal)
      .def_readonly("id", &vorFace::id)
      .def(py::pickle(
          [](const vorFace &vf) {
            auto eID = vf.getNeighborIDs();
            auto nID = vf.getNeighborIDs();
            auto vID = vf.getVertIDs();
            auto color = vf.color;
            auto id = vf.id;
            auto fID = vf.faceIndex;
            return py::make_tuple(eID, nID, vID, color, id, fID);
          },
          [](py::tuple t) {
            vorFace obj = vorFace();
            obj.reconstruct(t[0].cast<std::vector<size_t>>(),
                            t[1].cast<std::vector<size_t>>(),
                            t[2].cast<std::vector<size_t>>(), t[3].cast<long>(),
                            t[4].cast<long>(), t[5].cast<long>());
            return obj;
          }));

  // Halfedge records will need siteEvents and derived classes to have
  // reconstruct methods
  py::class_<siteEvent>(m, "siteEvent")
      .def_readonly("pos", &siteEvent::pos)
      .def_readonly("cent", &siteEvent::cent)
      .def_readonly("objectID", &siteEvent::objectIndex)
      .def_readonly("rad", &siteEvent::rad)
      .def_readonly("type", &siteEvent::objType)
      .def_property_readonly("graphVertID", &siteEvent::getVorVertID)
      .def("getClosestPoint", &siteEvent::getClosestPoint)
      .def("orientationCheck", &siteEvent::orientationCheck)
      .def("distToPoint", &siteEvent::distToPoint)
      .def("distToPoint_STRICT", &siteEvent::distToPoint_STRICT)
      .def(py::pickle(
          [](const siteEvent &se) {
            auto iID = se.getID();
            auto vpID = se.getVorVertID();
            auto dataType = se.objType;
            auto pos = se.pos;
            auto cent = se.cent;  // Should move this somewhere else
            auto eventLog = se.eventLog;
            auto objID = se.objectIndex;
            auto rad = se.rad;
            return py::make_tuple(iID, vpID, dataType, pos, cent, eventLog,
                                  objID, rad);
          },
          [](py::tuple t) {
            siteEvent obj = siteEvent();
            obj.reconstruct(t[0].cast<std::size_t>(), t[1].cast<std::size_t>(),
                            t[2].cast<_DATATYPE>(), t[3].cast<arrXY>(),
                            t[4].cast<arrXY>(), t[5].cast<long>(),
                            t[6].cast<long>(), t[7].cast<double>());
            return obj;
          }));
  //.def("distToPoint", &siteEvent::distToPoint) these rely on internal
  // pointers! .def("distToPoint_STRICT", &siteEvent::distToPoint_STRICT);
  py::class_<vertexEvent, siteEvent>(m, "vertexEvent")
      .def_readonly("replacePointerList", &vertexEvent::replacePointerList)
      .def_readonly("lineSpawnEvent", &vertexEvent::lineSpawnEvent)
      .def_readonly("mustBePinned", &vertexEvent::mustBePinned)
      .def(py::pickle(
          [](const vertexEvent &ve) {
            auto iID = ve.getID();
            auto vpID = ve.getVorVertID();
            auto dataType = ve.objType;
            auto pos = ve.pos;
            auto cent = ve.cent;  // Should move this somewhere else
            auto eventLog = ve.eventLog;
            auto objID = ve.objectIndex;
            auto rad = ve.rad;
            auto conEL = ve.connectedEgeList;
            auto isEP = ve.isEP;
            return py::make_tuple(iID, vpID, dataType, pos, cent, eventLog,
                                  objID, rad, conEL, isEP);
          },
          [](py::tuple t) {
            vertexEvent obj = vertexEvent();
            obj.reconstruct(
                t[0].cast<std::size_t>(), t[1].cast<std::size_t>(),
                t[2].cast<_DATATYPE>(), t[3].cast<arrXY>(), t[4].cast<arrXY>(),
                t[5].cast<long>(), t[6].cast<long>(), t[7].cast<double>(),
                t[8].cast<std::vector<size_t>>(), t[9].cast<bool>());
            return obj;
          }));

  py::class_<degenEvent, siteEvent>(m, "degenEvent")
      .def_readonly("replacedByPointer", &degenEvent::replacedByPointer)
      .def_readonly("linePointer", &degenEvent::linePointer);

  py::class_<circleEvent, siteEvent>(m, "circleEvent")
      .def_readonly("circRad", &circleEvent::circRad)
      .def_readonly("_PINCHCASE", &circleEvent::_PINCHCASE)
      .def_readonly("nodeVec", &circleEvent::nodeVec)
      .def_readonly("siteList", &circleEvent::siteList);

  py::class_<lineEvent, siteEvent>(m, "lineEvent")
      .def_readonly("ABC", &lineEvent::ABC)
      .def_readonly("dir", &lineEvent::dir)
      .def_readonly("infPos", &lineEvent::infPos)
      .def_readonly("infRad", &lineEvent::infRad)
      .def_readonly("magnitude", &lineEvent::magnitude)
      .def_readonly("centerAligned", &lineEvent::centerAligned)
      .def_readonly("UPPER", &lineEvent::UPPER)
      .def_readonly("twin", &lineEvent::twin)
      .def_readonly("endPoints", &lineEvent::endPoints)
      .def(py::pickle(
          [](const lineEvent &le) {
            auto iID = le.getID();
            auto vpID = le.getVorVertID();
            auto dataType = le.objType;
            auto pos = le.pos;
            auto cent = le.cent;  // Should move this somewhere else
            auto eventLog = le.eventLog;
            auto objID = le.objectIndex;
            auto rad = le.rad;
            auto epID = le.getEPIDs();
            auto abc = le.ABC;
            auto dir = le.dir;
            auto infPos = le.infPos;
            auto infRad = le.infRad;
            auto magnitude = le.magnitude;
            auto ca = le.centerAligned;
            auto UPPER = le.UPPER;
            return py::make_tuple(iID, vpID, dataType, pos, cent, eventLog,
                                  objID, rad, epID, abc, dir, infPos, infRad,
                                  magnitude, ca, UPPER);
          },
          [](py::tuple t) {
            lineEvent obj = lineEvent();
            obj.reconstruct(
                t[0].cast<std::size_t>(), t[1].cast<std::size_t>(),
                t[2].cast<_DATATYPE>(), t[3].cast<arrXY>(), t[4].cast<arrXY>(),
                t[5].cast<long>(), t[6].cast<long>(), t[7].cast<double>(),
                t[8].cast<std::array<size_t, 2>>(), t[9].cast<arrABC>(),
                t[10].cast<arrXY>(), t[11].cast<arrXY>(), t[12].cast<double>(),
                t[13].cast<double>(), t[14].cast<bool>(), t[15].cast<bool>());
            return obj;
          }));

  py::class_<halfEdgeRecords>(m, "halfEdgeRecords")
      .def("getVertex", &halfEdgeRecords::getVertex)
      .def("getEdge", &halfEdgeRecords::getEdge)
      .def("getFace", &halfEdgeRecords::getFace)
      .def("getVertices", &halfEdgeRecords::getVertices)
      // Override accept binary
      // vector/list of vertices
      .def("getEdges", &halfEdgeRecords::getEdges)
      .def("getFaces", &halfEdgeRecords::getFaces)
      .def("getInputEvent", &halfEdgeRecords::getInputEvent,
           py::return_value_policy::reference_internal)
      .def("getVertexEvent", &halfEdgeRecords::getVertexEvent,
           py::return_value_policy::reference_internal)
      .def("getLineEvent", &halfEdgeRecords::getLineEvent,
           py::return_value_policy::reference_internal)
      .def("getEL", &halfEdgeRecords::getEL)
      .def("edgeToEL", &halfEdgeRecords::edgeToEL)
      .def("DEBUG_getHalfEdgePtrVector",
           &halfEdgeRecords::DEBUG_getHalfEdgePtrVector,
           py::return_value_policy::reference_internal)
      .def(py::pickle(
          [](const halfEdgeRecords &hER) {
            auto vert = hER.getVerticesCopy();
            auto edge = hER.getEdgesCopy();
            auto inputV = hER.inputVertexContainer;
            auto inputE = hER.inputLineContainer;
            auto face = hER.Faces;
            return py::make_tuple(vert, edge, inputV, inputE, face);
          },
          [](py::tuple t) {
            halfEdgeRecords obj;
            obj.reconstruct(t[0].cast<std::vector<vorVert>>(),
                            t[1].cast<std::vector<halfEdge>>(),
                            t[2].cast<std::vector<vertexEvent>>(),
                            t[3].cast<std::vector<lineEvent>>(),
                            t[4].cast<std::vector<vorFace>>());
            return obj;
          }));

  py::class_<vorRBT::RBTree>(m, "RBTree")
      .def("DEBUG_runIteration", &vorRBT::RBTree::DEBUG_runIteration)
      .def("DEBUG_runNIterations", &vorRBT::RBTree::DEBUG_runNIterations)
      .def("DEBUG_runForDistance", &vorRBT::RBTree::DEBUG_runForDistance)
      .def_property_readonly("nextRad", &vorRBT::RBTree::getNextRad)
      .def_property_readonly("lastRad", &vorRBT::RBTree::getLastRad)
      .def_readonly("cent", &vorRBT::RBTree::cent)
      .def("DEBUG_findInsert_NoMod", &vorRBT::RBTree::findInsert,
           py::return_value_policy::reference_internal)
      .def("getAllBetween", &vorRBT::RBTree::getAllBetween,
           py::return_value_policy::reference_internal)
      .def("getFirstLeaf", &vorRBT::RBTree::getFirstLeaf,
           py::return_value_policy::reference_internal)
      .def("getLastLeaf", &vorRBT::RBTree::getLastLeaf,
           py::return_value_policy::reference_internal)
      .def("getFirstEdge", &vorRBT::RBTree::getFirstEdge,
           py::return_value_policy::reference_internal)
      .def("getLastEdge", &vorRBT::RBTree::getLastEdge,
           py::return_value_policy::reference_internal)
      .def_readonly("eventLog", &vorRBT::RBTree::eventLog)
      .def_readonly("numNodes", &vorRBT::RBTree::numNodes)
      .def("treeEntries_All", &vorRBT::RBTree::treeEntries_All,
           py::return_value_policy::reference_internal)
      .def("treeEntries_Leaf", &vorRBT::RBTree::treeEntries_Leaf,
           py::return_value_policy::reference_internal)
      .def("treeEntries_Edge", &vorRBT::RBTree::treeEntries_Edge,
           py::return_value_policy::reference_internal)
      .def("DEBUG_FinishVoronoi", &vorRBT::RBTree::DEBUG_finishVoronoi)
      .def_readonly("NodeContainer", &vorRBT::RBTree::NodeContainer)
      .def_readonly("DegenContainer", &vorRBT::RBTree::DegenContainer)
      .def_readonly("CircleContainer", &vorRBT::RBTree::CircleContainer);

  py::class_<vorRBT::Node>(m, "Node")
      .def("getSiteEvent", &vorRBT::Node::getSiteEvent,
           py::return_value_policy::reference_internal)
      .def("getHalfEdge", &vorRBT::Node::getHalfEdge,
           py::return_value_policy::reference_internal)
      .def_readonly("dataType", &vorRBT::Node::dataType)
      .def_readonly("ACTIVE", &vorRBT::Node::ACTIVE)
      .def_readonly("nodeIndex", &vorRBT::Node::nodeIndex)
      .def_readonly("left", &vorRBT::Node::left,
                    py::return_value_policy::reference_internal)
      .def_readonly("right", &vorRBT::Node::right,
                    py::return_value_policy::reference_internal)
      .def_readonly("parent", &vorRBT::Node::parent,
                    py::return_value_policy::reference_internal)
      .def_readonly("color", &vorRBT::Node::color)
      .def_readonly("circEventPointer", &vorRBT::Node::circEventPointer,
                    py::return_value_policy::reference_internal)
      .def("getIntercept", &vorRBT::Node::edgeNodeGetIntercept)
      .def("getLeftMostChild", &vorRBT::Node::getLeftMostChild,
           py::return_value_policy::reference_internal)
      .def("getRightMostChild", &vorRBT::Node::getRightMostChild,
           py::return_value_policy::reference_internal)
      .def("getSibling", &vorRBT::Node::getSibling,
           py::return_value_policy::reference_internal)
      .def("getLowerNode", &vorRBT::Node::getLowerNode,
           py::return_value_policy::reference_internal)
      .def("getHigherNode", &vorRBT::Node::getHigherNode,
           py::return_value_policy::reference_internal);

  py::class_<DEBUG_InternalStateHolder>(m, "internalStateHolder")
      .def_property_readonly("tree", &DEBUG_InternalStateHolder::getTree)
      .def_property_readonly("records", &DEBUG_InternalStateHolder::getRecords)
      .def_property_readonly("queue", &DEBUG_InternalStateHolder::getQueue);

  py::enum_<vorRBT::_NODECOLOR>(m, "COLOR")
      .value("BLACK", vorRBT::_NODECOLOR::BLACK)
      .value("RED", vorRBT::_NODECOLOR::RED);

  py::enum_<_DATATYPE>(m, "dataType")
      .value("HalfEdge", _DATATYPE::HALFEDGE)
      .value("Vertex", _DATATYPE::VERTEX)
      .value("Line", _DATATYPE::LINE)
      .value("Degenerate", _DATATYPE::DEGENERATE)
      .value("Circle", _DATATYPE::CIRCLEEVENT);

  declare_VPA<vorRBT::Node>(m, "vorRBT::Node");
  declare_VPA<degenEvent>(m, "degenEvent");
  declare_VPA<circleEvent>(m, "circleEvent");
  declare_VPA<vorVert>(m, "vorVert");
  declare_VPA<halfEdge>(m, "halfEdge");
}