// Source : https://oj.leetcode.com/problems/maximum-subarray/
// Author : Hao Chen
// Date   : 2014-06-20

/********************************************************************************** 
* 
* Find the contiguous subarray within an array (containing at least one number) 
* which has the largest sum.
* 
* For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
* the contiguous subarray [4,−1,2,1] has the largest sum = 6.
* 
* More practice:
* 
* If you have figured out the O(n) solution, try coding another solution using 
* the divide and conquer approach, which is more subtle.
* 
*               
**********************************************************************************/

#include <algorithm>

class Solution {
public:
    int maxSubArray(int A[], int n) {
        int maxv = A[0];
        for (int i=0, benefited = 0; i != n; ++i)
        {
            benefited = std::max(A[i], benefited + A[i]);
            maxv = std::max(maxv, benefited);
        }
        return maxv;
    }

    int maxSubArray(const int A[],int n)
    {  
        int thisSum = 0, maxSum = A[0];
        for(int i=0;i<n;i++)
        {
            thisSum += A[i];
            if (thisSum > maxSum)  
                maxSum = thisSum;  
            if (thisSum<0) 
                thisSum=0;  
        }  
        return maxSum;  
    }

};
