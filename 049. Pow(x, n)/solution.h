#include <cmath>

class Solution {
public:
    double pow(double x, int n) {
        if (!n) return 1;
        double tmp = pow(x, n/2);
        if (n&1) {
            return n>0 ? x*tmp*tmp : tmp*tmp/x;
        } else {
            return tmp * tmp;
        }
    }

    /*
    *   Basically, most people think this is very easy as below:
    *      double result = 1.0;
    *      for (int i=0; i<n; i++){
    *           result *=x;
    *      }
    *   However, 
    *     1) We need think about the `n` is negtive number.
    *     2) We need more wisely deal with the following cases:
    *         pow(1, MAX_INT);
    *         pow(-1,BIG_INT);
    *         pow(2, BIG_INT);
    *        To deal with such kind case, we can use x = x*x to reduce the `n` more quickly
    *        so, if `n` is an even number, we can `x = x*x`, and `n = n>>1;`
    *            if `n` is an odd number, we can just `result *= x;`
    */
    double pow(double x, int n) {
        bool sign = false;
        unsigned int exp = n;
        if (n<0) {
            exp = -n;
            sign = true;
        }
        double result = 1.0;
        while (exp) {
            if (exp & 1) { //奇数，指数exp每次除以2，最后一次总是1
                result *= x;
            }
            exp >>= 1;
            x *= x;
        }
        return sign ? 1/result : result;
    }

};
