#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "tree_dump.h"

int main()
{

    FILE *file = fopen ("dump.dot", "w");
    if (!file)
    {
        printf("File hasn't opened");
        return 0;
    }
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
    insert_node(&node_50, 10);
    insert_node(&node_50, 35);
    insert_node(&node_50, 60);

    print_tree(&node_50);
    dump (&node_50, file);


    if (fclose(file) != 0)
    {
        printf ("File hasn't closed");
        return 0;
    }

}

