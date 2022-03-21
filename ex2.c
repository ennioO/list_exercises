#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node
{
	int32_t data;
	struct node * next;
} node_t;

void add_node(node_t * base, int32_t item)
{
	node_t * current = base;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = (node_t *) malloc (sizeof(node_t));

	current->next->data = item;
	current->next->next = NULL;
}

int32_t delete_node(node_t * base)
{
	int32_t retdata;
	node_t * current = base;
	if (current->next == NULL)
	{
		retdata = current->data;
		free(current);
		return retdata;
	}

	while (current->next->next != NULL)
	{
		current = current->next;
	}
	retdata = current->next->data;
	free(current->next);
	current->next = NULL;
	return retdata;
}

void print_list(node_t * base)
{
	uint32_t i = 0;
	node_t * current = base;
	while (1)
	{
		printf("Node %d: %d\n", ++i, current->data);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

node_t * reverse_list(node_t * base)
{
	node_t * prev;
	node_t * temp;
	node_t * current;
	current = base;
	if (current->next == NULL)
		return base;
	current = current->next;
	base->next = NULL;
	prev = base;

	while (current->next != NULL)
	{
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	current->next = prev;

	return current;

}

int32_t main(int32_t argc, int8_t ** argv)
{
	uint32_t node_num = atoi(argv[1]);

	node_t * base;
	base = (node_t *) malloc (sizeof(node_t));
	base->data = atoi(argv[2]);
	base->next = NULL;

	int32_t i;
	for (i = 0; i < node_num-1; i++)
	{
		add_node(base, atoi(argv[3+i]));
	}

	print_list(base);

	node_t * reverse_base;
	reverse_base = reverse_list(base);
	print_list(reverse_base);

	for (i = 0; i< node_num; i++)
	{
		delete_node(reverse_base);
	}

	return 0;
}
