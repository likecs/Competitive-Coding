typedef long long LL;
typedef long double LD;

//gcd of 2 numbers a, b
//Complexity: O(log(max(a, b)))
template<typename T> T gcd(T a, T b) {
	return (b ? __gcd(a,b): a);
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
	LL res = (LL)a * b;
	return (res >= c ? res % c : res);
}

//(a * b) % c for very large numbers, to avoid overflows
//O(1) hack taken from http://codeforces.com/blog/entry/15884
LL mulmod(LL a, LL b, LL m) {
	LL q = (LL)(((LD)a*(LD)b)/(LD)m);
	LL r = a * b - q * m; 
	if(r > m) r %= m; if( r < 0) r += m;
	return r;
}

//(a ^ b)
//Complexity: O(log (b))
template <typename T>T expo(T e, T n) {
	T x = 1, p = e;
	while(n) {
		if(n & 1) x = x * p;
		p = p * p;
		n >>= 1;
	}
	return x;
}

//(a ^ b) % m
//Complexity : O(log (b))
template <typename T>T power(T e, T n, T m) {
	T x = 1, p = e;
	while(n) {
		if(n & 1) x = mul(x, p, m);
		p = mul(p, p, m);
		n >>= 1;
	}
	return x;
}