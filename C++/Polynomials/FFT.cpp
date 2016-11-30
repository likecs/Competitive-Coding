//Implementation of FFT (Taken from https://github.com/jaehyunp/stanfordacm/blob/master/code/FFT.cc)

typedef long long LL;
//Twice the maximum size of polynomial
const int MAX = 2e5 + 5; 

//Complex class: Quite faster than in-built C++ library as it uses only functions required 
class cmplx {
private:
	long double x, y;
public:
	cmplx () : x(0.0), y(0.0) {}
	cmplx (long double a) : x(a), y(0.0) {}
	cmplx (long double a, long double b) : x(a), y(b) {}
	long double get_real() { return this->x; }
	long double get_img() { return this->y; }
	cmplx conj() { return cmplx(this->x, -(this->y)); }
	cmplx operator = (const cmplx& a) { this->x = a.x; this->y = a.y; return *this; }
	cmplx operator + (const cmplx& b) { return cmplx(this->x + b.x, this->y + b.y); }
	cmplx operator - (const cmplx& b) { return cmplx(this->x - b.x, this->y - b.y); }
	cmplx operator * (const long double& num) { return cmplx(this->x * num, this->y * num); }
	cmplx operator / (const long double& num) { return cmplx(this->x / num, this->y / num); }
	cmplx operator * (const cmplx& b) { 
		return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y); 
	}
	cmplx operator / (const cmplx& b) {
		cmplx temp(b.x, -b.y); cmplx n = (*this) * temp;
		return n / (b.x * b.x + b.y * b.y);
	}
};
 
struct FFT {
	long double PI;
	int n, L, *rev;
	cmplx ONE, ZERO;
	cmplx *omega_powers;

	FFT() {
		PI = acos(-1.0);
		ONE = cmplx(1.0, 0.0);
		ZERO = cmplx(0.0, 0.0);
		int req = 1 << (32 - __builtin_clz(MAX));
		rev = new int[req];
		omega_powers = new cmplx[req];
	}

	~FFT() {
		delete rev;
		delete omega_powers;
	}

	void ReverseBits() {
		for (int i=1, j=0; i<n; ++i) {
			int bit = n >> 1;
			for (; j>=bit; bit>>=1) j -= bit;
			j += bit;
			rev[i] = j;
		}
	}
 
	void DFT(vector<cmplx> &A, bool inverse = false) {
		for(int i = 0; i < n; ++i) 
			if (rev[i] > i) swap(A[i], A[rev[i]]);
		for (int s = 1; s <= L; s++) {
			int m = 1 << s, half = m / 2;
			cmplx wm(cosl(2.0 * PI / m), sinl(2.0 * PI / m));
			if (inverse) wm = ONE / wm;
			omega_powers[0] = ONE;
			for(int k = 1; k < half; ++k) {
				omega_powers[k] = omega_powers[k-1] * wm;
			}
			for (int k = 0; k < n; k += m) {
				for (int j = 0; j < half; j++) {
					cmplx t = omega_powers[j] * A[k + j + half];
					cmplx u = A[k + j];
					A[k + j] = u + t;
					A[k + j + half] = u - t;
				}
			}
		}
		if (inverse) {
			for (int i = 0; i < n; i++) A[i] = A[i] / n;
		}
	}
 
	// c[k] = sum_{i=0}^k a[i] b[k-i]
	vector<LL> Multiply(const vector<LL> &a, const vector<LL> &b) {
		L = 0;
		int sa = a.size(), sb = b.size(), sc = sa + sb - 1;
		while ((1 << L) < sc) L++; 
		n = 1 << L;
		ReverseBits();
		vector<cmplx> aa(n, ZERO), bb(n, ZERO), cc;
		for (int i = 0; i < sa; ++i) aa[i] = cmplx(a[i], 0);
		for (int i = 0; i < sb; ++i) bb[i] = cmplx(b[i], 0);
		DFT(aa, false); DFT(bb, false);
		for (int i = 0; i < n; ++i) cc.push_back(aa[i] * bb[i]);
		DFT(cc, true);
		vector<LL> ans(sc);
		for (int i = 0; i < sc; ++i) ans[i] = cc[i].get_real() + 0.5;
		return ans;
	}
};