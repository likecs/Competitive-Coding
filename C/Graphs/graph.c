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
	print_graph(adj, n);

	return 0;
}