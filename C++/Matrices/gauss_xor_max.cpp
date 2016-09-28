//Subset Xor maximisation problem using Gaussian elimination

typedef long long LL;

const int LN = 32;			//equals ceil(log2(n)) where n is the maximum number to be inserted

template<typename T> struct maxxor{
	vector<T> v;
	vector<T> ans;
	maxxor(){
		v.clear();
	}
	void clear(){
		v.clear();
		ans.clear();
		ans.resize(LN , 0);
	}
	void insert(T num){
		v.emplace_back(num);
	}
	void solve(){
		for(int i=LN-1; i>=0; --i) {
			T ok = 0;
			for(auto &it : v) {
				if(it & (1LL << i)) {
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
	T getmax(T num = 0){
		T res = num;
		for(int i=LN-1; i>=0; --i){
			if((res ^ ans[i]) > res){
				res ^= ans[i];
			}
		}
		return res;
	}
};