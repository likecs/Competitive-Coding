//Segment tree operations: Point update and Range Query

const int MAX = 1e5 + 5;
const int LIM = 2 * (ceil(log2(MAX))) + 5;

int a[MAX];
int seg[LIM];

//Complexity: O(1)
//Stores what info. segment[i..j] should store
void combine(int t) {
	seg[t] = seg[t*2] + seg[t*2+1];
}

//Complexity: O(n)
void build(int t, int i, int j) {
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
void update(int t, int i, int j, int x, int y) {
	if (i > x || j < x) {
		return ;
	}
	if (i == j) {
		//base case : leaf node information to be stored here
		seg[t] = a[i];
		return ;
	}
	int mid = (i + j) / 2;
	update(t*2, i, mid, x, y);
	update(t*2 + 1, mid + 1, j, x, y);
	combine(t);
}

//Complexity: O(log n)
int query(int t, int i, int j, int l, int r) {
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
	return a + b;
}