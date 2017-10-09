//Program to calculate the LCA of 2 nodes in tree
//Also can be used to find the path between 2 nodes
//Taken from https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 2;
const int LIM = 17;

vector<int> adj[MAX];
int par[MAX];
int euler[MAX*2];
int level[MAX*2];
int height[MAX];
int subtree[MAX];
int occur[MAX];
int cnt;

//O(V + E)
void dfs_lca(int u, int p, int l) {
	par[u] = p;
	height[u] = l;
	subtree[u] = 1;
	occur[u] = cnt;
	level[cnt] = height[u];
	euler[cnt++] = u;
	for(auto v : adj[u]) {
		if (v != p) {
			dfs_lca(v, u, l+1);
			level[cnt] = height[u];
			euler[cnt++] = u;
			subtree[u] += subtree[v];
		}
	}
}

int lg[MAX*2];
int rmq[LIM+1][MAX*2];

void init() {
	for(int i = 2; i < 2*MAX; ++i) {
		lg[i] = lg[i/2] + 1;
	}
	for(int i = 1; i < 2*MAX; ++i) {
		rmq[0][i] = i;
	}
}

//Precomputation of O(V logV)
void build_rmq(int n) {
	init();
	for(int i = 1; i <= lg[n]; ++i) {
		int x = n - (1<<i) + 1, y = (1<<(i-1));
		for(int j = 1; j <= x; ++j) {
			if (level[rmq[i-1][j]] < level[rmq[i-1][j+y]]) {
				rmq[i][j] = rmq[i-1][j];
			}
			else {
				rmq[i][j] = rmq[i-1][j+y];
			}
		}
	}
}

//RMQ Query in O(1)
int query(int i, int j) {
	int x = lg[j-i+1];
	if (level[rmq[x][i]] < level[rmq[x][j-(1<<x)+1]]) {
		return rmq[x][i];
	}
	else {
		return rmq[x][j-(1<<x)+1];
	}
}

//LCA Query in O(1)
int lca(int x, int y) {
	if (occur[x] > occur[y]) {
		swap(x, y);
	}
	return euler[query(occur[x], occur[y])];
}

//Precomputation part
void init_lca(int n, int root = 1) {
	int _n = n << 1;
	cnt = 1;
	dfs_lca(root, -1, 0);
	build_rmq(_n - 1);
}

//Get the path between any 2 nodes in O(path_length)
vector<int> get_path(int x, int y) {
	vector<int> path, temp;
	int w = lca(x, y);
	while (x != w) {
		path.push_back(x);
		x = par[x];
	}
	while(y != w) {
		temp.push_back(y);
		y = par[y];
	}
	path.push_back(w);
	for(int i=temp.size()-1; i>=0; --i) {
		path.push_back(temp[i]);
	}
	return path;
}

//Sample program given below
int main() {
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	int n, x, y;
	scanf("%d", &n);
	for(int i=1; i<n; ++i) {
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	init_lca(n);

	return 0;
}