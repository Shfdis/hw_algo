#include <bits/stdc++.h>
using namespace std;
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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& i :a) {
        cin >> i;
    }
    Sort(a);
    for (auto i : a) {
        cout << i << " ";
    }
};