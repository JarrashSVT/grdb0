#include "graph.h"

/* APIs */

// a function to return the number of normal froms graph for a given graph g
int graph_normal_form_count(graph_t g);

// a function to return an array of normal from graph(s) for a given graph g
graph_t* graph_normal_form_get(graph_t g);

// a function to join 2 graphs and return the joined graph
graph_t graph_join(graph_t g1, graph_t g2);