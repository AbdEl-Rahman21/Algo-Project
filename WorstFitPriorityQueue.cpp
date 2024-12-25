#include "WorstFitPriorityQueue.h"

string WorstFitPriorityQueue::getName() {
    return "Worst-Fit Priority Queue";
}

void WorstFitPriorityQueue::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) { // O(N⋅log(M))
    int mostRemainingFolderDuration = 0;    // O(1)
    int mostRemainingFolderDurationIndex = 0;   // O(1)

    // By default the priority of the elements is dependent upon the first element of the pair.
    // The first element is the Remaining Duration & the second element is the Folder Index.
    priority_queue<pair<int, int>> remainingFolderDurations;    // O(1)

    remainingFolderDurations.push(make_pair(folderDuration, 0));   // O(log(M))

    for (int i = 0; i < fileDurations.size(); i++) {    // O(N⋅log(M))
        mostRemainingFolderDuration = remainingFolderDurations.top().first; // O(log(M))
        mostRemainingFolderDurationIndex = remainingFolderDurations.top().second;   // O(log(M))

        if (fileDurations[i] > mostRemainingFolderDuration) {   // O(log(M))
            remainingFolderDurations.push(make_pair(folderDuration - fileDurations[i], int(remainingFolderDurations.size())));  // O(log(M))

            files.push_back(make_pair(fileDurations[i], int(remainingFolderDurations.size()))); // O(1)
        }
        else {  // O(log(M))
            remainingFolderDurations.pop(); // O(log(M))

            remainingFolderDurations.push(make_pair(mostRemainingFolderDuration - fileDurations[i], mostRemainingFolderDurationIndex)); // O(log(M))

            files.push_back(make_pair(fileDurations[i], mostRemainingFolderDurationIndex + 1)); // O(1)
        }
    }
}
