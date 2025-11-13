#include "mesh_adjancency.h"
#include <chrono>




int read_mesh2D(struct Mesh2D* m, const char* filename){
    std::ifstream Fichier(filename);
    char* poubelle;
    Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;Fichier >> poubelle;
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

int main(){
    auto t1=chrono::system_clock::now();
	
	auto t2=chrono::system_clock::now();
	chrono::duration<double> diff=t2-t1;
}