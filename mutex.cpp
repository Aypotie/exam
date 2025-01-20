#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int64_t globalSum = 0;
mutex mtx;

void partialSum(const vector<int>& data, size_t start, size_t end) {
    uint64_t localSum = 0;
    for(size_t i = start; i < end; i++) {
        localSum += data[i];
    }

    lock_guard<mutex> lock(mtx);
    globalSum += localSum;
}

int main() {
    const size_t dataSize = 1000000;
    vector<int> data(dataSize, 1);

    auto startTime = chrono::high_resolution_clock::now();

    uint64_t singleThreadSum = 0;
    for(int val : data) {
        singleThreadSum += val;
    } 

    auto endTime = chrono::high_resolution_clock::now();
    auto singleThreadTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    cout << singleThreadSum << " Single: " << singleThreadTime << endl;

    int numThreads = 4;
    vector<thread> threads(numThreads);
    int blockSize = dataSize / numThreads;

    globalSum = 0;
    startTime = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numThreads; i++) {
        size_t start = i * blockSize;
        size_t end = (i == numThreads - 1) ? dataSize : start + blockSize;
    
        threads[i] = thread(partialSum, ref(data), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    endTime = chrono::high_resolution_clock::now();
    auto multiThreadDuration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    cout << globalSum << " Multi-threaded " << multiThreadDuration << endl;
   
    return 0;
}