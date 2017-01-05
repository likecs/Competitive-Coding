//Implementation of Edmond'd Karp algorithm to find MAximum flow in netwrok
//Uses Adjacency list representation

const int MAX = 15000;

//Complexity O(VE^2)
class EdmondKarp {
private:
	struct edge {
		int a, b, cap, flow;
	};
	int n, source, sink;
	int dis[MAX];
	int pred[MAX];
	vector<edge> e;
	vector<int> adj[MAX];
public:
	EdmondKarp(int a, int b, int c) {
		n = a;
		source = b;
		sink = c;
	}
	void set_dis() {
		for(int i=1; i<=n; ++i) {
			dis[i] = -1;
		}
	}
	void set_pred() {
		for(int i=1; i<=n; ++i) {
			pred[i] = -1;
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
	bool augment() {
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
					pred[to] = id;
					q.push(to);
				}
			}
		}
		while(!q.empty()) {
			q.pop();
		}
		return dis[sink] != -1;
	}
	int max_flow() {
		int flow = 0;
		set_pred();
		while(augment()) {
			int id = pred[sink];
			int pushed = INT_MAX;
			while(id != -1) {
				pushed = min(pushed, e[id].cap - e[id].flow);
				id = pred[e[id].a];
			}
			id = pred[sink];
			while(id != -1) {
				e[id].flow += pushed;
				e[id^1].flow -= pushed;
				id = pred[e[id].a];
			}
			flow += pushed;
			set_pred();
		}
		return flow;
	}
	void print_graph() {
		for(size_t i=0; i<(int)e.size(); ++i) {
			printf("from: %d to : %d flow : %d cap : %d\n", e[i].a, e[i].b, e[i].flow, e[i].cap);
		}
	}
};