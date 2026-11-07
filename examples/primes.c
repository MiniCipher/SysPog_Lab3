#include <stdio.h>

int is_prime(int n) {
    if (n < 2) return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0) return 0;
    return 1;
}

int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

double power(double x, int k) {
    double r = 1;
    while (k-- > 0) r *= x;
    return r;
}

int main() {
    int count = 0;
    printf("Primes < 50:");
    for (int i = 0; i < 50; i++)
        if (is_prime(i)) { printf(" %d", i); count++; }
    printf("\ncount = %d\n", count);

    for (int i = 0; i <= 10; i += 2) printf("fib(%d) = %d\n", i, fib(i));

    printf("2^10 = %g, 1.5^3 = %.4f\n", power(2, 10), power(1.5, 3));

    int t = 7.9;
    double h = 7 / 2;
    printf("t = %d, h = %.1f, !t = %d, c = %c\n", t, h, !t, 'A' + 2);
    return 0;
}
