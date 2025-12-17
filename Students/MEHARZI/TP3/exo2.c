#include <stdio.h>

struct Triangle {
	int v[3]; //indice des sommets {a,b,c}
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    for (int i = 0; i < 3; i++) {
        int a = t.v[i];
        int b = t.v[(i + 1) % 3];
        if (a == v1 && b == v2) return i;
    }
    return -1;
}

// Deux triangles sont voisins s'ils partagent une arête avec orientation opposée.
// On parcourt les 3 arêtes orientées de t1: (v[i] -> v[i+1]) et
// on vérifie si l'arête opposée (v[i+1] -> v[i]) existe dans t2

struct Mesh {
    int nvert;
    int ntri;
    struct Triangle *tri;  // tableau de taille ntri
};

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {

	const struct Triangle t1 = m->tri[tri1];
	const struct Triangle t2 = m->tri[tri2];

	for(int j=0; j<3; ++j) {
		int a = t1.v[j];
		int b = t1.v[(j+1)%3];
		if (edge_pos_in_tri(b,a,t2) !=-1) {
			return j; // le voisin est trouvé et on retourne la position de l'arête dans t1
		} 	
	}
	return -1; // si on a pas de voisin
}


int main(void) {
	struct Triangle T[] = {
		{1,2,3}, 
		{2,1,4}, 
		{2,1,3},
	}; // ici ils sont bien tous voisin donc renvoie 0
	struct Mesh M = { .nvert = 10, .ntri = 3, .tri = T };
	printf("%d\n", tris_are_neighbors(0, 1, &M));
	printf("%d\n", tris_are_neighbors(0, 2, &M));
	
return 0;
}
