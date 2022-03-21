#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node
{
	int32_t data;
	struct node * prev;
	struct node * next;
} node_t;

node_t * add_last(node_t * head, int32_t data)
{
	head->next = (node_t *) malloc (sizeof(node_t));
	if (head->next == NULL)
	{
		printf("error\n");
		exit(1);
	}
	head->next->data = data;
	head->next->next = NULL;
	head->next->prev = head;

	return head->next;
}

node_t * add_first(node_t * base, int32_t data)
{
	base->prev = (node_t *) malloc (sizeof(node_t));
	if (base->prev == NULL)
	{
		printf("error\n");
		exit(1);
	}
	base->prev->data = data;
	base->prev->prev = NULL;
	base->prev->next = base;

	return base->prev;
}

void add_any(node_t * base, uint32_t index, int32_t data)
{
	node_t * current = base;
	node_t * prev;
	uint32_t pos = 1;

	while (pos != index)
	{
		current = current->next;
		pos++;
	}

	prev = current->prev;
	current->prev = (node_t *) malloc (sizeof(node_t));
	if (current->prev == NULL)
	{
		printf("error\n");
		exit(1);
	}
	prev->next = current->prev;
	current->prev->data = data;
	current->prev->next = current;
	current->prev->prev = prev;

}

node_t * delete_last(node_t * head)
{
	if (head->prev == NULL)
	{
		printf("deleted node %p\n", head);
		free(head);
		return NULL;
	}
	node_t * new_head = head->prev;
	head->prev->next = NULL;
	printf("deleted node %p\n", head);
	free(head);

	return new_head;
}

node_t * delete_first(node_t * base)
{
	if (base->next == NULL)
	{
		printf("deleted node %p\n", base);
		free(base);
		return NULL;
	}
	node_t * new_base = base->next;
	base->next->prev = NULL;
	printf("deleted node %p\n", base);
	free(base);

	return new_base;
}

void delete_any(node_t * base, uint32_t index)
{
	node_t * current = base;
	uint32_t pos = 1;

	while (pos != index)
	{
		current = current->next;
		pos++;
	}

	current->prev->next = current->next;
	current->next->prev = current->prev;

	printf("deleted node %p\n", current);
	free(current);
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

void print_reverse(node_t * head)
{
	node_t * current = head;
	uint32_t num_nodes = 1;

	while (current->prev != NULL)
	{
		current = current->prev;
		num_nodes++;
	}

	current = head;
	while (1)
	{
		printf("Node %d: %d %p\n", num_nodes--, current->data, current);
		if (current->prev == NULL)
			break;
		current = current->prev;
	}
}

int32_t main(int32_t argc, int8_t ** argv)
{
	node_t * base;
	node_t * head;
	int32_t node_num = atoi(argv[1]);
	int32_t i;

	base = (node_t *) malloc (sizeof(node_t));
	if (base == NULL)
	{
		printf("error\n");
		return 0;
	}
	base->data = atoi(argv[2]);
	base->next = NULL;
	base->prev = NULL;
	head = base;

	for (i = 0; i < node_num-1; i++)
		head = add_last(head, atoi(argv[3+i]));

	print_list(base);
	printf("\n");
	print_reverse(head);
	printf("\n");

	base = add_first(base, 7);

	print_list(base);
	printf("\n");
	print_reverse(head);
	printf("\n");

	head = add_last(head, 9);

	print_list(base);
	printf("\n");
	print_reverse(head);
	printf("\n");

	add_any(base, 3, 10);
	print_list(base);
	printf("\n");
	print_reverse(head);
	printf("\n");

	delete_any(base, 5);
	print_list(base);
	printf("\n");
	print_reverse(head);
	printf("\n");

	for (i = 0; i < node_num+2; i++)
		base = delete_first(base);

	return 0;

}
