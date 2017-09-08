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
	int data;
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

stack* push(stack *a, int val)
{
	stack *ref = (stack*)malloc(sizeof(stack));
	ref->data = val;
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
	printf("Data deleted is %d\n", ref->data);
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

void sort(graph **adj, bool visited[], int v, stack **root)
{
	visited[v] = true;
	graph *temp = adj[v];
	while (temp != NULL)
	{
		if (!visited[temp->dest])
		{
			sort(adj, visited, temp->dest, root);
		}
		temp = temp->next;
	}
	(*root) = push(*root, v);
}

void topo_sort(graph **a, int n)
{
	stack *top = NULL;
	bool visited[n+1];
	int i;
	for(i=0; i<=n; ++i)
	{
		visited[i] = false;
	}
	for(i=1; i<=n; ++i)
	{
		if (!visited[i])
		{
			sort(a, visited, i, &top);
		}
	}
	int order[n+1], cnt = 0;
	while (top!=NULL)
	{
		order[cnt++] = top->data;
		top = top->next;
	}
	for(i=0; i<cnt; ++i)
		printf("%d ", order[i]);
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
	topo_sort(adj, n);
	return 0;
}