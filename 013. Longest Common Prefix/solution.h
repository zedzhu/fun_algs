#include <string> 
#include <vector>
using std::string; using std::vector;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty()) return "";
        for (size_t i=0; i<strs.front().size(); ++i) {
            for (const auto &str : strs)
                if (i == str.size() || str.at(i) != strs.front().at(i))
                    return strs.front().substr(0, i); 
        }
        //到此说明第一个字符串跟其它所有字符串都前缀匹配
        return strs.front();
    }
};
