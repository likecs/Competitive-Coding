typedef long long LL;
typedef vector< vector<int> > matrix;
const LL MOD = 10;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}

matrix powers[32];

//Initailise matrix to zero
matrix zero(int n) {
	matrix temp(n, vector<int>(n, 0));
	return temp;
}

//Initialise matrix to identity
matrix identity(int n) {
	matrix temp(n, vector<int>(n, 0));
	for(int i=0; i<n; ++i) temp[i][i] = 1;
	return temp;
}

//Complexity: O(n^2)
matrix add(const matrix a, const matrix b) {
	int n = a.size(), m = a[0].size();
	matrix temp(n, vector<int>(m));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			temp[i][j] = a[i][j] + b[i][j];
		}
	}
	return temp;
}

//Complexity: O(n^2)
matrix subtract(const matrix a, const matrix b) {
	int n = a.size(), m = a[0].size();
	matrix temp(n, vector<int>(m));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			temp[i][j] = a[i][j] - b[i][j];
		}
	}
	return temp;
}

//Complexity: O(n^3)
matrix multiply(const matrix a, const matrix b) {
	int n1 = a.size(), m1 = a[0].size();
	int n2 = b.size(), m2 = b[0].size();
	if (m1 != n2) {
		cerr<<"Matrices cannot be multiplied\n";
		exit(1);
	}
	matrix temp(n1, vector<int>(m2, 0));
	for(int i=0; i<n1; ++i) {
		for(int j=0; j<m2; ++j) {
			for(int k=0; k<m1; ++k) {
				temp[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return temp;
}

//Complexity: O(n^3)
//Multiplication in Modulo field
matrix multiply_mod(const matrix a, const matrix b) {
	int n1 = a.size(), m1 = a[0].size();
	int n2 = b.size(), m2 = b[0].size();
	if (m1 != n2) {
		cerr<<"Matrices cannot be multiplied\n";
		exit(1);
	}
	matrix temp(n1, vector<int>(m2, 0));
	for(int i=0; i<n1; ++i) {
		for(int j=0; j<m2; ++j) {
			for(int k=0; k<m1; ++k) {
				temp[i][j] = mod(temp[i][j] + (LL)a[i][k] * b[k][j], MOD);
			}
		}
	}
	return temp;
}

//Complexity; O(n^3 * log k)
matrix expo(const matrix a, int k) {
    int n = a.size();
    matrix x = identity(n), y = a;
    int cnt = 1;
    while (k) {
        if (k&1) {
            x = multiply(x, powers[cnt]);
        }
        cnt += 1;
        k >>= 1;
    }
    return x;
}

//Pre-compute all powers of 2
void pre_compute(const matrix inp) {
    int n = inp.size();
    powers[0] = identity(n);
    powers[1].resize(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            powers[1][i][j] = inp[i][j];
        }
    }
    for(int i=2; i<32; ++i) {
        powers[i] = multiply(powers[i-1], powers[i-1]);
    }
}

//Complexity: O(n^3 * log k)
//Matrix exponentation in Modulo field
matrix power(const matrix a, int k) {
	int n = a.size();
	matrix x = identity(n), y = a;
	while (k) {
		if (k&1) {
			x = multiply_mod(x, y);
		}
		y = multiply_mod(y, y);
		k >>= 1;
	}
	return x;
}

//Pre-compute all powers of 2
void pre_compute_mod(const matrix inp) {
    int n = inp.size();
    powers[0] = identity(n);
    powers[1].resize(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            powers[1][i][j] = mod((LL)inp[i][j], MOD);
        }
    }
    for(int i=2; i<32; ++i) {
        powers[i] = multiply_mod(powers[i-1], powers[i-1]);
    }
}