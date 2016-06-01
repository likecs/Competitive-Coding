/*
Fibonacci sequence defined by the following recusion 
f[0] = 0, f[1] = 1
f[n] = f[n-1] + f[n-2]
*/

typedef long long LL;

LL n, m, MOD;
 
LL mulmod(LL a,LL b, LL m){LL q=(LL)(((long double)a*(long double)b)/(long double)m);LL r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
 
inline LL fib(LL& x, LL& y, LL n) {
    if (!n) x = 0, y = 1;
    else {
        LL a, b;
        fib(a, b, n >> 1);
        LL z = (b << 1) - a;
        if (z < 0) z += MOD;
        x = mulmod(a, z);
        y = mulmod(a, a) + mulmod(b, b);
        if (y >= MOD) y -= MOD;
        if (n & 1) {
            x += y;
            if (x >= MOD) x -= MOD;
            x ^= y ^= x ^= y;
        }
    }
    return x;
}
 
inline LL fib(LL n) {
    LL x = 0, y = 1;
    return fib(x, y, n);
}