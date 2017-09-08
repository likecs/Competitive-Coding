#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#define MAX 			2005
#define INF 			1000000000
#define false 			0
#define true 			1

struct heap
{
	int freq;
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
	if (min_pq[i]->freq == min_pq[j]->freq)
		return (min_pq[i]->data < min_pq[j]->data);
	return (min_pq[i]->freq < min_pq[j]->freq);
}

void initialise()
{
	int i;
	for(i=0; i<MAX; ++i)
        min_pq[i] = (heap *)calloc(1, sizeof(heap));
}

void print(heap *x)
{
    printf("%d --> %d, ", x->data, x->freq);
}

void print_heap()
{
    int i;
    for (i=1; i<=min_pq[0]->size; ++i)
        print(min_pq[i]);
    printf("\n");
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

void build_min_heap()
{
	int i, j = (min_pq[0]->size)/2;
	for(i=j; i>=1; --i)
		min_heapify(i);
}

heap *heap_minimum()
{
	return min_pq[1];
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
	if (key > min_pq[i]->freq)
	{
		printf("New key is greater than current key\n");
		return ;
	}
	min_pq[i]->freq = key;
	while ((i>1) && (cmp(i, parent(i))))
	{
		swap(min_pq[i], min_pq[parent(i)]);
		i = parent(i);
	}
}

void insert(heap *temp)
{
	min_pq[0]->size += 1;
	min_pq[min_pq[0]->size] = temp;
	heap_decrease_key(min_pq[0]->size, temp->freq);
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif
	initialise();
	int n;
	scanf("%d", &n);
	int i, x, y;
	for (i=0; i<n; ++i)
	{
		heap *t = (heap *)malloc(sizeof(heap));
		scanf("%d %d", &x, &y);
		t->data = x;
		t->freq = y;
		insert(t);
	}

	// build_min_heap();
    printf("Initial --->\n");
    print_heap();
    printf("\n");

    // random insert and extract operations on heap

	for(i=0; i<=n; ++i)
	{
		heap *temp = heap_extract_minimum();
		printf("%d---> %d %d\n", i+1, temp->data, temp->freq);

	   	print_heap();

		if (i%2==0)
		{
	      	heap *t = (heap *)malloc(sizeof(heap));
	      	t->data = n % (i+1);
	      	t->freq = temp->data;
	      	printf("inserted-> %d %d\n", t->data, t->freq);
	      	insert(t);
	      	print_heap();
		}

		printf("************\n");
	}
	return 0;
}