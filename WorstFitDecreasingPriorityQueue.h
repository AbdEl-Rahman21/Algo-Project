#pragma once

#include "WorstFitPriorityQueue.h"

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class WorstFitDecreasingPriorityQueue : public WorstFitPriorityQueue {
public:
	string getName() override;
	void execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) override;
};
