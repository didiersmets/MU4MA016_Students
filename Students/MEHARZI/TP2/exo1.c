#include <stdio.h>
#include <stdlib.h>

// =======================
// Part en 2D
// =======================

// Sommets
struct Vertex {
    double x;
    double y;
};

// Triangle (indices des sommets)
struct Triangle {
    int v[3];
};

// Maillage 2D (ensemble de sommets et de triangles)
struct Mesh2D {
    int nv;                 // nombre de sommets
    struct Vertex* vert;    // tableau de sommets
    int nt;                 // nombre de triangles
    struct Triangle* tri;   // tableau de triangles
};

// Fonction pour initialiser un maillage
int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    m->vert = (struct Vertex*) malloc(vtx_capacity * sizeof(struct Vertex));
    m->tri  = (struct Triangle*) malloc(tri_capacity * sizeof(struct Triangle));

    if (m->vert == NULL || m->tri == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return 1;
    }
    return 0;
}

// Fonction pour libérer la mémoire
void dispose_mesh2D(struct Mesh2D* m) {
    free(m->vert);
    free(m->tri);
    m->nv = 0;
    m->nt = 0;
    m->vert = NULL;
    m->tri = NULL;
}

// Aire signée d'un triangle
double triangle_area_signed(struct Vertex a, struct Vertex b, struct Vertex c) {
    return 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

// Aire totale du maillage
double area_mesh2D(struct Mesh2D* m) {
    double total = 0.0;
    for (int i = 0; i < m->nt; i++) {
        struct Vertex a = m->vert[m->tri[i].v[0]];
        struct Vertex b = m->vert[m->tri[i].v[1]];
        struct Vertex c = m->vert[m->tri[i].v[2]];
        total += triangle_area_signed(a, b, c);
    }
    return total;
}


// =======================
// Part en 3D
// =======================

struct Vertex3D {
    double x;
    double y;
    double z;
};

struct Triangle3D {
    int v[3];  // indices des 3 sommets
};

struct Mesh3D {
    int nv;
    struct Vertex3D* vert;
    int nt;
    struct Triangle3D* tri;
};

int initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity) {
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = (struct Vertex3D*) malloc(vtx_capacity * sizeof(struct Vertex3D));
    m->tri  = (struct Triangle3D*) malloc(tri_capacity * sizeof(struct Triangle3D));
    if (m->vert == NULL || m->tri == NULL) {
        printf("Erreur d'allocation memoire (3D).\n");
        return 1;
    }
    return 0;
}

void dispose_mesh3D(struct Mesh3D* m) {
    free(m->vert);
    free(m->tri);
    m->nv = 0; m->nt = 0;
    m->vert = NULL; m->tri = NULL;
}

// produits utile pour le volume
static void cross3(const struct Vertex3D* a, const struct Vertex3D* b, struct Vertex3D* r) {
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
    r->z = a->x * b->y - a->y * b->x;
}
static double dot3(const struct Vertex3D* a, const struct Vertex3D* b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

/* Volume signe par la formule du tetraedre avec l'origine:
   V_tri = (1/6) * a · (b × c)  */
double volume_mesh3D(struct Mesh3D* m) {
    double V = 0.0;
    for (int i = 0; i < m->nt; i++) {
        int i0 = m->tri[i].v[0];
        int i1 = m->tri[i].v[1];
        int i2 = m->tri[i].v[2];

        // sommets du triangle
        struct Vertex3D a = m->vert[i0];
        struct Vertex3D b = m->vert[i1];
        struct Vertex3D c = m->vert[i2];

        // b x c
        struct Vertex3D bxc;                 
        cross3(&b, &c, &bxc);                //  calcul du produit vectoriel
        V += (1.0/6.0) * dot3(&a, &bxc);     //  accumulation du volume signe
    }
    return V;
}

/*
int main() {
    struct Mesh2D mesh;

    // Crée un maillage avec 3 sommets et 1 triangle
    if (initialize_mesh2D(&mesh, 3, 1) == 0) {
        // Sommets
        mesh.vert[0].x = 0; mesh.vert[0].y = 0;
        mesh.vert[1].x = 1; mesh.vert[1].y = 0;
        mesh.vert[2].x = 0; mesh.vert[2].y = 1;

        // Triangle
        mesh.tri[0].v[0] = 0;
        mesh.tri[0].v[1] = 1;
        mesh.tri[0].v[2] = 2;

        // Calcul aire
        double A = area_mesh2D(&mesh);
        printf("Aire signee du mesh = %f\n", A); // doit afficher 0.5
    }

    dispose_mesh2D(&mesh);

    struct Mesh3D M;
    if (initialize_mesh3D(&M, 4, 4) != 0) return 1;

    // Sommets du tetraedre: O(0,0,0), A(1,0,0), B(0,1,0), C(0,0,1)
    M.vert[0] = (struct Vertex3D){0,0,0};
    M.vert[1] = (struct Vertex3D){1,0,0};
    M.vert[2] = (struct Vertex3D){0,1,0};
    M.vert[3] = (struct Vertex3D){0,0,1};

    // 4 faces, orientees vers l'exterieur (attention a l'ordre)
    M.tri[0] = (struct Triangle3D){ {1,2,3} }; // face ABC (opposée à O)
    M.tri[1] = (struct Triangle3D){ {0,3,2} }; // O-C-B
    M.tri[2] = (struct Triangle3D){ {0,2,1} }; // O-B-A
    M.tri[3] = (struct Triangle3D){ {0,1,3} }; // O-A-C

    double V = volume_mesh3D(&M);
    printf("Volume signe = %.7f\n", V); // ~ +0.1666667 si orientations correctes

    dispose_mesh3D(&M);
    return 0;
}
*/