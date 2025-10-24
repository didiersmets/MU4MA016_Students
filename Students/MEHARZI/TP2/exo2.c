#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Vertex { double x; double y; };
struct Triangle { int v[3]; };
struct Mesh2D {
    int nv;
    struct Vertex* vert;
    int nt;
    struct Triangle* tri;
};

double area_mesh2D(struct Mesh2D* m);
void dispose_mesh2D(struct Mesh2D* m);


/* Lecture d'un fichier .mesh (accepte Dimension 2 OU 3).
   Si Dimension==3, on lit x y z ref mais on ignore z (on garde x,y).
   Remplit m->nv/m->vert et m->nt/m->tri.
   Retourne 0 si OK, 1 sinon. */
int read_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return 1;
    }

    char word[256];
    int nv = 0, nt = 0, dim = 0;

    /* MeshVersionFormatted */
    if (fscanf(f, "%255s", word) == 1 && strcmp(word, "MeshVersionFormatted") == 0) {
        int ver;
        if (fscanf(f, "%d", &ver) != 1) { fclose(f); return 1; }
    } else {
        /* si l'en-tête n'est pas là, on revient au début */
        fseek(f, 0, SEEK_SET);
    }

    /* Dimension 2 ou 3 */
    if (fscanf(f, "%255s", word) != 1 || strcmp(word, "Dimension") != 0) {
        printf("Section 'Dimension' manquante.\n");
        fclose(f);
        return 1;
    }
    if (fscanf(f, "%d", &dim) != 1 || (dim != 2 && dim != 3)) {
        printf("Dimension lue != 2 ou 3 (dimension = %d)\n", dim);
        fclose(f);
        return 1;
    }

    /* Vertices */
    if (fscanf(f, "%255s", word) != 1 || strcmp(word, "Vertices") != 0) {
        printf("Section 'Vertices' manquante.\n");
        fclose(f);
        return 1;
    }
    if (fscanf(f, "%d", &nv) != 1 || nv < 0) {
        printf("Nombre de sommets invalide.\n");
        fclose(f);
        return 1;
    }

    /* alloue les sommets */
    if (m->vert) { free(m->vert); m->vert = NULL; }
    m->vert = (struct Vertex*) malloc((size_t)nv * sizeof(struct Vertex));
    if (!m->vert) { fclose(f); return 1; }
    m->nv = nv;

    /* Lire nv lignes :
       - dim==2 :  x y ref
       - dim==3 :  x y z ref  (z ignoré pour Mesh2D) */
    for (int i = 0; i < nv; i++) {
        int refdummy;
        if (dim == 2) {
            double x, y;
            if (fscanf(f, "%lf %lf %d", &x, &y, &refdummy) != 3) {
                printf("Erreur lecture vertex %d (dim=2)\n", i);
                fclose(f);
                return 1;
            }
            m->vert[i].x = x;
            m->vert[i].y = y;
        } else { /* dim == 3 */
            double x, y, z;
            if (fscanf(f, "%lf %lf %lf %d", &x, &y, &z, &refdummy) != 4) {
                printf("Erreur lecture vertex %d (dim=3)\n", i);
                fclose(f);
                return 1;
            }
            m->vert[i].x = x;
            m->vert[i].y = y; /* z ignoré */
        }
    }

    /* Triangles */
    if (fscanf(f, "%255s", word) != 1 || strcmp(word, "Triangles") != 0) {
        printf("Section 'Triangles' manquante.\n");
        fclose(f);
        return 1;
    }
    if (fscanf(f, "%d", &nt) != 1 || nt < 0) {
        printf("Nombre de triangles invalide.\n");
        fclose(f);
        return 1;
    }

    /* alloue les triangles */
    if (m->tri) { free(m->tri); m->tri = NULL; }
    m->tri = (struct Triangle*) malloc((size_t)nt * sizeof(struct Triangle));
    if (!m->tri) { fclose(f); return 1; }
    m->nt = nt;

    /* Lire nt lignes : i j k ref */
    for (int t = 0; t < nt; t++) {
        int i, j, k, refdummy;
        if (fscanf(f, "%d %d %d %d", &i, &j, &k, &refdummy) != 4) {
            printf("Erreur lecture triangle %d\n", t);
            fclose(f);
            return 1;
        }
        m->tri[t].v[0] = i - 1;
        m->tri[t].v[1] = j - 1;
        m->tri[t].v[2] = k - 1;
    }

    fclose(f);
    return 0;
}

/* Export des arêtes vers un fichier lisible par gnuplot.
   Pour chaque arête : deux lignes "x y", puis une ligne vide.
   Retourne 0 si OK, 1 sinon. */
int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Impossible d'ouvrir %s en ecriture.\n", filename);
        return 1;
    }

    for (int t = 0; t < m->nt; t++) {
        int a = m->tri[t].v[0];
        int b = m->tri[t].v[1];
        int c = m->tri[t].v[2];

        /* arête AB */
        fprintf(f, "%lf %lf\n", m->vert[a].x, m->vert[a].y);
        fprintf(f, "%lf %lf\n\n", m->vert[b].x, m->vert[b].y);

        /* arête BC */
        fprintf(f, "%lf %lf\n", m->vert[b].x, m->vert[b].y);
        fprintf(f, "%lf %lf\n\n", m->vert[c].x, m->vert[c].y);

        /* arête CA */
        fprintf(f, "%lf %lf\n", m->vert[c].x, m->vert[c].y);
        fprintf(f, "%lf %lf\n\n", m->vert[a].x, m->vert[a].y);
    }

    fclose(f);
    return 0;
}

/* Écriture au format INRIA  */
int write_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Impossible d'ouvrir %s en ecriture.\n", filename);
        return 1;
    }

    fprintf(f, "MeshVersionFormatted 1\n");
    fprintf(f, "Dimension 2\n");

    fprintf(f, "Vertices\n");
    fprintf(f, "%d\n", m->nv);
    for (int i = 0; i < m->nv; i++) {
        fprintf(f, "%.15g %.15g %d\n", m->vert[i].x, m->vert[i].y, 0);
    }

    fprintf(f, "Triangles\n");
    fprintf(f, "%d\n", m->nt);
    for (int t = 0; t < m->nt; t++) {
        int i = m->tri[t].v[0] + 1;
        int j = m->tri[t].v[1] + 1;
        int k = m->tri[t].v[2] + 1;
        fprintf(f, "%d %d %d %d\n", i, j, k, 0);
    }

    fprintf(f, "End\n");
    fclose(f);
    return 0;
}

/* ============================================================
   MAIN test avec les 2 fichiers du prof
   ============================================================ */
int main() {
    struct Mesh2D M = {0, NULL, 0, NULL};

    /* Fichier 1 */
    if (read_mesh2D(&M, "mesh1-tp2.mesh") == 0) {
        printf("\n=== Fichier 1 (mesh1-tp2.mesh) ===\n");
        printf("%d sommets, %d triangles\n", M.nv, M.nt);

        double A1 = area_mesh2D(&M);
        printf("Aire signee = %f\n", A1);

        write_mesh2D(&M, "copie1.mesh");
        mesh2D_to_gnuplot(&M, "mesh1.dat");
        printf("Copie: copie1.mesh, gnuplot: mesh1.dat\n");

        dispose_mesh2D(&M);
    } else {
        printf("Echec lecture fichier 1\n");
    }

    /* Fichier 2 */
    if (read_mesh2D(&M, "mesh2-tp2.mesh") == 0) {
        printf("\n=== Fichier 2 (mesh2-tp2.mesh) ===\n");
        printf("%d sommets, %d triangles\n", M.nv, M.nt);

        double A2 = area_mesh2D(&M);
        printf("Aire signee = %f\n", A2);

        write_mesh2D(&M, "copie2.mesh");
        mesh2D_to_gnuplot(&M, "mesh2.dat");
        printf("Copie: copie2.mesh, gnuplot: mesh2.dat\n");

        dispose_mesh2D(&M);
    } else {
        printf("Echec lecture fichier 2\n");
    }

    return 0;
}
