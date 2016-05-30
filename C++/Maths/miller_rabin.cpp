//GENERAL PRIME CHECKER
//COMPLEXITY O(sqrt(n)/6)

typedef long long LL;

int check (LL n) {
    if (n<=1) return 0;
    if (n%2==0 || n%3==0) return 0;
    int x = sqrt(n);
    for (int i=5; i<=x; i+=6) {
        if (n%i==0) return 0;
        if (n%(i+2)==0) return 0;
    }
    return 1;
}


//MILER RABIN TEST

//(a*b)%m for a,b,m<=10^18
LL mulmod(LL a,LL b, LL MOD) {
    LL q=(LL)(((long double)a*(long double)b)/(long double)MOD);
	LL r=a*b-q*MOD;
	if (r>MOD) r %= MOD;
	if(r<0) r+=MOD;
	return r;
}

//list of small primes
LL pr[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
 
//(a^b)%m in log(b)
LL expo(LL b, LL n, LL mod) {
    LL x=1, p=b;
    while(n) {
        if(n&1) x = mulmod(x, p, mod);
        p = mulmod(p, p, mod);
        n>>=1;
    }
    return x;
}
 
//Miller Rabin test 
/*
Special cases- (No use of random int)
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
*/

bool rabin_miller(LL p) {
    if (p<2) return false;
    if (p!=2 && p%2==0) return false;
    if (p<8) return true;
    LL s = p-1, val = p-1, a, m, temp;
    while (s%2==0) s>>=1;
    for (int i=0; i<3; ++i) {
        a = 1LL*rand()%val + 1LL;
        temp = s;
        m = power(a, temp, p);
        while (temp!=(p-1) && m!=1 && m!=(p-1)) {
            m = mulmod(m, m, p);
            temp<<=1;
        }
        if (m!=(p-1) && temp%2==0) return false;
    }
    return true;
}