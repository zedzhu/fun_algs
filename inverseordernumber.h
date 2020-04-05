#include <vector>

using namespace std;

/*
 * 逆序数：在一个排列中，如果一对数的前后位置与大小顺序相反，即前面的数大于后面的数，那么它们就称为一个逆序。
 * 一个排列中逆序的总数就称为这个排列的逆序数。
 * 利用归并排序的思想来求解。 
 * 归并排序的主要思想是将整个序列分成两部分，分别递归将这两部分排好序之后，再和并为一个有序的序列.
 * 在合并的过程中是将两个相邻并且有序的序列合并成一个有序序列，如以下两个有序序列
 * Seq1：3  4  5
 * Seq2：2  6  8  9
 * 合并成一个有序序:
 * Seq：2  3  4  5  6  8  9
 * 对于序列seq1中的某个数a[i],序列seq2中的某个数a[j]，如果a[i]<a[j],没有逆序数，如果a[i]>a[j]，
 * 那么逆序数为seq1中a[i]后边元素的个数(包括a[i])，即len1-i+1,
 * 这样累加每次递归过程的逆序数，在完成整个递归过程之后，最后的累加和就是逆序的总数。
 * 时间复杂度O(nlogn)
 */

void merge(vector<int>& arr, vector<int>& tmp, int start, int mid, int end, int& count) {
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    int k = start;
    while (start1 <= end1 && start2 <= end2) {
        if (arr[start1] <= arr[start2])
            tmp[k++] = arr[start1++];
        else {
            tmp[k++] = arr[start2++];
            //arr从start1到mid(含)之间的数全都与arr[start2]构成逆序
            count += mid - start1 + 1;
        }
    }
    while (start1 <= end1)
        tmp[k++] = arr[start1++];
    while (start2 <= end2)
        tmp[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = tmp[k];    
}

void merge_sort_recursive(vector<int>& arr, vector<int>& tmp, 
    int start, int end, int& count) {
    if (start >= end)
        return;
    int mid = (start+end) >> 1;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, tmp, start1, end1, count);
    merge_sort_recursive(arr, tmp, start2, end2, count);
    merge(arr, tmp, start, mid, end, count);
}

int getInverseOrderNumber(vector<int>& arr) {
    vector<int> tmp(arr.size());
    int count;
    merge_sort_recursive(arr, tmp, 0, arr.size() - 1, count);
    return count;
}