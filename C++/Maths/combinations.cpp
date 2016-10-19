//COMBINATION LIBRARY

//Calculation C(n, r) modulo any number (prime or composite) using pascal triangle in O(n^2) complexity as precomputation and O(1) for retrevial
const int MAX = 1e3 + 3;
const int MOD = 1e9 + 7;

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
const int MAX = 1e3 + 3;
const int MOD = 1e9 + 7;

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

//Calculation of C(n, r) modulo prime in O(1) complexity
typedef long long LL;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;		//a prime number

int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){LL res=(LL)a*b;return(res>=c?res%c:res);}
template<typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;\
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T>T mod_inverse(T a, T n){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));}

int fact[MAX], invp[MAX];

//Complexity : O(nlog n)
void init() {
	fact[0] = invp[0] = 1;
	for(int i=1; i<MAX; ++i) {
		fact[i] = mul(fact[i-1], i, MOD);
		invp[i] = mod_inverse(fact[i], MOD);
	}
}

//Complexity : O(1)
int ncr(int n, int r) {
	if (r<0 || r>n) return 0;
	return mul(fact[n], mul(invp[n-r], invp[r], MOD), MOD);
}

//Calculation of C(n, r) modulo any number(prime or composite) in O(n logn)
//Method is to find the power of all primes in n! and multiply pow(prime, count) modulo num to the result
//Sieve stores smallest prime factor for every number 
//for prime it stores number itself, so checking of number to be prime or not can be done in O(1)
const int MAX = 1e5 + 5;
const int MOD = 100;		// can be any number
int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){LL res=(LL)a*b;return(res>=c?res%c:res);}
template<typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}

int lp[MAX];
vector<int> primes;

//Complexity: O(n) 
void factor_sieve() {
	lp[1] = 1;
	for (int i=2; i<MAX; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			primes.emplace_back (i);
		}
		for (int j=0; j<primes.size() && primes[j]<=lp[i]; ++j) {
			int x = i * primes[j];
			if (x >= MAX) break;
			lp[x] = primes[j];
		}
	}
}

//calculates maximum value of i such that p^i divided n!
//p should be prime
int count_fact(int n, int p) {
	int k = 0; 
	while (n) {
		k += n/p;
		n /= p;
	}
	return k;
}
 
int ncr(int n, int r) {
	if (n < r) return 0;
	if (n==r || r==0) return 1;
	int ans = 1;
	for(int i=2; i<=n; ++i) {
		if (lp[i]==i) {		// if number is prime
			int cnt = count_fact(n, i) - count_fact(n-r, i) - count_fact(r, i);
			ans = mul(ans, power(i, cnt, MOD), MOD);
		}
	}
	return ans;
}