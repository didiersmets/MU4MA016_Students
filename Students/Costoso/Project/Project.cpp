#include "Project.h"

//------------------------//
//      Constructeur      //
//------------------------//
int Read_xyz_file( struct K3_node* Points, const char* filename){
    std::ifstream Fichier(filename);
    char* poubelle;
    int num_el = 0;
    Fichier >> num_el; 
    Fichier >> poubelle; Fichier >> poubelle; 
    Points = (struct K3_node*)malloc(sizeof(struct K3_node) * num_el);
    for(int i = 0; i < num_el; i++){
        Fichier >> poubelle;
        int x; int y; int z;
        Fichier >> x;
        Fichier >> y;
        Fichier >> z;
        Points[i].x = x;
        Points[i].y = y;
        Points[i].z = z;
    }
    return 1;
}

void Merge(K3_node* In, K3_node* Out, int p, int q, int r, int Hyperplan) {
    int i = p;
    int j = q + 1;
    for (int k = p; k < r; ++k) {
        if(Hyperplan == 0){
            if (j == r || (i <= q && In[i].z <= In[j].z)) {
                Out[k] = In[i++];
            }
            else {
                Out[k] = In[j++];
            }
        }
        if (Hyperplan == 1) {
            if (j == r || (i <= q && In[i].x <= In[j].x)) {
                Out[k] = In[i++];
            }
            else {
                Out[k] = In[j++];
            }
        }
        if (Hyperplan == 2) {
            if (j == r || (i <= q && In[i].y <= In[j].y)) {
                Out[k] = In[i++];
            }
            else {
                Out[k] = In[j++];
            }
        }
    }
}

void Merge_sort(K3_node* In, K3_node* Out, int p, int r, int Hyperplan) {
    if (p + 1 < r) {
        int q = (p + r) / 2;
        Merge_sort(Out, In, p, q, Hyperplan);
        Merge_sort(Out, In, q + 1, r, Hyperplan);
        Merge(In, Out, p, q, r, Hyperplan);
    }
}

K3_tree::K3_tree(struct K3_node* Points, int size, int Hyperplan_, K3_tree* Pred_) {
    Hyperplan = Hyperplan_;
    struct K3_node* tri_Points;
    Merge_sort(Points, tri_Points, 0, size, Hyperplan); //Faire algo tri en fonction de l'hyperplan ( 0:z, 1:x, 2:y )
    K3_node node = Points[size / 2];

    //Change Hyperplan
    int new_Hyperplan = Hyperplan + 1;
    if (Hyperplan == 3) Hyperplan = 0;

    //LeftChild  RightChild
    K3_tree Lchild(tri_Points, size / 2, Hyperplan, this);
    K3_tree Rchild(tri_Points + size / 2 + 1, size / 2 - 1, Hyperplan, this);
    Left_Child = &Lchild;
    Right_Child = &Rchild;
    Pred = Pred_;
}






// Inutile
/*
void K3_tree::push_back(struct K3_node new_node, K3_tree* tree) {

    //Hyperplan (x,y)
    if (tree->Hyperplan == 0 && new_node.z > node.z) {
        if (tree->Right_Child) {
            push_back(new_node, tree->Right_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 1);
            tree->Right_Child = &new_tree;
        }
    }
    else {
        if (tree->Left_Child) {
            push_back(new_node, tree->Left_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 1);
            tree->Left_Child = &new_tree;
        }
    }

    //Hyperplan (y,z)
    if (tree->Hyperplan == 1 && new_node.x > node.x) {
        if (tree->Right_Child) {
            push_back(new_node, tree->Right_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 2);
            tree->Right_Child = &new_tree;
        }
    }
    else {
        if (tree->Left_Child) {
            push_back(new_node, tree->Left_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 2);
            tree->Left_Child = &new_tree;
        }
    }

    //Hyperplan (z,x)
    if (tree->Hyperplan == 2 && new_node.y > node.y) {
        if (tree->Right_Child) {
            push_back(new_node, tree->Right_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 0);
            tree->Right_Child = &new_tree;
        }
    }
    else {
        if (tree->Left_Child) {
            push_back(new_node, tree->Left_Child);
        }
        else {
            class K3_tree new_tree(0, new_node, 0);
            tree->Left_Child = &new_tree;
        }
    }

}
*/


//-----------------------------//
//      Search neighbours      //
//-----------------------------//
float distance(struct K3_node n1, struct K3_node n2){
    return sqrt((n1.x - n1.x) * (n1.x - n1.x) - (n1.y - n1.y) * (n1.y - n1.y) - (n1.z - n1.z) * (n1.z - n1.z));
}
float distance2(float x1,float x2, float y1, float y2, float z1, float z2) return sqrt((x1 - x2) * (x1 - x2) - (y1 - y2) * (y1 - y2) - (z1 - z2) * (z1 - z2));
struct K3_node* K3_tree::Search_p_neighbours(struct K3_node ref_node, int p){
    int best_distance = distance(node,ref_node);
    struct K3_tree curent_node;
    struct K3_tree previous_node;
    struct K3_node* best_neighbours = malloc(sizeof(struct K3_node) * p);
    for(int i = 0; i < p; i++){
        best_neighbours[i] = node;
    }
    if(distance(Left_Child->node, ref_node) > distance(Right_Child->node, ref_node)){ curent_node = Right_Child; }
    else{ curent_node = Left_Child; }
    while(curent_node->Left_Child && curent_node->Right_Child){
        if(distance(curent_node->Left_Child->node, ref_node) > distance(curent_node->Right_Child->node, ref_node)){ curent_node = Right_Child; }
        else{ curent_node = Left_Child; }
    }
    best_distance = distance(curent_node->node, ref_node);
    best_neighbours[0] = curent_node;
    

    while(curent_node->Pred){
        previous_node = curent_node;
        curent_node = curent_node->Pred;
        if(previous_node->node == curent_node->Right_Child->node && distance2()){

        }
        //Idee:
        //Regarder si le point projeter sur l'hyperplan est inf à la distance max
        //Si oui regarder la feuille la plus proche du point et noter la distance et remonter depuis cette feuille
        //Si non passe au Pred suivant
        //etc jusqu'a plus de Pred

        //Chercher sol pour p points        
    }
}