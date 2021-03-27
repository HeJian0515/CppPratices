//! 串问题===============================================================
#include <string>
#include <vector>
#include <utility>
using namespace std;

namespace _5longestPalinddrome
{
// 中心拓展法
pair<int, int> expandAroundCenter(const string& s, int left, int right)
{
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    return {left + 1, right - 1};
}
string longestPalindrome(const string& s) 
{
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); ++i) {
        auto [left1, right1] = expandAroundCenter(s, i, i);
        auto [left2, right2] = expandAroundCenter(s, i, i+1);

        if (right1 - left1 > end - start) {
            start = left1;
            end = right1;
        }
        if (right2 - left2 > end - start) {
            start = left2;
            end = right2;
        }
    }
    return s.substr(start, end - start + 1);
}
//* manacher算法===================================
int expand(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left;
        ++right;
    }
    return (right-left-2) / 2;
}

string longestPalindrome_1(const string& s) {
    int start = 0, end = -1;
    string t;
    t.reserve(2*s.size() + 1);
    t.push_back('#');

    for (char c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('#');

    vector<int> arm_len(t.size());
    int right = -1, j = -1;
    for (int i= 0; i < t.size(); ++i) {
        int cur_arm_len;
        if (right >= i) {
            int i_sym = j * 2 -i;
            int min_arm_len = std::min(arm_len[i_sym], right - i);
            cur_arm_len = expand(t, i - min_arm_len, i + min_arm_len);
        } else {
            cur_arm_len = expand(t, i, i);
        }

        arm_len[i] = cur_arm_len;
        if (i+cur_arm_len > right) {
            j = i;
            right = i + cur_arm_len;
        }
        if (cur_arm_len*2+1 > end - start) {
            start = i- cur_arm_len;
            end = i + cur_arm_len;
        }
    }

    string ans;
    for (int i = start; i <= end; ++i) {
        if (t[i] != '#') {
            ans + t[i];
        }
    }
    return ans;
}

}