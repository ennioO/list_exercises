/****************************************************************************
* https://www.w3resource.com/c-programming-exercises/linked_list/index.php
****************************************************************************/
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

uint32_t delete_last(node_t * base)
{
	uint32_t retdata;
	node_t * current = base;
	if (current->next == NULL)
	{
		retdata = current->data;
		printf("deleted node %p\n", current);
		free(current);
		return retdata;
	}
	while (current->next->next != NULL)
	{
		current = current->next;
	}
	retdata = current->next->data;
	printf("deleted node %p\n", current->next);
	free(current->next);
	current->next = NULL;
	return retdata;

}

void print_list(node_t * base)
{
	node_t * current = base;
	uint32_t i = 0;
	while (1)
	{
		printf("Node %d: %d %p\n", ++i, current->data, current);
		if (current->next == NULL)
			break;
		current = current->next;
	}
}

int main(int32_t argc, uint8_t ** argv)
{
	uint32_t node_num = atoi(argv[1]);

	node_t * base;
	base = (node_t *) malloc (sizeof(node_t));
	base->data = atoi(argv[2]);
	base->next = NULL;
	
	int32_t i;
	int32_t item;
	for (i = 0; i < node_num-1; i++)
	{
		item = atoi(argv[3+i]);
		add_node(base, item);
	}

	print_list(base);
	
	for (i = 0; i < node_num; i++)
	{
		delete_last(base);
	}

	return 0;
}
