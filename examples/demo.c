#include <stdio.h>

int fact(int n) {
    if (n <= 1) return 1;
    return n * fact(n - 1);
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

double average(int a, int b, int c) {
    return (a + b + c) / 3.0;
}

int main() {
    int i, sum = 0;
    for (i = 1; i <= 5; i++) {
        printf("%d! = %d\n", i, fact(i));
        sum += i * i;
    }
    printf("sum of squares = %d\n", sum);
    printf("gcd(84, 36) = %d\n", gcd(84, 36));
    printf("avg = %.3f\n", average(1, 2, 4));
    printf("7 / 2 = %d, -7 / 2 = %d, -7 %% 2 = %d\n", 7 / 2, -7 / 2, -7 % 2);

    int x = 15;
    if (x > 10 && x < 20) printf("x in (10, 20)\n");
    else if (x == 0) printf("zero\n");
    else printf("other\n");

    int n = 0;
    while (1) {
        n++;
        if (n * n > 50) break;
    }
    printf("first n with n*n > 50: %d\n", n);
    return 0;
}
