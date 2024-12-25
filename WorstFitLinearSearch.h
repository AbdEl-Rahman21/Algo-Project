#pragma once

#include "IAlgorithm.h"

#include <string>
#include <vector>

using namespace std;

class WorstFitLinearSearch : public IAlgorithm {
public:
	string getName() override;
	void execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) override;
};
