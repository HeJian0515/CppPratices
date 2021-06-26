#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;




vector<int> pancakeSort(vector<int>& arr)
{
    vector<int> ans;
    int n = arr.size();

    vector<int> indies(n); // 记录arr中元素的位置
    for (int i = 0; i < n; ++i) indies[i] = i+1;

    // 根据arr中元素从大到小排序， 最大的元素位置排在最前面， 次大的元素位置排在第二位...
    sort(indies.begin(), indies.end(), [&arr](const int i, const int j){
        return arr[i-1] > arr[j-1];
    });

    for (int i : indies) {  // 每次都找到还没排序好的最大元素
        for (int f : ans) { // 前面的操作(翻转)可能让这次最大元素的位置发生了改变
            if (i <= f) {
                i = f+1-i;
            }
        }
        ans.push_back(i); // 表示把最大元素放到最前面
        ans.push_back(n--);// 将最大元素放到最后面
    }
    return ans;
}


int main() {
    
    vector<int> v{3, 2, 4, 1};
    auto ans = pancakeSort(v);

    for (int a : v) {
        cout << a << " ";
    }
    cout << endl;

    for (int i : ans) cout << i << " ";
}