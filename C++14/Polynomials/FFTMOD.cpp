const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;

namespace FFTMOD {
const double PI = acos(-1);
const int BASE = 16;
const int LIM = 1 << BASE;

//Complex class: Quite faster than in-built C++ library as it uses only functions required 
template<typename T> class cmplx {
private:
	T x, y;
public:
	cmplx () : x(0.0), y(0.0) {}
	cmplx (T a) : x(a), y(0.0) {}
	cmplx (T a, T b) : x(a), y(b) {}
	T get_real() { return this->x; }
	T get_img() { return this->y; }
	cmplx conj() { return cmplx(this->x, -(this->y)); }
	cmplx operator = (const cmplx& a) { this->x = a.x; this->y = a.y; return *this; }
	cmplx operator + (const cmplx& b) { return cmplx(this->x + b.x, this->y + b.y); }
	cmplx operator - (const cmplx& b) { return cmplx(this->x - b.x, this->y - b.y); }
	cmplx operator * (const T& num) { return cmplx(this->x * num, this->y * num); }
	cmplx operator / (const T& num) { return cmplx(this->x / num, this->y / num); }
	cmplx operator * (const cmplx& b) { 
		return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y); 
	}
	cmplx operator / (const cmplx& b) {
		cmplx temp(b.x, -b.y); cmplx n = (*this) * temp;
		return n / (b.x * b.x + b.y * b.y);
	}
};

typedef cmplx<double> COMPLEX;

int revv[LIM];
COMPLEX roots[LIM];

void FFT(COMPLEX *f) {
	for(int i = 0; i < LIM; ++i) {
		if (i < revv[i]) swap(f[i], f[revv[i]]);
	}
	for (int k = 1; k < LIM; k <<= 1) {
		for (int i = 0; i < LIM; i += 2 * k) {
			for(int j = 0; j < k; ++j) {
				COMPLEX z = f[i + j + k] * roots[j + k];
				f[i + j + k] = f[i + j] - z;
				f[i + j] = f[i + j] + z;
			}
		}
	}
}

void preCompute() {
	for (int i = 1; i < LIM; ++i) {
		revv[i] = (revv[i >> 1] >> 1) + ((i & 1) << (BASE - 1));
	}
	int N = LIM >> 1;
	for(int i = 0; i < N; ++i) {
		roots[N + i] = COMPLEX(cos(2 * i * PI / LIM), sin(2 * i * PI / LIM));
	}
	for (int i = N - 1; i >= 1; --i) {
		roots[i] = roots[2 * i];
	}
}

int tmp[MAX];
COMPLEX f[LIM], g[LIM], ff[LIM], gg[LIM];

// c[k] = sum_{i=0}^k a[i] b[k-i] % MOD
vector<int> multiply(vector<int> &A, vector<int> &B) {
	int N = A.size();
	vector<int> C(N, 0);
	for(int i = 0; i < LIM; ++i) f[i] = COMPLEX();
	for(int i = 0; i < LIM; ++i) g[i] = COMPLEX();
	for(int i = 0; i < LIM; ++i) ff[i] = COMPLEX();
	for(int i = 0; i < LIM; ++i) gg[i] = COMPLEX();
	for(int i = 0; i < N; ++i) {
		f[i] = COMPLEX(A[i] & ((1<<15) - 1), A[i] >> 15);
	}
	for(int i = 0; i < N; ++i) {
		g[i] = COMPLEX(B[i] & ((1<<15) - 1), B[i] >> 15);
	}
	FFT(f), FFT(g);
	for(int i = 0; i < LIM; ++i) {
		int j = (LIM - i) & (LIM - 1);
		COMPLEX a1 = (f[i] + f[j].conj()) * COMPLEX(0.5, 0);
		COMPLEX a2 = (f[i] - f[j].conj()) * COMPLEX(0, -0.5);
		COMPLEX b1 = (g[i] + g[j].conj()) * COMPLEX(0.5, 0);
		COMPLEX b2 = (g[i] - g[j].conj()) * COMPLEX(0, -0.5);
		ff[j] = a1 * b1 + a1 * b2 * COMPLEX(0, 1);
		gg[j] = a2 * b1 + a2 * b2 * COMPLEX(0, 1);
	}
	FFT(ff), FFT(gg);
	for(int i = 0; i < N; ++i) {
		int v11 = (LL)(ff[i].get_real() / LIM + 0.5) % MOD;
		int v12 = (LL)(ff[i].get_img() / LIM + 0.5) % MOD;
		int v21 = (LL)(gg[i].get_real() / LIM + 0.5) % MOD;
		int v22 = (LL)(gg[i].get_img() / LIM + 0.5) % MOD;
		C[i] = (v11 + (v12 + v21) * (1ll<<15) + v22 * (1ll<<30)) % MOD;
	}
	return C;
}
};
using namespace FFTMOD;