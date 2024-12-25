#include "FolderFilling.h"

string FolderFilling::getName() {
    return "Folder Filling";
}

void FolderFilling::execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    int currentFolderNumber = 1;

    while (!fileDurations.empty()) {
        // (Indices) First index is the Folder Duration -- Second index is the File Durations Index (from fileDurations).
        // (Pair Values) First value is the folder duration -- Second value is used for tracing (0 == '←', 1 == '↖').
        vector<vector<pair<int, int>>> memo(folderDuration + 1, vector<pair<int, int>>(int(fileDurations.size() + 1), make_pair(-1, -1))); // O(N⋅D)

        getFolderFiles(memo, fileDurations, folderDuration);

        traceFolderFiles(memo, files, fileDurations, folderDuration, currentFolderNumber);

        ++currentFolderNumber;
    }
}

void FolderFilling::getFolderFiles(vector<vector<pair<int, int>>>& memo, vector<int>& fileDurations, int folderDuration) {
    for (int i = 0; i <= folderDuration; i++) {
        for (int j = 0; j <= fileDurations.size(); j++) {
            if (i == 0 || j == 0) {
                memo[i][j].first = i;
            }
            else if (fileDurations[j - 1] > i) {
                memo[i][j] = memo[i][j - 1];
            }
            else {
                memo[i][j].first = min(memo[i][j - 1].first, memo[i - fileDurations[j - 1]][j - 1].first);

                memo[i][j].second = (memo[i][j].first == memo[i][j - 1].first) ? 0 : 1;
            }
        }
    }
}

void FolderFilling::traceFolderFiles(vector<vector<pair<int, int>>>& memo, vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration, int currentFolderNumber) {
    int modifiedFileDurationsLength = int(fileDurations.size()) - 1;
    int fileDurationsLength = int(fileDurations.size());

    while (fileDurationsLength > 0 && folderDuration > 0) {
        if (memo[folderDuration][fileDurationsLength].second == 1) {
            files.push_back(make_pair(fileDurations[modifiedFileDurationsLength], currentFolderNumber));

            folderDuration -= fileDurations[modifiedFileDurationsLength];

            fileDurations.erase(fileDurations.begin() + modifiedFileDurationsLength);

            --modifiedFileDurationsLength;
            --fileDurationsLength;
        }
        else {
            --modifiedFileDurationsLength;
            --fileDurationsLength;
        }
    }
}
