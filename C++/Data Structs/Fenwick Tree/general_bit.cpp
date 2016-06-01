//Fenwick Tree - https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//Below implementation is for Point updates and Range queries

int n;				//value of n as per question, generally taken as input
int bit[n+5];		//1-based indexing for bit

//Complexity is O(n)
void initialise(int n) {
    for(int i=1; i<=n; ++i) bit[i][j] = 0LL;
}

//Complexity is O(log n)
void update(int idx ,int val, int n) {
    while (idx <= n) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
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

//Better code for point query
//Details refer to link of topcoder given above
//Complexity is O(1) for odd idx
//Complexity is c*O(log n) where 0<c<=1
int readSingle(int idx) {
	int sum = bit[idx]; 
	if (idx > 0) { 
    	int z = idx - (idx & -idx); 
    	idx--; 
    	while (idx != z) { 
        	sum -= bit[idx]; 
        	idx -= (idx & -idx);
    	}
	}
	return sum;
}

//Scale/Multiply/Divide each of array by c, where c is any number
//Complexity is O(n)
void scale(int c, int n) {
    for (int idx=1; idx<=n; ++idx) bit[idx] = bit[idx] / c;
}


//Find index with given cummulative frequency
//Below are 2 different versions

int get(int a) {
	if (a==0) return 0;
	int x = log2(a);
	return (1<<x);
}

//Version-1
//if in bit exists more than one index with a same cumulative frequency, this procedure will return some of them (we do not know which one)
int find(int cum_freq, int n) {
    int idx = 0;
	//bit_mask - initialy, it is the greatest bit of n and stores interval which should be searched
	int bit_mask = get(n);
    while ((idx < n) && (bit_mask != 0)) {
        int tIdx = idx + bit_mask; 
        if (cum_freq == bit[tIdx]) return tIdx;
        else if (cum_freq > bit[tIdx]) { 
            idx = tIdx; 
            cum_freq -= bit[tIdx];
        }
        bit_mask >>= 1;
    }
    if (cum_freq != 0) return -1;
    else return idx;
}

//Version-2
//if in bit exists more than one index with a same cumulative frequency, this procedure will return the greatest one
int findG(int cum_freq, int n) {
    int idx = 0;
    int bit_mask = get(n);
    while ((idx < n) && (bit_mask != 0)) {
        int tIdx = idx + bit_mask;
        if (cum_freq >= bit[tIdx]) { 
            idx = tIdx;
            cum_freq -= bit[tIdx];
        }
        bit_mask >>= 1;
    }
    if (cum_freq != 0) return -1;
    else return idx;
}