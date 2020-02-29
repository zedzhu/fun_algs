#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::max;


// Source : https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
// Author : Hao Chen
// Date   : 2014-07-19

/********************************************************************************** 
* 
* Given a string, find the length of the longest substring without repeating characters. 
* For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
* which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*               
**********************************************************************************/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t ret = 0, start = 0;
        unordered_map<char, size_t> trace;
        for (size_t i = 0; i < s.size(); ++i) {
            auto found = trace.find(s[i]);
            if (found != trace.end() && found->second >= start) {
                ret = max(ret, i - start);
                start = found->second + 1;
            }
            trace[s[i]] = i;
        }
        return max(ret, s.size() - start);
    }
};
