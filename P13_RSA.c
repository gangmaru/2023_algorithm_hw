#include <stdio.h>
#include <math.h>
// Function to calculate (x^y) % p using the repeated squaring method
long long mod_pow(long long x, unsigned long long y, long long p) {
    long long result = 1;
    x = x % p; // Reduce x to the range [0, p-1]
    while (y > 0) {
        // If y is odd, multiply x with the result
        if (y % 2 == 1) {
            result = (result * x) % p;
        }
        // y must be even now
        y = y / 2;
        x = (x * x) % p;
    }
    return result;
}

int main() {
    // Public Key
    long long n = 187; // Replace with your n value
    //long long e = 3;   // Replace with your e value

    // Ciphertext
    long long C = 106; // Replace with your ciphertext value

    // Calculate M = C^d mod n, where d is the private key exponent
    // In practice, you'd need the private key (d) to do this.
    // Without the private key, you cannot efficiently compute M.

    // For example, if you have d:
    long long d = 10; // Replace with your private key value
    long long M = mod_pow(C, d, n);

    // Without d, you cannot efficiently compute M, as it requires factoring n, which is a hard problem.

    printf("Original Message (M): %lld\n", M);

    return 0;
}
