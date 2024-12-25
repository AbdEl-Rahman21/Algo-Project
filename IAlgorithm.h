#pragma once

#include <string>
#include <vector>

using namespace std;

class IAlgorithm {
public:
	virtual string getName() = 0;
	virtual void execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) = 0;
};
