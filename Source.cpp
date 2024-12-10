#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void run();

void readInput(unordered_map<string, tm>& fileMap, vector<int>& fileDurations, int inputNumber);
void saveOutput(unordered_map<string, tm> fileMap, vector<pair<int, int>>& files, int inputNumber, string algorithmName);

void worstFitWithLinearSearch(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void worstFitWithPriorityQueue(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void worstFitDecreasingWithLinearSearch(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration);
void worstFitDecreasingWithPriorityQueue(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration);
void firstFitDecreasing(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration);
void folderFilling(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration);
int folderFillingHelper(vector<vector<pair<int, int>>>& memo, vector<int>& fileDurations, int fileDurationsLength, int folderDuration);
void tracefolderfiles(vector<vector<pair<int, int>>>& memo, vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration, int currentFolderNumber);

int main() {
    try {
        run();
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

void run() {
    int folderDuration = 100;

    vector<int> fileDurations;

    vector<pair<int, int>> files;  // First value is the file duration -- Second value is the folder the file belongs to.

    unordered_map<string, tm> fileMap;

    long long executionTime;
    chrono::steady_clock::time_point start, end;

    vector<string> algorithms = { "Worst-fit Linear Search", "Worst-fit Priority Queue", "WorstFit Decreasing Linear Search",
        "WorstFit Decreasing Priority Queue", "FirstFit Decreasing", "FolderFilling" };

    files.reserve(fileDurations.size());

    for (int i = 1; i < 4; i++) {
        readInput(fileMap, fileDurations, i);

        for (string& algorithm : algorithms) {
            if (algorithm == "Worst-fit Linear Search") {
                start = chrono::steady_clock::now();

                worstFitWithLinearSearch(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }
            else if (algorithm == "Worst-fit Priority Queue") {
                start = chrono::steady_clock::now();

                worstFitWithPriorityQueue(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }
            else if (algorithm == "WorstFit Decreasing Linear Search") {
                start = chrono::steady_clock::now();

                worstFitDecreasingWithLinearSearch(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }
            else if (algorithm == "WorstFit Decreasing Priority Queue") {
                start = chrono::steady_clock::now();

                worstFitDecreasingWithPriorityQueue(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }
            else if (algorithm == "FirstFit Decreasing") {
                start = chrono::steady_clock::now();

                firstFitDecreasing(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }
            else if (algorithm == "FolderFilling") {
                start = chrono::steady_clock::now();

                folderFilling(files, fileDurations, folderDuration);

                end = chrono::steady_clock::now();
            }

            executionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

            cout << "Execution time of test " << i << " using " << algorithm << " : " << executionTime << " microseconds" << endl;

            saveOutput(fileMap, files, i, algorithm);

            files.clear();
        }

        fileMap.clear();
        fileDurations.clear();
    }
}

void readInput(unordered_map<string, tm>& fileMap, vector<int>& fileDurations, int inputNumber) {
    int numberOfFiles = 0;

    string fileName = "";
    string fileDuration = "";

    ifstream audioMetadata;

    audioMetadata.open("Sample Tests/Sample " + to_string(inputNumber) + "/INPUT/AudiosInfo.txt", ios::in);

    audioMetadata >> numberOfFiles;

    fileMap.reserve(numberOfFiles);
    fileDurations.reserve(numberOfFiles);

    for (int i = 0; i < numberOfFiles; i++) {
        audioMetadata.ignore();

        audioMetadata >> fileName;
        audioMetadata >> fileDuration;

        istringstream ss(fileDuration);

        ss >> get_time(&fileMap[fileName], "%H:%M:%S");

        fileDurations.push_back(fileMap[fileName].tm_hour * 3600 + fileMap[fileName].tm_min * 60 + fileMap[fileName].tm_sec);
    }

    audioMetadata.close();
}

void saveOutput(unordered_map<string, tm> fileMap, vector<pair<int, int>>& files, int inputNumber, string algorithmName) {
    int folderNumber = 0;

    vector<vector<int>> folders = { {} };

    // Sort ascending by second element, if both are equal sort descending by first element 
    sort(files.begin(), files.end(), [](auto& left, auto& right) {
        return (left.second == right.second) ? left.first > right.first : left.second < right.second;
        });

    for (auto& file : files) {
        if (file.second - 1 != folderNumber) {
            ++folderNumber;

            folders.push_back({});
        }

        folders[folderNumber].push_back(file.first);
    }

    int fileDuration;

    string folderPath = "";
    string sourceFile = "";

    ofstream folderMetadata;

    for (int i = 0; i < folders.size(); i++) {
        folderPath = "OUTPUT/Sample " + to_string(inputNumber) + "/" + algorithmName + "/F" + to_string(i + 1);

        filesystem::create_directories(folderPath);

        folderMetadata.open(folderPath + "_METADATA.txt", ios::out | ios::trunc);

        folderMetadata << "F" + to_string(i + 1) << endl;

        tm totalDuration{};

        for (int j = 0; j < folders[i].size(); j++) {
            for (auto& file : fileMap) {
                fileDuration = file.second.tm_hour * 3600 + file.second.tm_min * 60 + file.second.tm_sec;

                if (fileDuration == folders[i][j]) {
                    sourceFile = "Sample Tests/Sample " + to_string(inputNumber) + "/INPUT/Audios/" + file.first;

                    filesystem::copy(sourceFile, folderPath, filesystem::copy_options::overwrite_existing);

                    folderMetadata << file.first << "\t" << put_time(&file.second, "%T") << endl;

                    totalDuration.tm_hour += file.second.tm_hour;
                    totalDuration.tm_min += file.second.tm_min;
                    totalDuration.tm_sec += file.second.tm_sec;

                    fileMap.erase(file.first);

                    break;
                }
            }
        }

        mktime(&totalDuration);

        folderMetadata << put_time(&totalDuration, "%T") << endl;

        folderMetadata.close();
    }
}

void worstFitWithLinearSearch(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration) {
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

void worstFitWithPriorityQueue(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration) {
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

void worstFitDecreasingWithLinearSearch(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    worstFitWithLinearSearch(files, fileDurations, folderDuration);
}

void worstFitDecreasingWithPriorityQueue(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    worstFitWithPriorityQueue(files, fileDurations, folderDuration);
}

void firstFitDecreasing(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
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

void folderFilling(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) {
    int currentFolderNumber = 1;

    while (!fileDurations.empty()) {
        // (Indices) First index is the Folder Duration -- Second index is the File Durations Index (from fileDurations).
        // (Pair Values) First value is the folder duration -- Second value is used for tracing (0 == '←', 1 == '↖').
        vector<vector<pair<int, int>>> memo(folderDuration + 1, vector<pair<int, int>>(int(fileDurations.size() + 1), make_pair(-1, -1))); // O(N⋅D)

        folderFillingHelper(memo, fileDurations, int(fileDurations.size()), folderDuration);

        tracefolderfiles(memo, files, fileDurations, folderDuration, currentFolderNumber);

        ++currentFolderNumber;
    }
}

int folderFillingHelper(vector<vector<pair<int, int>>>& memo, vector<int>& fileDurations, int fileDurationsLength, int folderDuration) {
    if (fileDurationsLength == 0 || folderDuration == 0) {
        memo[folderDuration][fileDurationsLength].first = folderDuration;
    }
    else if (memo[folderDuration][fileDurationsLength].first != -1) {
        return memo[folderDuration][fileDurationsLength].first;
    }
    else if (fileDurations[fileDurationsLength - 1] > folderDuration) {
        memo[folderDuration][fileDurationsLength] =
            make_pair(folderFillingHelper(memo, fileDurations, fileDurationsLength - 1, folderDuration), 0);
    }
    else {
        memo[folderDuration][fileDurationsLength].first =
            min(folderFillingHelper(memo, fileDurations, fileDurationsLength - 1, folderDuration),
                folderFillingHelper(memo, fileDurations, fileDurationsLength - 1, folderDuration - fileDurations[fileDurationsLength - 1]));

        if (memo[folderDuration][fileDurationsLength].first == memo[folderDuration][fileDurationsLength - 1].first) {
            memo[folderDuration][fileDurationsLength].second = 0;
        }
        else {
            memo[folderDuration][fileDurationsLength].second = 1;
        }
    }

    return memo[folderDuration][fileDurationsLength].first;
}

void tracefolderfiles(vector<vector<pair<int, int>>>& memo, vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration, int currentFolderNumber) {
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
