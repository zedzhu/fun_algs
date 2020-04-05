class Solution {
public:
    int search(int A[], int n, int target) {
        for (int i = 0, j = n-1; i <= j; )
        {
            int m = (i + j) >> 1;
            if (target == A[m]) return m;
            else if ((A[i] <= target && target < A[m]) || (A[m] < A[i] && (target < A[m] || A[i] <= target))) j = m - 1;
            else if ((A[m] < target && target <= A[j]) || (A[j] < A[m] && (target <= A[j] || A[m] < target))) i = m + 1;
            else break;
        }
        return -1;
    }

    /*
    *    Using binary search idea, 
    *    1) Spliting the array to two part, one part should be non-rotated, another one is rotated.
    *    2) Checking the "key" whether is possible in non-rotated sorted part.
    *        2.1) if it is, then go to the classcial binary searh.
    *        2.2) if it not, then keep spliting the rorated part.
    *
    */
    int search2(int A[], int n, int key) {
        if (n<=0) return -1;
        if (n==1) {
            return (A[0]==key) ? 0 : -1;
        }
        int low=0, high=n-1;
        while (low<=high){
            //有序同时key比最小的小，或者比最大的大，表明不存在了。
            if (A[low] <= A[high] && ( key < A[low] || key > A[high]) ) {
                return -1;
            }
            //int mid = low + (high-low)/2;
            int mid = (low+high)>>1;
            if ( A[mid] == key ) return mid;
            //the target in non-rotated array
            if (A[low] < A[mid] && key >= A[low] && key< A[mid]) {
                high = mid - 1;
                continue;
            }
            //the target in non-rotated array
            if (A[mid] < A[high] && key > A[mid] && key <= A[high] ){
                low = mid + 1;
                continue;
            }
            //the target in left rotated array
            if (A[low] > A[mid] ){
                high = mid - 1;
                continue;
            }
            //the target in right rotated array
            if (A[mid] > A[high] ){
                low = mid + 1;
                continue;
            }
        }
        return -1;
    }

    int search1 (int A[], int n, int target) {
        if (n<=0) return -1;
        if (n==1) {
            return (A[0]==key) ? 0 : -1;
        }
        for (int low = 0, high = n-1; low <= high; )
        {
            int mid = (low + high) >> 1;
            if (target == A[mid]) return m;
            else if (
                (A[low] <= target && target < A[mid]) || //target在左边部分，且左边部分是非rotate的
                //左边部分是rotate的，且：target比mid还小，或者target比low还大
                (A[low] > A[mid] && (target < A[mid] || A[low] <= target))) {
                high = mid - 1;
            }
            else if (
                (A[mid] < target && target <= A[high]) || //target在右边部分，且右边部分是非rotate的
                //右边部分是rotate的，且：target比mid还大，或者target比high还小
                (A[high] < A[mid] && ( A[mid] < target || target <= A[high]))) {
                low = mid + 1;
            }
            else break;
        }
        return -1;
    }


};
