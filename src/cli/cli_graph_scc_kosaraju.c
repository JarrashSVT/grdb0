#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cli.h"
#include "graph.h"
#include "stack.h"
#include <stdbool.h>
#include "api.h"

struct visited_map
{
	vertexid_t id;
	bool isVisited;
	
};

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
DFS( vertex_t v, struct visited_map *visited, StackNode *stack)
{
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS BEGIN~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~SUMMARY BEGIN~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	printf("V id is "); vertex_print(v); printf("\n");
	if(visited[v->id].isVisited) printf("isVisited? TRUE\n"); else printf("isVisited? FALSE\n");
	printStack(stack);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~SUMMARY END~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	static StackNode *my_stack;
	my_stack = stack;

	visited[v->id].isVisited = true;
	
	int  num_of_neighbors;
	//vertex_t *neighbors = malloc(num_of_vertices * sizeof(v)); 4/28 9:13 am
	//vertex_t v_next; 4/28 9:13 am
	//neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors); 4/28 9:13 am
	//if(v != NULL)
	//	printf("it's NOT NULL WTF!!!\n");
	/////// troublshot neighobrs
	vertex_with_neighbors_t my_neighbors;
	my_neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);
	vertex_with_neighbors_t cursor = my_neighbors->next;
	
/*	printf("~num_of_neighbors %d\n",num_of_neighbors );
	int index;
	for(index = 0 ; index < num_of_neighbors ; index++)	
	{
		printf("neighbors[%d] is ",index);
		vertex_print(neighbors[index]);
		printf("\n");
	} 4/28 9:15 am
*/ 
	while(cursor != NULL)
	{
		vertex_with_neighbors_print(cursor);
		if(!visited[cursor->id].isVisited)
			DFS((vertex_t) cursor, visited, my_stack);
		
		//printf("vertex # %llu will be added to my_stack\n", cursor->id);
		//push(&my_stack, cursor->id);
		//printStack(my_stack);
		cursor = cursor->next;
	}
	
	
	
	/////////////////
	/* 4/28 9:17 am
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
	}*/

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS END~~~~~~~~~~~~~~~~~~~~~~~~\n");

}

void
DFS_SCC(vertex_t v, struct visited_map *visited, struct visited_map *added, StackNode *stack, graph_t scc)
{
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS_SCC BEGIN~~~~~~~~~~~~~~~~~~~~~~~~\n");

	
	
	static StackNode *my_stack;
	my_stack = stack;

	visited[v->id].isVisited = true;
	//if(v != NULL)
	//printf("%llu -> ", v->id );
	
	int  num_of_neighbors;
	
	vertex_with_neighbors_t my_neighbors;
	my_neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);
	vertex_with_neighbors_t cursor = my_neighbors->next;
	

	while(cursor != NULL)
	{	
		printf("in DFS_SCC\n");
		vertex_with_neighbors_print(cursor);
		printf("\n");
		if(!visited[cursor->id].isVisited)
			DFS_SCC( (vertex_t) cursor, visited,added, my_stack, scc);
		else
		{
			vertex_with_neighbors_print(cursor);
			printf("is already visited\n");
		
		}
		//printf("vertex # %llu will be added to my_stack\n", cursor->id);
		//push(&my_stack, cursor->id);
		//printStack(my_stack);
		cursor = cursor->next;
	}
	
	if(!added[v->id].isVisited)
	{

		graph_insert_vertex(scc, v);
		added[v->id].isVisited = true;		

		if(added[v->id].isVisited)
			printf("add %llu\n", v->id );
	}
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~DFS_2 END~~~~~~~~~~~~~~~~~~~~~~~~\n");
//
}

void
cli_graph_scc_kosaraju(char *cmdline, int *pos)
{
	int num_of_normal_froms = graph_normal_form_count(current);
	graph_t* normal_form_graphs = graph_normal_form_get(current);

	int index;
	for(index = 0 ; index < num_of_normal_froms ; index++)
	{
		StackNode *stack;
		stack = malloc(sizeof(stack));
		vertex_t v;
		
		graph_t transposed = graph_transpose(current);
		graph_print(transposed, 0);
		printf("\n");
		int  num_of_vertices = graph_count_vertices(current);
		int  num_of_neighbors;
		//vertex_t *neighbors = malloc(num_of_vertices * sizeof(vertex_t)); TODAY

		vertex_with_neighbors_t my_neighbors;
		printf("num_of_vertices = %d\n",num_of_vertices );

		for(v = current->v ; v != NULL ; v = v->next)
		{
			vertex_print(v);
			printf("===================\n");
			//if(v->id == 1)
			//{
				my_neighbors = graph_find_vertex_neighbors(current, v->id, &num_of_neighbors);
				vertex_with_neighbors_t cursor = my_neighbors->next;
				//cursor = cursor->next;

				while(cursor != NULL)
				{
					vertex_with_neighbors_print(cursor);
					cursor = cursor->next;
				}
				printf("num_of_neighbors %d\n",num_of_neighbors );
			//}
		}

		
		struct visited_map visited_list[num_of_vertices];
		struct visited_map added_list[num_of_vertices];

		/* Make all vertices as not visited */
		//int index = 0;
		for(v = current->v ; v != NULL ; v = v->next)
		{
			//mlist[v->id].id = v->id;
			visited_list[v->id].isVisited = false;
			added_list[v->id].isVisited = false;

			if(visited_list[v->id].isVisited)
			//printf("mlist.id %llu\n", mlist[index].id );
			//index++;
				printf("%llu visited\n", v->id);
		}

		//order pass
		for(v = current->v ; v != NULL ; v = v->next)
		{
			printf("Going to be visit vertex # %llu\n", v->id );
			//vertex_print(v);
			//printf("\n");
			if(!visited_list[v->id].isVisited)
			{
				DFS( v, visited_list, stack);
			}
			
			//i++;
			printf("vertex # %llu will be added to stack\n", v->id);
			push(&stack, v->id);
			printStack(stack);
		}

		/* Make all vertices as not visited for the 2nd DFS */
		for(v = current->v ; v != NULL ; v = v->next)
		{
			visited_list[v->id].isVisited = false;

			//if(!visited_list[v->id].isVisited)
				//printf("%llu visited\n", v->id);
		}


		printf(" stackLenght %d\n",stackLenght(stack) );
		while(!isEmpty(stack) && stackLenght(stack) > 1)
		{
			graph_t scc, scc0;
			scc = (graph_t) malloc(sizeof(struct graph));
			scc0 = NULL;
			//assert (scc != NULL);
			graph_init(scc);
			vertexid_t dd = pop(&stack);

			if(!visited_list[dd].isVisited)
			{
			//	printf("%llu\n", dd);
				DFS_SCC(graph_find_vertex_by_id(transposed ,dd), visited_list,added_list, stack, scc);
			}
			scc = graph_join(scc,scc0);
			graph_print(scc,0);
			printf("\n");
		}
	}
}

