#ifndef __GRAPH_H
#define __GRAPH_H


#include "schema.h"
#include "tuple.h"
#include "vertexid.h"


struct vertex {
	/* Every vertex has a unique vertex id */
	vertexid_t id;

	/* Links for vertex set data structure in memory */
	struct vertex *prev;
	struct vertex *next;

	/* Vertex tuple */
	tuple_t tuple;
};

struct edge {
	/* Every edge has two vertex ids */
	vertexid_t id1, id2;

	/* Links for edge set data structure in memory */
	struct edge *prev;
	struct edge *next;

	/* Edge tuple */
	tuple_t tuple;
};

struct graph {
	struct vertex *v;	/* Vertices */
	schema_t sv;		/* Vertex schema */
	struct edge *e;		/* Edges */
	schema_t se;		/* Edge schema */
	enum_list_t el;		/* List of enums */

	struct graph *next;
};

struct vertex_with_neighbors {
	/* Every vertex has a unique vertex id */
	vertexid_t id;

	
	struct vertex_with_neighbors *prev;
	struct vertex_with_neighbors  *next;

	/* Vertex tuple */
	//tuple_t tuple;
};

typedef struct vertex_with_neighbors *vertex_with_neighbors_t;
typedef struct edge *edge_t;
typedef struct graph *graph_t;
typedef struct vertex *vertex_t;

void vertex_init(vertex_t v);
void vertex_set_id(vertex_t v, vertexid_t id);
void vertex_print(vertex_t v);

void vertex_with_neighbors_init(vertex_with_neighbors_t vwn);
void vertex_with_neighbors_set_id(vertex_with_neighbors_t vwn, vertexid_t id);
void vertex_with_neighbors_print(vertex_with_neighbors_t vwn);
vertex_with_neighbors_t vertex_with_neighbors_create(vertexid_t id , vertex_with_neighbors_t next);
vertex_with_neighbors_t vertex_with_neighbors_prepend(vertex_with_neighbors_t head, vertexid_t id);
vertex_with_neighbors_t vertex_with_neighbors_append(vertex_with_neighbors_t head, vertexid_t id);

void edge_init(edge_t e);
void edge_set_vertices(edge_t e, vertexid_t id1, vertexid_t id2);
void edge_print(edge_t e);

void graph_init(graph_t g);
void graph_insert_vertex(graph_t g, vertex_t v);
vertex_t graph_find_vertex_by_id(graph_t g, vertexid_t id);
edge_t graph_find_edge_by_ids(graph_t g, vertexid_t id1, vertexid_t id2);
void graph_insert_edge(graph_t g, edge_t e);
void graph_print(graph_t g, int with_tuples);
graph_t graph_transpose(graph_t g);
int graph_count_vertices(graph_t g);
vertex_with_neighbors_t graph_find_vertex_neighbors(graph_t g, vertexid_t vid, int* count);

#endif
