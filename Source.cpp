#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>
#include<filesystem>
#include<fstream>
#include <unordered_map>
#include <string>

using namespace std;

void worstFitWithLinearSearch(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void worstFitWithPriorityQueue(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void worstFitDecreasingWithLinearSearch(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void worstFitDecreasingWithPriorityQueue(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
void firstFitDecreasing(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration);
vector<vector<int>> folderFilling(vector<int> fileDurations, int folderDuration);
int folderFillingHelper(vector<vector<int>>& folderDurationMemo, vector<vector<char>>& fileMemo, vector<int>& fileDurations, int fileDurationsLength, int folderDuration);
void tracefolderfiles(vector<vector<char>>& fileMemo, vector<int>& folder, vector<int>& fileDurations, int fileDurationsLength, int folderDuration);
void create_folders(int sampleNumber, string algorithmName,  vector<vector<int>> folders, unordered_map<string, int> foldersMap, unordered_map<string, string>& foldersMapRaw);
void readSamples(unordered_map<string, int>& foldersMap, vector<int>& encodedDurations, int sampleNumber, unordered_map<string, string>& foldersMapRaw);
vector<int> encodeDuration(vector<string> durations);

int main() {
    int folderDuration = 100;
    unordered_map<string, int> foldersMap;
    unordered_map<string, string> foldersMapRaw;
    vector<vector<int>> folders;    

    vector<pair<int, int>> files;  // First value is the file duration -- Second value is the folder the file belongs to.

    // vector<int> fileDurations = { 70, 80, 20, 15, 15 };  // 2 folders
    // vector<int> fileDurations = { 10, 20, 25, 70, 80, 90 }; // 3 or 4 folders
    //vector<int> fileDurations = { 10, 15, 20, 5, 70, 80 };  // 2 folders
    vector<int> fileDurations;
    readSamples(foldersMap, fileDurations, 1, foldersMapRaw);

    files.reserve(fileDurations.size());

    auto start = chrono::steady_clock::now();

    // worstFitWithLinearSearch(files, fileDurations, folderDuration);
    // worstFitWithPriorityQueue(files, fileDurations, folderDuration);
    // worstFitDecreasingWithLinearSearch(files, fileDurations, folderDuration);
    // worstFitDecreasingWithPriorityQueue(files, fileDurations, folderDuration);
    // firstFitDecreasing(files, fileDurations, folderDuration);
    // folders = folderFilling(fileDurations, folderDuration);

    auto end = chrono::steady_clock::now();

    auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "\nExecution time: " << executionTime << " microseconds" << endl;
    create_folders(1, "FolderFilling", folders,foldersMap, foldersMapRaw);
    return 0;
}

void readSamples(unordered_map<string, int> &foldersMap, vector<int> &encodedDurations, int sampleNumber, unordered_map<string, string>& foldersMapRaw) {
    string samplePath = "Sample Tests/Sample " + to_string(sampleNumber) + "/INPUT/AudiosInfo.txt";
    ifstream sample(samplePath);
    string line;
    string concat = "";
    vector<string> inputs;
    vector<string> durations;
    
    vector<string> names;
    
    while (getline(sample, line)) {
        cout << line << endl;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ' ' ) {
                inputs.push_back(concat);
                concat = "";
            }
            else if(i == line.size() - 1)
            {
                concat += line[i];
                inputs.push_back(concat);
                concat = "";
            }
            else
            {
                concat += line[i];
            }
            
        }
    }
    for (int i = 1; i < inputs.size(); i += 2) {
        names.push_back(inputs[i]);
        durations.push_back(inputs[i + 1]);
    }
    
    for (int i = 0; i < names.size(); i++) {
        foldersMapRaw.insert({ names[i], durations[i] });
    }

    encodedDurations = encodeDuration(durations);
    
    for (int i = 0; i < names.size(); i++) {
        foldersMap.insert({ names[i], encodedDurations[i]});
    }
    
}

vector<int> encodeDuration(vector<string> durations) {
    string concat;
    vector<int> timeToParts;
    vector<int> finalDurations;
    int timeToSeconds;
    for (string val : durations) {
        for(int i= 0; i < val.size(); i++){
            if (val[i] == ':') {
                timeToParts.push_back(stoi(concat));
                concat = "";
                continue;
            }
            else if (i == val.size() - 1) {
                concat += val[i];
                timeToParts.push_back(stoi(concat));
            }
            concat += val[i];
        }
        timeToSeconds = timeToParts[0] * 3600 + timeToParts[1] * 60 + timeToParts[2];
        finalDurations.push_back(timeToSeconds);
        timeToParts.clear();
        concat = "";
    }

    return finalDurations;
}

void create_folders(int sampleNumber, string algorithmName, vector<vector<int>> folders, unordered_map<string, int> foldersMap, unordered_map<string, string>& foldersMapRaw) {

    string folderPath;
    string sourceFile ;
    

    for (int i = 0; i < folders.size(); i++) {
        folderPath = "OUTPUT/sample " + to_string(sampleNumber) + "/" + algorithmName + "/F" + to_string(i + 1);
        filesystem::create_directories(folderPath);
        ofstream metaData(folderPath + "_METADATA.txt");
        metaData << "F" + to_string(i + 1) << endl;
        
        
        for (int j = 0; j < folders[i].size(); j++) {
            for (const auto& pair : foldersMap) {
                if (pair.second == folders[i][j]) {
                    sourceFile = "Sample Tests/Sample 1/INPUT/Audios/" + pair.first;
                    filesystem::copy(sourceFile, folderPath, filesystem::copy_options::overwrite_existing);
                    metaData << pair.first << " " << foldersMapRaw[pair.first] << endl;
                    foldersMap.erase(pair.first);
                    break;
                }
            }
        }
        metaData.close();
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

void worstFitDecreasingWithLinearSearch(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    worstFitWithLinearSearch(files, fileDurations, folderDuration);
}

void worstFitDecreasingWithPriorityQueue(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration) {
    // The complexity of sort is O(N⋅log(N)) according to https://en.cppreference.com/w/cpp/algorithm/sort
    sort(fileDurations.begin(), fileDurations.end(), greater<int>());

    worstFitWithPriorityQueue(files, fileDurations, folderDuration);
}

void firstFitDecreasing(vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration) {
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

vector<vector<int>> folderFilling(vector<int> fileDurations, int folderDuration) {
    vector<int> temp;
    vector<vector<int>> folders;

    sort(fileDurations.begin(), fileDurations.end());   // O(N⋅log(N))

    while (!fileDurations.empty()) {
        folders.push_back({});

        vector<vector<char>> fileMemo(folderDuration + 1, vector<char>(int(fileDurations.size() + 1), '\0'));   // N * D
        vector<vector<int>> folderDurationMemo(folderDuration + 1, vector<int>(int(fileDurations.size() + 1), -1)); // N * D

        folderFillingHelper(folderDurationMemo, fileMemo, fileDurations, int(fileDurations.size()), folderDuration);

        tracefolderfiles(fileMemo, folders.back(), fileDurations, int(fileDurations.size()), folderDuration);

        set_symmetric_difference(fileDurations.begin(), fileDurations.end(),
            folders.back().begin(), folders.back().end(), back_inserter(temp)); // N + D

        fileDurations = temp;

        temp.clear();
    }
    
    return folders;
}

int folderFillingHelper(vector<vector<int>>& folderDurationMemo, vector<vector<char>>& fileMemo, vector<int>& fileDurations, int fileDurationsLength, int folderDuration) {
    if (fileDurationsLength == 0 || folderDuration == 0) {
        return folderDurationMemo[folderDuration][fileDurationsLength] = folderDuration;
    }
    else if (folderDurationMemo[folderDuration][fileDurationsLength] != -1) {
        return folderDurationMemo[folderDuration][fileDurationsLength];
    }
    else if (fileDurations[fileDurationsLength - 1] > folderDuration) {
        fileMemo[folderDuration][fileDurationsLength] = '-';

        return folderDurationMemo[folderDuration][fileDurationsLength] =
            folderFillingHelper(folderDurationMemo, fileMemo, fileDurations, fileDurationsLength - 1, folderDuration);
    }
    else {
        folderDurationMemo[folderDuration][fileDurationsLength] =
            min(folderFillingHelper(folderDurationMemo, fileMemo, fileDurations, fileDurationsLength - 1, folderDuration),
                folderFillingHelper(folderDurationMemo, fileMemo, fileDurations, fileDurationsLength - 1,
                    folderDuration - fileDurations[fileDurationsLength - 1]));

        if (folderDurationMemo[folderDuration][fileDurationsLength] == folderDurationMemo[folderDuration][fileDurationsLength - 1]) {
            fileMemo[folderDuration][fileDurationsLength] = '-';

            return folderDurationMemo[folderDuration][fileDurationsLength];
        }
        else {
            fileMemo[folderDuration][fileDurationsLength] = '\\';

            return folderDurationMemo[folderDuration][fileDurationsLength];
        }
    }
}

void tracefolderfiles(vector<vector<char>>& fileMemo, vector<int>& folder, vector<int>& fileDurations, int fileDurationsLength, int folderDuration) {
    if (fileDurationsLength == 0 || folderDuration == 0) {
        return;
    }
    else if (fileMemo[folderDuration][fileDurationsLength] == '\\') {
        tracefolderfiles(fileMemo, folder, fileDurations, fileDurationsLength - 1, folderDuration - fileDurations[fileDurationsLength - 1]);

        folder.push_back(fileDurations[fileDurationsLength - 1]);
    }
    else {
        tracefolderfiles(fileMemo, folder, fileDurations, fileDurationsLength - 1, folderDuration);
    }
}
