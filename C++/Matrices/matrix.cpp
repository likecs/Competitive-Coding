typedef long long LL;
typedef vector< vector<int> > matrix;
const LL MOD = 10;

template<typename T> T mod(T a, T b) {return (a<b ? a : a%b);}

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
	while (k) {
		if (k&1) {
			x = multiply(x, y);
		}
		y = multiply(y, y);
		k >>= 1;
	}
	return x;
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