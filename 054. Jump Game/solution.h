#include <algorithm>

class Solution {
public:
    bool canJump(int A[], int n) {
    for (int i=0,max=0; i<=max; ++i)
        if((max = std::max(max, i+A[i])) >= n-1) return true;
    return false;
    }

    /********************************************************************************** 
    * Given an array of non-negative integers, you are initially positioned at the first index of the array.
    * Each element in the array represents your maximum jump length at that position. 
    * Determine if you are able to reach the last index.
    * 
    * For example:
    * A = [2,3,1,1,4], return true.
    * A = [3,2,1,0,4], return false.
    **********************************************************************************/
    bool canJump(int A[], int n) {
        if (n<=0) return false;
        // the basic idea is traverse array, maintain the most far can go
        int max = 0;
        // the condition i<=max means traverse all of covered position 
        //注意这里必须是i<n，和上面不同，主要考虑这种边界[0]，也要能返回true
        for (int i=0; i<=max && i<n; i++){
            max = std::max(max, A[i]+i);
            if (max>=n-1) {
                return true;
            }
        }
        return false;
    }


};
