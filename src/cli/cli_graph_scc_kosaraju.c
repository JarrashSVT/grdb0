#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cli.h"
#include "graph.h"
#include "stack.h"
#include <stdbool.h>

bool is_vertex_in_nighbors(int val , vertex_t *neighbors, int count)
{
	int i;
	for(i = 0; i < count ; i++)
	{
		if(neighbors[i]->id == val)
			return true;
	}
	return false;
}

void
DFS(int i, vertex_t v, bool visited[], StackNode *stack)
{
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS BEGIN~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~SUMMARY BEGIN~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("i = %d\n", i);
	printf("V id is "); vertex_print(v); printf("\n");
	if(visited[i]) printf("isVisited? TRUE\n"); else printf("isVisited? FALSE\n");
	printStack(stack);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~SUMMARY END~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	visited[i] = true;
	int num_of_vertices = graph_count_vertices(current);
	int  num_of_neighbors;
	vertex_t *neighbors = malloc(num_of_vertices * sizeof(v));
	vertex_t v_next;
	neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);
	//if(v != NULL)
	//	printf("it's NOT NULL WTF!!!\n");
	/////// troublshot neighobrs
	printf("~num_of_neighbors %d\n",num_of_neighbors );
		int index;
	for(index = 0 ; index < num_of_neighbors ; index++)	
	{
		printf("neighbors[%d] is ",index);
		vertex_print(neighbors[index]);
		printf("\n");
	}
	/////////////////
	while(v != NULL)
	{
		
		if(v->next != NULL)
		{	
			v_next = v->next;
			//neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);

			if (is_vertex_in_nighbors(v_next->id, neighbors, num_of_neighbors))
				{printf("is %llu a neighbor to %llu? TRUE\n" ,v_next->id, v->id);}
			else
				{printf("is %llu a neighbor to %llu? FALSE\n" ,v_next->id, v->id);}
			i++;
			printf("i is now = %d\n", i );
			if(!visited[i])
			{
				if(is_vertex_in_nighbors(v_next->id, neighbors, num_of_neighbors))
				{
					printf("I'm in (Not visited and a neighbor) \n");
					printf("Node %llu will be visited via DFS\n", v_next->id);

					DFS(i, v_next, visited, stack);
				}
			}
			else
			{
				printf("%llu already visited\n", v_next->id);
				printf("@ i %d\n", i );
				//printf("vertex # %llu will be added to stack\n", v->id);
				//push(&stack, v->id);
				//printStack(stack);
			}
			//v = v->next;
		}
		else
		{
			//printf("vertex # %llu will be added to stack\n", v->id);
			//	push(&stack, v->id);
			//	printStack(stack);
		}
		v = v->next;
	}

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS END~~~~~~~~~~~~~~~~~~~~~~~~\n");

}

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
	int  num_of_neighbors;
	vertex_t *neighbors = malloc(num_of_vertices * sizeof(vertex_t));
	printf("num_of_vertices = %d\n",num_of_vertices );

	for(v = current->v ; v != NULL ; v = v->next)
	{
		//vertex_print(v);
		//printf("\n");
		if(v->id == 1)
			neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);
	}

	printf("num_of_neighbors %d\n",num_of_neighbors );
	int index;
	for(index = 0 ; index < num_of_neighbors ; index++)	
	{
		printf("neighbors[%d] is ",index);
		vertex_print(neighbors[index]);
		printf("\n");
	}


	//instructions();
	bool visited[num_of_vertices];

	for( int j = 1 ; j <= num_of_vertices ; j++)
	{
		visited[j] = false;
	}

	for( int j = 1 ; j <= num_of_vertices ; j++)
	{	
		if(!visited[j])
		printf("%d is FALSE\n", j);
	}

	//order pass
	for(v = current->v ; v != NULL ; v = v->next)
	{
		printf("Going to be visit vertex # %llu\n", v->id );
		vertex_print(v);
		printf("\n");
		if(!visited[i])
		{
			DFS(i , v, visited, stack);
		}
		i++;
printf("vertex # %llu will be added to stack\n", v->id);
		push(&stack, v->id);
		printStack(stack);
	}

	

	for( int j = 0 ; j < num_of_vertices ; j++)
	{
		//printf("%d\n", pop(&stack) );
	}

	printStack(stack);
}

