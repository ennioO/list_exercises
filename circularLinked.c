#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node
{
	int32_t data;
	struct node * next;
} node_t;

void add_last(node_t * base, int32_t data)
{
	node_t * current = base;

	while (current->next != base)
	{
		current = current->next;
	}

	current->next = (node_t *) malloc (sizeof(node_t));
	if (current->next == NULL)
	{
		printf("error\n");
		exit(1);
	}
	current->next->data = data;
	current->next->next = base;
}

node_t * add_first(node_t * base, int32_t data)
{
	node_t * current = base;

	while (current->next != base)
	{
		current = current->next;
	}

	current->next = (node_t *) malloc (sizeof(node_t));
	if (current->next == NULL)
	{
		printf("error\n");
		exit(1);
	}
	current->next->data = data;
	current->next->next = base;

	return current->next;
}

void add_any(node_t * base, uint32_t index, int32_t data)
{
	node_t * current = base;
	node_t * next;
	uint32_t pos = 1;

	while (pos != index-1)
	{
		current = current->next;
		pos++;
	}

	next = current->next;
	current->next = (node_t *) malloc (sizeof(node_t));
	if (current->next == NULL)
	{
		printf("error\n");
		exit(1);
	}
	current->next->data = data;
	current->next->next = next;
}

void delete_last(node_t * base)
{
	if (base->next == base)
	{
		free(base);
		return;
	}

	node_t * current = base;
	while (current->next->next != base)
	{
		current = current->next;
	}

	free(current->next);
	current->next = base;

}

node_t * delete_first(node_t * base)
{
	node_t * current = base;
	node_t * new_base = base->next;

	while (current->next != base)
	{
		current = current->next;
	}
	current->next = new_base;
	free(base);

	return new_base;
}

void delete_any(node_t * base, uint32_t index)
{
	node_t * current = base;
	node_t * prev;
	uint32_t pos = 1;

	while(pos != index)
	{
		prev = current;
		current = current->next;
		pos++;
	}

	prev->next = current->next;
	free(current);
}

uint32_t search_data(node_t * base, int32_t data)
{
	node_t * current = base;
	uint32_t node = 1;

	while(current->data != data)
	{
		if (current->next == base)
			return 0;

		current = current->next;
		node++;
	}

	return node;
}

void print_list(node_t * base)
{
	node_t * current = base;
	uint32_t i = 0;

	while (1)
	{
		printf("Node %d: %d %p\n", ++i, current->data, current);
		printf("\tnext: %p\n", current->next);
		if (current->next == base)
			break;
		current = current->next;
	}
}

int32_t main(int32_t argc, int8_t ** argv)
{
	uint32_t node_num = atoi(argv[1]);
	int32_t i;

	node_t * base;
	base = (node_t *) malloc (sizeof(node_t));
	if (base == NULL)
	{
		printf("error\n");
		exit(1);
	}
	base->data = atoi(argv[2]);
	base->next = base;

	for (i = 0; i < node_num-1; i++)
	{
		add_last(base, atoi(argv[3+i]));
	}

	print_list(base);
	printf("\n");

	base = add_first(base, 3);

	print_list(base);
	printf("\n");

	add_any(base, 2, 0);

	print_list(base);
	printf("\n");

	base = delete_first(base);

	print_list(base);
	printf("\n");

	delete_any(base, 3);

	print_list(base);
	printf("\n");

	uint32_t search = search_data(base, 5);
	if (search == 0)
		printf("Data not found in list\n");
	else
		printf("%d found at node %d\n", 5, search);

	for (i = 0; i < node_num; i++)
	{
		delete_last(base);
	}

	return 0;
}
