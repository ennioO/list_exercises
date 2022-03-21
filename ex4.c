#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
	if (base->next == NULL)
	{
		retdata = base->data;
		return retdata;
	}

	node_t * current = base;
	while (current->next->next !=NULL)
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
	node_t * current = base;
	int32_t i = 0;

	while (1)
	{
		printf("Node %d: %d\n", ++i, current->data);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

node_t * add_first(node_t * base, int32_t item)
{
	node_t * new_node;
	new_node = (node_t *) malloc (sizeof(node_t));
	
	new_node->data = item;
	new_node->next = base;
	base = new_node;

	return base;
}

int32_t main(int32_t argc, int8_t ** argv)
{
	uint32_t num_nodes = atoi(argv[1]);
	int32_t i;
	node_t * base;

	base = (node_t *) malloc (sizeof(node_t));
	base->data = atoi(argv[2]);
	base->next = NULL;
	for (i = 0; i < num_nodes-1; i++)
	{
		add_node(base, atoi(argv[3+i]));
	}

	print_list(base);

	node_t * new_base;
	new_base = add_first(base, 1);

	print_list(new_base);

	for (i = 0; i < num_nodes; i++)
		delete_node(new_base);

	return 0;
}
