//Implementation of Min cut using Dinic Algoruthm
//Debugging function provided too
//Edges in Min-cut are stored in vector
//Vertices are also partitioned into different sets

const int MAX = 15000;

//Complexity : O(V^2E)
class Dinic {
private:
	struct edge {
		int a, b, cap, flow;
	};
	int n, source, sink;
	int dis[MAX];
	int ptr[MAX];
	int color[MAX];
	vector<edge> e;
	vector<edge> min_cut;
	vector<int> adj[MAX];
public:
	Dinic(int a, int b, int c) {
		n = a;
		source = b;
		sink = c;
	}
	void set_dis() {
		for(int i=1; i<=n; ++i) {
			dis[i] = -1;
		}
	}
	void set_ptr() {
		for(int i=1; i<=n; ++i) {
			ptr[i] = 0;
		}
	}
	void add_edge(int a, int b, int cap) {
		edge e1 = {a, b, cap, 0};
		edge e2 = {b, a, 0, 0};
		adj[a].push_back((int)e.size());
		e.push_back(e1);
		adj[b].push_back((int)e.size());
		e.push_back(e2);
	}
	bool bfs() {
		queue<int> q;
		q.push(source);
		set_dis();
		dis[source] = 0;
		while(!q.empty() && dis[sink] == -1) {
			int v = q.front();
			q.pop();
			for(size_t i=0; i<adj[v].size(); ++i) {
				int id = adj[v][i];
				int to = e[id].b;
				if (dis[to] == -1 && e[id].flow < e[id].cap) {
					dis[to] = dis[v] + 1;
					q.push(to);
				}
			}
		}
		while(!q.empty()) {
			q.pop();
		}
		return dis[sink] != -1;
	}
	int dfs(int v, int flow) {
		if (!flow) {
			return 0;
		}
		if (v == sink) {
			return flow;
		}
		for(; ptr[v]<(int)adj[v].size(); ++ptr[v]) {
			int id = adj[v][ptr[v]];
			int to = e[id].b;
			if (dis[to] != dis[v] + 1) {
				continue;
			}
			int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
			if (pushed) {
				e[id].flow += pushed;
				e[id^1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
	int max_flow() {
		int flow = 0;
		while(bfs()) {
			set_ptr();
			int pushed;
			while(pushed = dfs(source, INT_MAX)) {
				flow += pushed;
			}
		}
		return flow;
	}
	void build_min_cut() {
		for(size_t i=0; i<(int)e.size(); i+=2) {
			if (e[i].flow == e[i].cap) {
				if (dis[e[i].a] != -1 && dis[e[i].b] == -1) {
					min_cut.push_back(e[i]);
				}
			}
		}
	}
	#define red 	1
	#define blue	2
	void build_partition() {
		for(int i=1; i<=n; ++i) {
			color[i] = dis[i] == -1 ? red : blue;
		}
	}
	void print_graph() {
		for(size_t i=0; i<(int)e.size(); ++i) {
			printf("from: %d to : %d flow : %d cap : %d\n", e[i].a, e[i].b, e[i].flow, e[i].cap);
		}
	}
	void print_min_cut() {
		printf("Edges in min cut are : \n");
		for(size_t i=0; i<(int)min_cut.size(); ++i) {
			printf("from : %d to : %d\n", min_cut[i].a, min_cut[i].b);
		}
	}
	void print_partition() {
		printf("Vertices in 1st partition are : \n");
		for(int i=1; i<=n; ++i) {
			if (color[i] == red) {
				printf("%d ", i);
			}
		}
		printf("\n");
		printf("Vertices in 2nd partition are : \n");
		for(int i=1; i<=n; ++i) {
			if (color[i] == blue) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
};