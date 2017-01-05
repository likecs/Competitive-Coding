//Basic Range minimum/maximum query function
//Assumption- 1-based indexing everywhere
//O(n) space complexity

//Using Segment Trees
//Can Support updates also

const int MAX = 1e5 + 5;
const int LIM = 3e5 + 5;	//equals 2*2^(ceil(log2(MAX)))

int inp[MAX];
int seg[LIM];

//Complexity: O(n)
void build(int t, int i, int j) {
	if (i == j) {
		seg[t] = inp[i];
		return;
	}
	int mid = (i + j) /;
	build(t*2, i, mid);
	build(t*2+1, mid+1, j);
	seg[t] = max(seg[t*2], seg[t*2+1]);
}

//range of query is [l, r] (both inclusive)
//Complexity: O(log n)
void query(int t, int i, int j, int l, int r) {
	if (i > r || j < l) return INT_MIN;
	if (l <= i && j <= r) return seg[t];
	int mid = (i+j)/2;
	int u = query(t*2, i, mid, l, r);
	int v = query(t*2+1, mid+1, j, l, r);
	return max(u, v);
}