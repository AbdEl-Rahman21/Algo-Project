#include <chrono>
#include <iostream>
#include <queue>
#include<vector>

using namespace std;
int MostRemaining(vector<int> RemainingSpace, int DesiredDuration)
{
    int MaxRemaining=-1;
    int MaxIndex = 0;
    for (int i = 0; i < RemainingSpace.size(); i++)
    {
        if (MaxRemaining <= RemainingSpace[i])
        {
            MaxRemaining = RemainingSpace[i];
            MaxIndex = i;
        }
    }
    return MaxIndex;
}
void Worstfit_LinearSearch(vector<int> AudiosDuration,int DesiredDuration)
{
    vector<vector<int>> Folders = { {} };
    vector<int> RemainingSpace = {DesiredDuration};

        for (int i = 0; i < AudiosDuration.size(); i++)
        {
            int Maxindex = MostRemaining(RemainingSpace, DesiredDuration);

            if (AudiosDuration[i] < RemainingSpace[Maxindex] && Maxindex != -1)
            {
                Folders[Maxindex].push_back(AudiosDuration[i]);
                RemainingSpace[Maxindex] -= AudiosDuration[i];
            }

            else
            {
                Folders.push_back({ AudiosDuration[i] });
                RemainingSpace.push_back(DesiredDuration - AudiosDuration[i]);
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
int main() {
    auto start = chrono::steady_clock::now();
    vector<int> AudiosDuration = { 70, 80, 20, 15, 15 };
    int DesiredDuration = 100;

    Worstfit_LinearSearch(AudiosDuration, DesiredDuration);
    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Execution time: " << duration << " microseconds" << endl;

    return 0;
}
