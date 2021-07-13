//! 串问题===============================================================
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
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
    t.reserve(2*s.size() + 2);
    // t.push_back('$');
    t.push_back('#');

    for (char c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    t.push_back('!');

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

        // 让right走的尽可能远
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
            ans += t[i];
        }
    }
    return ans;
}

}

//! 字符串乘法=============================================================
namespace _43multiply {
//****************************** 字符串加法********************************
string addString(const string& num1, const string& num2) {
    int i = num1.size()-1, j = num2.size()-1, add = 0;
    string ans;
    while (i >= 0 || j >= 0 || add != 0) {
        int x = i >= 0 ? num1[i]-'0' : 0;
        int y = j >= 0 ? num2[j]-'0' : 0;
        int result = x + y + add;
        ans.push_back(result % 10 + '0');
        add = result / 10;
        --i;
        --j;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    string ans = "0";
    int m = num1.size(), n = num2.size();
    for (int i = n-1; i >= 0; --i) {
        string curr;
        int add = 0;
        for (int j = n-1; j > i; --j) {
            curr.push_back(0);
        }
        int y = num2[i] - '0';

        for (int j = m-1; j >= 0; --j) {
            int x = num1[j] - '0';
            int product = x * y + add;
            curr.push_back(product % 10);
            add = product / 10;
        }
        while (add != 0) {
            curr.push_back(add % 10);
            add /= 10;
        }

        reverse(curr.begin(), curr.end());
        for(auto& c : curr) c += '0';
        ans = addString(ans, curr);
    }
    return ans;
}
//*********************************************************************
namespace _1 {
string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
        return "0"s;
    }
    int m = num1.size(), n = num2.size();
    vector<int> ansArr(m+n);

    for (int i = m-1; i >= 0; --i) {
        int x = num1[i] - '0';
        for (int j = n-1; j >= 0; --j) {
            int y = num2[j] - '0';
            ansArr[i+j+1] += x * y;
        }
    }

    for (int i = m+n-1; i > 0; --i) {
        ansArr[i-1] += ansArr[i] / 10;
        ansArr[i] %= 10;
    }

    int index = ansArr[0] == 0 ? 1 : 0;
    string ans;
    while (index < m+n) {
        ans.push_back(ansArr[index] + '0');
        ++index;
    }
    return ans;
}
}
}

