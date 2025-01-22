#include <iostream>
#include <vector>
#include "struct/set.hpp"

using namespace std;

bool findSubset(vector<int>& arr, vector<int>& subset, int target, int index) {
    if (target == 0) return true;
    if (index >= arr.size() || target < 0) return false;
    subset.push_back(arr[index]);
    if (findSubset(arr, subset, target - arr[index], index + 1)) return true;
    subset.pop_back();
    return findSubset(arr, subset, target, index + 1);
}

vector<vector<int>> partitionIntoSubsets(vector<int> arr, int target, int k) {
    vector<vector<int>> subsets;
    Set used;
    for (int i = 0; i < k; i++) {
        vector<int> subset;
        if (findSubset(arr, subset, target, 0)) {
            subsets.push_back(subset);
            for (int num : subset) {
                used.put(to_string(num));
            }
            vector<int> newArr;
            for (int num : arr) {
                if (!used.contains(to_string(num))) newArr.push_back(num);
            }
            arr = newArr;
        }
    }
    return subsets;
}

int main() {
    Set mySet;
    vector<int> values = {10, 5, 4, 7, 3, 1};
    for (int val : values) mySet.put(to_string(val));
    
    vector<int> sortedValues;
    string setStr = mySet.join();
    size_t pos = 0;
    while ((pos = setStr.find(",")) != string::npos) {
        sortedValues.push_back(stoi(setStr.substr(0, pos)));
        setStr.erase(0, pos + 1);
    }
    sortedValues.push_back(stoi(setStr));
    
    vector<vector<int>> result = partitionIntoSubsets(sortedValues, 10, 3);
    
    cout << "Разбиение на подмножества:" << endl;
    for (const auto& subset : result) {
        cout << "{";
        for (size_t i = 0; i < subset.size(); i++) {
            cout << subset[i] << (i < subset.size() - 1 ? ", " : "");
        }
        cout << "}" << endl;
    }
    return 0;
}
