#pragma once

#include "WorstFitLinearSearch.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class WorstFitDecreasingLinearSearch : public WorstFitLinearSearch {
public:
	string getName() override;
	void execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) override;
};
