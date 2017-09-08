//Extended Eulclid Algorithms and gcd calculations
//Mod-Inverse for any number using extended euclid algorithms

template<typename T> T gcd(T a, T b) {
	return (b ? __gcd(a,b): a);
}

template<typename T> T lcm(T a, T b) {
	return (a * (b / gcd(a,b)));
}

int add(int a, int b, int c) {
	int res = a + b;
	return (res >= c ? res - c : res);
}

int mod_neg(int a, int b, int c) {
	int res; if(abs(a-b) < c) res = a - b;
	else res = (a-b) % c;
	return (res < 0 ? res + c : res);
}

int mul(int a, int b, int c) {
	long long res = (long long)a * b;
	return (res >= c ? res % c : res);
}

//Extended Euclid algorithm
//returns d = gcd(a,b)
//finds any x,y such that d = ax + by
//Complexity : O(log(max(a, b)))
template<typename T> T extended_euclid(T a, T b, T &x, T &y) {
	T xx = 0, yy = 1; y = 0; x = 1;
	while(b) {
		T q = a / b, t = b;
		b = a % b; a = t;
		t = xx; xx = x - q * xx;
		x = t; t = yy;
		yy = y - q * yy; y = t;
	}
	return a;
}

// finds all solutions to ax = b (mod n)
vector<int> modular_linear_equation_solver(int a, int b, int n) {
	int x, y;
	vector<int> solutions;
	int d = extended_euclid(a, n, x, y);
	if (!(b%d)) {
		x = mod_neg(x*(b/d), 0, n);
		for (int i = 0; i < d; i++)
			solutions.push_back(mod_neg(x + i*(n/d), 0, n));
	}
	return solutions;
}

//Find modulo inverse of a w.r.t. n (for any general number)
//computes b such that ab = 1 (mod n), returns -1 on failure
//Complexity : O(log(n))
//HANDLE THE CASE OF N = 1 SEPARATELY, gives wrong results here
template<typename T> T mod_inverse(T a, T n) {
	T x, y, z = 0;
	T d = extended_euclid(a, n, x, y);
	return (d > 1 ? -1 : mod_neg(x, z, n));
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
template<typename T> T extended_euclid(T a, T b, T &x, T &y) {
	T xx = 0, yy = 1; y = 0; x = 1;
	while(b) {
		T q = a / b, t = b;
		b = a % b; a = t;
		t = xx; xx = x - q * xx;
		x = t; t = yy;
		yy = y - q * yy; y = t;
	}
	return a;
}

bool check(int a, int b, int n) {
	long long x, y;
	long long c = extended_euclid((long long)a, (long long)b, x, y);
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