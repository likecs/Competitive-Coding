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

typedef struct node link_list;

void print_list(link_list *a)
{
	if (a == NULL)
	{
		printf("List is empty\n");
		return;
	}
	while (a!=NULL)
	{
		printf("%d ", a->data);
		a = a->next;
	}
	printf("\n");
}

link_list* add_front(link_list *a, int val)
{
	link_list *ref = (link_list*)malloc(sizeof(link_list));
	ref->data = val;
	ref->next = a;
	a = ref;
	return a;
}

link_list* add_end(link_list *a, int val)
{
	link_list *ref = (link_list*)malloc(sizeof(link_list));
	ref->data = val;
	ref->next = NULL;
	link_list *last = a;
	if (last==NULL)
	{
		a = ref;
	}
	else
	{
		while(last->next!=NULL)
			last = last->next;
		last->next = ref;
	}
	return a;
}

link_list* delete_front(link_list *a)
{
	if (a==NULL)
	{
		printf("List is empty");
		return a;
	}
	link_list *ref = a;
	a = a->next;
	printf("Data deleted is %d\n", ref->data);
	free(ref);
	return a;
}

link_list* delete_end(link_list *a)
{
	if (a==NULL)
	{
		printf("List is empty");
		return a;
	}
	link_list *prev = a;
	link_list *last = a->next;
	if (last != NULL)
	{
		while (last->next!=NULL)
		{
			prev = last;
			last = last->next;
		}
		prev->next = NULL;
		printf("Data deleted is %d\n", last->data);
		free(last);
	}
	else
	{
		a = NULL;
		printf("Data deleted is %d\n", prev->data);
		free(prev);
	}
	return a;
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif

	link_list *root = NULL;
	while (1)
	{
		int choice;
		scanf("%d", &choice);
		if (choice == 1)
		{
			int dat;
			scanf("%d", &dat);
			root = add_front(root, dat);
		}
		else if (choice == 2)
		{
			int dat;
			scanf("%d", &dat);
			root = add_end(root, dat);
		}
		else if (choice == 3)
		{
			root = delete_front(root);
		}
		else if (choice == 4)
		{
			root = delete_end(root);
		}
		else
		{
			break;
		}
		print_list(root);
	}

	return 0;
}