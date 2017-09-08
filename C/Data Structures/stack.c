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

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	stack *top = NULL;
	while (1)
	{
		int choice;
		scanf("%d", &choice);
		if (choice == 1)
		{
			int dat;
			scanf("%d", &dat);
			top = push(top, dat);
		}
		else if (choice == 2)
		{
			top = pop(top);
		}
		else
		{
			break;
		}
		print_list(top);
	}

	return 0;
}