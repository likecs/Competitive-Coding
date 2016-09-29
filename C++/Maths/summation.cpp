// code to calculate Summation(i^k) in O(k logk) complexity
// Thanks to Codeforces educational round 7 Editorial for help
typedef long long LL;
const int MOD = 1e9 + 7;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}
template<typename T> T add(T a, T b, T c){T x=a+b;return (x>=c ? x-c : x);}
template<typename T> T mod_neg(T a, T b) {a=mod(a, b);if(a<0){a+=b;}return a;}
template<typename T> T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}
template<typename T> T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T> T mod_inverse(T a, T n){T x,y;T d = extended_euclid(a, n, x, y);return (d>1?-1:mod_neg(x,n));}

vector<int> vals;
int invp[MAX], invp2[MAX];

void pre_compute() {
    for(int i = 0; i < MAX; ++i) {
        invp[i] = mod_inverse(i, MOD);
    }
    for(int i = 0; i < MAX; ++i) {
        invp2[i] = mod_inverse(MOD-i, MOD);
    }
}

//Uses Lagrange interpolation method 
inline int summation(LL n, int k) {
    int sum = 0;
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
    n = mod(n, (LL)MOD);
    LL ans = 0;
    int store = 1, temp;
    // Lagrange interpolation pre-computation
    for(int j = 1; j < vals.size(); ++j) {
        store = mod((LL)store * mod_neg(n-j, (LL)MOD), (LL)MOD);
        store = mod((LL)store * invp2[j], (LL)MOD);
    }
    for(int i = 0; i < vals.size(); ++i) {
        ans += mod((LL)vals[i] * store, (LL)MOD);
        temp = mod(mod_neg(n - i, (LL)MOD) * mod_inverse(mod_neg(n - (i + 1), (LL)MOD), (LL)MOD), (LL)MOD);
        store = mod((LL)store * temp, (LL)MOD);
        temp = mod((LL)mod_neg(i - ((int)vals.size() - 1), MOD) * invp[i + 1], (LL)MOD);
        store = mod((LL)store * temp, (LL)MOD);
    }
    return ans % MOD;
}



//Summation(i^k), when k is small in O(k) using Bernoulli numbers
//pre-computation takes O(k^2)
const int MAX  = 1e3 + 3;
const int MOD  = 1e9 + 7;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}
template<typename T> T add(T a, T b, T c){T x=a+b;return (x>=c ? x-c : x);}
template<typename T> T mod_neg(T a, T b) {a=mod(a, b);if(a<0){a+=b;}return a;}
template<typename T> T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}
template<typename T> T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T> T mod_inverse(T a, T n){T x,y;T d = extended_euclid(a, n, x, y);return (d>1?-1:mod_neg(x,n));}

int invp[MAX];
int S[MAX][MAX];

void generate() {
    for(int i = 0; i < MAX; ++i) {
        invp[i] = mod_inverse(i, MOD);
    }
    S[0][0] = 1;
    for (int i = 1; i < MAX; ++i) {
        S[i][0] = 0;
        for (int j = 1; j <= i; ++j) {
            S[i][j] = mod((LL)S[i - 1][j] * j, (LL)MOD);
            S[i][j] = add(S[i][j], S[i-1][j-1], MOD);
        }
    }
    for(int i = 1; i < MAX; ++i) {
        for(int j = 1; j <= i; ++j) {
            S[i][j] = mod((LL)S[i][j] * invp[j + 1], (LL)MOD);
        }
    }
}
 
int solve_bernoulli(LL n, int k) {
    n = mod(n, (LL)MOD);
    if (k == 0) {
        return n;
    }
    int p = 1;
    LL res = 0;
    for (int j = 0; j <= k; ++j) {
        p = mod((LL)p * mod_neg(n + 1 - j, (LL)MOD), (LL)MOD);
        res += mod((LL)S[k][j] * p, (LL)MOD);
    }
    return mod(res, (LL)MOD);
}