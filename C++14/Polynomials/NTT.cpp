//implmentations of NTT using template-meta programming

//helper functions
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

int power(long long e, long long n, int m) {
	int x = 1, p = e % m;
	while(n) {
		if(n & 1) x = mul(x, p, m);
		p = mul(p, p, m);
		n >>= 1;
	}
	return x;
}

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

template<typename T> T mod_inverse(T a, T n) {
	T x, y, z = 0;
	T d = extended_euclid(a, n, x, y);
	return (d > 1 ? -1 : mod_neg(x, z, n));
}

//NTT implementation below
template<typename T, T prime, T root, int logn> struct NTT {
	int n, L, MAX, last, *rev;
	T *omega_powers, root_inv;

	NTT() {
		last = -1;
		MAX = (1 << logn);
		rev = new int[MAX];
		omega_powers = new T[MAX];
		root_inv = mod_inverse(root, prime);
	}

	~NTT() {
		delete rev;
		delete omega_powers;
	}

	void ReverseBits() {
		if (last != n) {
			for (int i=1, j=0; i<n; ++i) {
				int bit = n >> 1;
				for (; j>=bit; bit>>=1) j -= bit;
				j += bit;
				rev[i] = j;
			}
		}
	}

	void DFT(vector<T> &A, bool inverse = false) {
		for(int i = 0; i < n; ++i)
			if (rev[i] > i) swap(A[i], A[rev[i]]);
		for (int s = 1; s <= L; s++) {
			int m = 1 << s, half = m / 2;
			T wm = inverse ? root_inv : root;
			for(int i = m; i < n; i <<= 1) wm = mul(wm , wm, prime);
			omega_powers[0] = 1;
			for(int k = 1; k < half; ++k) {
				omega_powers[k] = mul(omega_powers[k-1], wm, prime);
			}
			for (int k = 0; k < n; k += m) {
				for (int j = 0; j < half; j++) {
					T v = mul(omega_powers[j] , A[k + j + half], prime);
					T u = A[k + j];
					A[k + j] = add(u, v, prime);
					A[k + j + half] = mod_neg(u, v, prime);
				}
			}
		}
		if (inverse) {
			T n_inv = mod_inverse(n, prime);
			for (int i = 0; i < n; i++) A[i] = mul(A[i], n_inv, prime);
		}
	}

	// c[k] = sum_{i=0}^k a[i] b[k-i] mod prime
	vector<T> Multiply(const vector<T> &a, const vector<T> &b) {
		L = 0;
		int sa = a.size(), sb = b.size();
		while ((1 << L) < (sa + sb - 1)) L++;
		n = 1 << L;
		ReverseBits();
		vector<T> aa(n, 0), bb(n, 0), cc;
		for (int i = 0; i < sa; ++i) aa[i] = a[i];
		for (int i = 0; i < sb; ++i) bb[i] = b[i];
		DFT(aa, false); DFT(bb, false);
		for (int i = 0; i < n; ++i) cc.push_back(mul(aa[i], bb[i], prime));
		DFT(cc, true);
		vector<T> ans;
		n = sa + sb - 1;
		for (int i = 0; i < n; ++i) ans.push_back(cc[i]);
		return ans;
	}
};

//prime = 2^k * m + 1
const int prime = 786433;		//equals prime
const int root = 10;			//root^size = 1 mod(prime)
const int size = 1 << 18;		//2^k

//usage example
NTT<int, prime, root, 18> ntt;

// Usage fftMod<int, 998244353, -1, 23> // g = 3
//       fftMod<int, 1004535809, -1, 19> fft; // g = 3
//       fftMod<int, 469762049, -1, 26> // g = 3
//       fftMod<li, 10000093151233, -1, 26> // g = 5
//       fftMod<li, 1000000523862017, -1, 26> // g = 3
//       fftMod<li, 1000000000949747713, -1, 26> // g = 2
//       fftMod<li, -1, li(1e13), 20>