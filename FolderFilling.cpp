#include "FolderFilling.h"

string FolderFilling::getName() {
    return "Folder Filling";
}

void FolderFilling::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) { // O(N²⋅D)
    int currentFolderNumber = 1;    // O(1)

    while (!fileDurations.empty()) {    // O(N²⋅D)
        // (Indices) First index is the Folder Duration -- Second index is the File Durations Index (from fileDurations).
        // (Pair Values) First value is the folder duration -- Second value is used for tracing (0 == '←', 1 == '↖').
        vector<vector<pair<int, int>>> memo(folderDuration + 1, vector<pair<int, int>>(int(fileDurations.size() + 1), make_pair(-1, -1)));  // O(N⋅D)

        getFolderFiles(memo, fileDurations, folderDuration);    // O(N⋅D)

        traceFolderFiles(memo, files, fileDurations, folderDuration, currentFolderNumber);  // O(N⋅D)

        ++currentFolderNumber;  // O(1)
    }
}

void FolderFilling::getFolderFiles(vector<vector<pair<int, int>>>& memo, vector<int>& fileDurations, int folderDuration) {  // O(N⋅D)
    for (int i = 0; i <= folderDuration; i++) { // O(N⋅D)
        for (int j = 0; j <= fileDurations.size(); j++) {   // O(N)
            if (i == 0 || j == 0) { // O(1)
                memo[i][j].first = i;   // O(1)
            }
            else if (fileDurations[j - 1] > i) {    // O(1)
                memo[i][j] = memo[i][j - 1];    // O(1)
            }
            else {  // O(1)
                memo[i][j].first = min(memo[i][j - 1].first, memo[i - fileDurations[j - 1]][j - 1].first);  // O(1)

                memo[i][j].second = (memo[i][j].first == memo[i][j - 1].first) ? 0 : 1; // O(1)
            }
        }
    }
}

void FolderFilling::traceFolderFiles(vector<vector<pair<int, int>>>& memo, vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration, int currentFolderNumber) {    // O(N⋅D)
    int modifiedFileDurationsLength = int(fileDurations.size()) - 1;    // O(1)
    int fileDurationsLength = int(fileDurations.size());    // O(1)

    while (fileDurationsLength > 0 && folderDuration > 0) { // O(N⋅D)
        if (memo[folderDuration][fileDurationsLength].second == 1) {    // O(N)
            files.push_back(make_pair(fileDurations[modifiedFileDurationsLength], currentFolderNumber));    // O(1)

            folderDuration -= fileDurations[modifiedFileDurationsLength];   // O(1)

            fileDurations.erase(fileDurations.begin() + modifiedFileDurationsLength);   // O(N)

            --modifiedFileDurationsLength;  // O(1)
            --fileDurationsLength;  // O(1)
        }
        else {  // O(1)
            --modifiedFileDurationsLength;  // O(1)
            --fileDurationsLength;  // O(1)
        }
    }
}
