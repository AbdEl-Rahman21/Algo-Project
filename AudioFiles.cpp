#include "AudioFiles.h"

void AudioFiles::load(unordered_map<string, tm>& fileMap, vector<int>& fileDurations, string testType, int testNumber) {
    int numberOfFiles = 0;

    ifstream audioMetadata;

    string fileName = "";
    string inputPath = "";
    string fileDuration = "";

    if (testType == "Sample") {
        inputPath = "Sample Tests/Sample " + to_string(testNumber) + "/INPUT/AudiosInfo.txt";
    }
    else {
        inputPath = "Complete" + to_string(testNumber) + "/AudiosInfo.txt";
    }

    audioMetadata.open(inputPath, ios::in);

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

void AudioFiles::save(unordered_map<string, tm> fileMap, vector<pair<int, int>>& files, string testType, int testNumber, string algorithm) {
    int fileDuration;

    string audioPath = "";
    string folderPath = "";
    string sourceFile = "";

    ofstream folderMetadata;

    vector<vector<int>> folders = { {} };

    fillFolders(files, folders);

    if (testType == "Sample") {
        audioPath = "Sample Tests/Sample " + to_string(testNumber) + "/INPUT/Audios/";
    }
    else {
        audioPath = "Complete" + to_string(testNumber) + "/Audios/";
    }

    for (int i = 0; i < folders.size(); i++) {
        folderPath = "OUTPUT/" + testType + " Test " + to_string(testNumber) + "/" + algorithm + "/F" + to_string(i + 1);

        filesystem::create_directories(folderPath);

        folderMetadata.open(folderPath + "_METADATA.txt", ios::out | ios::trunc);

        folderMetadata << "F" + to_string(i + 1) << endl;

        tm totalDuration = { 0 };

        for (int j = 0; j < folders[i].size(); j++) {
            for (auto& file : fileMap) {
                fileDuration = file.second.tm_hour * 3600 + file.second.tm_min * 60 + file.second.tm_sec;

                if (fileDuration == folders[i][j]) {
                    sourceFile = audioPath + file.first;

                    filesystem::copy(sourceFile, folderPath, filesystem::copy_options::overwrite_existing);

                    folderMetadata << file.first << " " << put_time(&file.second, "%T") << endl;

                    totalDuration.tm_hour += file.second.tm_hour;
                    totalDuration.tm_min += file.second.tm_min;
                    totalDuration.tm_sec += file.second.tm_sec;

                    fileMap.erase(file.first);

                    break;
                }
            }
        }

        totalDuration.tm_min += totalDuration.tm_sec / 60;
        totalDuration.tm_sec %= 60;

        totalDuration.tm_hour += totalDuration.tm_min / 60;
        totalDuration.tm_min %= 60;

        folderMetadata << put_time(&totalDuration, "%T") << endl;

        folderMetadata.close();
    }
}

void AudioFiles::fillFolders(vector<pair<int, int>>& files, vector<vector<int>>& folders) {
    int folderNumber = 0;

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
}
