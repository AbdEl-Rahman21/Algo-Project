#include "WorstFitLinearSearch.h"

string WorstFitLinearSearch::getName() {
    return "Worst-Fit Linear Search";
}

void WorstFitLinearSearch::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    int mostRemainingFolderDuration = 0;
    int mostRemainingFolderDurationIndex = 0;

    vector<int> remainingFolderDurations;

    remainingFolderDurations.reserve(fileDurations.size());

    for (int i = 0; i < fileDurations.size(); i++) {
        mostRemainingFolderDuration = 0;
        mostRemainingFolderDurationIndex = 0;

        for (int j = 0; j < remainingFolderDurations.size(); j++) {
            if (mostRemainingFolderDuration < remainingFolderDurations[j]) {
                mostRemainingFolderDuration = remainingFolderDurations[j];

                mostRemainingFolderDurationIndex = j;
            }
        }

        if (fileDurations[i] > mostRemainingFolderDuration) {
            remainingFolderDurations.push_back(folderDuration - fileDurations[i]);

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size())));
        }
        else {
            remainingFolderDurations[mostRemainingFolderDurationIndex] -= fileDurations[i];

            files.push_back(make_pair(fileDurations[i], mostRemainingFolderDurationIndex + 1));
        }
    }
}
