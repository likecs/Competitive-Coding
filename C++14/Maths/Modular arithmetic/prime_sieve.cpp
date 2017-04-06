//Generating List of Primes

/*
Prime number Theorem : Number of primes till n is approximately (n/log(n))
Size limits i.e. number of primes below given n
1	10				4
2	100				25
3	1,000			168
4	10,000			1,229
5	100,000			9,592
6	1,000,000		78,498
7	10,000,000		664,579
8	100,000,000		5,761,455
*/

//Factor sieve algorithm (taken from http://e-maxx.ru/algo/prime_sieve_linear)
//stores smallest prime factor of 'n' in vector 'lp'
//Complexity : O(n)
const int MAX = 1000001;

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

//Super fast, memory efficient Segmented Bit Sieve
const int MAX = 100000001;		//list of primes upto 10^8

//Takes about 0.5 seconds for the below process
int flag[MAX>>6];
vector<int> primes;

#define SET(x) (flag[x>>6]&(1<<((x>>1)&31)))
#define MARK(x) (flag[x>>6]|=(1<<((x>>1)&31)))

void sieve() {
	register int i, j, x;
	int LIM = ceil(sqrt(MAX));
	primes.emplace_back(2);
	for(i = 3; i < LIM; i += 2) {
		if(!SET(i)) {
			primes.emplace_back(i);
			for(j = i*i, x = i<<1; j < MAX; j += x) MARK(j);
		}
	}
	for(; i < MAX; i += 2) {
		if(!SET(i)) primes.emplace_back(i);
	}
}

//Using C++ bitset and much more optimisations
//Taken from https://github.com/kartikkukreja/blog-codes/blob/master/src/spoj_CPRIME.cpp
const int MAX = 1e8 + 8;

bitset<MAX/2+1> num;
vector<int> primes;

void EratostheneSieve() {
	int x = MAX/2, y =(sqrt(MAX)-1)/2, i, j, z;
	for (i = 1; i <= y; ++i) {
		if (num[i] == 0) {
			for (j = (i*(i+1))<<1, z = (i<<1); j <= x; j += z+1) {
				num[j] = 1;
			}
		}
	}
	primes.emplace_back(2);
	for (i = 3; i < MAX; i += 2) {
		if (!num[i>>1]) primes.emplace_back(i);
	}
}
