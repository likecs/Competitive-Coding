//Matrix library implementations (In modular arithemetic terms)
#include <bits/stdc++.h>
using namespace std;

const int SZ  = 102;			//size of matrix
const int LN  = 32;				//equals ceil(log2(n)), where n is maximum power to which matrix is raised
const int MOD = 1e9 + 7;

int N;							//size of matrix as given in input

template <typename T> struct Matrix {
	T data[SZ][SZ];
	long long UP;
	Matrix<T> () {
		init_identity();
		UP = (long long)MOD * MOD;
	}
	Matrix<T> (T base[SZ][SZ]) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				data[i][j] = base[i][j];
			}
		}
	}
	//Complexity: O(n^2)
	Matrix<T> operator =(const Matrix<T> &other) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				this->data[i][j] = other.data[i][j];
			}
		}
		return *this;
	}
	//Complexity: O(n^2)
	Matrix<T> operator +(const Matrix<T> &other) const {
		Matrix res;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				res[i][j] = data[i][j] + other[i][j];
				if (res[i][j] >= MOD) res[i][j] -= MOD;
			}
		}
		return res;
	}
	//Complexity: O(n^2)
	Matrix<T> operator -(const Matrix<T> &other) const {
		Matrix res;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				res[i][j] = data[i][j] - other[i][j];
				if (res[i][j] < 0) res[i][j] += MOD;
			}
		}
		return res;
	}
	//Complexity: O(n^3)
	Matrix<T> operator *(const Matrix<T> &other) const {
		Matrix res;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				long long val = 0;
				for(int k = 0; k < N; ++k) {
					val = val + 1ll*data[i][k]*other[k][j];
					if (val >= UP) val -= UP;
				}
				res[i][j] = (val >= MOD ? val % MOD : val);
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
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				data[i][j] = 0;
			}
		}
	}
	void init_identity() {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				data[i][j] = (i == j);
			}
		}
	}
	void print() {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
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
	for(int i = 2; i < LN; ++i) {
		pre[i] = pre[i-1] * pre[i-1];
	}
}

//Complexity: O(m^3 log(n)), where m = size of matrix
Matrix<int> power(Matrix<int> &a, long long n) {
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
	N = 2;
	int fib[SZ][SZ] = {{1, 1}, {1, 0}};
	base = fib;
	init(base);
	Matrix<int> ans = power(base, 3);
	ans.print();

	return 0;
}