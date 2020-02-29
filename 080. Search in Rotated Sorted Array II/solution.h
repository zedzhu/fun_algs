
// Source : https://oj.leetcode.com/problems/search-in-rotated-sorted-array-ii/
// Author : Hao Chen
// Date   : 2014-06-29

/********************************************************************************** 
* 
* Follow up for "Search in Rotated Sorted Array":
* What if duplicates are allowed?
* 
* Would this affect the run-time complexity? How and why?
* 
* Write a function to determine if a given target is in the array.
*               
**********************************************************************************/

class Solution {
public:
    bool search(int A[], int n, int target) {
        if (n<0) return false;
        for (int l=0, r=n-1; l<=r; )
        {
            int m = (l+r) >> 1;
            if (target == A[m] || target == A[l] || target == A[r]) return true;
            else if ((A[l] < A[m] && target > A[l] && target < A[m]) || (A[l] > A[m] && target > A[l])) r = m-1;
            else if ((A[m] < A[r] && target > A[m] && target < A[r]) || (A[m] > A[r] && target < A[r])) l = m+1;
            else ++l, --r;
        }
        return false;
    }

    // Using the same idea "Search in Rotated Sorted Array"
    // but need be very careful about the following cases:
    //   [3,3,3,4,5,6,3,3] 
    //   [3,3,3,3,1,3]
    // After split, you don't know which part is rotated and which part is not.
    // So, you have to skip the ducplication
    //   [3,3,3,4,5,6,3,3] 
    //          ^       ^
    //   [3,3,3,3,1,3]
    //            ^ ^
    bool search2(int A[], int n, int key) {
        if (n<=0) return false;
        if (n==1) {
            return (A[0]==key) ? true : false;
        }
        int low=0, high=n-1;
        while (low<=high) {
            if (A[low] < A[high] && ( key < A[low] || key > A[high]) ) {
                 return false;
            }
            //if dupilicates, remove the duplication
            while (low < high && A[low]==A[high]) {
                low++;
            }
            //int mid = low + (high-low)/2;
            int mid = (low+high)>>1;
            if ( A[mid] == key || A[low] == key || A[high] == key) return true;
            //the target in non-rotated array
            if (A[low] < A[mid] && key >= A[low] && key< A[mid]){
                high = mid - 1;
                continue;
            }
            //the target in non-rotated array
            if (A[mid] < A[high] && key > A[mid] && key <= A[high] ){
                low = mid + 1;
                continue;
            }
            //the target in rotated array
            if (A[low] > A[mid] ){
                high = mid - 1;
                continue;
            }
            //the target in rotated array
            if (A[mid] > A[high] ){
                low = mid + 1;
                continue;
            }
            //reach here means nothing found. 因为允许重复，所以可能A[mid]==A[low] or A[mid]==A[high]
            low++;
        }
        return false;
    }

};
