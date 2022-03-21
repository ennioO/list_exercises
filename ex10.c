#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node
{
	int32_t data;
	struct node * next;
} node_t;

void add_node(node_t * base, int32_t data)
{
	node_t * current = base;

	while (current->next != NULL)
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
	current->next->next = NULL;
}

void delete_node(node_t * base)
{
	node_t * current = base;

	if (current->next == NULL)
	{
		free(current);
		return;
	}

	while (current->next->next != NULL)
	{
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
}

void print_list(node_t * base)
{
	node_t * current = base;
	uint32_t i = 0;

	while (1)
	{
		printf("Node %d: %d\n", ++i, current->data);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

uint32_t search_data(node_t * base, int32_t data)
{
	node_t * current = base;
	int32_t index = 1;

	while (current->data != data)
	{
		if (current->next == NULL)
		{
			return 0;
		}
		current = current->next;
		index++;
	}

	return index;
}

int32_t main(int32_t argc, int8_t ** argv)
{
	node_t * base;
	uint32_t node_num = atoi(argv[1]);
	uint32_t i;

	base = (node_t *) malloc (sizeof(node_t));
	if (base == NULL)
	{
		printf("error\n");
		exit(1);
	}
	base->data = atoi(argv[2]);
	base->next = NULL;

	for (i = 0; i < node_num-1; i++)
		add_node(base, atoi(argv[3+i]));

	print_list(base);

	uint32_t index;
	int32_t data = 5;
	index = search_data(base, data);
	if (index != 0)
		printf("%d found in node %d\n", data, index);
	else
		printf("%d not found in list\n", data);
	
	data = 9;
	index = search_data(base, data);
	if (index != 0)
		printf("%d found in node %d\n", data, index);
	else
		printf("%d not found in list\n", data);

	for (i = 0; i < node_num; i++)
		delete_node(base);

	return 0;
}
