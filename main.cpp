#include <numeric>
#include <algorithm>

#include <iostream>
#include <vector>

using namespace std;

vector<int> findErrorNums(vector<int>& nums)
{
    vector<int> ans; ans.reserve(2);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        // 如果i+1位置 不等于nums[i]
        while (i+1 != nums[i]) { 
            // 如果nums[i]-1位置的元素等于nums[i] 则nums[i]重复
            if (ans.empty() && nums[i] == nums[nums[i] - 1]) {
                ans.push_back(nums[i]); 
                break;
            }

            // 如果又访问到重复的元素
            if (!ans.empty() && nums[i]==ans[0]) break;
            swap(nums[i], nums[nums[i]-1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != i+1) {
            ans.push_back(i+1);
            break;
        }
    }
    return ans;
}


int main(void)
{   

}