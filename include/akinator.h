#ifndef AKINATOR
#define AKINATOR

#include "tree.h"

Node* search (Node *node, const char *item);
void guess(Node *node);
bool is_leaf(Node *node);
int define (Tree * my_tree);

#endif
