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

struct node
{
	int data, data2;
	struct node *next;
};

typedef struct node stack;

void print_list(stack *a)
{
	if (a==NULL)
	{
		printf("Stack is empty\n");
		return;
	}
	while (a!=NULL)
	{
		printf("%d ", a->data);
		a = a->next;
	}
	printf("\n");
}

stack* push(stack *a, int val, int val2)
{
	stack *ref = (stack*)malloc(sizeof(stack));
	ref->data = val;
	ref->data2 = val2;
	ref->next = a;
	a = ref;
	return a;
}

stack* pop(stack *a)
{
	if (a==NULL)
	{
		printf("Stack is empty\n");
		return a;
	}
	stack *ref = a;
	a = a->next;
	// printf("Data deleted is %d\n", ref->data);
	free(ref);
	return a;
}


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

void dfs(graph **adj, bool visited[], int parent[], int disc[], int low[], stack **top, int *count, int u)
{
	static int tim = 0;
	visited[u] = true;
	int children = 0;
	disc[u] = low[u] = ++tim;
	graph *temp = adj[u];
	while (temp != NULL)
	{
		int v = temp->dest;
		if (!visited[v])
		{
			children += 1;
			parent[v] = u;
			(*top) = push(*top, u, v);
			dfs(adj, visited, parent, disc, low, top, count, v);

			if (low[u] > low[v])
				low[u] = low[v];

			if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u]))
			{
				while ((*top)->data != u || (*top)->data2 != v)
				{
					printf("%d--%d ", (*top)->data, (*top)->data2);
					(*top) = pop(*top);
				}
				if (top != NULL)
				{
					printf("%d--%d ", (*top)->data, (*top)->data2);
					(*top) = pop(*top);
				}
				(*count) += 1;
				printf("\n");
			}
		}
		else if (v != parent[u])
		{
			if (low[u] > disc[v])
			{
				low[u] = disc[v];
				(*top) = push(*top, u, v);
			}
		}
		temp = temp->next;
	}
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
	int disc[n+1], low[n+1], parent[n+1];
	bool visited[n+1], is_ap[n+1];
	for(i=1; i<=n; ++i)
	{
		visited[i] = false;
		is_ap[i] = false;
		parent[i] = -1;
	}
	int count = 0;
	for(i=1; i<=n; ++i)
	{
		stack *top = NULL;
		if (!visited[i])
		{
			dfs(adj, visited, parent, disc, low, &top, &count, i);
		}
		bool component = false;
		while (top!=NULL)
		{
			component = true;
			printf("%d--%d ", top->data, top->data2);
			top = pop(top);
		}
		if (component)
		{
			count += 1;
			printf("\n");
		}
	}
	printf("\n");
	return 0;
}