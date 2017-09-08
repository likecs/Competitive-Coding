//Implementation of Hopcrapt Karp Bipartite Maximum Matching Algorithm
const int MAX = 1e5 + 5;

//Complexity : O(E sqrt(V))
class HopcraftKarp {
private:
	bool reverse;
	int n, m;
	int dis[MAX];
	int match[MAX];
	vector<int> adj[MAX];
public:
	#define NIL		0
	HopcraftKarp(int a, int b) {
		n = a;
		m = b;
		reverse = false;
		if (n > m) {
			reverse = true;
			swap(n, m);
		}
		for(int i=0; i<=n; ++i) {
			match[i] = NIL;
		}
	}
	void add_edge(int a, int b) {
		if (reverse) {
			adj[a + n].push_back(b);
			adj[b].push_back(a + n);
		}
		else {
			adj[a].push_back(b + n);
			adj[b + n].push_back(a);
		}
	}
	bool bfs() {
		queue<int> q;
		for(int i=1; i<=n; ++i) {
			if (match[i] == NIL) {
				dis[i] = 0;
				q.push(i);
			}
			else {
				dis[i] = INT_MAX;
			}
		}
		dis[NIL] = INT_MAX;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			if (u != NIL) {
				for(size_t i=0; i<adj[u].size(); ++i) {
					int v = adj[u][i];
					if (dis[match[v]] == INT_MAX) {
						dis[match[v]] = dis[u] + 1;
						q.push(match[v]);
					}
				}
			}
		}
		return dis[NIL] != INT_MAX;
	}
	int dfs(int u) {
		if (u != NIL) {
			for(size_t i=0; i<adj[u].size(); ++i) {
				int v = adj[u][i];
				if (dis[match[v]] == dis[u] + 1) {
					if (dfs(match[v])) {
						match[v] = u;
						match[u] = v;
						return true;
					}
				}
			}
			dis[u] = INT_MAX;
			return false;
		}
		return true;
	}
	int max_matching() {
		int matching = 0;
		while(bfs()) {
			for(int i=1; i<=n; ++i) {
				if (match[i] == NIL && dfs(i)) {
					++matching;
				}
			}
		}
		return matching;
	}
	void print_matches() {
		for(int i=1; i<=n; ++i) {
			if (match[i] != NIL) {
				printf("%d matches with %d\n", i, match[i]-n);
			}
		}
	}
};