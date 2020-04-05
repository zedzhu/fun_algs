/*
 * http://stackoverflow.com/questions/16388982/algorithm-function-for-fibonacci-series
 */

//T(n) = T(n-1) + T(n-2), O（(3/2)^N）
long fib1(int n)
{
    if ( n <= 1 ) return n;
    return fib1(n-1) + fib1(n-2);
}

//Dynamic Programming, Time Complexity: O(n) Extra Space: O(n)
long fib2(int n)
{
    /* Declare an array to store fibonacci numbers. */
    long* f = new long[n+1]();
    int i;

    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++)
    {
        /* Add the previous 2 numbers in the series and store it */
        f[i] = f[i-1] + f[i-2];
    }

    long ret = f[n];
    delete[] f;
    return ret;
}

//Space Otimized Method 2, Time Complexity: O(n) Extra Space: O(1)
long fib3 (int n)
{
    if ( n <= 1 ) return n;

    long x = 0, y = 1;
    for (int j = 1; j <= n; j++)
    {
        y = x + y;
        x = y - x;
    }
    return y;
}

/* M = {{1,1},{1,0}}, {fn, fn-1} = M^(n-1)*{f1,f0}
 * Time Complexity: O(n) Extra Space: O(1)
 */
/* Helper function that multiplies 2 matricies F and M of size 2*2, and
   puts the multiplication result back to F[][] */
void multiply(long F[2][2], long M[2][2]);

/* Helper function that calculates F[][] raise to the power n and puts the
   result in F[][]
   Note that this function is desinged only for fib() and won't work as general
   power function */
void power(long F[2][2], int n);

long fib4(int n)
{
    long F[2][2] = {{1,1},{1,0}};
    if(n == 0)
        return 0;
    power(F, n-1);

    return F[0][0];
}

void multiply(long F[2][2], long M[2][2])
{
    long x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
    long y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
    long z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
    long w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(long F[2][2], long n)
{
    if( n <= 1) return;
    int i;
    long M[2][2] = {{1,1},{1,0}};

    // n - 1 times multiply the matrix to {{1,0},{0,1}}
    for ( i = 2; i <= n; i++ )
        multiply(F, M);
}

/* M = {{1,1},{1,0}}, {fn, fn-1} = M^(n-1)*{f1,f0}
 * Optimized Method 4.  We can do recursive multiplication to get power(M, n) in the prevous method
 * Time Complexity: O(Logn) Extra Space: O(Logn) if we consider the function call stack size, otherwise O(1).
 */

/* Optimized version of power() in method 4 */
void power2(int F[2][2], int n)
{
    if( n <= 1) return;
    power2(F, n/2);
    multiply(F, F);
    if (n%2 != 0)
    {
        long M[2][2] = {{1,1},{1,0}};
        multiply(F, M);
    }
}

int fib5(int n)
{
    if ( n <= 1 ) return n;
    long F[2][2] = {{1,1},{1,0}};
    power2(F, n-1);
    return F[0][0];
}
