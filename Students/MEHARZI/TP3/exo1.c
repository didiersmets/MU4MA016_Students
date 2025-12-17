#include <stdio.h>

struct Triangle {
	int v[3]; //les sommets du triangle
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
	for (int i=0; i<3; i++) {
		int a = t.v[i];
		int b = t.v[(i+1)%3]; // pour toutes les autres arrete
		if(a==v1 && b==v2) {
			return i; // c'est position qu'on aura trouvé
		}
	}
	return -1; //condition si l'arrete n'existe pas
}

int main(){
	struct Triangle t = {1,2,3};
	
	printf("%d \n", edge_pos_in_tri(1, 2, t)); // return la pos 0
	printf("%d \n", edge_pos_in_tri(2, 3, t)); // return la pos 1
	printf("%d \n", edge_pos_in_tri(3, 1, t)); // return la pos 2
	printf("%d \n", edge_pos_in_tri(2, 1, t)); // return la pos -1
	
	return 0;	
}
