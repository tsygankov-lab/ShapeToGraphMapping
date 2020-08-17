#include <queue>
#include <vector>

#include "../Records/halfEdgeRecords.hpp"
// IF an infinite vertex is found, must assign all objects of regionid curRegion
// to backgroundID <0>
// Implement - return a region vector.  Use region vector to check visit status
std::vector<long> bfsSearch_Assign_Legacy(const std::vector<vorVert>& verts,
                                          const std::vector<halfEdge>& edges) {
  std::vector<long> regionID;
  regionID.insert(regionID.begin(), verts.size(), -1l);

  std::queue<long> queue;
  long curRegion = 0;
  long startID = 0;
  for (auto r : regionID) {
    if (r == -1 && verts[startID].vertexCoorID == -2) {
      queue.push(startID);
      while (!queue.empty()) {
        auto curID = queue.front();
        queue.pop();
        if (regionID[curID] == -1) {
          regionID[curID] = curRegion;
          for (auto eID : verts[curID].getEdgeIDs()) {
            auto nID = edges[edges[eID].getTwinID()].getOriginID();
            if (verts[nID].vertexCoorID == -2 && regionID[nID] == -1) {
              queue.push(nID);
            }
          }
        }
      }
      ++curRegion;
    }
    ++startID;
  }
  return regionID;
}

std::vector<long> bfsSearch_Assign_v2_Contours(
    const std::vector<vorVert>& verts, const std::vector<halfEdge>& edges) {
  // RegionID still acts as a 'visitted' flag, but reachableID tracks the nodes
  // which have been visitted incase an infinite has been reached
  std::vector<long> regionID;
  std::vector<long> reachableID;
  regionID.insert(regionID.begin(), verts.size(), -1l);

  std::queue<long> queue;
  long curRegion = 1;
  long startID = 0;
  for (auto r : regionID) {
    reachableID.clear();
    bool unboundedRegion = false;
    if (r == -1 && verts[startID].vertexCoorID == -2) {
      queue.push(startID);
      while (!queue.empty()) {
        auto curID = queue.front();
        queue.pop();
        if (regionID[curID] == -1) {
          regionID[curID] = curRegion;
          reachableID.push_back(curID);
          if (verts[curID].infVert) {
            unboundedRegion = true;
          }
          for (auto eID : verts[curID].getEdgeIDs()) {
            auto nID = edges[edges[eID].getTwinID()].getOriginID();
            if (verts[nID].vertexCoorID == -2 && regionID[nID] == -1) {
              queue.push(nID);
            }
          }
        }
      }
      if (unboundedRegion) {
        for (auto id : reachableID) {
          regionID[id] = 0;
        }
      } else {
        ++curRegion;
      }
    }
    ++startID;
  }
  return regionID;
}

std::vector<long> bfsSearch_Assign(const std::vector<vorVert>& verts,
                                   const std::vector<halfEdge>& edges) {
  // This will track the right most reachable vertex. This will have the color
  // of the outer most boundary. This then assigns the region of this outer most
  // vertex to all reachable vertices
  // right-most -> outer as each boundary contains each other.
  std::vector<long> regionID;
  std::vector<long> reachableID;
  regionID.insert(regionID.begin(), verts.size(), -1l);

  std::queue<long> queue;
  long curRegion = -2;
  long startID = 0;
  for (auto r : regionID) {
    reachableID.clear();
    bool unboundedRegion = false;
    double xPos = -INFINITY;
    curRegion = -2;
    if (r == -1 && verts[startID].vertexCoorID == -2) {
      queue.push(startID);
      while (!queue.empty()) {
        auto curID = queue.front();
        queue.pop();
        if (regionID[curID] == -1) {
          regionID[curID] = curRegion;
          reachableID.push_back(curID);
          if (verts[curID].infVert) {
            unboundedRegion = true;
          }
          for (auto eID : verts[curID].getEdgeIDs()) {
            auto nID = edges[edges[eID].getTwinID()].getOriginID();
            if (verts[nID].vertexCoorID == -2 && regionID[nID] == -1) {
              queue.push(nID);
            } else if (verts[nID].vertexCoorID != -2) {
              if (verts[nID].pos[0] > xPos) {
                xPos = verts[nID].pos[0];
                curRegion = edges[eID].color;
              }
            }
          }
        }
      }
      if (unboundedRegion) {
        for (auto id : reachableID) {
          regionID[id] = 0;
        }
      } else {
        for (auto id : reachableID) {
          regionID[id] = curRegion;
        }
      }
    }
    ++startID;
  }
  return regionID;
}