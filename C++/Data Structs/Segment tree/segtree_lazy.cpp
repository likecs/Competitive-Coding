//Segment tree operations: Range update(Lazy propagation) and Range Query

const int MAX = 1e5 + 5;
const int LIM = 2 * (ceil(log2(MAX))) + 5;

int a[MAX];
int seg[LIM];
int lazy[LIM];
bool push[LIM];

//Complexity: O(1)
//Stores what info. segment[i..j] should store
void combine(int t) {
	seg[t] = max(seg[t*2], seg[t*2+1]);
}

//Lazy propagation
void propagate(int t, int i, int j) {
	if (push[t]) {
		seg[t] = seg[t] + lazy[t];
		if (i != j) {
			push[t*2] = true;
			push[t*2 + 1] = true;
			lazy[t*2] = lazy[t*2] + lazy[t];
			lazy[t*2 + 1] = lazy[t*2 + 1] + lazy[t];
		}
		push[t] = false;
		lazy[t] = 0;
	}
}

//Complexity: O(n)
void build(int t, int i, int j) {
	push[t] = false;
	lazy[t] = 0;
	if (i == j) {
		//base case : leaf node information to be stored here
		seg[t] = a[i];
		return ;
	}
	int mid = (i + j) / 2;
	build(t*2, i, mid);
	build(t*2 + 1, mid + 1, j);
	combine(t);
}

//Complexity: O(log n)
void update(int t, int i, int j, int l, int r, int x) {
	propagate(t, i, j);
	if (i > r || j < l) {
		return ;
	}
	if (l <= i && j <= r) {
		//base case : leaf node information to be stored here
		lazy[t] += x;
		push[t] = true;
		propagate(t, i, j);
		return ;
	}
	int mid = (i + j) / 2;
	update(t*2, i, mid, l, r, x);
	update(t*2 + 1, mid + 1, j, l, r, x);
	combine(t);
}

//Complexity: O(log n)
int query(int t, int i, int j, int l, int r) {
	propagate(t, i, j);
	if (i > r || j < l){
		//base case: result of out-of-bound query
		return 0;
	}
	if (l <=i && j <= r) {
		return seg[t];
	}
	int mid = (i + j) / 2;
	int a = query(t*2, i, mid, l, r) ;
	int b = query(t*2 + 1,  mid + 1, j, l, r);
	return max(a,  b);
}