#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void
vertex_with_neighbors_init(vertex_with_neighbors_t vwn)
{
	assert(vwn != NULL);
	memset(vwn, 0, sizeof(struct vertex_with_neighbors));
}

void
vertex_with_neighbors_set_id(vertex_with_neighbors_t vwn, vertexid_t id)
{
	assert(vwn != NULL);

	vwn->id = id;
}

void
vertex_with_neighbors_print(vertex_with_neighbors_t vwn)
{
	assert(vwn != NULL);

	//printf("%04llx", v->id);
	printf("%llu", vwn->id);
	//printf("\n");
}


vertex_with_neighbors_t
vertex_with_neighbors_create(vertexid_t id , vertex_with_neighbors_t next)
{
	vertex_with_neighbors_t v;
	v = (vertex_with_neighbors_t) malloc(sizeof(struct vertex_with_neighbors));
	assert (v != NULL);
	vertex_with_neighbors_init(v);
	v->id = id;
	v->next = next;
	return v;
}

vertex_with_neighbors_t
vertex_with_neighbors_prepend(vertex_with_neighbors_t head, vertexid_t id)
{
	vertex_with_neighbors_t v;
	v = vertex_with_neighbors_create(id, head);
	head = v;
	return head;
}

vertex_with_neighbors_t
vertex_with_neighbors_append(vertex_with_neighbors_t head, vertexid_t id)
{
	vertex_with_neighbors_t cursor;
	vertex_with_neighbors_t new_v;
	
	// go to the last node
	cursor = head;
	
	while(cursor->next != NULL)
		cursor = cursor->next;

	// create new vertex
	new_v = vertex_with_neighbors_create(id, NULL);

	cursor->next = new_v;
	return head;
}
