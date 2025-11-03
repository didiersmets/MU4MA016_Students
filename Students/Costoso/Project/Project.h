



struct K3_node{
    int x;
    int y;
    int z;
}

class K3_tree{
    private:
        class K3_tree* Left_child;
        class K3_tree* Right_child;
        struct K3_node node;
        int Height;
        int Hyperplan;
    public:
        K3_tree(int Height_, struct K3_node node_, int Hyperplan_): Height(Height_), node(node_), Hyperplan(Hyperplan_){}
        K3_tree(struct K3_node* Points, int size, int Hyperplan_);
        void push_back(struct K3_node new_node, K3_tree* tree);
};