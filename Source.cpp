#include <chrono>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int>> worstFitWithLinearSearch(vector<int> &fileDurations, int folderDuration);

int main() {
    int folderDuration = 100;

    vector<vector<int>> folders = { {} };
    vector<int> fileDurations = { 70, 80, 20, 15, 15 };

    auto start = chrono::steady_clock::now();

    folders = worstFitWithLinearSearch(fileDurations, folderDuration);

    auto end = chrono::steady_clock::now();

    auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Folders:-" << endl;

    for (int i = 0; i < folders.size(); i++) {
        cout << "Folder " << i + 1 << ": ";

        for (int j = 0; j < folders[i].size(); j++) {
            cout << folders[i][j] << " ";
        }

        cout << endl;
    }

    cout << "\nExecution time: " << executionTime << " microseconds" << endl;

    return 0;
}

vector<vector<int>> worstFitWithLinearSearch(vector<int> &fileDurations, int folderDuration) {
    int mostRemainingFolderDuration = 0;
    int mostRemainingFolderDurationIndex = 0;

    vector<vector<int>> folders = { {} };
    vector<int> remainingFolderDurations = { folderDuration };

    for (int i = 0; i < fileDurations.size(); i++) {
        mostRemainingFolderDuration = 0;
        mostRemainingFolderDurationIndex = 0;

        for (int j = 0; j < remainingFolderDurations.size(); j++) {
            if (mostRemainingFolderDuration < remainingFolderDurations[j]) {
                mostRemainingFolderDuration = remainingFolderDurations[j];
                mostRemainingFolderDurationIndex = j;
            }
        }

        if (fileDurations[i] <= remainingFolderDurations[mostRemainingFolderDurationIndex]) {
            folders[mostRemainingFolderDurationIndex].push_back(fileDurations[i]);
            remainingFolderDurations[mostRemainingFolderDurationIndex] -= fileDurations[i];
        }
        else {
            folders.push_back({ fileDurations[i] });
            remainingFolderDurations.push_back(folderDuration - fileDurations[i]);
        }
    }

    return folders;
}
void Worstfit_priority_queue(vector<int> AudiosDuration, int DesiredDuration)
{
    vector<vector<int>> Folders = { {} };
    priority_queue<pair<int, int>> RemainingSpace; // first is value , second is index
    RemainingSpace.push({ DesiredDuration , 0 });
    for (int i = 0; i < AudiosDuration.size(); i++)
    {
        if (AudiosDuration[i] < RemainingSpace.top().first)
        {
            Folders[RemainingSpace.top().second].push_back(AudiosDuration[i]);
            RemainingSpace.push({ RemainingSpace.top().first - AudiosDuration[i], RemainingSpace.top().second });
            RemainingSpace.pop();
        }

        else
        {
            Folders.push_back({ AudiosDuration[i] });
            RemainingSpace.push({ DesiredDuration - AudiosDuration[i], i });
        }
    }
    // Printing the resulting folders
    cout << "Folders:" << endl;
    for (int i = 0; i < Folders.size(); i++) {
        cout << "Folder " << i + 1 << ": ";
        for (int file : Folders[i]) {
            cout << file << " ";
        }
        cout << endl;
    }
}