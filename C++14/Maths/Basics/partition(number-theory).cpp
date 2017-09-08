/*
 *Algorithm taken from
  https://en.wikipedia.org/wiki/Partition_(number_theory)#Generating_function
 */

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

//to avoid any precision loss
long long absl(long long a) {
	if (a < 0) return (-a);
	return a;
}

vector<int> idx;
long long dp[MAX];

//Complexity : O(sqrt(n))
void init() {
	for(int i = 1; i < MAX; ++i) {
		int u = i*(3*i-1)/2 * (i%2==0 ? -1:1);
		idx.push_back(u);
		u = i*(3*i+1)/2 * (i%2==0 ? -1:1);
		idx.push_back(u);
		if (absl(u) > MAX) {
			break;
		}
	}
}

//Complexity : O(n * sqrt(n))
void calculate() {
	dp[0] = 1;
	int ops = 0;
	for(int i = 1; i < MAX; ++i) {
		for(int j = 0; j < idx.size(); ++j) {
			int u = (idx[j] < 0 ? -1:1);
			if (i >= absl(idx[j])) {
				ops += 1;
				dp[i] += u * dp[i-absl(idx[j])];
			}
			else {
				break;
			}
		}
		dp[i] = (dp[i] + MOD) % MOD; //dp[i] <= 6e10 before this
	}
}