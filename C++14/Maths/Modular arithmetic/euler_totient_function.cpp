//EULER TOTIENT FUNCTION

//Generate euler totient function list for all numbers till given n
//Complexity: O(n loglog n)
const int MAX = 100005;

int phi[MAX];

void generate_etf() {
	phi[1] = 1;
	for(int i = 2; i < MAX; i++) {
		if(!phi[i]) {
			phi[i] = i-1;
			for(int j = (i<<1); j<MAX; j += i) {
				if(!phi[j]) phi[j] = j;
				phi[j] = phi[j]/i*(i-1);
			}
		}
	}
}

//Improved Complexity : O(n)
//taken from http://codeforces.com/blog/entry/10119
const int MAX = 1000001;

vector<int> lp, primes, phi;

void generate_etf() {
	lp.resize(MAX);
	phi.rezize(MAX);
	lp[1] = phi[1] = 1;
	for (int i = 2; i < MAX; ++i) {
		if (!lp[i]) {
			lp[i] = i;
			phi[i] = i-1;
			primes.emplace_back(i);
		}
		for (int j = 0; j < primes.size(); ++j) {
			int x = i * primes[j];
			if (x >= MAX) break;
			lp[x] = primes[j];
			if (i % primes[j] == 0) {
				phi[x] = phi[i] * primes[j];
				break;
			}
			else {
				phi[x] = phi[i] * (primes[j]-1);
			}
		}
	}
}

//Find Value of ETF for given number
/*
phi (ab) = phi(a)*phi(b)
for primes, phi(p) = p-1
and phi(p^k) = p^k (1-1/p)

for general N = p1^k1 * p2^k2 * .... pn^kn
phi(N) = N * (1-1/p1)*(1-1/p2)*....(1-1/pn)
*/

//Method 1- O(Sqrt(n)) complexity but no need of prime number list
int phi(int n) {
	int a = n, k = sqrt(n);
	if (n % 2 == 0) {
		a -= a/2;
		while (n%2==0) n >>= 1;
	}
	for (int j = 3; j <= k; j += 2) {
		if (n % j == 0) {
			a -= a/j;
			while (n % j == 0) n /= j;
		}
	}
	if (n > 1) a -= a/n; //number left is prime
	return a;
}

//Method 2- O(log(n)) complexiltiy by generating list of primes till sqrt(n)
/*
useful even we need to calculate ETF for fiven n for large number of test cases.
Since maximum number of prime factors of n is approximately log(n), so is the complexity
*/
vector<int> lp, primes;

void factor_sieve() {
	lp.resize(MAX);
	lp[1] = 1;
	for (int i = 2; i < MAX; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			primes.emplace_back(i);
		}
		for (int j = 0; j < primes.size() && primes[j] <= lp[i]; ++j) {
			int x = i * primes[j];
			if (x >= MAX) break;
			lp[x] = primes[j];
		}
	}
}

int phi(int n) {
	if (n == 1) return 1;
	int etf = n, val;
	while (n != 1) {
		val = lp[n];
		etf -= etf/val;
		while (n % val==0) n /= val;
	}
	return etf;
}
