#include <stdio.h>
#include <stdlib.h>

#include "/users/home/28624202/MU4MA016_Students/TP3/include/mesh_adjacency.h"
#include "/users/home/28624202/MU4MA016_Students/TP3/include/mesh.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	if ((t.idx[0] == v1) && (t.idx[1] == v2))
	{
		return 0;
	}
	if ((t.idx[1] == v1) && (t.idx[2] == v2))
	{
		return 1;
	}
	if ((t.idx[2] == v1) && (t.idx[0] == v2))
	{ 
		return 2;
	}
	else {
		return -1;
	}
}




