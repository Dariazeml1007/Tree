#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "tree.h"

int get_size_of_file (const char *name_of_file);

int reading_tree (Tree *my_tree)
{
    assert(my_tree);

    my_tree->file = fopen (my_tree->name_file, "r");
    if (!my_tree->file)
    {
        printf("File hasn't opened");
        return TREE_FILE_NOT_OPENED;
    }

    int size = get_size_of_file(my_tree->name_file);
    my_tree->text = (char *) calloc(size, sizeof(char));
    fread(my_tree->text, sizeof(char), size, my_tree->file);

    if (fclose(my_tree->file) != 0)
    {
        printf ("File hasn't closed");
        return TREE_FILE_NOT_CLOSED;
    }
    return TREE_SUCCESS;
}


void import_to_tree (Tree *my_tree, Node *node)
{
    assert(my_tree);
    assert(node);

    while (*my_tree->text != '\"')
    {
        my_tree->text++;
    }
    node->date = ++my_tree->text ;

    while (*my_tree->text != '\"')
    {
        my_tree->text++;
    }
    *my_tree->text = '\0';

    while (*my_tree->text != '{' && *my_tree->text != '}')
    {

        my_tree->text++;
    }

    if (*my_tree->text == '{')
    {
        struct Node *new_node_right = (Node*)calloc (1, sizeof(struct Node));
        node->right = new_node_right;
        import_to_tree(my_tree, node->right);
        struct Node *new_node_left = (Node*)calloc (1, sizeof(struct Node));
        node->left = new_node_left;
        import_to_tree(my_tree, node->left);
    }
    else
    {
        return;
    }
}

int get_size_of_file (const char *name_of_file)
{
    assert(name_of_file);

    int info_of_file = 0;
    struct stat buffer;

    if ((info_of_file = stat(name_of_file, &buffer)) != 0)
    {
        printf("stat failure error .%d\n", info_of_file);
        return TREE_STAT_ERROR;
    }

    return buffer.st_size;
}

void insert_node (Node *node, info_t value)
{

    assert(node);

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
        if (node->right == NULL)
        {
            struct Node *new_node = (Node *) calloc (1, sizeof(Node));
            node->right = new_node;

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
    printf (specif_for_tree_elem, node->date);
    if (node->left)
        print_tree(node->left);

    if (node->right)
        print_tree(node->right);
    printf (")");
}
