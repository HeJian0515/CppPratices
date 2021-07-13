#include <algorithm>
#include <vector>
#include <unordered_map>
#include <list>
#include <memory>

using namespace std;

class LRUCache
{
private:
    unordered_map<int, list<pair<int, int>>::iterator> hash_;
    list<pair<int, int>> cache_;
    int size_;

public:
    LRUCache(int cap) : size_(cap) 
    {}

    int get(int key) {
        auto it = hash_.find(key);
        if (it == hash_.end()) {
            return -1;
        }
        cache_.splice(cache_.begin(), cache_, it->second); // 将找到的元素插到链表最前面
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = hash_.find(key);

        // 如果元素已经存在放到链表最前面
        if (it != hash_.end()) {
            it->second->second = value; // 更新value
            cache_.splice(cache_.begin(), cache_, it->second);
            return;
        }

        cache_.push_front(make_pair(key, value)); // 将新元素放到最前面
        hash_[key] = cache_.begin();
        if (cache_.size() > size_) {
            hash_.erase(cache_.back().first); // 删除map里的在链表最后的元素 ---即要通过链表在map找元素
            cache_.pop_back();
        }
    }
};

//! 字典树
namespace Trie
{
struct TrieNode
{
    using TrieNodePtr = unique_ptr<TrieNode>;
    int count; // 以该节点结尾的单词数量
    int prefix; // 该节点浅前缀数量
    vector<TrieNodePtr> nextNode;

    TrieNode():count(0), prefix(0), nextNode(vector<TrieNodePtr>(26))
    {
    }
};
using TrieNodePtr = TrieNode::TrieNodePtr;

void Insert(const TrieNodePtr& rootNode, const string& str)
{
    auto root = rootNode.get();
    if (root == nullptr || str.size() == 0) {
        return;
    }

    for (const char c : str) 
    {
        if (root->nextNode[c - 'a'] == nullptr) {
            root->nextNode[c - 'a'] = make_unique<TrieNode>();
        }
        root = root->nextNode[c - 'a'].get();
        root->prefix++;
    }

    root->count++; // 以该字符结尾的单词数量+1
}

int Search(const TrieNodePtr& rootNode, const string& str)
{
    auto root = rootNode.get();
    if (root == nullptr || str.size() == 0) {
        return -1;
    }

    for (const char c : str) {
        // 分支不存在
        if (root->nextNode[c - 'a'] == nullptr) {
            return -1;
        }
        // 存在继续往下遍历
        root = root->nextNode[c - 'a'].get();
    }

    // 如果 count == 0, 也说明该单词不存在
    if (root->count == 0) {
        return -1;
    }
    return root->count;
}

int SearchPrefix(const TrieNodePtr& rootNode, const string& str)
{
    auto root = rootNode.get();
    if (root == nullptr || str.size() == 0) {
        return -1;
    }

    for (const char c : str) {
        if (root->nextNode[c - 'a'] == nullptr) {
            return -1;
        }

        root = root->nextNode[c - 'a'].get();
    }
    return root->prefix;
}

}
