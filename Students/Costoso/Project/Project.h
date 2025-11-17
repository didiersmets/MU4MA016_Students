



struct K3_node {
    int x;
    int y;
    int z;
};

class K3_tree {
private:
    class K3_tree* Left_Child;
    class K3_tree* Right_Child;
    class K3_tree* Pred;
    struct K3_node node;
    int Hyperplan; // 1:Plan(xy) 2:Plan(yz) 3:Plan(zx)
public:
    K3_tree(int Height_, struct K3_node node_, int Hyperplan_) : node(node_), Hyperplan(Hyperplan_) {}
    K3_tree(struct K3_node* Points, int size, int Hyperplan_, K3_tree* Pred_);
    void push_back(struct K3_node new_node, K3_tree* tree);
    struct K3_node Search_neighbours(struct K3_node);
    void Remove_point(struct K3_node);
    struct K3_node* Search_p_neighbours(struct K3_node, int p);
};