//Fenwick Tree - https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//Below implementation is for Range updates and Point queries

const int MAX = 1e5 + 5;
int bit[MAX];       //1-based indexing for bit

//Update [a, b], both inclusive, with some value
//Add "val" to (a) and "-val" to (b+1)
//Complexity is 2*O(log n)
void update_internal(int idx ,int val) {
	while (idx < MAX) {
		bit[idx] += val;
		idx += (idx & -idx);
	}
}

void update(int a, int b, int val) {
	update_internal(a, val);
	update_internal(b+1, -val);
}

//Complexity is O(log n)
int query(int idx) {
	int sum = 0;
	while (idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
}