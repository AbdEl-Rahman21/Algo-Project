#include "WorstFitDecreasingPriorityQueue.h"

string WorstFitDecreasingPriorityQueue::getName() {
    return "Worst-Fit Decreasing Priority Queue";
}

void WorstFitDecreasingPriorityQueue::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    WorstFitPriorityQueue::execute(files, fileDurations, folderDuration);
}
