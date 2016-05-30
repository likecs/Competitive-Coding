//Polard-Rho brent Factorisation method in C++
 
typedef long long LL;

template <typename T>T mod(T a, T b) {return (a < b ? a : a % b);}
LL mulmod(LL a,LL b, LL m){LL q=(LL)(((long double)a*(long double)b)/(long double)m);LL r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template <typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mod(x*p,m);p=mod(p*p,m);n>>=1;}return x;}

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

LL brent(LL n) {
    if (n%2==0) return 2;
    LL x, y, c, m, g, r, q, k, ys, w;
    y = 1LL*rand()%(n-1) + 1LL;
    c = 1LL*rand()%(n-1) + 1LL;
    m = 1LL*rand()%(n-1) + 1LL;
    g = r = q = 1LL;
    while (g==1) {
        x = y;
        for (LL i=0; i<r; ++i) y = (mulmod(y,y,n) + c)%n;
        k = 0; 
        while (k<r && g==1) {
            ys = y;
            w = min(m, r-k);
            for (int i=0; i<w; ++i) {
                y = (mulmod(y,y,n) + c)%n;
                q = mulmod(q,(abs(x-y))%n,n);
            }
            g = __gcd(q, n);
            k += m;
        }
        r=r*2;
    }
    if (g==n) {
        while (true) {
            ys = (mulmod(ys,ys,n) + c)%n;
            g = __gcd(abs(x-ys), n);
            if (g>1) break;
        }
    }
    return g;
}

//Sample program to use above algorithm

vector<LL> factors;

int main() {
    int count;
    LL n;
    while (true) {
        scanf("%lld", &n);
        if (n==0) break;
        if (n==1) { 
            printf("1\n"); 
            continue;
        }
        queue<LL> q;
        q.push(n);
        while (!q.empty())
        {
            LL l = q.front();
            q.pop();
            if (rabin_miller(l)) {
                factors.push_back(l);
                continue;
            }
            LL d = brent(l);
            if (d==l) q.push(l);
            else {
                q.push(d);
                q.push(l/d);
            }
        }
        sort(factors.begin(), factors.end());
        for (int i=0, j; i<factors.size(); ++i) {
            printf("%lld^", factors[i]);
            count = 1;
            j = i+1;
            while (factors[i]==factors[j]) {
                count++; 
                j++;
            }
            i = j-1;
            printf("%d ", count);
        }
        printf("\n");
        factors.clear();
    }
    return 0;
}