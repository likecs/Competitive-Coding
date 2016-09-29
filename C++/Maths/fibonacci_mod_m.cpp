/*
Fibonacci sequence defined by the following recusion 
f[0] = 0, f[1] = 1
f[n] = f[n-1] + f[n-2]
*/

typedef long long LL;
const int MAX = 1e5 + 5;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}

int fibo[MAX];
void pre_compute() {
    fibo[0] = 0, fibo[1] = 1;
    for(int i=2; i<MAX; ++i) {
        fibo[i] = add(fibo[i-1], fibo[i-2], MOD);
    }
}

inline int fib(int& x, int& y, LL n) {
    if (n<1e5) {
        x = fibo[n], y = fibo[n+1];
    }
    else {
        int a, b;
        fib(a, b, n >> 1);
        int z = (b << 1) - a;
        if (z < 0) z += MOD;
        x = mod((LL)a * z, (LL)MOD);
        y = mod((LL)a * a + (LL)b * b, (LL)MOD);
        if (n & 1) {
            x += y;
            if (x >= MOD) x -= MOD;
            x ^= y ^= x ^= y;
        }
    }
    return x;
}

inline int fib(LL n) {
    int x = 0, y = 1;
    return fib(x, y, n);
}