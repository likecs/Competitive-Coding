//faster FFT implementation

//use multiply(a, b) to multiply two polynomials a and b
//the higher power coefficients have the lower index in the vectors
//a= [ a(n-1) , a(n-2) , a(n-3) , ............a(0) ]
//the multiply function will return a vector of long long
//If mod is different just change the value of prime

const int prime = 13313;

namespace FFT {
	//taken from https://www.codechef.com/viewsolution/11939789
	const int N = 20;
	const int MAXN = (1<<N);
	const double PI = acos(-1.0);
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
	cmplx w[MAXN];
	cmplx f1[MAXN];
	int rev[MAXN];
	void ReserveBits(int k) {
		static int rk = -1, lim;
		if(k == rk) return ;
		rk = k, lim = 1 << k;
		for(int i = 1; i <= lim; ++i) {
			int j = rev[i-1], t = k - 1;
			while(t >= 0 && ((j>>t)&1)) {
				j ^= 1 << t; --t;
			}
			if(t >= 0) {
				j ^= 1 << t; --t;
			}
			rev[i] = j;
		}
	}
	void fft(cmplx *a, int k) {
		ReserveBits(k);
		int n = 1 << k;
		for(int i = 0 ; i < n; ++i)
			if(rev[i] > i) swap(a[i], a[rev[i]]);
		for(int l = 2, m = 1; l <= n; l += l, m += m) {
			if(w[m].get_real() == 0 && w[m].get_img() == 0) {
				double angle = PI / m;
				cmplx ww(cos(angle), sin(angle));
				if(m > 1) {
					for(int j = 0; j < m; ++j) {
						if(j & 1) w[m + j] = w[(m+j)/2] * ww;
						else w[m + j] = w[(m+j)/2];
					}
				}
				else w[m] = cmplx(1, 0);
			}
			for(int i = 0; i < n; i += l) {
				for(int j = 0; j < m; ++j) {
					cmplx v = a[i + j], u = a[i + j + m] * w[m + j];
					a[i + j] = v + u;
					a[i + j + m] = v - u;
				}
			}
		}
	}
	vector<long long> multiply(const vector<long long>& a, const vector<long long>& b) {
		int k = 1;
		while((1<<k) < (a.size() + b.size())) ++k;
		int n = (1<<k);
		for(int i = 0; i < n; ++i) f1[i] = cmplx(0,0);
		for(int i = 0; i < a.size(); ++i) f1[i] = f1[i] + cmplx(a[i], 0);
		for(int i = 0; i < b.size(); ++i) f1[i] = f1[i] + cmplx(0, b[i]);
		fft(f1, k);
		for(int i = 0; i <= n/2; ++i) {
			cmplx p = f1[i] + f1[(n-i)%n].conj();
			cmplx _q = f1[(n-i)%n] - f1[i].conj();
			cmplx q(_q.get_img(), _q.get_real());
			f1[i] = (p * q) * 0.25;
			if(i > 0) f1[(n - i)] = f1[i].conj();
		}
		for(int i = 0; i < n; ++i) f1[i] = f1[i].conj();
		fft(f1, k);
		vector<long long> ans(a.size() + b.size() - 1);
		for(int i = 0; i < ans.size(); ++i) {
			ans[i] = (long long) (f1[i].get_real() / n + 0.5);
		}
		return ans;
	}
};