#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


void
graph_init(graph_t g)
{
	assert (g != NULL);
	memset(g, 0, sizeof(struct graph));
}

void
graph_insert_vertex(graph_t g, vertex_t v)
{
	vertex_t w;

	assert (g != NULL);
	assert (v != NULL);

	if (g->v == NULL) {
		/* Insert vertex into empty graph */
		g->v = v;
		return;
	}
	/* Insert at the end of the double linked list */
	for (w = g->v; w->next != NULL; w = w->next);
	w->next = v;
	v->prev = w;
}

vertex_t
graph_find_vertex_by_id(graph_t g, vertexid_t id)
{
	vertex_t v;

	assert (g != NULL);

	for (v = g->v; v != NULL; v = v->next)
		if (v->id == id)
			return v;

	return NULL;
}


edge_t
graph_find_edge_by_ids(graph_t g, vertexid_t id1, vertexid_t id2)
{
	edge_t e;

	assert (g != NULL);

	for (e = g->e; e != NULL; e = e->next)
		if (e->id1 == id1 && e->id2 == id2)
			return e;

	return NULL;
}

void
graph_insert_edge(graph_t g, edge_t e)
{
	edge_t f;

	if (g->e == NULL) {
		/* Insert edge into empty graph edge set */
		g->e = e;
		return;
	}
	/* Insert at the end of the double linked list */
	for (f = g->e; f->next != NULL; f = f->next);
	f->next = e;
	e->prev = f;
}

void
graph_print(graph_t g, int with_tuples)
{
	vertex_t v;
	edge_t e;

	assert (g != NULL);

	printf("({");
	/* Vertices */
	for (v = g->v; v != NULL; v = v->next) {
		vertex_print(v);
		if (v->tuple != NULL && with_tuples)
			tuple_print(v->tuple, g->el);
		if (v->next != NULL)
			printf(",");
	}

	printf("},{");
	/* Edges */
	for (e = g->e; e != NULL; e = e->next) {
		edge_print(e);
		if (e->tuple != NULL && with_tuples)
			tuple_print(e->tuple, g->el);
		if (e->next != NULL)
			printf(",");
	}
	printf("})");
}

graph_t
graph_transpose(graph_t g)
{
	//printf("ENTERED: graph_transpose\n" );
	
	vertex_t v;
	graph_t gt;
	edge_t e ,et;

	assert(g != NULL);

	/* Create new graph */
	gt = (graph_t) malloc(sizeof(struct graph));
	assert (gt != NULL);
	graph_init(gt);

	for (v = g->v ; v !=NULL ; v = v->next)
	{
		if(v->id == 1)
			graph_insert_vertex(gt, v);
	}


	for(e = g->e ; e != NULL ; e = e->next)
	{
		et = (edge_t) malloc(sizeof(struct edge));
		assert (et != NULL);
		edge_init(et);
		edge_set_vertices(et, e->id2, e->id1);
		graph_insert_edge(gt, et);
	}

	return gt;


}

int 
graph_count_vertices(graph_t g)
{
	int count = 0;
	vertex_t v;

	for(v = g->v ; v != NULL ; v = v->next)
	{
		count++;
	}

	return count;

}



vertex_with_neighbors_t
graph_find_vertex_neighbors(graph_t g, vertexid_t vid, int* count)
{
	
	assert (g != NULL);
	vertex_with_neighbors_t vwn;
	vwn = (vertex_with_neighbors_t) malloc(sizeof(struct vertex_with_neighbors));
	
	edge_t e;
	int cnt = 0;

	vertex_with_neighbors_init(vwn);
	
	vwn = vertex_with_neighbors_prepend(vwn, vid);
	
	for (e = g->e; e != NULL; e = e->next)
	{
	
		if (e->id1 == vid)
		{
			vwn = vertex_with_neighbors_append(vwn, e->id2);
			cnt++;
		}
	}

	*count = cnt;
	return vwn->next;
}
