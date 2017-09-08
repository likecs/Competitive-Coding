/*
Fibonacci sequence defined by the following recusion
f[0] = 0, f[1] = 1
f[n] = f[n-1] + f[n-2]
*/

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){long long res=(long long)a*b;return(res>=c?res%c:res);}

int fibo[MAX];

void init() {
	fibo[0] = 0, fibo[1] = 1;
	for(int i = 2; i < MAX; ++i) {
		fibo[i] = add(fibo[i-1], fibo[i-2], MOD);
	}
}

//Complexity: O(log n)
inline int fib(int& x, int& y, long long n) {
	if (n < 100000) {
		x = fibo[n], y = fibo[n+1];
	}
	else {
		int a, b;
		fib(a, b, n >> 1);
		int z = (b << 1) - a;
		if (z < 0) z += MOD;
		x = mul(a, z, MOD);
		y = add(mul(a, a, MOD), mul(b, b, MOD), MOD);
		if (n & 1) {
			x = add(x, y, MOD);
			x ^= y ^= x ^= y;
		}
	}
	return x;
}

inline int fib(long long n) {
	int x = 0, y = 1;
	return fib(x, y, n);
}