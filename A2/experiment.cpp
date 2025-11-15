#include <bits/stdc++.h>
using namespace std;

class ArrayGenerator {
    vector<int> base_array;
    mt19937 rng;
public:
    ArrayGenerator() : rng(179) {
        base_array.resize(100000);
        for (int i = 0; i < 100000; ++i) {
            base_array[i] = rng() % 6001;
        }
    }
    
    vector<int> getRandom(int n) {
        vector<int> result(base_array.begin(), base_array.begin() + n);
        shuffle(result.begin(), result.end(), rng);
        return result;
    }
    
    vector<int> getReversed(int n) {
        vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = n - i;
        }
        return result;
    }
    
    vector<int> getAlmostSorted(int n) {
        vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = i;
        }
        int swaps = n / 100;
        for (int i = 0; i < swaps; ++i) {
            int idx1 = rng() % n;
            int idx2 = rng() % n;
            swap(result[idx1], result[idx2]);
        }
        return result;
    }
};

void mergeSortStandard(vector<int>& a, int l, int r) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergeSortStandard(a, l, m);
    mergeSortStandard(a, m, r);
    vector<int> buffer(r - l);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, buffer.begin());
    for (int i = 0; i < r - l; ++i) {
        a[l + i] = buffer[i];
    }
}

void insertionSort(vector<int>& a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void mergeSortHybrid(vector<int>& a, int l, int r, int threshold) {
    if (r - l <= threshold) {
        insertionSort(a, l, r);
        return;
    }
    int m = (l + r) / 2;
    mergeSortHybrid(a, l, m, threshold);
    mergeSortHybrid(a, m, r, threshold);
    vector<int> buffer(r - l);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, buffer.begin());
    for (int i = 0; i < r - l; ++i) {
        a[l + i] = buffer[i];
    }
}

class SortTester {
    ArrayGenerator gen;
public:
    long long testStandard(vector<int> arr, int type) {
        auto start = chrono::high_resolution_clock::now();
        mergeSortStandard(arr, 0, arr.size());
        auto elapsed = chrono::high_resolution_clock::now() - start;
        return chrono::duration_cast<chrono::microseconds>(elapsed).count();
    }
    
    long long testHybrid(vector<int> arr, int threshold) {
        auto start = chrono::high_resolution_clock::now();
        mergeSortHybrid(arr, 0, arr.size(), threshold);
        auto elapsed = chrono::high_resolution_clock::now() - start;
        return chrono::duration_cast<chrono::microseconds>(elapsed).count();
    }
    
    vector<int> generateArray(int n, int type) {
        if (type == 0) return gen.getRandom(n);
        if (type == 1) return gen.getReversed(n);
        return gen.getAlmostSorted(n);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <size> <type> [standard|hybrid] [threshold]" << endl;
        return 1;
    }
    
    int size = atoi(argv[1]);
    int type = atoi(argv[2]);
    string mode = argc > 3 ? argv[3] : "standard";
    int threshold = argc > 4 ? atoi(argv[4]) : 15;
    
    SortTester tester;
    vector<long long> times;
    int runs = 5;
    
    for (int run = 0; run < runs; ++run) {
        vector<int> arr = tester.generateArray(size, type);
        long long time;
        if (mode == "standard") {
            time = tester.testStandard(arr, type);
        } else {
            time = tester.testHybrid(arr, threshold);
        }
        times.push_back(time);
    }
    
    sort(times.begin(), times.end());
    long long median = times[times.size() / 2];
    long long avg = accumulate(times.begin(), times.end(), 0LL) / runs;
    
    cout << median << " " << avg << endl;
}
