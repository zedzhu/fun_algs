
// Source : https://oj.leetcode.com/problems/4sum/
// Author : Hao Chen
// Date   : 2014-07-03

/********************************************************************************** 
* 
* Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? 
* Find all unique quadruplets in the array which gives the sum of target.
* 
* Note:
* 
* Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
* The solution set must not contain duplicate quadruplets.
* 
*     For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
* 
*     A solution set is:
*     (-1,  0, 0, 1)
*     (-2, -1, 1, 2)
*     (-2,  0, 0, 2)
* 
*               
**********************************************************************************/

#include <vector>
using std::vector;
#include <algorithm>
#include <unordered_map>
#include <set>

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        if (num.size() < 4) return vector<vector<int>>{};
        std::set<vector<int>> ret;
        std::sort(num.begin(), num.end());
        std::unordered_map<int, vector<std::pair<int, int>>> cache;
        
        for (size_t i=0; i<num.size(); ++i)
            for (size_t j=i+1; j<num.size(); ++j)
                cache[num[i]+num[j]].emplace_back(i, j);
        
        for (const auto &rp : cache) {
            auto found = cache.find(target - rp.first);
            if (found != cache.end())
                for (const auto &low : rp.second)
                    for (const auto &high : found->second)
                        if (low.second < high.first) ret.insert(vector<int>{num[low.first], num[low.second], num[high.first], num[high.second]});
        }
        
        return vector<vector<int>>(ret.cbegin(), ret.cend());
    }

    /*
    * 1) Sort the array,
    * 2) traverse the array, and solve the problem by using "3Sum" soultion.
    */
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector< vector<int> > result;
        if (num.size()<4) return result;
        sort( num.begin(), num.end() );
        
        for(int i=0; i<num.size()-3; i++) {
            //skip the duplication
            if (i>0 && num[i-1]==num[i]) continue;
            //把target-num[i]作为新target，num[i+1:n]作为新数组
            vector<int> n(num.begin()+i+1, num.end());
            vector<vector<int> > ret = threeSum(n, target-num[i]);
            //将结果集里每个结果增加num[i]，构成4元组答案
            for(int j=0; j<ret.size(); j++){
                ret[j].insert(ret[j].begin(), num[i]);
                result.push_back(ret[j]);
            }
        }

        return result; 
    }

    vector<vector<int> > threeSum(vector<int> num, int target) {
        vector< vector<int> > result;
        //sort the array (if the qrray is sorted already, it won't waste any time)
        sort(num.begin(), num.end());
        int n = num.size();
        for (int i=0; i<n-2; i++) {
            //skip the duplication
            if (i>0 && num[i-1]==num[i]) continue;
            int a = num[i];
            int low = i+1;
            int high = n-1;
            while ( low < high ) {
                int b = num[low];
                int c = num[high];
                int tmpsum = a + b + c;
                if (tmpsum == target) {
                    //got one soultion
                    result.push_back({a, b, c});
                    // Continue search for all triplet combinations summing to zero.
                    //skip the duplication
                    while(low<n && num[low]==num[low+1]) low++;
                    while(high>0 && num[high]==num[high-1]) high--;
                    low++;
                    high--;
                } else if (tmpsum < target) { //比target小就增强一点
                    //skip the duplication
                    while(low<n && num[low]==num[low+1]) low++;
                    low++;
                } else { //比target大就减弱一点
                    //skip the duplication
                    while(high>0 && num[high]==num[high-1]) high--;
                    high--;
                }
            }
        }
        return result;
    }

};