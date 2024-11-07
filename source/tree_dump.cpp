#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "tree_dump.h"

void print_node_in_file (Node *node, FILE * pointer_file);
void print_edge_in_file (Node *node, FILE * pointer_file);

void dump (Node *node, FILE * pointer_file)
{
    assert(node);
    assert(pointer_file);

    fprintf (pointer_file,  "digraph structs {\n"
                            "rankdir=HR;\n"
                            "node[color= \"#003A8C\",style=\"filled\", fillcolor=\"#B4FBFF\", fontsize=14];\n"
                            "edge[color=\"black\", weight = 9,fontsize=14];\n");
    print_node_in_file(node, pointer_file);
    print_edge_in_file(node, pointer_file);
    fprintf (pointer_file, "\n}");

}

void print_node_in_file (Node *node, FILE * pointer_file)
{

    if (node == NULL)
    {
        printf ("NULL pointer\n");
        return;
    }
    fprintf (pointer_file, "el_%p [shape=record, label= \"date = %d\"];\n", &node->date, node->date);

    if (node->left)
        print_node_in_file(node->left, pointer_file);

    if (node->right)
        print_node_in_file(node->right, pointer_file);
}

void print_edge_in_file (Node *node, FILE * pointer_file)
{
    if (node == NULL)
    {
        printf ("NULL pointer\n");
        return;
    }

    if (node->left)
    {
        fprintf (pointer_file, "el_%p", &node->date);
        fprintf (pointer_file, "->");
        fprintf (pointer_file, "el_%p;\n", &node->left->date);
        print_edge_in_file(node->left, pointer_file);
    }
    if (node->right)
    {
        fprintf (pointer_file, "el_%p", &node->date);
        fprintf (pointer_file, "->");
        fprintf (pointer_file, "el_%p;\n", &node->right->date);
        print_edge_in_file(node->right, pointer_file);
    }
}
