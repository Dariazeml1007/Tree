#ifndef TREE
#define TREE

struct Node
{
    int date;
    Node *right;
    Node *left;
};

void insert_node (Node *node, int value);
void print_tree (Node *node);

#endif


