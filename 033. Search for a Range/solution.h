
// Source : https://oj.leetcode.com/problems/search-for-a-range/
// Author : Hao Chen
// Date   : 2014-06-26

/********************************************************************************** 
* 
* Given a sorted array of integers, find the starting and ending position of a given target value.
* 
* Your algorithm's runtime complexity must be in the order of O(log n).
* 
* If the target is not found in the array, return [-1, -1].
* 
* For example,
* Given [5, 7, 7, 8, 8, 10] and target value 8,
* return [3, 4].
* 
*               
**********************************************************************************/

#include <vector>

using std::vector;

class Solution {
    int binarySearch(int A[], int l, int r, int target) {
        for (int mid; l <= r; ) {
            mid = ( l + r ) >> 1;
            if      ( A[mid] < target ) l = mid + 1;
            else if ( A[mid] > target ) r = mid - 1;
            else return mid;
        }
        return -1;
    }

    int binary_search(int A[], int low, int high, int key){
        while (low<=high) {
            //int mid = low + (high-low)/2;
            int mid = (low + high) >> 1;
            if (A[mid] == key) {
                return mid;
            }
            else if (key > A[mid]) {
                low = mid + 1;
            }
            else if (key < A[mid]) {
                high = mid - 1;
            }
        }
        return -1;
    }

public:
    vector<int> searchRange(int A[], int n, int target) {
        int iPos = binarySearch( A, 0, n-1, target ), l = -1, r = -1;
        if ( iPos != -1 ) {
            l = r = iPos;
            for (int lo = l; (lo = binarySearch(A, 0,   lo-1, target)) != -1; l = lo ) ;
            for (int hi = r; (hi = binarySearch(A, hi+1, n-1, target)) != -1; r = hi ) ;
        }
        return {l ,r};
    }

    /*
    *   O(log n) solution must be something like binary search.
    *   So, we can use the binary search to find the one postion - `pos`
    *   then, we can keep using the binary search find the target in A[0..pos-1] and A[pos+1..n]
    *   The code below is self-explaination
    */
    vector<int> searchRange(int A[], int n, int target) {
        int pos = binary_search(A, 0, n-1, target);

        int low = -1, high = -1;
        if (pos >=0) {
            low = high = pos;
            for (int l = low; l >= 0; ) {
                l = binary_search(A, 0, l-1, target);
                if (l >= 0) {
                    low = l;
                }
            }
            for (int h = high; h >= 0; ) {
                h = binary_search(A, h+1, n-1, target);
                if (h >= 0) {
                    high = h;
                }
            }
        }

        return {low, high}
    }

};
