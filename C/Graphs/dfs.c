#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#define MAX             2005
#define SIZE            256
#define INF 			1000000000
#define bool            int
#define false           0
#define true            1

struct G
{
	int dest, weight;
	struct G *next;
};

typedef struct G graph;

graph *add_edge(graph *a, int y, int w)
{
	graph *temp = (graph*)malloc(sizeof(graph));
	temp->dest = y;
	temp->weight = w;
	temp->next = NULL;
	if (a == NULL)
	{
		a = temp;
	}
	else if (a->next == NULL)
	{
		a->next = temp;
	}
	else
	{
		graph *last = a->next;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = temp;
	}
	return a;

}

void print_graph(graph **a, int n)
{
	int i;
	for(i=1; i<=n; ++i)
	{
		graph *temp = a[i];
		printf("%d-> ", i);
		while (temp != NULL)
		{
			printf("%d(%d) ", temp->dest, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("\n");
}

void dfs(graph **adj, bool visited[], int parent[], int pos[], int to[], int v)
{
	static int tim = 0;
	visited[v] = true;
	tim += 1;
	pos[v] = tim;
	graph *temp = adj[v];
	while (temp != NULL)
	{
		if (!visited[temp->dest])
		{
			parent[temp->dest] = v;
			dfs(adj, visited, parent, pos, to, temp->dest);
		}
		temp = temp->next;
	}
	tim += 1;
	to[v] = tim;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	graph *adj[MAX];
	int i, j, k, n, edges;
	for(i=0; i<MAX; ++i)
	{
		adj[i] = NULL;
	}
	scanf("%d %d", &n, &edges);
	int x, y, w;
	for(i=1; i<=edges; ++i)
	{
		scanf("%d %d %d", &x, &y, &w);
		adj[x] = add_edge(adj[x], y, w);
		adj[y] = add_edge(adj[y], x, w);
	}
	int pos[n+1], to[n+1], parent[n+1];
	bool visited[n+1];
	for(i=1; i<=n; ++i)
	{
		visited[i] = false;
		parent[i] = -1;
	}
	for(i=1; i<=n; ++i)
	{
		if (!visited[i])
		{
			dfs(adj, visited, parent, pos, to, i);
		}
	}
	print_graph(adj, n);
	for(i=1; i<=n; ++i)
	{
		printf("%d: %d %d %d\n", i, parent[i], pos[i], to[i]);
	}
	return 0;
}