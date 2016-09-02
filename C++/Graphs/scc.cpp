//Implementation of Strongly connected components using Kosaraju Algorithm

const int MAX = 2e5 + 5;

//Complexity : O(V + E)
class StronglyConnected {
private:
	int V, E, cnt;
	stack<int> S;
	bool visited[MAX];
	vector<int> adj[MAX];
	vector<int> trans[MAX];
	vector<int> components[MAX];
public:
	StronglyConnected(int n, int m) {
		V = n;
		E = m;
		cnt = 0;
	}
	void clear() {
		for(int i=1; i<=V; ++i) {
			adj[i].clear();
			trans[i].clear();
			components[i].clear();
		}
	}
	void set_visited() {
		for(int i=1; i<=V; ++i) {
			visited[i] = false;
		}
	}
	void add_edge(int a, int b) {
		adj[a].push_back(b);
		trans[b].push_back(a);
	}
	void dfs1(int u) {
		visited[u] = true;
		for(size_t i=0; i<adj[u].size(); ++i) {
			if (visited[adj[u][i]] == false) {
				dfs1(adj[u][i]);
			}
		}
		S.push(u);
	}
	void dfs2(int u) {
		visited[u] = true;
		components[cnt].push_back(u);
		for(size_t i=0; i<trans[u].size(); ++i) {
			if(visited[trans[u][i]] == false) {
				dfs2(trans[u][i]);
			}
		}
	}
	void scc() {
		set_visited();
		for(int i=1; i<=V; ++i) {
			if(!visited[i]) {
				dfs1(i);
			}
		}
		set_visited();
		cnt = 0;
		while(!S.empty()) {
			int v = S.top();
			S.pop();
			if (visited[v] == false) {
				dfs2(v);
				cnt += 1;
			}
		}
	}
	bool is_scc() {
		return (cnt == 1);
	}
	int no_of_scc() {
		return cnt;
	}
	void print() {
		for(int i=0; i<cnt; ++i) {
			printf("Component %d : ", i+1);
			for(size_t j=0; j<components[i].size(); ++j) {
				printf("%d ", components[i][j]);
			}
			printf("\n");
		}
	}
};
