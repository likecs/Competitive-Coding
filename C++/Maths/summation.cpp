// code to calculate Summation(i^k) in O(k logk) complexity
// Thanks to Codeforces educational round 7 Editorial for help
typedef long long LL;
typedef long double LD;
const int MOD = 1e9 + 7;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}
template<typename T> T mod_neg(T a, T b) {return ((a%b)+b)%b;}
LL mulmod(LL a,LL b, LL m){LL q=(LL)(((LD)a*(LD)b)/(LD)m);LL r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template<typename T> T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}
template<typename T> T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T> T mod_inverse(T a, T n){T x,y;T d = extended_euclid(a, n, x, y);return (d>1?-1:mod_neg(x,n));}

//Uses Lagrange interpolation method 
inline int summation(LL n, int k) {
    vector <LL> vals;
    LL sum = 0;
    vals.push_back(sum);
    for(int i = 0; i <= k; ++i) {
        sum += power(i + 1LL, (LL)k, (LL)MOD);
        if (sum >= MOD) {
            sum -= MOD;
        }
        vals.push_back(sum);
    } 
    if (n < vals.size()) {
        return (int)vals[n];
    }
    int ans = 0;
    LL store = 1, temp;
    // Lagrange interpolation pre-computation
    for(int j = 1; j < vals.size(); ++j) {
        store = mulmod(store, n-j, MOD);
        store = mulmod(store, mod_inverse(MOD-j, MOD), MOD);
	}
	for(int i = 0; i < vals.size(); ++i) {
        ans += mulmod(vals[i], mod(store, (LL)MOD), (LL)MOD);
        if (ans >= MOD) {
            ans -= MOD;
		}
        temp = mulmod(n-i, mod_inverse(n - (i + 1), (LL)MOD), MOD);
        store = mulmod(store, temp, MOD);
        temp = mulmod(mod_neg(i - ((int)vals.size() - 1), MOD), mod_inverse(i + 1, MOD), MOD);
        store = mulmod(store, temp, MOD);
    }
    return ans;
}
