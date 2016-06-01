//Fenwick Tree - https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//Below implementation is for Range updates and Point queries

int n;				//value of n as per question, generally taken as input
int bit[n+5];		//1-based indexing for bit

//Complexity is O(n)
void initialise(int n) {
    for(int i=1; i<=n; ++i) bit[i][j] = 0LL;
}

//Update [a, b], both inclusive, with some value
//Add "val" to (a) and "-val" to (b+1)
//Complexity is 2*O(log n)
void update_internal(int idx ,int val, int n) {
    while (idx <= n) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

void update(int a, int b, int val, int n) {
    update_internal(a, val, n);
    update_internal(b+1, -val, n);
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

//For point query
//Complexity is 2*O(log n)
int point_query(int idx) {
	return query(idx) - query(idx-1);
}