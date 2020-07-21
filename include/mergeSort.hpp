#include <vector>
using namespace std;

void merge(vector<int>& input, int lo, int mid, int hi, vector<int>& temp) {
    int i = lo;       // 第一段序列下标
    int j = mid;  //第二段序列的下标
    int k = 0;        // 临时存放合并序列的下标

    // 扫描第一段和第二段序列，直到有一个扫描结束
    while (i < mid && j < hi) {
        // 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
        if (input[i] <= input[j])
            temp[k++] = input[i++];
        else
            temp[k++] = input[j++];
    }

    // 若第一段序列还没扫描完，将其全部复制到合并序列中
    while (i < mid) {
        temp[k++] = input[i++];
    }
    // 若第二段段序列还没扫描完，将其全部复制到合并序列中
    while (j < hi) {
        temp[k++] = input[j++];
    }

    k = 0;
    // 将合并序列复制到原始序列中
    while (lo < hi) {
        input[lo++] = temp[k++];
    }
}

void mergeSort(vector<int>& input, int lo, int hi, vector<int>& temp) {
    if (hi - lo < 2) return;
    int mid = (lo + hi) / 2;
    mergeSort(input, lo, mid, temp);
    mergeSort(input, mid, hi, temp);
    merge(input, lo, mid, hi, temp);
}

void mergeSort(vector<int>& input) {
    vector<int> temp(input.size());
    mergeSort(input, 0, input.size(), temp);
}