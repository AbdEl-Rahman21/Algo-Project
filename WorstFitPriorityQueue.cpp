#include "WorstFitPriorityQueue.h"

string WorstFitPriorityQueue::getName() {
    return "Worst-Fit Priority Queue";
}

void WorstFitPriorityQueue::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    int mostRemainingFolderDuration = 0;
    int mostRemainingFolderDurationIndex = 0;

    // By default the priority of the elements is dependent upon the first element of the pair.
    // The first element is the Remaining Duration & the second element is the Folder Index.
    priority_queue<pair<int, int>> remainingFolderDurations;

    remainingFolderDurations.push(make_pair(folderDuration, 0));   // O(log(M))

    for (int i = 0; i < fileDurations.size(); i++) {
        mostRemainingFolderDuration = remainingFolderDurations.top().first;
        mostRemainingFolderDurationIndex = remainingFolderDurations.top().second;

        if (fileDurations[i] > mostRemainingFolderDuration) {
            remainingFolderDurations.push(make_pair(folderDuration - fileDurations[i], int(remainingFolderDurations.size())));

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size())));
        }
        else {
            remainingFolderDurations.pop();

            remainingFolderDurations.push(make_pair(mostRemainingFolderDuration - fileDurations[i], mostRemainingFolderDurationIndex));

            files.push_back(make_pair(fileDurations[i], mostRemainingFolderDurationIndex + 1));
        }
    }
}