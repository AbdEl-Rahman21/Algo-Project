#include "WorstFitLinearSearch.h"

string WorstFitLinearSearch::getName() {
    return "Worst-Fit Linear Search";
}

void WorstFitLinearSearch::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {  // O(N⋅M)
    int mostRemainingFolderDuration = 0;    // O(1)
    int mostRemainingFolderDurationIndex = 0;   // O(1)

    vector<int> remainingFolderDurations;   // O(1)

    remainingFolderDurations.reserve(fileDurations.size()); // O(1)

    for (int i = 0; i < fileDurations.size(); i++) {    // O(N⋅M)
        mostRemainingFolderDuration = 0;    // O(1)
        mostRemainingFolderDurationIndex = 0;   // O(1)

        for (int j = 0; j < remainingFolderDurations.size(); j++) { // O(M)
            if (mostRemainingFolderDuration < remainingFolderDurations[j]) {    // O(1)
                mostRemainingFolderDuration = remainingFolderDurations[j];  // O(1)

                mostRemainingFolderDurationIndex = j;   // O(1)
            }
        }

        if (fileDurations[i] > mostRemainingFolderDuration) {   // O(1)
            remainingFolderDurations.push_back(folderDuration - fileDurations[i]);  // O(1)

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size()))); // O(1)
        }
        else {  // O(1)
            remainingFolderDurations[mostRemainingFolderDurationIndex] -= fileDurations[i]; // O(1)

            files.push_back(make_pair(fileDurations[i], mostRemainingFolderDurationIndex + 1)); // O(1)
        }
    }
}
