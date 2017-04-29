#include "graph.h"
#include <stdbool.h>

#define HASHSIZE 255

struct visited { /* table entry: */
	vertexid_t v_id; /* next entry in chain */
   	bool is_visited;
};

//typedef struct visited *visited_list;

void add(vertexid_t v_id, bool is_visited);
bool lookup(vertexid_t v_id);