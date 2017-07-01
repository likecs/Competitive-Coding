// Gaussian elemination problems on XOR

const int LN = 32;			//equals ceil(log2(n)) where n is the maximum number to be inserted

template<typename T> struct gaussian {
	vector<T> v;
	vector<T> ans;
	gaussian() {
		clear();
	}
	void clear() {
		v.clear();
		ans.clear();
		ans.resize(LN , 0);
	}
	void insert(T num) {
		v.emplace_back(num);
	}
	void solve() {
		for(int i = LN - 1; i >= 0; --i)  {
			T ok = 0;
			for(auto &it : v) {
				if(it & (1ll << i)) {
					if(ok) {
						it ^= ok;
					}
					else {
						ans[i] = it;
						ok = it;
						it = 0;
					}
				}
			}
		}
	}
	// Returns maximum xor of any subset with num
	// num = 0 -> Maximum subset xor
	T getmax(T num = 0) {
		T res = num;
		for(int i = LN - 1; i >= 0; --i) {
			if((res ^ ans[i]) > res) {
				res ^= ans[i];
			}
		}
		return res;
	}
	// Returns minimum xor of any subset with num
	// num = 0 -> minimum subset xor
	T getmin(T num = 0) {
		T res = num;
		for(int i = LN-1; i >= 0; --i) {
			if ((res ^ ans[i]) < res) {
				res ^= ans[i];
			}
		}
		return res;
	}
	// Returns true if there exists subset with xor num
	bool subset(T num) {
		T x = getmin(num);
		return (x == 0);
	}
};