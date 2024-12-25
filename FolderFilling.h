#pragma once

#include "IAlgorithm.h"

#include <string>
#include <vector>

using namespace std;

class FolderFilling : public IAlgorithm {
public:
	string getName() override;
	void execute(vector<pair<int, int>>& files, vector<int> fileDurations, int folderDuration) override;

private:
	void getFolderFiles(vector<vector<pair<int, int>>>& memo, vector<int>& fileDurations, int folderDuration);
	void traceFolderFiles(vector<vector<pair<int, int>>>& memo, vector<pair<int, int>>& files, vector<int>& fileDurations, int folderDuration, int currentFolderNumber);
};
