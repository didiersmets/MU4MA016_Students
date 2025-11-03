#include "Project.h"






Merge_sort(struct K3_node* Points_, int size_, int Hyperplan_){
    
}






K3_tree(struct K3_node* Points, int size, int Hyperplan_){
    Hyperplan = Hyperplan_;
    Height = 0;//Placeholder calculer avec size
    if(Hyperplan == 1) Merge_sort(Points, size, Hyperplan); //Faire algo tri en fonction de l'hyperplan ( 0:z, 1:x, 2:y )
    node = Points[size/2];
    Left_Child = K3_tree(Points, size/2);
    Right_Child = K3_tree(Points + size/2 + 1, size/2 - 1); 
}








void K3_tree::push_back(struct K3_node new_node, K3_tree* tree){

    //Hyperplan (x,y)
    if(tree->Hyperplan == 0 && new_node.z > node->z){
        if(tree->Right_child){
            tree->Height++;
            push_back(new_node, tree->Right_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,1);
            tree->Right_Child = new_tree;
        }
    }
    else{
        if(tree->Left_child){
            tree->Height++;
            push_back(new_node, tree->Left_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,1);
            tree->Left_Child = new_tree;
        }
    }

    //Hyperplan (y,z)
    if(tree->Hyperplan == 1 && new_node.x > node->x){
        if(tree->Right_child){
            tree->Height++;
            push_back(new_node, tree->Right_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,2);
            tree->Right_Child = new_tree;
        }
    }
    else{
        if(tree->Left_child){
            tree->Height++;
            push_back(new_node, tree->Left_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,2);
            tree->Left_Child = new_tree;
        }
    }

    //Hyperplan (z,x)
    if(tree->Hyperplan == 2 && new_node.y > node->y){
        if(tree->Right_child){
            tree->Height++;
            push_back(new_node, tree->Right_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,0);
            tree->Right_Child = new_tree;
        }
    }
    else{
        if(tree->Left_child){
            tree->Height++;
            push_back(new_node, tree->Left_Child);
        }
        else{
            class K3_tree new_tree(0,new_node,0);
            tree->Left_Child = new_tree;
        }
    }

}