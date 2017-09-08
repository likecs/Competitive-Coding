//General Modulo FFT implementation
//Quite fast as it uses just 4 FFT calls
//Just call preCompute() in main() before usage

const int MAX = 1e5 + 5;			//Size of Polynomial
const int MOD = 1e9 + 7;

namespace FFTMOD {
const double PI = acos(-1);
const int LIM = 1 << 18;			//2 * 2^ceil(log2(POLY_SIZE))

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

typedef cmplx<double> COMPLEX;		//change this to long double in case of error

COMPLEX W[LIM], invW[LIM];

void preCompute() {
	for(int i = 0; i < LIM/2; ++i) {
		//change this to long double in case of error
		double ang = 2 * PI * i / LIM;
		double _cos = cos(ang), _sin = sin(ang);
		W[i] = COMPLEX(_cos, _sin);
		invW[i] = COMPLEX(_cos, -_sin);
	}
}

void FFT(COMPLEX *a, int n, bool invert = false) {
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1) {
		for(int i =	0; i < n; i += len) {
			int ind  = 0, add = LIM/len;
			for(int j = 0; j < len/2; ++j) {
				COMPLEX u = a[i+j];
				COMPLEX v = a[i+j+len/2] * (invert ? invW[ind] : W[ind]);
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				ind += add;
			}
		}
	}
	if (invert) for(int i = 0; i < n; ++i) a[i] = a[i]/n;
}

COMPLEX f[LIM], g[LIM], ff[LIM], gg[LIM];

// c[k] = sum_{i=0}^k a[i] b[k-i] % MOD
vector<int> multiply(vector<int> &A, vector<int> &B) {
	int n1 = A.size(), n2 = B.size();
	int final_size = n1 + n2 - 1, N = 1;
	while(N < final_size) N <<= 1;
	vector<int> C(final_size, 0);
	int SQRTMOD = (int)sqrt(MOD) + 10;
	for(int i = 0; i < N; ++i) f[i] = COMPLEX(), g[i] = COMPLEX();
	for(int i = 0; i < n1; ++i) f[i] = COMPLEX(A[i]%SQRTMOD, A[i]/SQRTMOD);
	for(int i = 0; i < n2; ++i) g[i] = COMPLEX(B[i]%SQRTMOD, B[i]/SQRTMOD);
	FFT(f, N), FFT(g, N);
	COMPLEX X, Y, a1, a2, b1, b2;
	for(int i = 0; i < N; ++i) {
		X = f[i], Y = f[(N-i)%N].conj();
		a1 = (X + Y) * COMPLEX(0.5, 0);
		a2 = (X - Y) * COMPLEX(0, -0.5);
		X = g[i], Y = g[(N-i)%N].conj();
		b1 = (X + Y) * COMPLEX(0.5, 0);
		b2 = (X - Y) * COMPLEX(0, -0.5);
		ff[i] = a1 * b1 + a2 * b2 * COMPLEX(0, 1);
		gg[i] = a1 * b2 + a2 * b1;
	}
	FFT(ff, N, 1), FFT(gg, N, 1);
	for(int i = 0; i < final_size; ++i) {
		long long x = (LL)(ff[i].get_real() + 0.5);
		long long y = (LL)(ff[i].get_img() + 0.5) % MOD;
		long long z = (LL)(gg[i].get_real() + 0.5);
		C[i] = (x + (y * SQRTMOD + z) % MOD * SQRTMOD) % MOD;
	}
	return C;
}
};
using namespace FFTMOD;
