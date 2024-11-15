#ifndef AKINATOR
#define AKINATOR

#include "tree.h"

Node* search (Node *node, const char *item);
int guess(Tree *my_tree);
bool is_leaf(Node *node);
int define (Tree * my_tree);
int insert_node (Node *node);

#endif
