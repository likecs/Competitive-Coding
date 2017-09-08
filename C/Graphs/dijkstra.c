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

struct heap
{
	int weight;
	int data;
	int size;
};

typedef struct heap heap;

heap *min_pq[MAX];

int parent(int i)
{
	return (i/2);
}

int left(int i)
{
	return i+i;
}

int right(int i)
{
	return i+i+1;
}

void swap(heap *a, heap *b)
{
	heap c = *a;
	*a = *b;
	*b = c;
}

bool cmp(int i, int j)
{
	if (min_pq[i]->weight == min_pq[j]->weight)
		return (min_pq[i]->data < min_pq[j]->data);
	return (min_pq[i]->weight < min_pq[j]->weight);
}

void initialise()
{
	int i;
	for(i=0; i<MAX; ++i)
        min_pq[i] = (heap *)calloc(1, sizeof(heap));
}

void min_heapify(int i)
{
	int l = left(i);
	int r = right(i);

	int smallest = i;

	if (l <= min_pq[0]->size)
	{
		if (cmp(l, smallest))
			smallest = l;
	}
	if (r <= min_pq[0]->size)
	{
		if (cmp(r, smallest))
			smallest = r;
	}

	if (smallest != i)
	{
		swap(min_pq[i], min_pq[smallest]);
		min_heapify(smallest);
	}
}

heap *heap_extract_minimum()
{
	if (min_pq[0]->size < 1)
	{
		printf("heap underflow\n");
		exit(0);
	}

	heap *w;
	swap(min_pq[1], min_pq[min_pq[0]->size]);

	w = min_pq[min_pq[0]->size];
	min_pq[0]->size -= 1;
	min_heapify(1);
	return w;
}

void heap_decrease_key(int i, int key)
{
	if (key > min_pq[i]->weight)
	{
		printf("New key is greater than current key\n");
		return ;
	}
	min_pq[i]->weight = key;
	while ((i>1) && (cmp(i, parent(i))))
	{
		swap(min_pq[i], min_pq[parent(i)]);
		i = parent(i);
	}
}

void insert(int x, int y)
{
	heap *temp = (heap *)malloc(sizeof(heap));
	temp->weight = x;
	temp->data = y;
	min_pq[0]->size += 1;
	min_pq[min_pq[0]->size] = temp;
	heap_decrease_key(min_pq[0]->size, temp->weight);
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

void dijkstra(graph **adj, int n)
{
	int parent[n+1], ans[n+1];
	int i, j, k;
	for(i=0; i<=n; ++i)
	{
		parent[i]  = -1;
		ans[i] = INF;
	}
	ans[1] = 0;
	initialise();
	insert(0, 1);
	while (min_pq[0]->size >= 1)
	{
		heap *t = heap_extract_minimum();
		int d = t->weight;
		int u = t->data;
		if (d != ans[u])
			continue;
		graph *temp = adj[u];
		while (temp != NULL)
		{
			int v = temp->dest;
			int check = temp->weight + ans[u];
			if (check < ans[v])
			{
				ans[v] = check;
				parent[v] = u;
				insert(check, v);
			}
			temp = temp->next;
		}
	}
	for(i=1; i<=n; ++i)
		printf("%d %d\n", i, ans[i]);
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
	dijkstra(adj, n);

	return 0;
}