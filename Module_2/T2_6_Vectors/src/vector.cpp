#include "vector.hpp"
#include <vector>

int GetMin(std::vector<int> v) {
    int min_val = v[0];
    for (int x : v) {
        if (x < min_val) min_val = x;
    }
    return min_val;
}

int GetMax(std::vector<int> v) {
    int max_val = v[0];
    for (int x : v) {
        if (x > max_val) max_val = x;
    }
    return max_val;
}

double GetAvg(std::vector<int> v) {
    long long sum = 0;
    for (int x : v) sum += x;
    return static_cast<double>(sum) / static_cast<double>(v.size());
}
