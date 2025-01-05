#include <stdio.h>

long long modular_exponentiation(int base, int exp, int mod)
{
    long long result = 1;
    //? perform modular exponentiation if the base is a big number to handle overflow
    long long b = base % mod;

    while (exp > 0)
    {
        // ? if the exponent is odd, multiply the result with the base and take the modulo
        if (exp % 2 == 1)
        {
            result = (result * b) % mod;
        }
        //? square the base and take the modulo
        b = (b * b) % mod;
        //? divide the exponent by 2
        exp /= 2;
    }

    return result;
}

int main()
{
    // ? B = base, N = exponent, M = modulus, error flag for invalid input
    int B, N, M, error = 0;

    printf("Enter the base (B): ");
    //? base should be  >= zero
    if (scanf("%d", &B) != 1 || B < 0)
    {
        printf("Invalid input. Base must be a positive integer.\n");
        error = 1;
    }

    if (!error)
    {   
        printf("Enter the exponent (N): ");
        //? exponent should be >= zero
        if (scanf("%d", &N) != 1 || N < 0)
        {
            printf("Invalid input. Exponent must be a non-negative integer.\n");
            error = 1;
        }
    }

    if (!error)
    {
        printf("Enter the modulus (M): ");
        //? modulus should be > 1
        if (scanf("%d", &M) != 1 || M <= 1)
        {
            printf("Invalid input. Modulus must be a positive integer greater than 1.\n");
            error = 1;
        }
    }

    //? if error flag is set, return 1
    if (error)
    {
        return 1;
    }

    long long result = modular_exponentiation(B, N, M);

    printf("Result: %lld\n", result);

    return 0;
}
