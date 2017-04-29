#include "api.h"
#include <stdlib.h>
/* APIs */


int graph_normal_form_count(graph_t g) { return 1;}


graph_t* graph_normal_form_get(graph_t g) 
{ 
	int n = graph_normal_form_count(g);
	
	graph_t* gnf;
	gnf = malloc( n * sizeof(graph_t));
	
	return gnf;
}


graph_t graph_join(graph_t g1, graph_t g2) {return g1;}