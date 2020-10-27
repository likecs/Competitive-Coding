#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define endl '\n'
#define mod 1000000007

void bfs(vector<int> *g, int start,int  *vis)
{
	queue<int> q;
	q.push(start);				// print starting node
	cout<<start<<" ";			// print starting node
	vis[start]++;				// Mark vis[start] as visited
	while(!q.empty())
	{
		int front=q.front();	// storing front element
		q.pop();				// poping the front element
		for(int i=0;i<g[front].size();i++)		// Traversing all directly connected nodes to node front
		{
			if(!vis[g[front][i]])				// Checking if the node is not been already visited
			{
				vis[g[front][i]]++;				// Making the node visited
				cout<<g[front][i]<<" ";			// printing the node
				q.push(g[front][i]);			// pushing the node to queue
			}
		}
	}
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

    int n,m,x,y;
    cin>>n>>m;   				// n -> Number of Nodes ,, m -> Number of edges
    vector<int> g[n+1];			// An array of type vector of size N such that g[i] signifies the nodes connected to node i
    int vis[n+1]={};			// An array to check which nodes are visited and which are remained
    for(int i=0;i<m;i++)
    {
    	cin>>x>>y;         		// defines that there is a bidirectional edge between Node x and Node y
    	g[x].push_back(y);		// pushing y in g[x] which signifies that there is and edge from x to y
    	g[y].push_back(x);		// pushing x in g[y] which signifies that there is and edge from y to x
    }
    bfs(g,1,vis);					// Calling BFS from starting Node 1
	return 0;
}
