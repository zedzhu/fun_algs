#include <vector>

using namespace std;

/*
快速排序思路：
1. 选取第一个数为基准
2. 将比基准小的数交换到前面，比基准大的数交换到后面
3. 对左右区间重复第二步，直到各区间只有一个数
*/

//qsort partition
int partition(vector<int>& nums, int low, int high) {
    int first = low;
    int last = high;
    int pivot = nums[first];
    while (first < last) {
        while (first < last && nums[last] >= pivot) last--;
        if (first < last)
            nums[first++] = nums[last];
        
        while (first < last && nums[first] <= pivot) first++;
        if (first < last)
            nums[last--] = nums[first];
    }
    nums[first] = pivot;
    return first;
}

// 快速排序（递归）
void QuickSort(vector<int>& v, int low, int high) {
    if (low >= high)        // 结束标志
        return;
    int mid = partition(v, low, high); 
    // 前半递归
    QuickSort(v, low, mid - 1);
    // 后半递归
    QuickSort(v, mid + 1, high);
}

// ----------------------------------------------------

// 模板实现快速排序（递归）
template <typename T>
void quick_sort_recursive(T arr[], int start, int end) {
    if (start >= end)
        return;
    T mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        std::swap(arr[left], arr[right]);
    }
    if (arr[left] >= arr[end])
        std::swap(arr[left], arr[end]);
    else
        left++;
    quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}
template <typename T> //整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], int len) {
    quick_sort_recursive(arr, 0, len - 1);
}

// ----------------------------------------------------

// 模板实现快速排序（迭代）
struct Range {
    int start, end;
    Range(int s = 0, int e = 0) {
        start = s, end = e;
    }
};
template <typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
void quick_sort(T arr[], const int len) {
    if (len <= 0)
        return; // 避免len等於負值時宣告堆疊陣列當機
    // r[]模擬堆疊,p為數量,r[p++]為push,r[--p]為pop且取得元素
    Range r[len];
    int p = 0;
    r[p++] = Range(0, len - 1);
    while (p) {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        T mid = arr[range.end];
        int left = range.start, right = range.end - 1;
        while (left < right) {
            while (arr[left] < mid && left < right) left++;
            while (arr[right] >= mid && left < right) right--;
            std::swap(arr[left], arr[right]);
        }
        if (arr[left] >= arr[range.end])
            std::swap(arr[left], arr[range.end]);
        else
            left++;
        r[p++] = Range(range.start, left - 1);
        r[p++] = Range(left + 1, range.end);
    }
}