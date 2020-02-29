
// Source : https://oj.leetcode.com/problems/remove-element/
// Author : Hao Chen
// Date   : 2014-06-19

/********************************************************************************** 
* 
* Given an array and a value, remove all instances of that value in place and return the new length.
* 
* The order of elements can be changed. It doesn't matter what you leave beyond the new length.
* 
*               
**********************************************************************************/

#include <algorithm>

class Solution {
public:
    int removeElement(int A[], int n, int elem)
    {
        for (int i = 0; i < n;)
        {
            if (A[i] == elem) std::swap(A[i], A[--n]);
            else ++i;
        }
        return n;
    }
};
