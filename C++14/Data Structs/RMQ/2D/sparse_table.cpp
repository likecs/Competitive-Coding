//Basic Range minimum/maximum query function
//Assumption- 0-based indexing everywhere
//O(nm logn logm) space complexity

const int MAX = 1e3 + 3;
const int LIM = 10;				//equals ceil(log2(MAX))

int inp[MAX][MAX];
int lg[MAX];					//contains log of numbers from 1 to n
int p2[LIM];					//contains powers of 2
int rmq[LIM][LIM][MAX][MAX];	//sparse table implementation

//Complexity: O(nm logn logm)
void build_rmq(int n, int m) {
	for(int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;
	for(int i=0; i<LIM; ++i) p2[i] = 1<<i;
	p2[0] = 1;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			rmq[0][0][i][j] = inp[i][j];
		}
	}
	for(int k = 0; k < n; ++k) {
		for(int j = 1; j <= lg[m]; ++j) {
			int x2 = m - p2[j], y2 = p2[j-1];
			for(int l = 0; l <= x2; ++l) {
				rmq[0][j][k][l] = max(rmq[0][j-1][k][l], rmq[0][j-1][k][l+y2]);
			}
		}
	}
	for(int i = 1; i <= lg[n]; ++i) {
		int x1 = n - p2[i], y1 = p2[i-1];
		for(int k = 0; k <= x1; ++k) {
			for(int l = 0; l < m; ++l) {
				rmq[i][0][k][l] = max(rmq[i-1][0][k][l], rmq[i-1][0][k+y1][l]);
			}
		}
	}
	for(int i = 1; i <= lg[n]; ++i) {
		int x1 = n - p2[i], y1 = p2[i-1];
		for(int k = 0; k <= x1; ++k) {
			for(int j = 1; j <= lg[m]; ++j) {
				int x2 = m - p2[j], y2 = p2[j-1];
				for(int l = 0; l <= x2; ++l) {
					rmq[i][j][k][l] = max(max(rmq[i-1][j-1][k][l], rmq[i-1][j-1][k][l+y2]), max(rmq[i-1][j-1][k+y1][l], rmq[i-1][j-1][k+y1][l+y2]));
				}
			}
		}
	}
}

//Complexity : O(1)
//(L1, R1) is lower-left point
//(L2, R2) is upper-right point
int query(int L1, int R1, int L2, int R2) {
	int a = L2 - L1 + 1, b = R2 - R1 + 1;
	int A = lg[a], B = lg[b], P2A = p2[lg[a]]-1, P2B = p2[lg[b]]-1;
	int u = max(rmq[A][B][L1][R1], rmq[A][B][L2-P2A][R1]);
	int v = max(rmq[A][B][L1][R2-P2B], rmq[A][B][L2-P2A][R2-P2B]);
	return max(u, v);
}