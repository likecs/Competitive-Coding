//Class to implement union find using path compression
//1-based indexing assumed

class union_find {
    private:
        int n, set_size, *parent, *rank;
    public:
        union_find(int a) {
            n = set_size = a;
            parent = new int[n+1];
            rank = new int[n+1];
            for(int i=1; i<=n; ++i) parent[i]=i, rank[i]=1;
        }
        void print() {
            for(int i=1; i<=n; ++i) printf("%d -> %d\n", i, parent[i]);
        }
        int find(int x) {
            if (x!=parent[x]) return parent[x] = find(parent[x]);
            return x;
        }
        void unite(int x, int y) {
            int xroot = find(x), yroot = find(y);
            if (xroot!=yroot) {
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
        bool same_set(int x, int y) {
            return find(x) == find(y);
        }
        int size() {
            return set_size;
        }
        ~union_find() {
            delete rank;
            delete parent;
        }
};
