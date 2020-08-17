#pragma once
#include "../nodeSearch.hpp"
#include <queue>
#include <stack>


double compareDirections_General(const std::vector<double> &myDir, const std::vector<double> &otherDir) {
	auto dirMag = sqrt(myDir[0] * myDir[0] + myDir[1] * myDir[1]);
	auto otherMag = sqrt(otherDir[0] * otherDir[0] + otherDir[1] * otherDir[1]);
	if (otherMag < 0.000000000002) { return 0.0; }
	auto nDir1 = (dirMag == 1.0) ? myDir : std::vector<double>({ myDir[0] / dirMag, myDir[1] / dirMag });
	auto nDir2 = (otherMag == 1.0) ? otherDir : std::vector<double>({ otherDir[0] / otherMag, otherDir[1] / otherMag });
	auto sinth = nDir1[0] * nDir2[1] - nDir1[1] * nDir2[0];
	auto costh = nDir1[0] * nDir2[0] + nDir1[1] * nDir2[1];
	auto costhnum = costh < 0.000000000002 ? 2.0 : 0.0;
	if (sinth == 0) {
		return sinth - costhnum;
	}
	return sinth + costhnum*(1 - abs(sinth)) * (sinth < 0 ? -1.0 : 1.0);
}

struct childDirPair {
	std::vector<double> dir;
	long ID;

	childDirPair::childDirPair(long childID, std::vector<double> dir) : ID(childID), dir(dir) {};
	childDirPair::childDirPair() : ID(-1), dir(std::vector<double>({ 0.0,0.0 })) {};
};

struct DFSstruct:nodeGen {
	long parID;
	std::vector<double> parDir;
	std::vector<std::vector<double>> childrenDir;
	std::queue<childDirPair> childQueue;
	bool isTerminal = false;
	bool isRegionBoundary = false;
	double dirMag;
	childDirPair loopBoundaryInfo;

	DFSstruct::DFSstruct(long myID) : nodeGen(myID), dirMag(-1.0), parID(-1) {};

	void setParent(const DFSstruct *DFSParent) {
		parID = DFSParent->myID;
		int index = 0;
		for (auto node : neighborID) {
			if (node == DFSParent->myID) {
				auto dir = childrenDir.at(index);
				parDir = { -dir.at(0),-dir.at(1) };
			}
			++index;
		}
		this->sortOutgoingEdges();
	}

	double compareDirections(const std::vector<double> &otherDir) {
		dirMag = (dirMag == -1.0) ? sqrt(parDir[0] * parDir[0] + parDir[1] * parDir[1]) : dirMag;
		auto otherMag = sqrt(otherDir[0] * otherDir[0] + otherDir[1] * otherDir[1]);
		if (otherMag < 0.000000000002) { return 0.0; }
		auto nDir1 = (dirMag == 1.0) ? parDir : std::vector<double>({ parDir[0] / dirMag, parDir[1] / dirMag });
		auto nDir2 = (otherMag == 1.0) ? otherDir : std::vector<double>({ otherDir[0] / otherMag, otherDir[1] / otherMag });
		auto sinth = nDir1[0] * nDir2[1] - nDir1[1] * nDir2[0];
		auto costh = nDir1[0] * nDir2[0] + nDir1[1] * nDir2[1];
		auto costhnum = costh < 0.000000000002 ? 2.0 : 0.0;
		if (sinth == 0) {
			return sinth - costhnum;
		}
		return sinth + costhnum*(1 - abs(sinth)) * (sinth < 0 ? -1.0 : 1.0);
	}

	void sortOutgoingEdges() {
		long edgeCounter = 0;
		std::vector<childDirPair> childrenOrder;
		std::vector<double> angleNumber;
		for (auto outDir : childrenDir) {
			auto otherNodeID = neighborID[edgeCounter];
			if (otherNodeID != parID) {
				auto roughAngle = compareDirections(outDir);
				long ind = 0;
				for (auto &angle : angleNumber) {
					if (roughAngle < angle) {
						break;
					}
					++ind;
				}
				angleNumber.insert(angleNumber.begin() + ind, roughAngle);
				childrenOrder.insert(childrenOrder.begin() + ind, childDirPair(otherNodeID, outDir));
			}
			++edgeCounter;
		}
		for (auto child : childrenOrder) {
			childQueue.push(child);
		}
	}

	void setAsTerminalPoint() {
		isTerminal = true;
		this->setAsRestrictedNode();
		this->childrenDir.clear();
	}

	void setAsRegionBoundary() {
		isRegionBoundary = true;
	}

	void setRegionBoundaryInfo(std::vector<double> loopDir, long loopParID) {
		loopBoundaryInfo.dir = loopDir;
		loopBoundaryInfo.ID = loopParID;
	}

	long getRightMost(std::vector<DFSstruct> &events, std::vector<double> curDir, long prevID) {
		auto curID = myID;
		auto leftNodeID = myID;
		auto nuDir = parDir;
		while (!events.at(curID).isTerminal) {
			auto edgeCounter = 0;
			double smallestAngle = 3.0; //Angle goes between +-2.
			for (auto outDir : events.at(curID).childrenDir) {
				auto otherNodeID = events.at(curID).neighborID.at(edgeCounter); // compareDirections_General(curDir, outDir);
				if (otherNodeID != prevID) {
					double roughAngle = compareDirections_General(curDir, outDir);// events[curID].compareDirections(outDir);
					if (roughAngle < smallestAngle) {
						smallestAngle = roughAngle;
						leftNodeID = otherNodeID;
						nuDir = outDir;
					}
				}
				++edgeCounter;
			}
			prevID = curID;
			curID = leftNodeID;
			curDir = nuDir;
		}
		return curID;
	}

	long getLeftMost(std::vector<DFSstruct> &events, std::vector<double> curDir, long prevID) {
		auto curID = myID;
		auto leftNodeID = myID;
		auto nuDir = parDir;
		while (!events.at(curID).isTerminal) {
			auto edgeCounter = 0;
			double smallestAngle = -3.0; //Angle goes between +-2.
			for (auto outDir : events.at(curID).childrenDir) {
				auto otherNodeID = events.at(curID).neighborID.at(edgeCounter); // compareDirections_General(curDir, outDir);
				if (otherNodeID != prevID) {
					double roughAngle = compareDirections_General(curDir, outDir);// events[curID].compareDirections(outDir);
					if (roughAngle > smallestAngle) {
						smallestAngle = roughAngle;
						leftNodeID = otherNodeID;
						nuDir = outDir;
					}
				}
				++edgeCounter;
			}
			prevID = curID;
			curID = leftNodeID;
			curDir = nuDir;
		}
		return curID;
	}
};


typedef struct DFS_returnList {
	std::vector<long> reachable;
	std::vector<long> reachableTerminalPoints;
	//std::vector<long> reachableAxisPoints;
	//std::vector<long> reachableOneBeforeAxis;
}DFS_returnList;


DFS_returnList dfsSearch(std::vector<DFSstruct> &events, long startID, bool regionBoundaryMode) {
	std::stack<DFSstruct*> nodeStack;
	DFS_returnList info;
	info.reachable.reserve(events.size());
	info.reachableTerminalPoints.reserve(events.size());
	events.at(startID).parDir = std::vector<double>({ 0,1.0 });
	events.at(startID).sortOutgoingEdges();
	nodeStack.push(&events.at(startID));

	while (!nodeStack.empty()) {
		auto curVert = nodeStack.top();
		if (regionBoundaryMode && curVert->isRegionBoundary) {
			if (!curVert->isTerminal)
			{
				auto leftMost = curVert->getLeftMost(events, curVert->loopBoundaryInfo.dir, curVert->loopBoundaryInfo.ID);
				auto rightMost = curVert->getRightMost(events, curVert->loopBoundaryInfo.dir, curVert->loopBoundaryInfo.ID);
				auto testLeft = events[leftMost];
				auto testRight = events[rightMost];

				info.reachableTerminalPoints.push_back(rightMost);// curVert->getLeftMost(events, curVert->loopBoundaryInfo.dir, curVert->myID));
				if (leftMost != rightMost) info.reachableTerminalPoints.push_back(leftMost);// curVert->getRightMost(events, curVert->loopBoundaryInfo.dir, curVert->myID));
			}
			if(curVert->isTerminal){
				if(curVert->myID !=info.reachableTerminalPoints.back()) {info.reachableTerminalPoints.push_back(curVert->myID);}
			}
			nodeStack.pop();
		}
		else {
			if (!curVert->visited) { info.reachable.push_back(curVert->myID); }
			if (curVert->isTerminal) {
				info.reachableTerminalPoints.push_back(curVert->myID);
			}
			if (!curVert->isRegionBoundary && !curVert->childQueue.empty()) {
				auto cInfo = curVert->childQueue.front();
				curVert->childQueue.pop();
				if (!events.at(cInfo.ID).visited && !events.at(cInfo.ID).isRegionBoundary) {
					events.at(cInfo.ID).setParent(curVert);
					nodeStack.push(&events.at(cInfo.ID));
				}
				if (regionBoundaryMode && events.at(cInfo.ID).isRegionBoundary) {
					events.at(cInfo.ID).setRegionBoundaryInfo(cInfo.dir, curVert->myID);
					nodeStack.push(&events.at(cInfo.ID));
				}
			}
			else {
				curVert->setAsRegionBoundary();
				nodeStack.pop();
			}
		}
		curVert->visited = true;
	}
	return info;

}