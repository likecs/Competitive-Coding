//Fenwick Tree - https://kartikkukreja.wordpress.com/2013/12/02/range-updates-with-bit-fenwick-tree/
//Below implementation is for Range updates and Range queries

const int MAX = 1e5 + 5;
int bit1[MAX], bit2[MAX];       //1-based indexing for bit

//Complexity is 4*O(log n)
void U1(int idx, int x) {
	while (idx < MAX) {
		bit1[idx] += x;
		idx += (idx & -idx);
	}
}

void U2(int idx, int x) {
	while (idx < MAX) {
		bit2[idx] += x;
		idx += (idx & -idx);
	}
}

void update(int u, int v, int w) {
	U1(u, w);
	U1(v+1, -w);
	U2(u, w*(u-1));
	U2(v+1, -w*v);
}

//Complexity is 4*O(log n)
int Q1(int idx) {
	int sum = 0;
	while (idx > 0) {
		sum += bit1[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

int Q2(int idx) {
	int sum = 0;
	while (idx > 0) {
		sum += bit2[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

int Q3(int u) {
	return Q1(u)*u - Q2(u);
}

int query(int u, int v) {
	return Q3(v) - Q3(u-1);
}