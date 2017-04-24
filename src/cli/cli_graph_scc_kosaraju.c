#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cli.h"
#include "graph.h"
#include "stack.h"
#include <stdbool.h>

void
cli_graph_scc_kosaraju(char *cmdline, int *pos)
{

	StackNode *stack = malloc(sizeof(stack));
	vertex_t v;
	int i = 1;
	//printf("ENTERED: cli_graph_transpose\n" );
	graph_t transposed = graph_transpose(current);
	graph_print(transposed, 0);
	printf("\n");
	int  num_of_vertices = graph_count_vertices(current);

	printf("~~~> %d\n",num_of_vertices );

	//instructions();
	bool visited[num_of_vertices];

	for( int i = 0 ; i < num_of_vertices ; i++)
	{
		visited[i] = false;
	}



	for(v = current->v ; v != NULL ; v = v->next)
	{
		if(!visited[i])
		{
			push(&stack, v->id);
		}
		i++;
	}

	while(! isEmpty(stack))
	{
		printf("%d\n", pop(&stack) );
	}

	//printStack(stack);
}