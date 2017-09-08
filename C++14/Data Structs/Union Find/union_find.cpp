//Class to implement union find using path compression
//1-based indexing assumed

class UnionFind {
private:
	int n, set_size, *parent, *rank;
public:
	//Complexity: O(n)
	UnionFind(int a) {
		n = set_size = a;
		parent = new int[n+1];
		rank = new int[n+1];
		for(int i = 1; i <= n; ++i) parent[i]=i, rank[i]=1;
	}
	~UnionFind() {
		delete rank;
		delete parent;
	}
	//Path Compression
	int find(int x) {
		if (x != parent[x]) return parent[x] = find(parent[x]);
		return x;
	}
	//Complexity : O(A N), where A = Inverse Ackermann function
	void unite(int x, int y) {
		int xroot = find(x), yroot = find(y);
		if (xroot != yroot) {
			if (rank[xroot] >= rank[yroot]) {
				parent[yroot] = xroot;
				rank[xroot] += rank[yroot];
			}
			else {
				parent[xroot] = yroot;
				rank[yroot] += rank[xroot];
			}
			set_size -= 1;
		}
	}
	int size() { return set_size; }
	void print() {
		for(int i = 1; i <= n; ++i)
			cout << i << " -> " << parent[i] << "\n";
	}
};