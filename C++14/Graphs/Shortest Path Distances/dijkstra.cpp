//Implementation of Dijkstra's algorithm using Priority queues
//Works for both directed and undirected graphs
//Works for graphs with only positive edge weights

const int MAX = 1e5 + 5;

//Complexity : O(E logV)
class Dijkstra {
private:
	int V, E;
	bool directed;
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > Q;
public:
	vector< pair<int,int> > adj[MAX];
	int dis[MAX];
	int pred[MAX];
	Dijkstra(int n, int m, bool type=false) {
		V = n;
		E = m;
		directed = type;
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
	void solve(int source) {
		set_dis();
		while(!Q.empty()) {
			Q.pop();
		}
		dis[source] = 0;
		pred[source] = -1;
		Q.push({dis[source], source});
		while(!Q.empty()) {
			int d = Q.top().first;
			int u = Q.top().second;
			Q.pop();
			if (d != dis[u]) {
				continue;
			}
			for(size_t i=0; i<adj[u].size(); ++i) {
				int v = adj[u][i].first;
				int prio = dis[u] + adj[u][i].second;
				if (dis[v] > prio) {
					dis[v] = prio;
					pred[v] = u;
					Q.push({dis[v], v});
				}
			}
		}
	}
	void print() {
		for(int i=1; i<=V; ++i) {
			printf("Vertex: %d, Distance: %d, Predecessor: %d\n", i, dis[i], pred[i]);
		}
		printf("\n");
	}
};
