#include "FirstFitDecreasing.h"

string FirstFitDecreasing::getName() {
    return "First-Fit Decreasing";
}

void FirstFitDecreasing::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {    // O(max(N⋅log(N), N⋅M))
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());   // O(N⋅log(N))

    bool isFirstFitFound = false;   // O(1)

    vector<int> remainingFolderDurations;   // O(1)

    remainingFolderDurations.reserve(fileDurations.size()); // O(1)

    for (int i = 0; i < fileDurations.size(); i++) {    // O(N⋅M)
        isFirstFitFound = false;    // O(1)

        for (int j = 0; j < remainingFolderDurations.size(); j++) { // O(M)
            if (fileDurations[i] <= remainingFolderDurations[j]) {  // O(1)
                files.push_back(make_pair(fileDurations[i], j + 1));    // O(1)

                remainingFolderDurations[j] -= fileDurations[i];    // O(1)

                isFirstFitFound = true; // O(1)

                break;  // O(1)
            }
        }

        if (!isFirstFitFound) { // O(1)
            remainingFolderDurations.push_back(folderDuration - fileDurations[i]);  // O(1)

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size()))); // O(1)
        }
    }
}
