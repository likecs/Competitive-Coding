//COMBINATION LIBRARY

//Calculation C(n, r) modulo any number (prime or composite) using pascal triangle in O(n^2) complexity as precomputation
const int MAX = 1005;
const int MOD = 1000000007;

int ncr[MAX][MAX];

void pascal() {
	for (int i=0; i<MAX; ++i) {
		for (int j=0; j<=i; ++j) {
			if (j==0 || j==i) ncr[i][j] = 1;
			else ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
			if (ncr[i][j]>=MOD) ncr[i][j] -= MOD;
		}
	}
}

//space optimised version of above function
//dp state depends on only previous row elements so space can be reduced by factor of n
//for C(n, r) use ncr[n&1][r]
const int MAX = 1005;
const int MOD = 1000000007;

int ncr[2][MAX];

void pascal() {
	for (int i=0; i<MAX; ++i) {
		for (int j=0; j<=i; ++j) {
			if (j==0 || j==i) ncr[i&1][j] = 1;
			else ncr[i&1][j] = ncr[(i-1)&1][j-1] + ncr[(i-1)&1][j];
			if (ncr[i&1][j]>=MOD) ncr[i&1][j] -= MOD;
		}
	}
}

//Calculation of C(n, r) modulo prime in O(1) complexity after O(n logn) precomputation
typedef long long LL;
const int MAX = 100005;
const LL MOD = 1000000007;		//a prime number

template <typename T>T mod(T a, T b) {return (a < b ? a : a % b);}
template <typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}
template <typename T>T InverseEuler(T a, T m){return (a==1?1:power(a,m-2,m));}

LL fact[MAX], invp[MAX];

void pre() {
	fact[0] = invp[0] = 1LL;
	for(int i=1; i<MAX; ++i) {
		fact[i] = mod(fact[i-1]*i, MOD);
		invp[i] = InverseEuler(fact[i], MOD);
	}
}

LL ncr(LL n, r) {
	return mod(fact[n] * mod(invp[n-r]*invp[r], MOD), MOD);
}

//Calculation of C(n, r) modulo any number(prime or composite) in O(n logn)
//Methos is to find the power of all primes in n! and multiply pow(prime, count) modulo num to the result
const int MAX = 100005;
const LL MOD = 1000000007;		// can be any number
template <typename T>T mod(T a, T b) {return (a < b ? a : a % b);}
template <typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}

int c[MAX];

//sieve to store smallest prime factor for every number, for prime it stores number itself, so checking of number to be prime or not can be done in O(1)
void factor_sieve() {
	int i, j, x;
	for (i=2; i<MAX; i+=2) {
		c[i] = 2;
	}
	for (i=3; i<=LIM; i+=2) {
		if (c[i]==0) {
			c[i] = i;
			for (j=i*i, x=i<<1; j<MAX; j+=x) {
				if (!c[j]) c[j] = i;
			}
		}
	}
	for (; i<MAX; i+=2) {
		if (c[i]==0) c[i] = i;
	}
}

//calculates power of prime p in n!
int count_fact(int n, int p) {
    int k = 0; 
    while (n) {
        k += n/p;
        n /= p;
    }
    return k;
}
 
LL ncr(int n, int r) {
    if (n < r) return 0LL;
    if (n==r || r==0) return 1LL;
    LL ans = 1LL;
    for(int i=2; i<=n; ++i) {
        if (c[i]==i) {		// if number of prime
            int cnt = count_fact(n, i) - count_fact(n-r, i) - count_fact(r, i);
            ans = mod(ans * power((LL)i, (LL)cnt, MOD), MOD);
        }
    }
    return ans;
}