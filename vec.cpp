#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

//子数组最大乘积：求出n个元素数组中最大的n-1个数的乘积
double maxSubArrayProduct(const vector<double>& vec) {
    size_t n = vec.size();
    if (n == 0) return 0;
    if (n == 1) return vec[0];
    //f[i]表示前i个数的乘积，即f[i]=f[i-1]*vec[i-1]，并令边界f[0]=1.0
    vector<double> f(n+1, 1.0);
    for (size_t i = 1; i <= n; i++) {
        f[i] = f[i-1] * vec[i-1];
    }
    //b[i]表后n-i个数的乘积，即b[i]=b[i+1]*vec[i]，并令b[n]=1.0
    vector<double> b(n+1, 1.0);
    for (size_t i = n-1; i>=0; i--) {
        b[i] = b[i+1] * vec[i];
    }

    //p[i]表示出去i以外的n-1个数的乘积，由上面可知：p[i]=f[i]*b[i+1]，除去i的前面的数的乘积是f[i]，后面的数的乘积是b[i+1]
    vector<double> p(n, 0);
    /*
    p[0] = f[0] * b[1]; //因为f[0]=1.0
    p[1] = f[1] * b[2];
    p[2] = f[2] * b[3];
    p[n-1] = f[n-1] * b[n]; //因为b[n]=1.0
    */
    for (size_t i = 0; i < n; i++) {
        p[i] = f[i] * b[i+1];
    }
    vector<double>::iterator it = std::max_element(p.begin(), p.end());
    return *it;
}

//子数组最大乘积：求出n个元素数组中最大的n-1个数的乘积
double maxSubArrayProduct2(const vector<double>& vec) {
    int zeroNum = 0; //0的个数
    int negNum = 0;  //负数的个数
    int posNum = 0;  //正数的个数
    for (size_t i = 0; i < vec.size(); i++) {
        const double& d = vec[i];
        if (d == 0) {
            zeroNum++;
        } else if (d < 0) {
            negNum++;
        } else {
            posNum++;
        }
    }

    if (zeroNum >= 2) {
        //含两个以上0
        return 0;
    } else if (zeroNum == 1) {
        //含1个0
        if (negNum & 1) { //奇数个负数
            return 0; //因为奇数个负数，除了0之外的N-1个数乘积必然为负，所以还不如0大。 
        } else {
            //除0之外的其它N-1个数乘积必然为正，返回这个正数积。
        }
    } else {
        //不含0
        if (negNum & 1) { //奇数个负数
            //去掉一个负数后，其余N-1个数必然为正，所以去掉绝对值最小的负数，返回其余数之积；
        } else { //偶数个负数
            //此时N个数相乘为正，因此要去掉值最小的正数，返回剩余N-1个数之积即可。
        }
    }
}

/********************************************************************************** 
* Find Minimum in Rotated Sorted Array:
* Suppose a sorted array is rotated at some pivot unknown to you beforehand.
* (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
* Find the minimum element.
* You may assume no duplicate exists in the array.
**********************************************************************************/
int findMinOfRotateArray(const vector<int>& vec) {
    int low = 0, high = vec.size() - 1;
    //大于1的意思就是low与high之间有3个及以上的元素才进入循环
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        if (vec[low] <= vec[mid] && vec[mid] <= vec[high])
            return vec[low];
        if (vec[low] > vec[mid])
            high = mid;
        else if (vec[mid] > vec[high])
            low = mid;
    }
    if (high == low) 
        return vec[low];
    else 
        return std::min(vec[low], vec[high]);
}

/*
 * Follow up for "Find Minimum in Rotated Sorted Array":
 * What if duplicates are allowed?
 * Need be very careful for the following cases:
 *    [3, 3, 3, 3, 3]
 *    [3, 3, 3, 1, 3]
 */
int findMin(const vector<int> &num) {
    int low=0, high=num.size()-1;
    while (high - low > 1) {
        //skip the same element, this would cause the O(n) run-time complexity. 
        while (high - low > 1 && num[low] == num[high])
            low++;
        //binary search
        int mid = (high+low)>>1;
        //If the array is not rotated then return num[low]
        //Notes: checking the equal situation
        if (num[low] <= num[mid] && num[mid] <= num[high])
            return num[low];
        //move the high pointer to the middle, if sub-array from low to mid is rotated.
        if (num[low] > num [mid])
            high = mid;
        // move the low pointer to the middle, if sub-array from mid to high is rotated.
        else if (num[mid] > num[high])
            low = mid;
    }
    // checking the edge case 
    if (high == low) 
        return num[low];
    else
        return num[low] < num[high] ? num[low] : num[high];
}

/*
 * https://www.ibm.com/developerworks/community/blogs/jfp/entry/Fast_Computation_of_AUC_ROC_score?lang=en
 * AUC-ROC = | {(i,j), i in pos, j in neg, p(i) > p(j)} | / (| pos | x | neg |)
 */
double fastAUC(const vector<int>& labels, const vector<float>& predicts) {
    //按predicts从小到大排序
    double auc = 0.0;
    int nfalse = 0;
    for (size_t i = 0; i < predicts.size(); i++) {
        if (labels[i] == 0) {
            nfalse++;
        } else {
            auc += nfalse;
        }
    }

    auc /= nfalse * (predicts.size() - nfalse);
    return auc;
}
