//Implementation of articulation point
const int MAX = 2e5 + 5;

vector<int> adj[MAX];

//Complexity : O(V + E)
class ArticulationPoint {
private:
	int V, E;
	bool visited[MAX];
	int parent[MAX];
	int low[MAX];
	int disc[MAX];
public:
	bool articulation[MAX];
	ArticulationPoint (int n, int m) {
		V = n;
		E = m;
		for(int i=1; i<=V; ++i) {
			parent[i] = -1;
			visited[i] = false;
			articulation[i] = false;
		}
	}
	void clear() {
		for(int i=1; i<=V; ++i) {
			adj[i].clear();
		}
	}
	void add_edge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	void dfs(int u) {
		static int cnt = 0;
		int children = 0;
		visited[u] = true;
		disc[u] = low[u] = ++cnt;
		for(size_t i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i];
			if (visited[v] == false) {
				parent[v] = u;
				children += 1;
				dfs(v);
				low[u] = min(low[u], low[v]);
				if (parent[u] == -1 && children > 1) {
					articulation[u] = true;
				}
				else if (parent[u] != -1 && low[v] >= disc[u]) {
					articulation[u] = true;
				}
			}
			else if (v != parent[u]) {
				low[u] = min(low[u], disc[v]);
			}
		}
	}
	int solve() {
		for(int i=1; i<=V; ++i) {
			if (visited[i] == false) {
				dfs(i);
			}
		}
	}
	void print() {
		printf("Articulation points are : \n");
		for(int i=1; i<=V; ++i) {
			if (articulation[i] == true) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
};