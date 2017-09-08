/*
Template for finding ncr % m for any general integers
n, m, r. There is no restriction on the values of n,
m and r except that it should fit in long long.

The complexity is O(sqrt(m) + pk + log2(n)*log_pk(n) + log(m))
where pk = p^k where p is prime & pk | m
Initial sqrt(m) is due to factorisation of m
Second part is due to initialisation of factorials
Third part is the complexity of fact_mod function
Last part log(m) is due to Chinese remainder theorem

Since, the limiting term can be pk, it works for m <= 10^6
As with larger m, if given prime, it will TLE
For larger m, which are prime, one might use lucas theorem.

Usage : No dependencies.
Just copy the template and call ncr(n, r, m).
*/

namespace combinations {
vector<pair<long long, int>> factorise(long long m) {
	vector<pair<long long, int>> ans;
	int UP = sqrt(m);
	for(int i = 2; i <= UP; ++i) {
		if (m % i == 0) {
			int e = 0;
			while(m % i == 0) m /= i, e += 1;
			ans.push_back({i, e});
		}
	}
	return ans;
}

long long mul(long long a, long long b, long long c) {
	long long res = a * b;
	return (res >= c ? res % c : res);
}

long long mod_neg(long long a, long long b, long long c) {
	long long res; if(abs(a-b) < c) res = a - b;
	else res = (a-b) % c;
	return (res < 0 ? res + c : res);
}

long long extended_euclid(long long a, long long b, long long &x, long long &y) {
	long long xx = 0, yy = 1; y = 0; x = 1;
	while(b) {
		long long q = a / b, t = b;
		b = a % b; a = t;
		t = xx; xx = x - q * xx;
		x = t; t = yy;
		yy = y - q * yy; y = t;
	}
	return a;
}

long long mod_inverse(long long a, long long n) {
	long long x, y, z = 0;
	long long d = extended_euclid(a, n, x, y);
	return (d > 1 ? -1 : mod_neg(x, z, n));
}

long long expo(long long a, long long b) {
	long long x = 1, y = a;
	while(b) {
		if (b&1) x = x * y;
		y = y * y;
		b >>= 1;
	}
	return x;
}

long long power(long long a, long long b, long long c) {
	long long x = 1, y = a;
	while(b) {
		if (b&1) x = mul(x, y, c);
		y = mul(y, y, c);
		b >>= 1;
	}
	return x;
}

vector<long long> init(long long p, long long pk) {
	vector<long long> fact(pk);
	fact[0] = 1;
	for(int i = 1; i < pk; ++i) {
		long long red = i;
		if (red % p == 0) red = 1;
		fact[i] = mul(fact[i-1], red, pk);
	}
	return fact;
}

long long fact_mod(long long n, long long p, long long pk, vector<long long> &fact) {
	long long res = 1;
	while(n > 0) {
		long long times = n/pk;
		res = mul(res, power(fact[pk-1], times, pk), pk);
		res = mul(res, fact[n%pk], pk);
		n /= p;
	}
	return res;
}

long long count_fact(long long n, long long p) {
	long long ans = 0;
	while(n) {
		ans += n/p;
		n /= p;
	}
	return ans;
}

long long ncr(long long n, long long r, long long p, long long e) {
	if (r > n || r < 0) return 0;
	if (r == 0 || n == r) return 1;
	long long _e = count_fact(n, p) - count_fact(r, p) - count_fact(n-r, p);
	assert(_e >= 0);
	if (_e >= e) return 0;
	long long pk = expo(p, e);
	vector<long long> fact = init(p, pk);
	long long ans = fact_mod(n, p, pk, fact);
	ans = mul(ans, mod_inverse(fact_mod(r, p, pk, fact), pk), pk);
	ans = mul(ans, mod_inverse(fact_mod(n-r, p, pk, fact), pk), pk);
	ans = mul(ans, expo(p, _e), pk);
	return ans;
}

vector<long long> rem, mods;
vector<pair<long long,pair<long long,long long>>> crt;

void pre_process() {
	crt.clear();
	long long a = 1, b = 1, m = mods[0];
	crt.push_back({mods[0], {a, b}});
	for(int i = 1; i < mods.size(); ++i) {
		a = mod_inverse(m, mods[i]);
		b = mod_inverse(mods[i], m);
		crt.push_back({m, {a, b}});
		m *= mods[i];
	}
}

long long find_crt() {
	long long ans = rem[0], m = crt[0].first, a, b;
	for(int i = 1; i < mods.size(); ++i) {
		a = crt[i].second.first;
		b = crt[i].second.second;
		m = crt[i].first;
		ans = (ans * b * mods[i] + rem[i] * a * m) % (m * mods[i]);
	}
	return ans;
}

long long ncr(long long n, long long r, long long m) {
	vector<pair<long long, int>> pf = factorise(m);
	rem.clear();
	mods.clear();
	for(auto it : pf) {
		long long get = ncr(n, r, it.first, it.second);
		rem.push_back(get);
		mods.push_back(expo(it.first, it.second));
	}
	pre_process();
	return find_crt();
}
};
using namespace combinations;