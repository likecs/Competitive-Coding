//2-D Fenwick tree implementations
//Below implementation is for Point updates and Range queries

const int MAX = 1005;
int bit[MAX][MAX];

//Complexity is O(log^2 n)
void update(int x, int y, int val) {
	while (x < MAX) {
		int v = y;
		while (v < MAX) {
			bit[x][v] += val;
			v += (v & -v);
		}
		x += (x & -x);
	}
}

//Complexity is O(log^ 2)
int query(int x, int y) {
	int sum = 0;
	while (x > 0) {
		int v = y;
		while (v > 0) {
			sum += bit[x][v];
			v -= (v & -v);
		}
		x -= (x & -x);
	}
	return sum;
}

//Sum of values within rectangle (x1, y1) to (x2, y2), both inclusive
//(x2, y2) lies above or right to (x1, y1) else sum is 0
//Complexity is 4*O(logn * logm)
int sum(int x1, int y1, int x2, int y2) {
	return query(x2, y2) + query(x1-1, y1-1) - query(x2, y1-1) - query(x1-1, y2);
}
