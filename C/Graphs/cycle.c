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

struct Node
{
	int data;
	struct Node *next;
};

typedef struct Node node;

struct Q
{
	node *front;
	node *rear;
};

typedef struct Q queue;

void print_list(queue *w)
{
	node *a = w->front;
	if (a == NULL)
	{
		printf("Queue is empty\n");
		return;
	}
	while (a!=NULL)
	{
		printf("%d ", a->data);
		a = a->next;
	}
	printf("\n");
}

queue* push_back(queue *a, int val)
{
	node *ref = (node*)malloc(sizeof(node));
	ref->data = val;
	ref->next = NULL;
	node *start = a->front;
	node *end = a->rear;
	if (start==NULL)
	{
		a->front = ref;
		a->rear = ref;
	}
	else
	{
		while(end->next!=NULL)
			end = end->next;
		end->next = ref;
		a->rear = ref;
	}
	return a;
}

queue* pop_front(queue *a)
{
	node *start = a->front;
	node *end = a->rear;
	if (start==NULL)
	{
		printf("Queue is empty");
	}
	else if (start == end)
	{
		a->front = NULL;
		a->rear = NULL;
		// printf("Data deleted is %d\n", start->data);
		free(start);
	}
	else
	{
		a->front = a->front->next;
		// printf("Data deleted is %d\n", start->data);
		free(start);
	}
	return a;
}

queue* pop_back(queue *a)
{
	node *start = a->front;
	node *end = a->rear;
	if (start==NULL)
	{
		printf("Queue is empty\n");
	}
	else if (start == end)
	{
		a->front = NULL;
		a->rear = NULL;
		// printf("Data deleted is %d\n", end->data);
		free(start);
	}
	else
	{
		while (start->next != end)
			start = start->next;
		start->next = NULL;
		a->rear = start;
		// printf("Data deleted is %d\n", end->data);
		free(end);
	}
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

void check_cycle(graph **adj, int n)
{
	int color[n+1], parent[n+1], level[n+1];
	int i, j, k;
	for(i=0; i<=n; ++i)
	{
		color[i] = 0;
		parent[i]  = i;
		level[i] = -1;
	}
	bool has_cycle = false;
	for(i=1; i<=n; ++i)
	{
		if (color[i] == 0)
		{
			color[i] = 1;
			level[i] = 0;
			queue *root = (queue *)malloc(sizeof(queue));
			root->front = NULL;
			root->rear = NULL;
			root = push_back(root, i);
			while (root->front != NULL)
			{
				int s = root->front->data;
				root = pop_front(root);
				graph *temp = adj[s];
				while (temp!=NULL)
				{
					if (color[temp->dest] == 0)
					{
						color[temp->dest] = 1;
						level[temp->dest] = level[s] + 1;
						parent[temp->dest] = s;
						root = push_back(root, temp->dest);
					}
					if (color[temp->dest] == 1)
					{
						has_cycle = true;
						break;
					}
					temp = temp->next;
				}
				color[s] = 2;
			}
		}
		if (has_cycle)
			break;
	}
	if (has_cycle)
	{
		printf("There is cycle in graph\n");
		return;
	}
	for(i=1; i<=n; ++i)
	{
		printf("%d : %d %d\n", i, parent[i], level[i]);
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
	check_cycle(adj, n);

	return 0;
}