#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"


int main()
{
    struct Node node_50 = {};

    node_50.date = 50;
    node_50.right = NULL;
    node_50.left = NULL;

    struct Node node_30 = {};
    node_30.date = 30;
    node_30.right = NULL;
    node_30.left = NULL;

    node_50.left = &node_30;

    struct Node node_70 = {};
    node_70.date = 70;
    node_70.right = NULL;
    node_70.left = NULL;


    node_50.right = &node_70;

    print_tree (&node_50);

    printf ("\n");

    insert_node(&node_50, 10);

    print_tree (&node_50);
}

