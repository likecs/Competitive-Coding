typedef vector<int> VI;
typedef pair<int,int> PII;

// return a % b (positive value)
int mod_neg(int a, int b) {return ((a%b)+b)%b;}

template<typename T> T gcd(T a, T b){return __gcd(a, b);}

template<typename T> T lcm(T a, T b){return (a*(b/gcd(a,b)));}

//Extended Euclid algorithm
//returns d = gcd(a,b)
//finds any x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
	int xx = y = 0;
	int yy = x = 1;
	while (b) {
		int q = a/b;
		int t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

// finds all solutions to ax = b (mod n)
VI modular_linear_equation_solver(int a, int b, int n) {
	int x, y;
	VI solutions;
	int d = extended_euclid(a, n, x, y);
	if (!(b%d)) {
		x = mod_neg (x*(b/d), n);
		for (int i = 0; i < d; i++)
			solutions.push_back(mod_neg(x + i*(n/d), n));
	}
	return solutions;
}

// Find modulo inverse of a w.r.t. n (for any general number)
// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
	int x, y;
	int d = extended_euclid(a, n, x, y);
	if (d > 1)
		return -1;
	return mod_neg(x,n);
}

// computes x and y such that ax + by = c
// on failure, x = y = -1
void linear_diophantine(int a, int b, int c, int &x, int &y) {
	int d = gcd(a,b);
	if (c%d) x = y = -1;
	else {
		x = c/d * mod_inverse(a/d, b/d);
		y = (c-a*x)/b;
	}
}

//check if ax+by=d has a solution such that x>=0 and y>=0
//find one random solution and use linear equation and genral solution to get the result
int extended_euclid(int a, int b, int &x, int &y) {
	int xx = y = 0;
	int yy = x = 1;
	while (b) {
		int q = a/b;
		int t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

bool check(int a, int b, int n) {
	int c = extended_euclid(a, b, x, y);
	if (n%c != 0) return false;
    else {
        x *= n/c;
        y *= n/c;
        double t1 = ceil((-1.0 * x * c)/b);
        double t2 = floor((1.0 * y * c)/a);
        if (t2 >= t1) return true;
        else return false;
    }
}

// extended euclid algo for mod inverse is much faster than that of fermat algo
// code by LAKSMAN(spoj)
inline int modInverse(int a, int n) {
	int i = n, v = 0, d = 1;
	while (a>0) {
		int t = i/a, x = a;
		a = i % x;
		i = x;
		x = d;
		d = v - t*x;
		v = x;
	}
	v %= n;
	if (v<0) v = (v+n);
	return v;
}