/********************************************************************************** 
* 
* Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
* 
* For example,
* Given [100, 4, 200, 1, 3, 2],
* The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
* 
* Your algorithm should run in O(n) complexity.
* 
*               
**********************************************************************************/

//
//  Obviously, the easist way is sort the array, however the run-time complexity is O(nlogn)
//  
//  If we cannot use the sort algorithm, then it seems we have to use O(n^2) solution.
//
//  That's fine, let's take a look the O(n^2) soultion
//
//      1) for each item num[i] in the array
//      2) for loop to seach ...... num[i-2], num[i-1],  num[i]+1, num[i]+2 ......
//  
//  We can see, the search is really heavy, and the best data structure for seaching is HashMap.
//  hash map is O(1) run-time complexity for seaching.
//
//  So, we can have the following solution by using Hash Map.
//  
#include <vector>
#include <unordered_map>
using std::vector; using std::unordered_map;

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        unordered_map<int, int> map;
        int max{0};
        for (auto i : num)
            if (!map[i]) {
                map[i] = map[i+1] + map[i-1] + 1;
                map[i-map[i-1]] = map[i+map[i+1]] = map[i];
                max = std::max(max, map[i]);
            }
        return max;
    }

    //Better
    int longestConsecutive2(vector<int> &nums) {
        unordered_map<int, int> m;
        for (int i=0; i<nums.size(); i++){
            m[nums[i]] = i;
        }
        int max_seq=0;
        for (int i=0; i<nums.size(); i++){
            int cnt=1;
            //为什么不能这么写？
            /**
             * for (int n = nums[i]+1, auto found = m.find(n); found!=m.end() ; n++) {
                    m.erase(found);
                    cnt++;
             * }
             */
            for (int n = nums[i]+1; ; n++) {
                auto found = m.find(n)
                if (found != m.end())
                    m.erase(found);
                else
                    break;
                cnt++;
            }
            for (int n = nums[i]-1; ; n--) {
                auto found = m.find(n)
                if (found != m.end())
                    m.erase(found);
                else
                    break;
                cnt++;
            }
            if (max_seq < cnt){
                max_seq = cnt;
            }
            if (m.empty()) {
                break;
            }
        }
        return max_seq;
    }

};