//Implementation of Bellman Ford algorithm for finding shortest path from given source
//Works for both directed and undirected graphs
//Works for graphs with negative edge weights also

const int MAX = 1e4 + 4;

vector< pair<int,int> > adj[MAX];

//Complexity : O(V * E)
class BellmanFord {
private:
	int V, E;
	bool directed;
	bool negative_cycle;
public:
	int dis[MAX];
	int pred[MAX];
	BellmanFord (int n, int m, bool type=false) {
		V = n;
		E = m;
		directed = type;
		negative_cycle = false;
	}
	void clear() {
		for(int i=1; i<=V; ++i) {
			adj[i].clear();
		}
	}
	void set_dis() {
		for(int i=1; i<=V; ++i) {
			dis[i] = INT_MAX;
		}
	}
	void add_edge(int a, int b, int c) {
		adj[a].push_back({b, c});
		if (!directed) {
			adj[b].push_back({a, c});
		}
	}
	bool solve(int source) {
		set_dis();
		dis[source] = 0;
		pred[source] = -1;
		for(int i=1; i<V; ++i) {
			for(int u=1; u<=V; ++u) {
				for(size_t j=0; j<adj[u].size(); ++j) {
					int v = adj[u][j].first;
					int prio = dis[u] + adj[u][j].second;
					if (dis[v] > prio) {
						dis[v] = prio;
						pred[v] = u;
					}
				}
			}
		}
		return check_negative_cycle();
	}
	bool check_negative_cycle() {
		for(int u=1; u<=V; ++u) {
			for(size_t i=0; i<adj[u].size(); ++i) {
				int v = adj[u][i].first;
				if (dis[v] != INT_MAX && dis[v] > dis[u] + adj[u][i].second) {
					return true;
				}
			}
		}
		return false;
	}
	void print() {
		for(int i=1; i<=V; ++i) {
			printf("Vertex: %d, Distance: %d, Predecessor: %d\n", i, dis[i], pred[i]);
		}
		printf("\n");
	}
};