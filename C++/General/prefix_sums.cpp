//Prefix Sums
//Used for questions related to querying for sums in a range
//1-based indexing assumed everywhere


//1-D
//Pre-computation : Complexity O(n)
//Query : Complexity O(1)
typedef long long LL;
const int MAX = 100005;

int inp[MAX];
LL sum[MAX];

void build(int n) {
	//sum array is global, so initailised to 0 initially
	for(int i=1; i<=n; ++i) {
		sum[i] = sum[i-1] + inp[i];
	}
}

LL query(int l, int r) {
	return sum[r] - sum[l-1];
}

//2-D
//Pre-computation : Complexity O(n*m) 
//Query : Complexity O(1)
typedef long long LL;
const int MAX = 1005;

int inp[MAX][MAX];
LL sum[MAX][MAX];

void build(int n, int m) {
	//sum array is global, so initailised to 0 initially
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=m; ++j) {
			sum[i][j] = sum[i][j-1] + inp[i][j];
		}
	}
	for(int j=1; j<=m; ++j) {
		for(int i=2; i<=n; ++i) {
			sum[i][j] += sum[i-1][j];
		}
	}
}

//(x1, y1) are lower-most coordinates of submatrix
//(x2, y2) are upper-most coordinates of submatrix
LL query(int x1, int y1, int x2, int y2) {
	return sum[x2][y2] + sum[x1-1][y1-1] - sum[x2][y1-1] - sum[x1-1][y2];
}
