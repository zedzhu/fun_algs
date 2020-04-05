#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <climits>

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

/*
 * https://www.cnblogs.com/bestdavid/p/dpleastcoin.html
 * 有面值为1元、3元和5元的硬币若干枚，如何用最少的硬币凑够11元？
 * 贪心算法不是对所有问题都能得到整体最优解，必须满足条件：后一个的权值（这里就是纸币面值）是前一个的2倍或以上才可以使用，
 * 比如，1，7，9，10，这里10不到9的两倍，贪心法凑18元就不错了。
 * 我怎么觉得这个条件也不成立，比如：1,5,11，满足2倍以上关系但凑15元就不行。
 * 但是这个1、3、5我觉得可以用贪心法，不然反例？
 * d(i)=j来表示凑够i元最少需要j个硬币,
 * d(i) = min{ d(i - Vj) + 1} ,i >= Vj。
 * 比如：
 * d(0) = 0
 * d(1) = min{d(0)+1} = 1
 * d(2) = min{d(2-1)+1} = 2
 * d(3) = min{d(3-1)+1,d(3-3)+1} = min{2,1} = 1
 * d(4) = min{d(4-1)+1,d(4-3)+1} = min{2,2} = 2
 * d(5) = min{d(5-1)+1,d(5-3)+1,d(5-5)+1} = min{3,3,1} = 1
 */
//coins按面值从小到大排序
int dpLeastCoins(const vector<int>& coins, int target) {
    //初始化动态规划数组，初始值设置为最大
    vector<int> d(target+1, 0);
    //用于检测零钱是否存在解（如果不含有1元的硬币）
    vector<int> c(target+1, 0);
    for (int i = 1; i <= target; i++) {
        int min = i; //最多用i个1元硬币，但是如果没有1元硬币呢？这就是c的作用。
        for (int j = 0; j < coins.size(); j++) {
            //目标金额i比当前硬币面额还小，则说明后面的硬币都不能满足要求了，提前退出循环。
            if (i < coins[j]) break;
            if (d[i-coins[j]] + 1 < min &&
                //以下判断检测上一个是否有效，无效则跳过。如果含有一元硬币，这个判断就不需要。
                (i == coins[j] || c[i - coins[j]] != 0)) {
                min = d[i-coins[j]] + 1;
                c[i] = coins[j];
            }
        }
        d[i] = min; 
    }
    //下面是找到具体用了哪些面值的硬币
    int money = target;
    if (c[money] != 0) {
        while (money) {
            //cout << c[money] << ",";
            money -= c[money];
        }
    }

    if (c[target] > 0) //有解
        return d[target];
    else  //无解
        return -1; 
}

//coins按面值从小到大排序，有问题的贪心法，只对对于特殊的硬币面值组合可以。
int greedyLeastCoins(const vector<int>& coins, int target) {
    int ret = 0;
    int left = target;
    for (size_t i = coins.size()-1; i >= 0; i--) {
        int k = target/coins[i];
        ret += k;
        //用了k枚coins[i]之后更新余额
        target -= k * coins[i];
    }

    return ret;
} 
