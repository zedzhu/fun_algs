class Solution {
public:
    int sqrt(int x) {
        int l = 1, r = x, ret = 0;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (m * m <= x) {
                l = m+1; 
                ret = m; 
            }
            else 
                r = m-1;
        }
        return ret;
    }

    float sqrtf(float x) {
        float ret;
        for (float f = 1.f; true; ) {
            ret = (f + x / f) / 2;
            if (std::abs(f - ret) < FLT_MIN) break;
            f = ret;
        }
        return ret;
    }
};
