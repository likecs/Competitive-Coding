//Discrete log implementations

int mod_neg(int a, int b, int c) {
	long long res = (long long)a * b;
	if (res < 0) res = (res % c + c);
	else if (res >= c) res %= c;
	return res;
}

int mul(int a, int b, int c) {
	long long res = (long long)a * b;
	return (res >= c ? res % c : res);
}

template<typename T> T extended_euclid(T a, T b, T &x, T &y) {
	T xx = 0, yy = 1; y = 0; x = 1;
	while(b) {
		T q = a / b, t = b;
		b = a % b; a = t;
		t = xx; xx = x - q * xx;
		x = t; t = yy;
		yy = y - q * yy; y = t;
	}
	return a;
}

//find smallest x such that a^x = b (mod c)
//returns -1 on failure
int baby_step_giant_leap(int a, int b, int c) {
	int temp = 1, cnt = 0, d = 1, x = a, z = b, y;
	for(int i = 0; i < 32; ++i) {
		if (temp == b) return i;
		temp = mul(temp, a, c);
	}
	int res = __gcd(a, c);
	while(res > 1) {
		if (b % res) return -1;
		b /= res;
		c /= res;
		d = mul(d, a/res, c);
		res = __gcd(a, c);
		cnt += 1;
	}
	int n = ceil(sqrt(c));
	int base = 1, v;
	unordered_map<int,int> vals;
	for(int i = 0; i < n; ++i) {
		if (!vals.count(base))
			vals[base] = i;
		base = mul(base, a, c);
	}
	for (int i = 0; i < n; ++i) {
		z = extended_euclid(d, c, x, y);
		v = c / z;
		x = mod_neg(b, x / z, v);
		if (vals.count(x)) {
			return i * n + cnt + vals[x];
		}
		d = mul(d, base, c);
	}
	return -1;
}