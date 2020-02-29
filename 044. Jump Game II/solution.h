// Source : https://oj.leetcode.com/problems/jump-game-ii/
// Author : Hao Chen
// Date   : 2014-07-18

/********************************************************************************** 
* 
* Given an array of non-negative integers, you are initially positioned at the first index of the array.
* 
* Each element in the array represents your maximum jump length at that position. 
* 
* Your goal is to reach the last index in the minimum number of jumps.
* 
* For example:
* Given array A = [2,3,1,1,4]
* 
* The minimum number of jumps to reach the last index is 2. 
* (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
* 
*               
**********************************************************************************/

#include <algorithm>

class Solution {
public:
    int jump(int A[], int n) {
        int step = 0, max = 0, tmpMax = 0;
        //注意这里i<n-1，主要考虑这种边界[0]，step=0，即移动0步（不需要移动）就已到达最后。
        for (int i=0; i<=max && i<n-1; ++i) {
            tmpMax = std::max(tmpMax, A[i]+i);
            if (i == max) { //当 i 到达上次记录的最远位置
                max = tmpMax; //更新 max 记录 
                ++step; // 这算一步
            }
            if (max >= n-1) {
                break;
            }
        }
        return max >= (n-1) ? step : -1;
    }

    //统一边界到n
    int jump2(int A[], int n) {
        //加上这个判断就可以后面循环统一边界，不用考虑[0]、[1]等这样0步就可以到达末尾的情况了
        if (n <=1) return 0;
        int step = 0, max = 0, tmpMax = 0;
        for (int i=0; i<=max && i<n; ++i) {
            tmpMax = std::max(tmpMax, A[i]+i);
            //用tmpMax>0限定一下[0]这种独立情况
            if (i == max) { //当 i 到达上次记录的最远位置
                max = tmpMax; //更新 max 记录 
                ++step; // 这算一步
            }
            if (max >= n-1) break;
        }
        return max >= (n-1) ? step : -1;
    }

};

