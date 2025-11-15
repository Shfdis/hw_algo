#include <bits/stdc++.h>
using namespace std;
void Merge(vector<int>& a, int l, int r) {
    if (r - l <= 15) {
        for (int i = l; i < r; ++i) {
            int mn = i;
            for (int j = i + 1; j < r; ++j) {
                if (a[j] < a[mn]) {
                    mn = j;
                }
            }
            swap(a[i], a[mn]);
        }
        return;
    }
    int m = (r + l) / 2;
    Merge(a, l, m);
    Merge(a, m, r);
    vector<int> buffer(r - l);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, buffer.begin());
    for (int i = 0; i < r - l; ++i) {
        a[l + i] = buffer[i];
    }
}
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& i :a) {
        cin >> i;
    }
    Merge(a, 0, n);
    for (auto i : a) {
        cout << i << " ";
    }
};