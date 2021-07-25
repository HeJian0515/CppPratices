#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

struct A{
    virtual ~A(){}
};

struct B{
    virtual ~B(){}
};

struct C :public A, public B {
};


int main() {
    int n;
    cin >> n;
    vector<char> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (char c : v) cout << c;
}