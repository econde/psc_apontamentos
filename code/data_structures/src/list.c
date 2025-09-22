#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

struct list_node {
	struct list_node *next, *prev;
	void *data;
};

void list_init(struct list_node *node)
{
	node->next = node->prev = node;
}

struct list_node *list_create()
{
	struct list_node *node = malloc(sizeof *node);
	if (NULL == node)
		return NULL;
	node->next = node->prev = node;
	return node;
}

void list_destroy(struct list_node *list)
{
	for (struct list_node *next, *node = list->next; node != list; node = next) {
		next = node->next;
		free(node);
	}
	free(list);
}

int list_insert_sort(struct list_node *list, void *data,
				bool (*compare)(const void*, const void*))
{
	struct list_node *node;
	for (node = list->next;
		node != list && compare(node->data, data) < 0; node = node->next)
		;
	return list_insert_rear(node, data);
}

struct list_node *list_search(struct list_node *list,
	bool (*predicate)(const void *, const void *), const void *context)
{
	for (struct list_node *p = list->next; p != list; p = p->next)
		if (predicate(p->data, context))
			return p;
	return NULL;
}

struct list_node *list_search_forward(struct list_node *list,
	bool (*predicate)(const void *, const void *), const void *context)
{
	for (struct list_node *p = list->next; p != list; p = p->next)
		if (predicate(p->data, context))
			return p;
	return NULL;
}

struct list_node *list_search_backward(struct list_node *list,
	bool (*predicate)(const void *, const void *), const void *context)
{
	for (struct list_node *p = list->prev; p != list; p = p->prev)
		if (predicate(p->data, context))
			return p;
	return NULL;
}

int list_insert_front(struct list_node *node, void *data)
{
	struct list_node *new_node = malloc(sizeof *new_node);
	if (NULL == new_node)
		return 0;
	new_node->data = data;

	new_node->next = node->next;
	new_node->prev = node;
	node->next->prev = new_node;
	node->next = new_node;
	return 1;
}

int list_insert_rear(struct list_node *node, void *data)
{
	struct list_node *new_node = malloc(sizeof *new_node);
	if (NULL == new_node)
		return 0;
	new_node->data = data;

	new_node->prev = node->prev;
	new_node->next = node;
	node->prev->next = new_node;
	node->prev = new_node;
	return 1;
}

void list_remove(struct list_node *node) {
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
}

void list_remove_front(struct list_node *node)
{
	list_remove(node->next);
}

void list_remove_rear(struct list_node *node)
{
	list_remove(node->prev);
}

void list_foreach(struct list_node *node,
		void (*do_it)(void *, void *), void *context)
{
	for (struct list_node *p = node->next; p != node; p = p->next)
		do_it(p->data, context);
}

struct list_node *list_get_front(struct list_node *node)
{
	return node->next;
}

struct list_node *list_get_rear(struct list_node *node)
{
	return node->prev;
}

void *list_get_data(struct list_node *node)
{
	return node->data;
}

int list_empty(struct list_node *node)
{
	return node->next == node;
}

size_t list_size(struct list_node *list)
{
	size_t size = 0;
	for (struct list_node *p = list->next; p != list; p = p->next)
		size++;
	return size;
}
