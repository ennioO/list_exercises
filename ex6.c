#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node
{
	int32_t data;
	struct node * next;
} node_t;

void add_node(node_t * base, uint32_t data)
{
	node_t * current = base;
	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = (node_t *) malloc (sizeof(node_t));
	if (current->next == NULL)
	{
		printf("erorr\n");
		exit(1);
	}
	current->next->data = data;
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
	node_t * current = base;
	uint32_t i = 0;

	while(1)
	{
		printf("Node %d: %d\n", ++i, current->data);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

void add_middle(node_t * base, uint32_t index, int32_t data)
{
	node_t * current = base;
	node_t * foll;
	uint32_t i = 1;

	while (i != index-1)
	{
		current = current->next;
		i++;
	}

	foll = current->next;
	current->next = (node_t *) malloc (sizeof(node_t));
	if (current->next == NULL)
	{
		printf("error\n");
		exit(1);
	}
	current->next->next = foll;
	current->next->data = data;
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

	for (i = 0; i < node_num-1; i++)
	{
		add_node(base, atoi(argv[3+i]));
	}

	print_list(base);

	add_middle(base, 3, 5);

	print_list(base);

	for (i = 0; i < node_num; i++)
		delete_node(base);

	return 0;
}
