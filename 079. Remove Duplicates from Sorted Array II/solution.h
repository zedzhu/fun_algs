// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
// Author : Hao Chen
// Date   : 2014-06-29

/********************************************************************************** 
* 
* Follow up for "Remove Duplicates":
* What if duplicates are allowed at most twice?
* 
* For example,
* Given sorted array A = [1,1,1,2,2,3],
* 
* Your function should return length = 5, and A is now [1,1,2,2,3].
* 
*               
**********************************************************************************/

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n<3) return n;
        int size{1};
        for (int i=2; i<n; ++i)
            if (A[i] != A[size] || A[i] != A[size-1])
                A[++size] = A[i];
        return ++size;
    }

    int removeDuplicates2(int A[], int n) {
        if (n<=2) return n;
        int pos=0;
        int cnt=1;
        for (int i=1; i<n; i++){
            if (A[i] == A[pos]){
                cnt++;
                if (cnt==2){
                    A[++pos] = A[i];
                }
            }else{
                cnt=1;
                A[++pos] = A[i];
            }
        } 
        return pos+1;
    }
};
