//Implementation of Topological Sort using stack and dfs

const int MAX = 2e5 + 5;

vector<int> adj[MAX];

//Complexity : O(V + E)
class TopologicalSort {
private:
	int V, E;
	stack<int> S;
	bool visited[MAX];
public:
	vector<int> topological_order;
	TopologicalSort(int n, int m) {
		V = n;
		E = m;
	}
	void clear() {
		for(int i=1; i<=V; ++i) {
			adj[i].clear();
		}
	}
	void set_visited() {
		for(int i=1; i<=V; ++i) {
			visited[i] = false;
		}
	}
	void add_edge(int a, int b) {
		adj[a].push_back(b);
	}
	void dfs(int u) {
		visited[u] = true;
		for(size_t i=0; i<adj[u].size(); ++i) {
			if (visited[adj[u][i]] == false) {
				dfs(adj[u][i]);
			}
		}
		S.push(u);
	}
	void topo_sort() {
		set_visited();
		for(int i=1; i<=V; ++i) {
			if(!visited[i]) {
				dfs(i);
			}
		}
		while(!S.empty()) {
			topological_order.push_back(S.top());
			S.pop();
		}
	}
	void print() {
		for(size_t i=0; i<V; ++i) {
			printf("%d ", topological_order[i]);
		}
		printf("\n");
	}
};
