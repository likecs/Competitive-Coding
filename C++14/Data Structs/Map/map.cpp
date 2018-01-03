//Implementation of Map to get O(1) access for small values
//and O(logn) for large values.
//But it uses larger memory as many small places are uninitialised.

struct MAP {
	#define LIM 128
	#define NIL -1
	int small[LIM];
	map<int, int> mp;
	MAP() {
		mp.clear();
		for(int i = 0; i < LIM; ++i) {
			small[i] = NIL;
		}
	}
	bool has(int a) {
		if (a < LIM) {
			return (small[a] != NIL);
		}
		return mp.find(a) != mp.end();
	}
	int value(int a) {
		if (a < LIM) {
			return small[a];
		}
		return mp[a];
	}
	void assign(int a, int b) {
		if (a < LIM) {
			small[a] = b;
		}
		else {
			mp[a] = b;
		}
	}
};