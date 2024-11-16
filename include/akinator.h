#ifndef AKINATOR
#define AKINATOR

#include "tree.h"

struct Item_t
{
    Node **array_features;
    int amount_of_features;
    char *name;
    Node *node;
};

Node* search (Node *node, const char *item);
int guess(Tree *my_tree);
bool is_leaf(Node *node);
int define (Tree * my_tree);
int insert_node (Node *node);
int difference (Tree *my_tree);

#endif
