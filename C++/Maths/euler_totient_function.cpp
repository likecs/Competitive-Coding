//EULER TOTIENT FUNCTION

//Generate euler totient function list for all numbers till given n
//Complexity: O(n logn)
const int MAX = 100005;

int phi[MAX];

void generate_etf() {
    phi[1] = 1;
    for(int i=2; i<MAX; i++) {
        if(!phi[i]) {
            phi[i] = i-1;
            for(int j=(i<<1); j<MAX; j+=i) {
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}

//Improved Complexity : O(n)
//taken from http://codeforces.com/blog/entry/10119
const int MAX = 1000001;

int lp[MAX], phi[MAX];
vector<int> primes;
 
void generate_etf() {
    phi[1] = 1;
    for (int i=2; i<MAX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            phi[i] = i-1;
            primes.push_back (i);
        }
        else {
            if (lp[i] == lp[i/lp[i]]) 
                phi[i] = phi[i / lp[i]] * lp[i];
            else
                phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j=0; j<primes.size() && primes[j]<=lp[i]; ++j) {
            int x = i * primes[j];
            if (x >= MAX) break;
            lp[x] = primes[j];
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
    if (n%2==0) {
        a -= a/2;
        while (n%2==0) n>>=1;
    }
    for (int j=3; j<=k; j+=2) {
        if (n%j==0) {
            a -= a/j; 
            while (n%j==0) n /= j;
        }
    }
    if (n>1) a -= a/n;		//number left is prime
    return a;
}

//Method 2- O(log(n)) complexiltiy by generating list of primes till sqrt(n)
/*
useful even we need to calculate ETF for fiven n for large number of test cases.
Since maximum number of prime factors of n is approximately log(n), so is the complexity
*/

const int MAX = 100005;
const int LIM = 1001;

int c[MAX];

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
 
int phi(int n) {
    if (n==1) return 1;
    int etf = n, val;
    while (n!=1) {
        val = c[n];
        etf -= etf/val;
        while (n%val==0) n /= val;
    }
    return etf;
}
