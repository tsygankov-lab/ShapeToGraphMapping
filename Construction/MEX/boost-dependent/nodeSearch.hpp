#pragma once
#include <vector>;
struct nodeGen {
	std::vector<long> neighborID;
	long myID;
	bool passable;
	bool visited;
	nodeGen::nodeGen(long myID) : myID(myID), visited(false) {};

	void setAsRestrictedNode() {
		neighborID.clear();
	}
};
