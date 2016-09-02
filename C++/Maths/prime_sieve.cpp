//Generating List of Primes

//Prime number Theorem : Number of primes till n is approximately (n/log(n))

//Normal Sieve of Eranthoses
//Complexity : O(n loglogn)
typedef long long LL;

const int MAX = 1000001;
const int LIM = 1001				//equals sqrt(MAX)
/*
size limits i.e. number of primes below given n
1	10				4	 
2	100				25	 
3	1,000			168	 
4	10,000			1,229	 
5	100,000			9,592	 
6	1,000,000		78,498	 
7	10,000,000		664,579	 
8	100,000,000		5,761,455	
*/

vector<int> primes;
int c[MAX];

void generate() {
	int i, j, x;
	primes.push_back(2);
	for (i=3; i<=LIM; i+=2) {
		if (c[i]==0) {
			primes.push_back(i);
			for (j=i*i, x=i<<1; j<MAX; j+=x) c[j] = 1;
		}
	}
	for (; i<MAX; i+=2) {
		if (c[i]==0) primes.push_back(i);
	}
}

// modified form for sieve to store smallest prime factor of each number
//Complexity: O(n loglogn)
int c[MAX];

void factor_sieve() {
	int i, j, x;
	c[i] = 1;
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

//modified algorithm for factor sieve (taken from http://e-maxx.ru/algo/prime_sieve_linear)
//Complexity : O(n)
const int MAX = 1000001;

int lp[MAX];
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

//Super fast, memory efficient Segmented Bit Sieve
const int MAX = 100000001;		//list of primes upto 10^8
const int LIM = 10001;

//Takes about 0.5 seconds for the below process
int flag[MAX>>6];
vector<int> primes;
 
#define ifcV(x) (flag[x>>6]&(1<<((x>>1)&31)))
#define iscV(x) (flag[x>>6]|=(1<<((x>>1)&31)))
 
void sieve() {
    register int i, j, k=1, x;
    primes.push_back(2);
	for(i=3; i<LIM; i+=2) {
		if(!ifcV(i)) {
			primes.push_back(i);
			for(j=i*i, x=i<<1; j<MAX; j+=x) iscV(j);
		}
	}
    for(; i<MAX; i+=2) {
        if(!ifcV(i)) primes.push_back(i);
    }
}

//Using C++ bitset and much more optimisations, refer to https://github.com/kartikkukreja/blog-codes/blob/master/src/spoj_CPRIME.cpp

const int MAX = 100000005;

bitset<MAX/2+1> num;
vector<int> primes;

void EratostheneSieve() {
    int x = MAX/2, y =(sqrt(MAX)-1)/2, i, j, z;
    for (i=1; i<=y; ++i) {
        if (num[i] == 0) {
            for (j=(i*(i+1))<<1, z=(i<<1); j<=x; j+=z+1) num[j] = 1;
        }
    }
    primes.push_back(2);
    for (i=3; i<MAX; i+=2) {
        if (!num[i>>1]) primes.push_back(i);
    }
}