//Generating List of Primes

/*
Prime number Theorem
Number of primes till n is approximately (n/log(n))
*/

//Normal Sieve of Eranthoses

typedef long long LL;

#define MAX 1000000
#define LIM 1001				//equals sqrt(MAX)

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

//Super fast, memory efficient Segmented Bit Sieve

#define MAX 100000001		//list of primes upto 10^8
#define LIM 10001

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