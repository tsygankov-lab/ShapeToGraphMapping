#include <vector>
#include <queue>

struct bfsVert {
	std::vector<long> neighborID;
	long myID;
	bool terminalTarget;
	bool axisTargets;
	bool visited;
	bfsVert::bfsVert(long myID) : myID(myID), terminalTarget(false), axisTargets(false), visited(false) {};
	void setAsTerminalPoint() {
		terminalTarget = true;
	}
	void setAsRestrictedTarget() {
		axisTargets = true;
	}
	void setAsRestrictedNode() {
		neighborID.clear();
	}
};

typedef struct returnList {
	std::vector<long> reachable;
	std::vector<long> reachableTerminalPoints;
	std::vector<long> reachableAxisPoints;
	std::vector<long> reachableOneBeforeAxis;
}returnList;

returnList bfsSearch(std::vector<bfsVert> events, long startID) {
	std::queue<bfsVert*> queue;
	returnList info;
	info.reachable.reserve(events.size());
	queue.push(&events[startID]);

	while (!queue.empty()) {
		auto curVert = queue.front();
		queue.pop();
		if (!curVert->visited) {
			curVert->visited = true;
			info.reachable.push_back(curVert->myID);
			if (curVert->terminalTarget) info.reachableTerminalPoints.push_back(curVert->myID);
			if (curVert->axisTargets) info.reachableAxisPoints.push_back(curVert->myID);
			for (auto i = 0; i < curVert->neighborID.size(); i++) {
				auto nID = curVert->neighborID[i];
				//We can not go from a point on the axis to another point on the axis, and we cannot go to a previously visitted point
				if (!(curVert->axisTargets && events[nID].axisTargets) && !events[nID].visited) {
					if (events[nID].axisTargets) {
						info.reachableOneBeforeAxis.push_back(curVert->myID);
					}
					else { queue.push(&events[nID]); }
				}
			}
		}
	}
	return info;

}