//Mobius function
/*
	mu[1] = 1
	mu[i] = i, if i is non-squarefree
	mu[i] = (-1)^x , where i = p1 * p2 * .. px, (pi are primes)
*/

const int MAX = 1000001;
//modified algorithm for factor sieve (taken from http://e-maxx.ru/algo/prime_sieve_linear)
//Complexity : O(n)
int lp[MAX];
int mobius[MAX];
vector<int> primes;

void factor_sieve() {
	lp[1] = 1;
	for (int i=2; i<MAX; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			primes.push_back (i);
		}
		for (int j=0; j<primes.size() && primes[j]<=lp[i]; ++j) {
			int x = i * primes[j];
			if (x >= MAX) break;
			lp[x] = primes[j];
		}
	}
}

//Complexity : O(n)
void mobius_sieve() {
	mobius[1] = 1;
	for(int i=2; i<MAX; ++i) {
		int w = lp[i];
		if (lp[i/w] == w) {
			mobius[i] = 0;
		}
		else {
			mobius[i] = -mobius[i/w];
		}
	}
}

//Sieve for square-free numbers
//Complexity: O(n), actually T(n) <= (PI^2/6) * n

bool sqfree[MAX];

void square_free() {
	memset(sqfree, true, sizeof sqfree);
	for(int i=1; i<MAX; ++i) {
		if ((long long)i*i > MAX) {
			break;
		}
		int step = i*i;
		for(int j=step; j<MAX; j+=step) {
			sqfree[i] = false;
		}
	}
}