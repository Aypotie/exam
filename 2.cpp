#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

uint64_t globalSum = 0;
mutex mtx;

void partialSum(const vector<int>& data, int start, int end) {
    uint64_t localSum = 0;
    for (int i = start; i < end; i++) {
        localSum += data[i];
    }
    lock_guard<mutex> lock(mtx);
    globalSum += localSum;

}

int main() {
    int dataSize = 10000000;
    vector<int> data(dataSize, 1);

    auto startTime = chrono::high_resolution_clock::now();
    uint64_t singleSum = 0;
    for(int val: data) {
        singleSum += val;
    }
    auto endTime = chrono::high_resolution_clock::now();
    auto singleTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    cout << singleTime << " " << singleSum << endl;

    int numThreads = 4;
    int blockSize = dataSize / numThreads;
    globalSum = 0;

    vector<thread> threads(numThreads);
    startTime = chrono::high_resolution_clock::now();

    for(int i = 0; i < numThreads; i++) {
        uint64_t start = i * blockSize;
        uint64_t end = (i == numThreads - 1) ? dataSize : start + blockSize;

        threads[i] = thread(partialSum, ref(data), start, end);
    }

    for(auto& t : threads) {
        t.join();
    }
    endTime = chrono::high_resolution_clock::now();
    auto multiTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    cout << multiTime << " " << globalSum << endl;

    return 0;
}