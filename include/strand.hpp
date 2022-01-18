//! 串问题===============================================================
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
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


//! 至少有K个重复字符的最长子串
namespace _395longestSubstring {
    int dfs(const string& s, int l, int r, int k) {
        vector<int> cnt(26);
        for (int i = l; i <= r; ++i) {
            ++cnt[s[i] - 'a'];
        }

        char split = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0 && cnt[i] < k) {
                split = i + 'a';
                break;
            }
        }

        if (split == 0) {
            return r - l + 1;
        }

        int i = l;
        int ret = 0;
        // 按split将字符切成多段
        while (i <= r) {
            // 找到第一个不为split的字符
            while (i <= r && s[i] == split) {
                ++i;
            }
            if (i > r) break;
            int start = i;
            // 找到下一次出现的split
            while (i <= r && s[i] != split) {
                ++i;
            }

            int len = dfs(s, start, i-1, k);
            ret = max(ret, len);
        }
        return ret;
    }

    int longestSubstring(string s, int k) {
        int n = s.size();
        return dfs(s, 0, n-1, k);
    }
//* 滑动窗口***************************************************************
namespace _1 {
    int longestSubstring(string s, int k) {
        int ret = 0;
        int n = s.size();
        for (int t = 0; t <= 26; ++t) {
            int l = 0, r = 0;
            vector<int> cnt(26, 0);
            int tot = 0; // 窗口内字符的种类
            int less = 0; // 窗口内的字符离满足要求的差距
            while (r < n) {
                cnt[s[r] - 'a']++;
                if (cnt[s[r] - 'a'] == 1) {
                    tot++;
                    less++;
                }

                // s[r]满足要求
                if (cnt[s[r] - 'a'] == k) {
                    less--;
                }

                // 窗口内字符种类大于t时
                while (tot > t) {
                    cnt[s[l] - 'a']--;
                    if (cnt[s[l] - 'a'] == k-1) {
                        less++;
                    }
                    if (cnt[s[l] - 'a'] == 0) {
                        tot--;
                        less--;
                    }
                    l++;
                }
                if (less == 0) {
                    ret = max(ret, r - l + 1);
                }
                ++r;
            }
        }

        return ret;
    }
}

//************************************************************
namespace _2 {
    int longestSubstring(string s, int k) {
        if (k <= 1) return s.size();
        if (s.empty() || s.size() < k) return 0;

        vector<int> cnt(26, 0);
        for (char c : s) ++cnt[c - 'a'];

        int i = 0;
        //[0, i)内字符个数都大于k
        while (i < s.size() && cnt[s[i] - 'a'] >= k) ++i;
        if (i == s.size()) return s.size();

        int l = longestSubstring(s.substr(0, i), k);

        //[i0, i1)内的字符个数小于k,不可能包含在结果中
        while (i < s.size() && cnt[s[i] - 'a'] < k) ++i;
        int r = longestSubstring(s.substr(i), k);

        return max(l, r);

    }
}
}

namespace _memcpy {
    //! 内存逐个拷贝
    void* my_memcpy_byte(void *dst, const void *src, int n) {
        if (dst == NULL || src == NULL || n <= 0) {
            return NULL;
        }

        char *pdst = (char*)dst;
        char *psrc = (char*)src;

        if (pdst > psrc && pdst < psrc+n) {
            pdst = pdst + n - 1;
            psrc = psrc + n - 1;
            while (n--) {
                *pdst-- = *psrc--;
            }
        } else {
            while(n--) {
                *pdst++ = *psrc++;
            }
        }

        return dst;
    }

    //! 字符串拷贝
    char* my_memcpy(char *dst, const char *src, int n) {
        assert(dst != NULL && src != NULL && n > 0);
        char *ret = dst;

        // 内存重叠,从高地址开始复制
        if (dst >= src && dst <= src+n-1) {
            dst = dst + n - 1;
            src = src + n - 1;
            while (n--) {
                *dst-- = *src--;
            }
        } else { // 正常情况，从低地址开始复制
            while (n--) {
                *dst++ = *src++;
            }
        }

        return ret;
    }

    int my_strcmp(const char* s1, const char* s2) {
        assert(s1 != NULL);
        assert(s2 != NULL);
        while (*s1 && *s2 && (*s1 == *s2)) {
            ++s1; ++s2;
        }
        return *s1 - *s2;
    }

    int my_strcmp_ms(const char *s1, const char *s2) {
        assert(s1 != NULL);
        assert(s2 != NULL);
        int ret = 0;
        while (!(ret = *(unsigned char *)s1 - *(unsigned char *)s2) && *s2) {
            ++s1;
            ++s2;
        }

        if (ret < 0) ret = -1;
        else if (ret > 0) ret = 1;
        return ret;
    }
    // 在s1中找s2
    const char* strStr(const char* haystack, const char *needle) {
        int n = strlen(haystack), m = strlen(needle);
        for (int i = 0; i + m <= n; ++i) {
            bool flag = true;
            for (int j = 0; j < m; ++j) {
                if (haystack[i+j] != needle[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return haystack + i;
        }
        return NULL;
    }

}