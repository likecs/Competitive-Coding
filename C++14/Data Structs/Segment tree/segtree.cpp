//Segment tree operations: Point update and Range Query

const int MAX = 1e5 + 5;
const int LIM = 3e5 + 5;        //equals 2 * 2^ceil(log2(n))

int a[MAX];
int seg[LIM];

//Complexity: O(1)
//Stores what info. segment[i..j] should store
int combine(int &a, int &b) {
	return a + b;
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
	seg[t] = combine(seg[2*t], seg[2*t+1]);
}

//Complexity: O(log n)
void update(int t, int i, int j, int x, int y) {
	if (i > x || j < x) {
		return ;
	}
	if (i == j) {
		//base case : leaf node information to be stored here
		seg[t] = y;
		return ;
	}
	int mid = (i + j) / 2;
	update(t*2, i, mid, x, y);
	update(t*2 + 1, mid + 1, j, x, y);
	seg[t] = combine(seg[2*t], seg[2*t+1]);
}

//Complexity: O(log n)
int query(int t, int i, int j, int l, int r) {
	if (l <=i && j <= r) {
		return seg[t];
	}
	int mid = (i + j) / 2;
	if (l <= mid) {
		if (r <= mid) {
			return query(t*2, i, mid, l, r);
		}
		else {
			int a = query(t*2, i, mid, l, r);
			int b = query(t*2 + 1,  mid + 1, j, l, r);
			return combine(a, b);
		}
	}
	else {
		return query(t*2 + 1,  mid + 1, j, l, r);
	}
}