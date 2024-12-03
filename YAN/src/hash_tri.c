#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "mesh_adjacency.h"
#include "hash_table.h"

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

int tris_are_neighbors(int tri1, int tri2, const Mesh* m){

	int v1 = edge_pos_in_tri(m->tri[tri2].b, m->tri[tri2].a, m->tri[tri1]);
	if (v1!=-1){
		return v1;
	}
	int v2 = edge_pos_in_tri(m->tri[tri2].c, m->tri[tri2].b, m->tri[tri1]);
	if(v2!=-1){
		return v2;
	}
	int v3 = edge_pos_in_tri(m->tri[tri2].a, m->tri[tri2].c, m->tri[tri1]);
	if(v3!=-1){
		return v1;

	}
	else{
		return -1;
	}
}
	
int * build_adjacency_table1(const Mesh* m){

	int adj[3*m->nt]={-1};
	for(int i = 0, i<m->nt, i++){
		for(int k=0, k<m->nt, k++){
			v = tris_are_neighbors(m->tri[i],m->tri[k],m);
			if(v!=-1){
				adj[3*i+v]=k;
			}
		}
	}
	return adj;
}


Hashtable *build_edge_table1(const Mesh*m){
	Hashtable* ht = hash_table_init(6*m->nt,sizeof(Edge),sizeof(int));
	for(int i= 0,i <m->nt,i++){
		Edge key;
		int val;
		key = (Edge){m->tri[i].a,m->tri[i].b};
		val = 3 * i + 0;
		hash_table_insert(ht,&key,&val);
		key = (Edge){m->tri[i].b,m->tri[i].c};
		val = 3 * i + 1;
		hash_table_insert(ht,&key,&val);
		key = (Edge){m->tri[i].c,m->tri[i].a};
		val = 3 * i + 2;
		hash_table_insert(ht,&key,&val);
	
	}
	return ht;
}

int *build_adjacency_table2(const Mesh*m){
	int adj[3*m->nt]={-1};
	Hashtable* ht = build_edge_table1(m);
	for( int i=0, i< m->nt,i++){
		Edge key = {m->tri[i].b,m->tri[i].a};
		int val = *(int *)hash_table_find(ht,&key);
		adj[3*i+0]=val;
		Edge key2 = {m->tri[i].c,m->tri[i].b};
		int val2 = *(int *)hash_table_find(ht,&key2);
		adj[3*i+1]=val2;
		Edge key3 = {m->tri[i].a,m->tri[i].c};
		int val3 = *(int *)hash_table_find(ht,&key3);
		adj[3*i+2]=val3;
	}
	hash_table_fini(ht);
	free(ht);
	return adj;
}

void edge_table_initialize(EdgeTable * et, int nv, int nt){
	et->head = malloc(nv*sizeof(int));
	et->next = malloc(nt*3*sizeof(int));
}


