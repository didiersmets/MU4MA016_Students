#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int index_pt1;
    int index_pt2;
    int index_pt3;
}Triangle;

typedef struct Mesh2D{
    int nv; //number of vertices in the mesh
    Vertex *vert;

    int nt; //Number of triangles in the msh
    Triangle *tri;
}Mesh2D;

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(sizeof(Vertex)*m->nv);
    m->tri = malloc(sizeof(Triangle)*m->nt);

    if (!m->vert || !m->tri){
        return 0;
    }
    return 1;
}

void dispose_mesh2D(struct Mesh2D*m){
    if (!m) return;
    free(m->vert);
    free(m->tri);
    free(m);
}

double area_mesh2D(struct Mesh2D* m){ //je comprends que c'est la somme de l'air de chaque triangle de mesh2D

    double aire_totale = 0;

    for(int i=0; i<(m->nt); i++){

        Vertex A = m->vert[(m->tri[i]).index_pt1]; //points A,B et C du trangle i
        Vertex B = m->vert[(m->tri[i]).index_pt2];
        Vertex C = m->vert[(m->tri[i]).index_pt3];

        Vertex AB; //vecteur AB
        AB.x = B.x - A.x;
        AB.y = B.y - A.y;

        Vertex AC;
        AC.x = C.x - A.x;
        AC.y = C.y - A.y;

        aire_totale += 0.5*(AB.x*AC.y-AC.x*AB.y); //déterminant de la matrice composée des vecteurs colonnes AB et AC, qui divisé par 2 donne l'aire signé du trangle ABC
    }

    return aire_totale;
}

int read(/*struct Mesh2D* m, */const char* filename){
    FILE *f = fopen(filename,"r");
    if (!f){
        printf("fichier non ouvert\n");
        exit(1);
    }

    //on voit dans les fichiers mesh à disposition que la dimension est 3, on a 5 points de 3 coordonnées, et 4 triangles, formant, une pyramide à base triangulaire
    //nous allons alors prendre les valeurs en oubliant la 3ème coordonnée
    char buffer[256];
    char mot[256];
    int nb_vertices;
    char* res;

    while ((strcmp(mot,"Vertices")!=0) && res!=NULL){ //strcmp == 0 si les deux chaines de caractères mises en argument sont identiques
        res = fgets(buffer, 256, f);
        sscanf(buffer, "%s", mot);
    }
    if (res == NULL) printf("Pas de 'Vertices' dans ton fichier\n");
    sscanf(buffer, "%s %d", mot, &nb_vertices);

    int coordonnée_x;
    int coordonnée_y;
    int i=0;


    for(int i=0; i<=nb_vertices;i++){
        fgets(buffer, 256, f);
        printf("////////////\n");
        while (i!=256){
            if (sizeof(buffer[i])==sizeof(int)){
                printf("%d\n",i);
            }
            i++;
        }
    }

    fclose(f);
}

int main(){
    read("mesh1-tp2.mesh");
    return 0;
}