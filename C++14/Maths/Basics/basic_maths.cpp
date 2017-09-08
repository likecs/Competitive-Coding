//gcd of 2 numbers a, b
//Complexity: O(log(max(a, b)))
template<typename T> T gcd(T a, T b) {
	return (b ? __gcd(a,b) : a);
}

//lcm of 2 numbers a and b
//Complexity: O(log(max(a, b)))
template<typename T> T lcm(T a, T b) {
	return (a * (b / gcd(a,b)));
}

//(a + b) % c
int add(int a, int b, int c) {
	int res = a + b;
	return (res >= c ? res - c : res);
}

//(a - b) % c
int mod_neg(int a, int b, int c) {
	int res; if(abs(a-b) < c) res = a - b;
	else res = (a-b) % c;
	return (res < 0 ? res + c : res);
}

//(a * b) % c
int mul(int a, int b, int c) {
	long long res = (long long)a * b;
	return (res >= c ? res % c : res);
}

//(a * b) % c for very large numbers, to avoid overflows
//O(1) hack taken from http://codeforces.com/blog/entry/15884
long long mulmod(long long a, long long b, long long m) {
	long long q = (long long)(((long double)a*(long double)b)/(long double)m);
	long long r = a * b - q * m;
	if(r > m) r %= m; if( r < 0) r += m;
	return r;
}

//(a ^ n)
//Complexity: O(log (n))
long long expo(long long a, long long n) {
	long long x = 1, p = a;
	while(n) {
		if(n & 1) x = x * p;
		p = p * p;
		n >>= 1;
	}
	return x;
}

//(a ^ n) % m
//Complexity : O(log (n))
int power(long long a, long long n, int m) {
	int x = 1, p = a % m;
	while(n) {
		if(n & 1) x = mul(x, p, m);
		p = mul(p, p, m);
		n >>= 1;
	}
	return x;
}