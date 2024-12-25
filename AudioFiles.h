#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class AudioFiles {
public:
	void load(unordered_map<string, tm>& fileMap, vector<int>& fileDurations, string testType, int testNumber);
	void save(unordered_map<string, tm> fileMap, vector<pair<int, int>>& files, string testType, int testNumber, string algorithm);

private:
	void fillFolders(vector<pair<int, int>>& files, vector<vector<int>>& folders);
};
