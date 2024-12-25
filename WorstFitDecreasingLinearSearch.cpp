#include "WorstFitDecreasingLinearSearch.h"

string WorstFitDecreasingLinearSearch::getName() {
    return "Worst-Fit Decreasing Linear Search";
}

void WorstFitDecreasingLinearSearch::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    WorstFitLinearSearch::execute(files, fileDurations, folderDuration);
}
