#include "FirstFitDecreasing.h"

string FirstFitDecreasing::getName() {
    return "First-Fit Decreasing";
}

void FirstFitDecreasing::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    bool isFirstFitFound = false;

    vector<int> remainingFolderDurations;

    remainingFolderDurations.reserve(fileDurations.size());

    for (int i = 0; i < fileDurations.size(); i++) {
        isFirstFitFound = false;

        for (int j = 0; j < remainingFolderDurations.size(); j++) {
            if (fileDurations[i] <= remainingFolderDurations[j]) {
                files.push_back(make_pair(fileDurations[i], j + 1));

                remainingFolderDurations[j] -= fileDurations[i];

                isFirstFitFound = true;

                break;
            }
        }

        if (!isFirstFitFound) {
            remainingFolderDurations.push_back(folderDuration - fileDurations[i]);

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size())));
        }
    }
}
