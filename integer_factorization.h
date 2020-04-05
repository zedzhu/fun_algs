#include <cstdio>
#include <vector>

using namespace std;

vector<int> calIntegerPrimeFactors(int n) {
    vector<int> ret;
    int z = 2;
    while (z * z <= n) {
        if (n % z == 0) {
            ret.push_back(z);
            n /= z;
        }
        else
            z++;
    }

    //如果最后n>1，这说明n本身也是素数了。
    if (n > 1)
        ret.push_back(n);
    
    return ret;
}
