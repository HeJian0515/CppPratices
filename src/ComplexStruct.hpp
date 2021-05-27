#include <algorithm>
#include <vector>
#include <unordered_map>
#include <list>
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

};
