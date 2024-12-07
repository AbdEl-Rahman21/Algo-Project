#include <chrono>
#include <iostream>
#include <queue>

using namespace std;

int main() {
    auto start = chrono::steady_clock::now();

    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Execution time: " << duration << " microseconds" << endl;

    return 0;
}
