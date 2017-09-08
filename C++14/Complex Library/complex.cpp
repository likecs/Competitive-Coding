//Implementation of Complex library with operator overloading

#include <bits/stdc++.h>
using namespace std;

//Quite faster than inbuilt-complex C++ library as contains only the functions required
template<typename T> class cmplx {
private:
	T x, y;
public:
	cmplx () : x(0.0), y(0.0) {}
	cmplx (T a) : x(a), y(0.0) {}
	cmplx (T a, T b) : x(a), y(b) {}
	friend ostream &operator << (ostream &output, const cmplx& a) {
		if (a.y >= 0) output << a.x << "+" << a.y << "i\n";
		else output << a.x << a.y << "i\n";
		return output;
	}
	friend istream &operator >> (istream &input, cmplx& a) {
		input >> a.x >> a.y;
		return input;
	}
	T get_real() { return this->x; }
	T get_img() { return this->y; }
	T norm() { return this->x * this->x + this->y * this->y; }
	T abs() { return sqrt(this->x * this->x + this->y * this->y); }
	T arg() { return atan2(this->y, this->x) * 180.0 / M_PI; }
	cmplx conj () { return cmplx(this->x, -(this->y)); }
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
	cmplx operator * (const T& num) {
		return cmplx(this->x * num, this->y * num);
	}
	cmplx operator * (const cmplx& b) {
		return cmplx(this->x * b.x - this->y * b.y, this->y * b.x + this->x * b.y);
	}
	cmplx operator / (const T& num) {
		return cmplx(this->x / num, this->y / num);
	}
	cmplx operator / (const cmplx& b) {
		cmplx temp(b.x, -b.y);
		cmplx n = (*this) * temp;
		T d = b.x * b.x + b.y * b.y;
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
	cmplx operator *= (const T& a) {
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
	cmplx operator /= (const T& a) {
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

//Sample program to use above library
int main() {
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	cmplx<double> a, b, c;

	cin >> a >> b;
	cout << a.get_real() << " " << a.get_img() << "\n";
	cout << a;
	cout << b;

	cout << a+b;
	cout << a-b;
	cout << a*b;
	cout << a/b;

	cout << b.abs() << "\n";
	cout << b.norm() << "\n";
	cout << b.arg() << "\n";
	cout << a.conj();

	c = a;
	cout << c;
	c += b;
	cout << c;
	c -= b;
	cout << c;
	c *= b;
	cout << c;
	c /= b;
	cout << c;
	c *= 2.0;
	cout << c;
	c /= 2.5;
	cout << c;
	return 0;
}