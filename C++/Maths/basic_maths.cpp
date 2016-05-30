//absolute of a number
template <typename T>T abs(T &n) {return (n < 0 ? -n : n);}

//maximum of 2 numbers
template <typename T>T max(T &a, T &b) {return (!(a < b) ? a : b);}

//minimum of 2 numbers
template <typename T>T min(T &a, T &b) {return (a < b ? a : b);}

//a modulo b
template <typename T>T mod(T a, T b) {return (a < b ? a : a % b);}

//(a*b)%m for a,b,m<=10^18
//O(1) hack below, for O(log n) function refer https://goo.gl/3JOvSp
LL mulmod(LL a,LL b, LL m){LL q=(LL)(((long double)a*(long double)b)/(long double)m);LL r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}

//(a^b)%m in log(b)
template <typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}

//Fermat principle for Modulo Inverse for prime numbers only
template <typename T>T InverseEuler(T a, T m){return (a==1?1:power(a,m-2,m));}

//gcd of 2 numbers
template<typename T>T gcd(T a, T b){if(a)while(a%=b^=a^=b^=a); return b;}

//lcm of 2 numbers
template <typename T>T lcm(T a, T b){return (a*(b/gcd(a,b)));}