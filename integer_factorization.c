#include <cstdio>

void print_integer_prime_factors(int n)
{
    int z = 2;
    while (z * z <= n)
    {
        if (n % z == 0)
        {
            printf("%d\n", z);
            n /= z;
        }
        else
            z++;
    }

    if (n > 1)
        printf("%d\n", n);
}

