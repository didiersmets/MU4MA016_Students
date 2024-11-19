#include <stdio.h>
#include <stdlib.h>

int edge_pos_in_tri(int v1, int v2, Triangle t){
	if(v1 == t.a && v2 == t.b){
		return 0;
	}	
	if(v1 == t.b && v2 == t.c){
		return 1;
	}
	if(v1 == t.c && v2 == t.a){
		return 2;
	}
	return -1;
}

int tri_are_neighbors(int tri1, int tri2, const Mesh* m){
	int v1 = edge_pos_in_tri(m->tri[tri2].a, m->tri[tri2].c, m->tri[tri1]);
	if(v1!=-1){
		return v1;
	}
	int v2 = edge_pos_in_tri(m->tri[tri2].c, m->tri[tri2].b, m->tri[tri1]);
	if(v2!=-1){
		return v2;
	}
	int v3 = edge_pos_in_tri(m->tri[tri2].b, m->tri[tri2].a, m->tri[tri1]);
	if(v3!=-1){
		return v3;
	}
	return -1;
}

 
int *build_adjacency_tabl1(const Mesh *m){
	int adj[3*m->nt]={-1};
	for(int i = 0, i < m->nt, i++){
		for(int k = 0,i<m->nt, k++){
			v = edge_pos_in_tri(i,k,m);
			if(v!=-1){
			       adj[3*i+v]=k;
			}
		}
	}
}





