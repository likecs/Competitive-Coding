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
		printf("Data deleted is %d\n", start->data);
		free(start);
	}
	else
	{
		a->front = a->front->next;
		printf("Data deleted is %d\n", start->data);
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
		printf("Data deleted is %d\n", end->data);
		free(start);
	}
	else
	{
		while (start->next != end)
			start = start->next;
		start->next = NULL;
		a->rear = start;
		printf("Data deleted is %d\n", end->data);
		free(end);
	}
	return a;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	queue *root = (queue *)malloc(sizeof(queue));
	root->front = NULL;
	root->rear = NULL;

	while (1)
	{
		int choice;
		scanf("%d", &choice);
		if (choice == 1)
		{
			int dat;
			scanf("%d", &dat);
			root = push_back(root, dat);
		}
		else if (choice == 2)
		{
			root = pop_front(root);
		}
		else if (choice == 3)
		{
			root = pop_back(root);
		}
		else
		{
			break;
		}
		print_list(root);
	}

	return 0;
}