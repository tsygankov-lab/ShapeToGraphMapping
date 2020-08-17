#pragma once
#include <vector>
struct vorSettings {
	std::vector<std::vector<uint16_t>> labelMatrix;
	std::vector<std::vector<uint8_t>> imageMask;
	std::vector<int64_t> vertColors;
	std::vector<int64_t> edgeColors;
	std::vector<int64_t> vertexFaceID;
	std::vector<int64_t> edgeFaceID;

	bool trackColors = false;
	int vertFaceIDMode = 0;
	int edgeFaceIDMode = 0;

	bool validateCircleEvents = false;
	bool validateTreeStructure = false;

	int loopLogFrequency = 0; //disabled
	bool SEQLog = false;
	bool RBTLog = false;
	char *logName[];

	vorSettings::vorSettings(std::vector<std::vector<double>> vertexCoor, std::vector<std::vector<uint64_t>> EL, std::vector<double> cent) {
		//Think about implementation more, depends on source of arguments
	}
};