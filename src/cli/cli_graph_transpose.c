#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cli.h"
#include "graph.h"

void
cli_graph_transpose(char *cmdline, int *pos)
{
	printf("ENTERED: cli_graph_transpose\n" );
	graph_transpose(current);
}