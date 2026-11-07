# Згенеровано транслятором c2py з підмножини мови C
import sys, math

def _div(a, b):  # цілочисельне ділення C (усічення до нуля)
    q = abs(a) // abs(b)
    return q if (a >= 0) == (b >= 0) else -q

def _mod(a, b):  # остача C (знак як у діленого)
    return a - b * _div(a, b)

def printf(fmt, *args):
    s = fmt % args
    sys.stdout.write(s)
    return len(s)

def is_prime(n):
    if n < 2:
        return 0
    d = 2
    while (d * d) <= n:
        if _mod(n, d) == 0:
            return 0
        d += 1
    return 1

def fib(n):
    if n < 2:
        return n
    return (fib((n - 1)) + fib((n - 2)))

def power(x, k):
    r = float(1)
    while ((k := k - 1) + 1) > 0:
        r = r * x
    return r

def main():
    count = 0
    printf("Primes < 50:")
    i = 0
    while i < 50:
        if is_prime(i):
            printf(" %d", i)
            count += 1
        i += 1
    printf("\ncount = %d\n", count)
    i = 0
    while i <= 10:
        printf("fib(%d) = %d\n", i, fib(i))
        i = i + 2
    printf("2^10 = %g, 1.5^3 = %.4f\n", power(float(2), 10), power(1.5, 3))
    t = int(7.9)
    h = float(_div(7, 2))
    printf("t = %d, h = %.1f, !t = %d, c = %c\n", t, h, int(not t), (65 + 2))
    return 0

if __name__ == "__main__":
    sys.exit(main())
