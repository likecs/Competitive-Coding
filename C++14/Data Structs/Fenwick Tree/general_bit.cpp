//Fenwick Tree - https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
//Below implementation is for Point updates and Range queries

const int MAX = 1e5 + 5;
int bit[MAX];		//1-based indexing for bit

//Complexity: O(log n)
void update(int idx, int val) {
	while (idx < MAX) {
		bit[idx] += val;
		idx += (idx & -idx);
	}
}

//Complexity: O(log n)
int query(int idx) {
	int sum = 0;
	while(idx > 0) {
		sum += bit[idx];
		idx -= (idx & -idx);
	}
	return sum;
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
void scale(int c) {
	for (int idx = 1; idx < MAX; ++idx) bit[idx] = bit[idx] / c;
}


//Find index with given cummulative frequency
//Below are 2 different versions
int get(int a) {
	if (a == 0) return 0;
	int x = 31 - __builtin_clz(x);
	return (1<<x);
}

//Version-1
//if in bit exists more than one index with a same cumulative frequency, this procedure will return some of them (we do not know which one)
int find(int cum_freq) {
	int idx = 0;
	//bit_mask - initialy, it is the greatest bit of n and stores interval which should be searched
	int bit_mask = get(MAX);
	while ((idx < MAX) && (bit_mask != 0)) {
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
int findG(int cum_freq) {
	int idx = 0;
	int bit_mask = get(MAX);
	while ((idx < MAX) && (bit_mask != 0)) {
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
