//Implementation of FFT (Taken from https://github.com/jaehyunp/stanfordacm/blob/master/code/FFT.cc)

//Maximum size of polynomial
const int MAX = 1e5 + 5; 

//Complex class: Quite faster than in-built C++ library as it uses only functions required 
class cmplx {
private:
	double x, y;
public:
	cmplx () : x(0.0), y(0.0) {}
	cmplx (double a) : x(a), y(0.0) {}
	cmplx (double a, double b) : x(a), y(b) {}
	double get_real() { return this->x; }
	double get_img() { return this->y; }
	cmplx conj() { return cmplx(this->x, -(this->y)); }
	cmplx operator = (const cmplx& a) { this->x = a.x; this->y = a.y; return *this; }
	cmplx operator + (const cmplx& b) { return cmplx(this->x + b.x, this->y + b.y); }
	cmplx operator - (const cmplx& b) { return cmplx(this->x - b.x, this->y - b.y); }
	cmplx operator * (const double& num) { return cmplx(this->x * num, this->y * num); }
	cmplx operator / (const double& num) { return cmplx(this->x / num, this->y / num); }
	cmplx operator * (const cmplx& b) { 
		return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y); 
	}
	cmplx operator / (const cmplx& b) {
		cmplx temp(b.x, -b.y); cmplx n = (*this) * temp;
		return n / (b.x * b.x + b.y * b.y);
	}
};
 
typedef long long LL;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<cmplx> VC;

struct FFT {
	VC A;
	int n, L, *rev;
	cmplx ONE, ZERO;
	cmplx *omega_powers;

	FFT() {
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
		for(int j = 0; j < n; ++j) {
			int k = j; rev[j] = 0;
			for (int i = 0; i < L; i++) {
				rev[j] = (rev[j] << 1) | (k & 1);
				k >>= 1;
			}
		}
	}
 
	void BitReverseCopy(VC a) {
		A.resize(n);
		for (int k = 0; k < n; k++) 
			A[rev[k]] = a[k];
	}
  
	VC DFT(VC a, bool inverse) {
		BitReverseCopy(a);
		for (int s = 1; s <= L; s++) {
			int m = 1 << s, half = m / 2;
			cmplx wm(cos(2.0 * M_PI / m), sin(2.0 * M_PI / m));
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
		return A;
	}
 
	// c[k] = sum_{i=0}^k a[i] b[k-i]
	VL Multiply(const VL &a, const VL &b) {
		L = 0;
		int sa = a.size(), sb = b.size();
		while ((1 << L) < (sa + sb - 1)) L++; 
		n = 1 << L;
		ReverseBits();
		VC aa(n, ZERO), bb(n, ZERO), cc;
		for (int i = 0; i < sa; ++i) aa[i] = cmplx(a[i], 0);
		for (int i = 0; i < sb; ++i) bb[i] = cmplx(b[i], 0);
		VC AA = DFT(aa, false), BB = DFT(bb, false), CC;
		for (int i = 0; i < n; ++i) CC.push_back(AA[i] * BB[i]);
		cc = DFT(CC, true);
		VL ans;
		n = sa + sb - 1;
		for (int i = 0; i < n; ++i) {
			LL x = cc[i].get_real() + 0.5;
			ans.push_back(x);
		}
		return ans;
	}
};