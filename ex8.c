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
		current = current ->next;

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
		printf("deleted node %p\n", current);
		free(current);
		return;
	}

	while (current->next->next != NULL)
		current = current->next;

	printf("deleted node %p\n", current->next);
	free(current->next);
	current->next = NULL;
}

void delete_middle(node_t * base, uint32_t index)
{
	node_t * current = base;
	node_t * prev;
	int32_t i = 1;

	while (i != index)
	{
		prev = current;
		current = current->next;
		i++;
	}

	prev->next = current->next;
	printf("deleted node %p\n", current);
	free(current);
}

void print_list(node_t * base)
{
	node_t * current = base;
	uint32_t i = 0;

	while(1)
	{
		printf("Node %d: %d %p\n", ++i, current->data, current);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

int32_t main(int32_t argc, int8_t ** argv)
{
	node_t * base;
	int32_t node_num = atoi(argv[1]);
	int32_t i;

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

	delete_middle(base, 2);

	print_list(base);

	for (i = 0; i < node_num-1; i++)
		delete_node(base);

	return 0;


}
