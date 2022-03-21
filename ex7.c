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
		current = current->next;

	current->next = (node_t *) malloc(sizeof(node_t));
	if (current->next == NULL)
	{
		printf("erorr\n");
		exit(1);
	}

	current->next->data = data;
	current->next->next = NULL;
}

node_t * delete_first(node_t * base)
{
	node_t * new_base = base->next;
	printf("deleted node %p\n", base);
	free(base);
	return new_base;
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
	uint32_t node_num = atoi(argv[1]);

	base = (node_t *) malloc (sizeof(node_t));
	if (base == NULL)
	{
		printf("error\n");
		exit(1);
	}
	base->data = atoi(argv[2]);
	base->next = NULL;

	int32_t i;
	for (i = 0; i < node_num-1; i++)
	{
		add_node(base, atoi(argv[3+i]));
	}

	print_list(base);

	node_t * new_base = delete_first(base);

	print_list(new_base);

	for(i = 0; i < node_num-1; i++)
	{
		new_base = delete_first(new_base);
	}

	return 0;
}
