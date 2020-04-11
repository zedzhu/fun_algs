/*
 *Given an unsorted array of N integers, write a function that returns Kth smallest number in the array, for zero-based K.
 *Example: Suppose that the following array with 5 numbers is given: 3, 1, 7, 5, 9. For K=3, the result is 7. This is because, when arry is sorted into 1, 3, 5, 7, 9, the element at zero-based position 3 is number 7.
 *Keywords: Kth smallest, array, median of medians, selection problem.
 *
 *http://www.sysexpand.com/?path=exercises/kth-smallest
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Source : https://leetcode.com/problems/kth-largest-element-in-an-array/
// Author : Hao Chen
// Date   : 2015-06-11

/********************************************************************************** 
 * 
 * Find the kth largest element in an unsorted array. 
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * 
 * For example,
 * Given [3,2,1,5,6,4] and k = 2, return 5.
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 * 
 * Credits:Special thanks to @mithmatt for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

class Solution {
public:
    //STL using qsort to solve this problem
    int findKthLargest_buildin(vector<int>& nums, int k) {
        int n=nums.size();
        std::nth_element(nums.begin(),nums.end()-k,nums.end());
        return nums[n-k];
    }
    
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

    //O(N * logK)
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k - 1) { 
                return nums[pos];
            }
            if (pos > k - 1) {
                right = pos - 1;
            } else {
                left = pos + 1;  
            }  
        }
    }

};

int findMedian(const vector<int>& vec){
    //Find median of a vector
    return vec[vec.size()/2];
}

int findMedianOfMedians(const vector<vector<int> >& values){
    vector<int> medians;

    for (int i = 0; i < values.size(); i++) {
        int m = findMedian(values[i]);
        medians.push_back(m);
    }

    return findMedian(medians);
}

void selectionByMedianOfMedians(const vector<int>& values, int k){
//    Divide the list into n/5 lists of 5 elements each
    vector<vector<int> > vec2D;

    int count = 0;
    while (count < values.size()) {
        int countRow = 0;
        vector<int> row;

        while ((countRow < 5) && (count < values.size())) {
            row.push_back(values[count]);
            count++;
            countRow++;
        }
        vec2D.push_back(row);
    }

    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++) {
            cout<<vec2D[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

//    Calculating a new pivot for making splits
    int m = findMedianOfMedians(vec2D);
    cout<<"Median of medians is : "<<m<<endl;

//    Partition the list into unique elements larger than 'm' (call this sublist L1) and
//    those smaller them 'm' (call this sublist L2)
    vector<int> L1, L2;

    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++) {
            if (vec2D[i][j] > m) {
                L1.push_back(vec2D[i][j]);
            }else if (vec2D[i][j] < m){
                L2.push_back(vec2D[i][j]);
            }
        }
    }

//    Checking the splits as per the new pivot 'm'
    cout<<endl<<"Printing L1 : "<<endl;
    for (int i = 0; i < L1.size(); i++) {
        cout<<L1[i]<<" ";
    }

    cout<<endl<<endl<<"Printing L2 : "<<endl;
    for (int i = 0; i < L2.size(); i++) {
        cout<<L2[i]<<" ";
    }

//    Recursive calls
    if ((k - 1) == L1.size()) {
        cout<<endl<<endl<<"Answer :"<<m;
    }else if (k <= L1.size()) {
        return selectionByMedianOfMedians(L1, k);
    }else if (k > (L1.size() + 1)){
        return selectionByMedianOfMedians(L2, k-((int)L1.size())-1);
    }
}

int main()
{
    int values[] = {2, 3, 5, 4, 1, 12, 11, 13, 16, 7, 8, 6, 10, 9, 17, 15, 19, 20, 18, 23, 21, 22, 25, 24, 14};

    vector<int> vec(values, values + 25);

    cout<<"The given array is : "<<endl;
    for (int i = 0; i < vec.size(); i++) {
        cout<<vec[i]<<" ";
    }

    selectionByMedianOfMedians(vec, 8);

    return 0;
}

