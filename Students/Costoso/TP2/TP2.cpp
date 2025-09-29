#include <vector>
#include <fstream>
#include <cstring>

struct Vertex {
    double x;
    double y;
};

struct Triangle{
    int a;
    int b;
    int c;
};

struct Mesh2D{
    int nv;
    void* vert;
    int nt;
    void* tri;
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = (char*)malloc(sizeof(Vertex)*vtx_capacity);
    m->tri = (char*)malloc(sizeof(Triangle)*tri_capacity);
    return 0;
}

void dispose_mesh2D(struct Mesh2D* m){
    free(m);
}


double distance_point(struct Vertex a, struct Vertex b){
    return abs(b.x-a.x)+abs(b.y-a.y);
}


double area_mesh2D(struct Mesh2D* m){
    double area=0;

    for(int i=0;i<m->nt;i++){
        Triangle t = ((Triangle*)m->tri)[i];
        double d1 = distance_point(((Vertex*)m->vert)[t.a],((Vertex*)(m->vert))[t.b]);
        double d2 = distance_point(((Vertex*)m->vert)[t.b],((Vertex*)(m->vert))[t.c]);
        area = area + d1*d2/2;
    }
    return area;
}


int read_mesh2D(struct Mesh2D* m, const char* filename){
    std::ifstream Fichier(filename);
    char* poubelle;
    Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;
    int vtx_capacity_(0);
    int tri_capacity_(0);
    Fichier>>vtx_capacity_;
    m->nv=vtx_capacity_;
    m->vert = (char*)malloc(sizeof(Vertex)*vtx_capacity_);
    for(int i=0;i<vtx_capacity_;i++){
        Vertex v;
        Fichier>>v.x;
        Fichier>>v.y;
        ((Vertex*)(m->vert))[i]=v;
        Fichier>>poubelle; //Pour 3D vers 2D
        Fichier>>poubelle;
    }
    Fichier>>poubelle;
    Fichier>>tri_capacity_;
    m->tri = (char*)malloc(sizeof(Triangle)*tri_capacity_);
    for(int i=0;i<tri_capacity_;i++){
        Triangle t;
        Fichier>>t.a;
        Fichier>>t.b;
        Fichier>>t.c;
        ((Triangle*)(m->tri))[i]=t;
        Fichier>>poubelle;
    }
    char* End;
    Fichier>>End;
    if(strncmp(End,"End",3)!=0){
        return 0;
    }
    return 1;
}




int write_mesh2D(struct Mesh2D* m, const char* filename){
    std::ofstream Fichier(filename);
    Fichier<<"MeshVersionFormatted 2"<<"\n";
    Fichier<<"Dimension 2"<<"\n";
    Fichier<<"Vertices "<<m->nv<<"\n";
    for(int i=0;i<m->nv;i++){
        Fichier<<"  "<<((Vertex*)(m->vert))[i].x<<" "<<((Vertex*)(m->vert))[i].y<<"   "<<"1"<<"\n";
    }
    Fichier<<"Triangles "<<m->nt<<"\n";
    for(int i=0;i<m->nt;i++){
        Fichier<<"  "<<((Triangle*)(m->tri))[i].a<<"    "<<((Triangle*)(m->tri))[i].b<<"    "<<((Triangle*)(m->tri))[i].c<<"    "<<"1"<<"\n";
    }
    Fichier<<"End";
    return 0;
}


int main(){
    struct Mesh2D* m;
    initialize_mesh2D(m,1,1);

    return 0;
}