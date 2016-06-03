//Basic Range minimum/maximum query function

//Assumption- 0-based indexing everywhere

//Using Segment Trees
//O(n) precomputation
//O(log n) query
//O(n) space complexity
const int MAX = 100005;
const int LIM = 263005;
const int INF = 1000000001;

vector<int> inp;
int seg[LIM];

//initially called with build(1, 0, inp.size()-1)
void build(int t, int i, int j) {
	if (i==j) {
		seg[t] = inp[i];
		return;
	}
	int mid = (i+j)>>1;
	build(t*2, i, mid);
	build(t*2+1, mid+1, j);
	seg[t] = max(seg[t*2], seg[t*2+1]);
}

//[l, r] is range of query inclusive
void query(int t, int i, int j, int l, int r) {
	if (i>r || j<l) {
		return -INF;
	}
	if (l<=i && j<=r) {
		return seg[t];
	}
	int mid = (i+j)/2;
	int u = query(t*2, i, mid, l, r);
	int v = query(t*2+1, mid+1, j, l, r);
	return max(u, v);
}