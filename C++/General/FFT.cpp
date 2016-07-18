//Implementation of FFT (Taken from https://github.com/jaehyunp/stanfordacm/blob/master/code/FFT.cc)

//Maximum size of polynomial
const int MAX = 10004; 
const int LIM = 16;         //equal ceil(log2(MAX))
const double PI = acos(-1.0);
 
//Complex class: Quite faster than in-built C++ library as it uses only functions required 
class cmplx {
private:
    double x, y;
public:
    cmplx () {
        x = 0.0, y = 0.0;
    }
    cmplx (double a) {
        x = a, y = 0.0;
    }
    cmplx (double a, double b) {
        x = a, y = b;
    }
    friend ostream &operator << (ostream &output, const cmplx& a) {
        if (a.y >= 0) {
            output << a.x << "+" << a.y << "i\n"; 
        }
        else {
            output << a.x << a.y << "i\n";
        }
        return output;
    }
    friend istream &operator >> (istream &input, cmplx& a) {
        input >> a.x >> a.y;
        return input;
    }
    double get_real() {
        return this->x;
    }
    double get_img() {
        return this->y;
    }
    double norm() {
        return this->x * this->x + this->y * this->y;
    }
    double abs() {
        return sqrt(this->x * this->x + this->y * this->y);
    }
    double arg() {
        return atan2(this->y, this->x) * 180.0 / PI;
    }
    cmplx conj () {
        return cmplx(this->x, -(this->y));
    }
    cmplx operator = (const cmplx& a) {
        this->x = a.x;
        this->y = a.y;
        return *this;
    }
    cmplx operator + (const cmplx& b) {
        return cmplx(this->x + b.x, this->y + b.y);
    }
    cmplx operator - (const cmplx& b) {
        return cmplx(this->x - b.x, this->y - b.y);
    }
    cmplx operator * (const double& num) {
        return cmplx(this->x * num, this->y * num);
    }
    cmplx operator * (const cmplx& b) {
        return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y);
    }
    cmplx operator / (const double& num) {
        return cmplx(this->x / num, this->y / num);
    }
    cmplx operator / (const cmplx& b) {
        cmplx temp(b.x, -b.y);
        cmplx n = (*this) * temp;
        double d = b.x * b.x + b.y * b.y;
        cmplx res = n / d;
        return res;
    }
    cmplx operator += (const cmplx& a) {
        this->x += a.x;
        this->y += a.y;
        return *this;
    }
    cmplx operator -= (const cmplx& a) {
        this->x -= a.x;
        this->y -= a.y;
        return *this;
    }
    cmplx operator *= (const double& a) {
        cmplx temp = (*this) * a;
        this->x = temp.x;
        this->y = temp.y;
        return *this;
    }
    cmplx operator *= (const cmplx& a) {
        cmplx temp = (*this) * a;
        this->x = temp.x;
        this->y = temp.y;
        return *this;
    }
    cmplx operator /= (const double& a) {
        cmplx temp = (*this) / a;
        this->x = temp.x;
        this->y = temp.y;
        return *this;
    }
    cmplx operator /= (const cmplx& a) {
        cmplx temp = (*this) / a;
        this->x = temp.x;
        this->y = temp.y;
        return *this;   
    }
};
 
typedef long long LL;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<cmplx> VC;
 
double a[MAX], b[MAX];
int p2[LIM];
 
void init() {
    for(int i=0; i<LIM; ++i) p2[i]=1<<i;
}

struct FFT {
    VC A;
    int n, L;
    cmplx ONE, ZERO;
 
    FFT() {
        ONE = cmplx(1.0, 0.0);
        ZERO = cmplx(0.0, 0.0);
        init();
    }
    
    int ReverseBits(int k) {
        int ret = 0;
        for (int i = 0; i < L; i++) {
            ret = (ret << 1) | (k & 1);
            k >>= 1;
        }
        return ret;
    }
 
    void BitReverseCopy(VC a) {
        for (n = 1, L = 0; n < a.size(); n <<= 1, L++) ;
        A.resize(n);
        for (int k = 0; k < n; k++) 
            A[ReverseBits(k)] = a[k];
    }
  
    VC DFT(VC a, bool inverse) {
        BitReverseCopy(a);
        for (int s = 1; s <= L; s++) {
            int m = p2[s];
            cmplx wm(cos(2.0 * PI / m), sin(2.0 * PI / m));
            if (inverse) {
                wm = ONE / wm;
            }
            for (int k = 0; k < n; k += m) {
                cmplx w = ONE;
                for (int j = 0; j < m/2; j++) {
                    cmplx t = w * A[k + j + m/2];
                    cmplx u = A[k + j];
                    A[k + j] = u + t;
                    A[k + j + m/2] = u - t;
                    w = w * wm;
                }
            }
        }
        if (inverse) {
            for (int i = 0; i < n; i++) A[i] /= n;
        }
        return A;
    }
 
    // c[k] = sum_{i=0}^k a[i] b[k-i]
    VD Convolution(double *a, double *b, int sa, int sb) {
        int L = 1;
        while (p2[L] < sa) L++;
        while (p2[L] < sb) L++;
        int n = p2[L+1];
        VC aa, bb;
        for (size_t i = 0; i < sa; ++i) aa.push_back(cmplx(a[i], 0));
        for (size_t i = sa; i < n; ++i) aa.push_back(ZERO);
        for (size_t i = 0; i < sb; ++i) bb.push_back(cmplx(b[i], 0));
        for (size_t i = sb; i < n; ++i) bb.push_back(ZERO);
        VC AA = DFT(aa, false);
        VC BB = DFT(bb, false);
        VC CC;
        for (size_t i = 0; i < AA.size(); i++) CC.push_back(AA[i] * BB[i]);
        VC cc = DFT(CC, true);
        VD c;
        n = sa + sb - 1;
        for (int i = 0; i < n; i++) c.push_back(cc[i].get_real());
        return c;
    }
 
    VL Multiply(double *a, double *b, int n, int m) {
        VD res = Convolution(a, b, n, m);
        VL ans;
        for(int i = 0; i < res.size(); ++i) {
            LL x = res[i] + 0.5;
            ans.push_back(x);
        }
        return ans;
    }
};