//Merge Sort Tree implementations

const int MAX = 1e5 + 5;
const int LIM = 3e5 + 5;        //equals 2 * 2^ceil(log2(n))

int a[MAX];
vector<int> seg[LIM];

//Complexity : O(n logn)
void build(int t, int i, int j) {
	seg[t].clear();
	if (i == j) {
		seg[t].push_back(a[i]);
		return ;
	}
	int left = t << 1, right = left | 1;
	int mid = (i + j) / 2;
	build(left, i, mid);
	build(right, mid+1, j);
	merge(seg[left].begin(), seg[left].end(), seg[right].begin(), seg[right].end(), back_inserter(seg[t]));
}

//Returns count of i, A[i] <= val, l <= i <= r
//Complexity : O(log^2 n)
int query1(int t, int i, int j, int l, int r, int val) {
	if (i > r || j < l) return 0;
	if (l <= i && j <= r) {
		int pos = upper_bound(seg[t].begin(), seg[t].end(), val) - seg[t].begin();
		return pos;
	}
	int left = t << 1, right = left | 1;
	int mid = (i + j) / 2;
	return query1(left, i, mid, l, r, val) + query1(right, mid+1, j, l, r, val);
}

//Returns count of i, A[i] >= val, l <= i <= r
//Complexity : O(log^2 n)
int query2(int t, int i, int j, int l, int r, int val) {
	if (i > r || j < l) return 0;
	if (l <= i && j <= r) {
		int pos = lower_bound(seg[t].begin(), seg[t].end(), val) - seg[t].begin();
		return (int)seg[t].size() - pos;
	}
	int left = t << 1, right = left | 1;
	int mid = (i + j) / 2;
	return query2(left, i, mid, l, r, val) + query2(right, mid+1, j, l, r, val);
}