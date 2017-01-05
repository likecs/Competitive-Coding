//Primitive root implementations for general n

int mul(int a, int b, int c) {
	long long res = (long long)a * b;
	return (res >= c ? res % c : res);
}

int power(int a, int b, int c) {
	int x = 1, y = a;
	while(b) {
		if (b & 1) x = mul(x, y, c);
		y = mul(y, y, c);
		b >>= 1;
	}
	return x;
}

int phi(int n) {
	int up = sqrt(n), ph = n;
	for(int i = 2; i <= up; ++i) {
		if (n % i == 0) {
			ph /= i;
			ph *= (i - 1);
			while(n % i == 0) n /= i;
		}
		if (n == 1) break;
	}
	if (n > 1) {
		ph /= n;
		ph *= (n-1);
	}
	return ph;
}

int primitive_root(int p) {
	vector<int> factors;
	int n = phi(p), up = sqrt(n);
	for(int i = 2; i <= up; ++i) {
		if (n % i == 0) {
			factors.push_back(i);
			if (n != i*i) factors.push_back(n/i);
		}
	}
	for(int i = 2; i < p; ++i) {
		if (__gcd(i, p) != 1) continue;
		bool done = true;
		for(auto it : factors) {
			if (power(i, n / it, p) == 1) {
				done = false;
				break;
			}
		}
		if (done) return i;
	}
	return -1;
}
