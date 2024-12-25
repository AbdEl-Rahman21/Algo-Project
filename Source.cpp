#include "AudioFiles.h"
#include "FirstFitDecreasing.h"
#include "FolderFilling.h"
#include "IAlgorithm.h"
#include "WorstFitDecreasingLinearSearch.h"
#include "WorstFitDecreasingPriorityQueue.h"
#include "WorstFitLinearSearch.h"
#include "WorstFitPriorityQueue.h"

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void runTests(string testType);

int main() {
    int choice = 0;

    try {
        cout << "Tests:-\n" << "1 - Sample Tests\n" << "2 - Complete Tests\n" << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            runTests("Sample");
        }
        else {
            runTests("Complete");
        }
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}

void runTests(string testType) {
    int folderDuration = 0;

    vector<int> fileDurations;

    long long executionTime = 0;

    // First value is the file duration -- Second value is the folder the file belongs to.
    vector<pair<int, int>> files;

    unordered_map<string, tm> fileMap;

    AudioFiles* audiofiles = new AudioFiles();

    chrono::steady_clock::time_point start, end;

    vector<IAlgorithm*> algorithms = { new WorstFitLinearSearch(), new WorstFitPriorityQueue(), new WorstFitDecreasingLinearSearch(),
        new WorstFitDecreasingPriorityQueue(), new FirstFitDecreasing(), new FolderFilling() };

    for (int i = 1; i < 4; i++) {
        audiofiles->load(fileMap, fileDurations, testType, i);

        files.reserve(fileDurations.size());

        if (testType == "Sample") {
            folderDuration = 100;
        }
        else {
            switch (i) {
            case 1:
                folderDuration = 152;

                break;
            case 2:
                folderDuration = 275;

                break;
            case 3:
                folderDuration = 321;

                break;
            }
        }

        for (IAlgorithm* algorithm : algorithms) {
            start = chrono::steady_clock::now();

            algorithm->execute(files, fileDurations, folderDuration);

            end = chrono::steady_clock::now();

            executionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

            cout << "Execution time of Sample Test " << i << " using " << algorithm->getName() << ": " << executionTime << " microseconds" << endl;

            audiofiles->save(fileMap, files, testType, i, algorithm->getName());

            files.clear();
        }

        fileMap.clear();
        fileDurations.clear();
    }
}
