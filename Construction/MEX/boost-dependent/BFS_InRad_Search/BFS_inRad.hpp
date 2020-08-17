#include <vector>
#include <queue>
#include <cmath>
struct bfsVert_inrad {
	std::vector<long> neighborID;
	std::vector<double> pos;
	double rad;
	bfsVert_inrad* ascendentNode;
	long myID;
	bool axisTargets;
	bool visited;
	bfsVert_inrad::bfsVert_inrad(long myID, double x, double y, double rad) : myID(myID), pos(std::vector<double>({ x,y })), axisTargets(false), visited(false), rad(rad) {};

	void setAsRestrictedTarget() {
		axisTargets = true;
	}
	bool inRad(bfsVert_inrad* ascendent) {
		auto dist = sqrt(pow((pos[0] - ascendent->pos[0]), 2.0) + pow((pos[1] - ascendent->pos[1]), 2.0));
		return (dist - ascendent->rad < 0);
	}
};

std::vector<long> bfsSearch_inRad(std::vector<bfsVert_inrad> &events, std::vector<long> startIDs) {
	std::queue<bfsVert_inrad*> queue;
	std::vector<long> reachable;
	for (auto id : startIDs) {
		events[id].ascendentNode = &events[id];
		events[id].setAsRestrictedTarget();
		queue.push(&events[id]);
	}
	while (!queue.empty()) {
		auto curVert = queue.front();
		queue.pop();
		if (!curVert->visited) {
			curVert->visited = true;
			reachable.push_back(curVert->myID);
			for (auto i = 0; i < curVert->neighborID.size(); i++) {
				auto nID = curVert->neighborID[i];
				//We can not go from a point on the axis to another point on the axis, and we cannot go to a previously visitted point
				if (!(events[nID].axisTargets || events[nID].visited) && events[nID].inRad(curVert->ascendentNode)) {
					events[nID].ascendentNode = curVert->ascendentNode;
					queue.push(&events[nID]);
				}
			}
		}
	}
	return reachable;
}