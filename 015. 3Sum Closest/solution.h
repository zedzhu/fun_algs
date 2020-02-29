#include <vector>
#include <algorithm>
using std::vector; 

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        std::sort(num.begin(), num.end());
        int min{INT_MAX}, sum{0}, tmpsum{0};
        for (auto it=num.cbegin(); it!=num.cend(); ++it)
            for (auto b = std::next(it), e = std::prev(num.cend()); b<e; tmpsum > target ? --e : ++b)
                if ((tmpsum = *it + *b + *e) == target) return target;
                else if (std::abs(tmpsum - target) < min) {sum = tmpsum; min = std::abs(tmpsum - target);}
        return sum;
    }

    int threeSumClosest2(vector<int> &num, int target) {
        std::sort(num.begin(), num.end());
        int min_distance = INT_MAX, closest_sum = 0;
        int n = num.size();
        for (int i = 0; i < n-2; i++) {
            //略过重复的数
            if (i > 0 && num[i-1] == num[i]) continue;
            int low = i + 1;
            int high = n - 1;
            while (low < high) {
                int tmpsum = num[i] + num[low] + num[high];
                if (tmpsum == target) return target;
                else {
                    if (std::abs(tmpsum - target) < min_distance) {
                        closest_sum = tmpsum;
                        min_distance = std::abs(tmpsum - target);
                    }
                    if (tmpsum < target) { //比target小，那就增强一点
                        //略过重复的数
                        while (low < n && num[low]==num[low+1]) low++;
                        low++;
                    } else if (tmpsum > target) { //比target大，那就减弱一点
                        //略过重复的数
                        while (high > 0 && num[high]==num[high-1]) high--;
                        high--;
                    }
                }
            }
        }

        return closest_sum;
    }
};
