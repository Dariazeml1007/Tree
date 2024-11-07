#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

void insert_node (Node *node, int value)
{
    if (value < node->date)
    {
        if (node->left == NULL)
        {
            struct Node *new_node = (Node*)calloc (1, sizeof(struct Node));
            node->left = new_node;
            new_node->date = value;
        }
        else
            insert_node(node->left, value);
    }
    else
    {
        if (node->left == NULL)
        {
            struct Node *new_node = (Node *) calloc (1, sizeof(Node));
            node->left = new_node;

            new_node->date = value;
        }
        else
            insert_node(node->right, value);
    }

}

void print_tree (Node *node)
{

    if (node == NULL)
    {
        printf ("NULL pointer\n");
        return;
    }
    printf ("(");

    if (node->left)
        print_tree(node->left);

    printf ("%d", node->date);

    if (node->right)
        print_tree(node->right);
    printf (")");
}