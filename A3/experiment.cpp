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

void heapify(vector<int>& a, int i) {
    if (i == 0) {
        return;
    }
    if (a[(i - 1) / 2] > a[i]) {
        swap(a[(i - 1) / 2], a[i]);
    }
    heapify(a, (i - 1) / 2);
}

void fistingify(vector<int>& a, int i) {
    if (2 * i + 1 >= a.size()) {
        return;
    }
    if (2 * i + 2 < a.size()) {
        if (a[i] <= min(a[2 * i + 1], a[2 * i + 2])) {
            return;
        }
        if (a[2 * i + 1] < a[2 * i + 2]) {
            swap(a[i], a[2 * i + 1]);
            fistingify(a, 2 * i + 1);
        }
        else {
            swap(a[i], a[2 * i + 2]);
            fistingify(a, 2 * i + 2);
        }
    }
    else if (a[2 * i + 1] < a[i]) {
        swap(a[i], a[2 * i + 1]);
        fistingify(a, 2 * i + 1);
    }
}

void buildMaxHeap(vector<int>& a) {
    for (int i = 0; i < a.size(); ++i) {
        heapify(a, i);
    }
}

void heapSort(vector<int>& a) {
    vector<int> result;
    buildMaxHeap(a);
    while (!a.empty()) {
        swap(a.front(), a.back());
        result.push_back(a.back());
        a.pop_back();
        fistingify(a, 0);
    }
    a = result;
}

void insertionSort(vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        int mn = i;
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[j] < a[mn]) {
                mn = j;
            }
        }
        swap(a[mn], a[i]);
    }
}

mt19937_64 rnd(1488);

void quickSortStandard(vector<int>& a) {
    if (a.size() <= 1) return;
    int piv = rnd() % a.size();
    vector<int> l, r;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] < a[piv] || (a[i] == a[piv] && rnd() % 2 == 0)) {
            l.push_back(a[i]);
        }
        else {
            r.push_back(a[i]);
        }
    }
    quickSortStandard(l);
    quickSortStandard(r);
    a.clear();
    for (auto i : l) a.push_back(i);
    for (auto i : r) a.push_back(i);
}

void Sort(vector<int>& a, int dpth = 0) {
    if (a.size() <= 1) {
        return;
    }
    if (__lg(a.size()) * 2 <= dpth) {
        heapSort(a);
        return;
    }
    if (a.size() <= 16) {
        insertionSort(a);
        return;
    }
    int piv = rnd() % a.size();
    vector<int> l, r;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] < a[piv] || a[i] == a[piv] && rnd() % 2 == 0) {
            l.push_back(a[i]);
        }
        else {
            r.push_back(a[i]);
        }
    }
    Sort(l, dpth + 1);
    Sort(r, dpth + 1);
    a.clear();
    for (auto i : l) {
        a.push_back(i);
    }
    for (auto i : r) {
        a.push_back(i);
    }
}

class SortTester {
    ArrayGenerator gen;
public:
    long long testStandard(vector<int> arr, int type) {
        auto start = chrono::high_resolution_clock::now();
        quickSortStandard(arr);
        auto elapsed = chrono::high_resolution_clock::now() - start;
        return chrono::duration_cast<chrono::microseconds>(elapsed).count();
    }
    
    long long testHybrid(vector<int> arr) {
        auto start = chrono::high_resolution_clock::now();
        Sort(arr);
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
        cerr << "Usage: " << argv[0] << " <size> <type> [standard|hybrid]" << endl;
        return 1;
    }
    
    int size = atoi(argv[1]);
    int type = atoi(argv[2]);
    string mode = argc > 3 ? argv[3] : "standard";
    
    SortTester tester;
    vector<long long> times;
    int runs = 5;
    
    for (int run = 0; run < runs; ++run) {
        vector<int> arr = tester.generateArray(size, type);
        long long time;
        if (mode == "standard") {
            time = tester.testStandard(arr, type);
        } else {
            time = tester.testHybrid(arr);
        }
        times.push_back(time);
    }
    
    sort(times.begin(), times.end());
    long long median = times[times.size() / 2];
    long long avg = accumulate(times.begin(), times.end(), 0LL) / runs;
    
    cout << median << " " << avg << endl;
    return 0;
}

