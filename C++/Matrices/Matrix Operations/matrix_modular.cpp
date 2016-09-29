//Matrix library implementations (In modular arithemetic terms)
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int SZ  = 2;					//size of matrix
const int LN  = 32;					//equals ceil(log2(n)), where n is maximum power to which matrix is raised
const int MOD = 1e9 + 7;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}
template<typename T> T add(T a, T b, T c){T x=a+b;return (x>=c ? x-c : x);}
template<typename T> T mod_neg(T a, T b) {a=mod(a, b);if(a<0){a+=b;}return a;}

template <typename T> struct Matrix {
	T data[SZ][SZ];
	Matrix<T> () {
		init_identity();
	}
	Matrix<T> (T base[SZ][SZ]) {
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				data[i][j] = base[i][j];
			}
		}
	}
	//Complexity: O(n^2)
	Matrix<T> operator =(const Matrix<T> &other) {
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				this->data[i][j] = other.data[i][j];
			}
		}
		return *this;
	}
	//Complexity: O(n^2)
	Matrix<T> operator +(const Matrix<T> &other) const {
		Matrix res;
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				res[i][j] = add(data[i][j], other[i][j], MOD);
			}
		}
		return res;
	}
	//Complexity: O(n^2)
	Matrix<T> operator -(const Matrix<T> &other) const {
		Matrix res;
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				res[i][j] = mod_neg(data[i][j] - other[i][j], MOD);
			}
		}
		return res;
	}
	//Complexity: O(n^3)
	Matrix<T> operator *(const Matrix<T> &other) const {
		Matrix res;
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				res[i][j] = 0;
				for(int k=0; k<SZ; ++k) {
					res[i][j] = mod(res[i][j] + (LL)data[i][k] * other[k][j], (LL)MOD);
				}
			}
		}
		return res;
	}
	const T* operator[](int i) const {
		return data[i];
	}
	T* operator[](int i) {
		return data[i];
	}
	void init_zero() {
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				data[i][j] = 0;
			}
		}
	}
	void init_identity() {
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				data[i][j] = (i == j);
			}
		}	
	}
	void print() {
		for(int i=0; i<SZ; ++i) {
			for(int j=0; j<SZ; ++j) {
				cout << data[i][j] << " ";
			}
			cout <<"\n";
		}
	}
};

Matrix<int> base;
Matrix<int> pre[LN];

//Complexity: O(m^3 log(n)), where m = size of matrix
void init(Matrix<int> mat) {
	pre[0].init_identity();
	pre[1] = mat;
	for(int i=2; i<LN; ++i) {
		pre[i] = pre[i-1] * pre[i-1];
	}
}

//Complexity: O(m^3 log(n)), where m = size of matrix
Matrix<int> power(Matrix<int> a, LL n) {
	Matrix<int> res;
	int cnt = 1;
	while(n) {
		if (n & 1) {
			res = res * pre[cnt];
		}
		cnt += 1;
		n >>= 1;
	}
	return res;
}

//Sample usage details
int main() {
	
	//Calculates nth fibonacci number
	int fib[SZ][SZ] = {{1, 1}, {1, 0}};
	base = fib;
	init(base);
	Matrix<int> ans = power(base, 3);
	ans.print();

	return 0;
}