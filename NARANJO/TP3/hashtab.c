#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


#include "/root/MU4MA016_Students/NARANJO/TP2/tri_mesh.c"

int edge_pos_in_tri ( int v1 , int v2 , struct Triangle t )
{
	if (v1 == t.alpha && v2 == t.beta){
		return 0
	}
	if  (v1 == t.beta && v2 == t.gamma){
                return 1
        }
	if (v1 == t.gamma && v2 == t.alpha){
                return 2
        }
	else{
		return -1
	}
}
