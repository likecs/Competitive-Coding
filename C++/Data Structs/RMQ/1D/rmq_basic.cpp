//Basic Range minimum/maximum query function

//Assumption- 0-based indexing everywhere

//Most naive implementaion
//O(n^3) precomputation
//O(1) query
//O(n^2) space complexity
const int MAX = 1005;

vector<int> inp;
int pre[MAX][MAX];

void build_rmq() {
	int n = inp.size();
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++i) {
			int val = -1;
			for(int k=i; k<=j; ++k) {
				val = max(val, inp[k]);
			}
			pre[i][j] = val;
		}
	}
}

int query(int i, int j) {
	return pre[i][j];
}

//Dp optimised version of above code
//O(n^2) precomputation
//O(1) query
//O(n^2) space complexity
const int MAX = 1005;

vector<int> inp;
int pre[MAX][MAX];

void build_rmq() {
	int n = inp.size();
	for(int i=0; i<n; ++i) {
		pre[i][i] = inp[i];
		for(int j=i+1; j<n; ++i) {
			int val = pre[i][j-1];
			if (inp[j] < val) {
				val = inp[j]
			}
			pre[i][j] = pre[j][i] = val;
		}
	}
}

int query(int i, int j) {
	return pre[i][j];
}
