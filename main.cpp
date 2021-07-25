#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    list<int> v;
    for (int i = 0, tmp = 0; i < n; ++i) {
       cin >> tmp;
       v.push_back(tmp);
    }
    v.erase(unique(v.begin(), v.end()), v.end());

   int minNum = INT_MAX;
   for (int i : v) {
       if (i != 0) minNum = min(minNum, i);
   }

    int m = 0;
    vector<int> ans;
    while (minNum != INT_MAX) {
        int minNum2 = INT_MAX;
        for (int& i : v) {
            if (i != 0) {
                i -= minNum;
                if (i != 0) minNum2 = min(minNum2, i);
            }
        }
        minNum = minNum2;
        v.erase(unique(v.begin(), v.end()), v.end());
        ans.push_back(v.size());
        ++m;
    }
    cout << m << '\n';
    for (int i : ans) cout << m << ' ';
}