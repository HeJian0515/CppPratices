#include <vector>
#include <algorithm>
using namespace std;

class UnionFind
{
private:
    int count_;
    vector<int> parent_; // parent_[i] 表示 i的父节点是parent_[i]
    vector<int> size_; // i 作为父节点的集合个数

public:
    explicit UnionFind(int n) :count_(n), parent_(n), size_(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
        } 
    }

public:
    int FindRoot(int x) 
    {
        while (parent_[x] != x) {
            parent_[x] = parent_[parent_[x]]; //! 将路径压缩
            x = parent_[x];
        }
        return x;
    }

    void Union(int p, int q)
    {
        int rootP = FindRoot(p);
        int rootQ = FindRoot(q);
        if (rootP == rootQ) return;

        if (size_[rootP] < size_[rootQ]) {
            swap(rootP, rootQ);
        }
        parent_[rootQ] = rootP;
        size_[rootP] += size_[rootQ];

        --count_;
    }

    int Count() const { return count_; }

    bool Connectd(int p, int q) {
        return FindRoot(p) == FindRoot(q);
    }

    int MaxUnion() const {
        auto beignIt = size_.cbegin();
        auto indexIt = max_element(size_.cbegin(), size_.cend());
        return distance(beignIt, indexIt);
    }
};