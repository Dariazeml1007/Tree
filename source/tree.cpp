#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "tree.h"
#include "akinator.h"


void record_node (Node *node, FILE *file, int *count_space);
int get_size_of_file (const char *name_of_file);

int reading_tree (Tree *my_tree)
{
    assert(my_tree);

    my_tree->pfile_tree = fopen (my_tree->name_of_file_with_tree, "r");
    if (!my_tree->pfile_tree)
    {
        printf("File hasn't opened");
        return TREE_FILE_NOT_OPENED;
    }

    int size = get_size_of_file(my_tree->name_of_file_with_tree);
    my_tree->text = (char *) calloc(size, sizeof(char));
    fread(my_tree->text, sizeof(char), size, my_tree->pfile_tree);

    if (fclose(my_tree->pfile_tree) != 0)
    {
        printf ("File hasn't closed");
        return TREE_FILE_NOT_CLOSED;
    }
    return TREE_SUCCESS;
}

int record_tree_to_file (Tree *my_tree, Node *node, const char* name_of_file)
{
    assert(my_tree);

    my_tree->pfile_tree = fopen(name_of_file, "w");

    if (!my_tree->pfile_tree)
    {
        printf("File hasn't opened");
        return TREE_FILE_NOT_OPENED;
    }
    int count_space = 0;
    record_node(node, my_tree->pfile_tree, &count_space);

    if (fclose(my_tree->pfile_tree) != 0)
    {
        printf ("File hasn't closed");
        return TREE_FILE_NOT_CLOSED;
    }
    return TREE_SUCCESS;

}

void record_node (Node *node, FILE *file, int *count_space)
{
    assert(node);
    assert(file);

    for (int index = 0; index < *count_space; index++)
        fprintf(file, "    ");

    fprintf(file, "{%s\n", node->data);
    if (!is_leaf(node))
    {
        (*count_space)++;

        record_node(node->right, file, count_space);

        record_node(node->left, file, count_space);

        (*count_space)--;

    }

    for (int index = 0; index < *count_space; index++)
        fprintf(file, "    ");
    fprintf(file,"}\n");

}

void import_to_tree (Tree *my_tree, Node *node)
{
    assert(my_tree);
    assert(node);

    while (*my_tree->text != '\"')
    {
        my_tree->text++;
    }
    node->data = ++my_tree->text ;

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
        node->right->parent = node;
        import_to_tree(my_tree, node->right);
        struct Node *new_node_left = (Node*)calloc (1, sizeof(struct Node));
        node->left = new_node_left;
        node->left->parent = node;
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



void print_tree (Node *node)
{

    if (node == NULL)
    {
        printf ("NULL pointer\n");
        return;
    }
    printf ("(");
    printf (specif_for_tree_elem, node->data);
    if (node->left)
        print_tree(node->left);

    if (node->right)
        print_tree(node->right);
    printf (")");
}

int tree_ctor (Tree *my_tree, const char *name_of_file_with_tree, const char * name_of_dump_file)
{
    assert(my_tree);
    assert(name_of_file_with_tree);
    assert(name_of_dump_file);

    my_tree->name_of_file_with_tree = name_of_file_with_tree;
    my_tree->name_of_dump_file = name_of_dump_file;

    my_tree->pfile_dump = fopen (my_tree->name_of_dump_file, "w");
    if (!my_tree->pfile_dump)
    {
        printf("File hasn't opened");
        return TREE_FILE_NOT_OPENED;
    }

    return TREE_SUCCESS;

}

int tree_dtor (Tree *my_tree)
{
    assert(my_tree);

    if (fclose(my_tree->pfile_dump) != 0)
    {
        printf ("File hasn't closed");
        node_dtor(my_tree->root_tree);
        return TREE_FILE_NOT_CLOSED;
    }

    node_dtor(my_tree->root_tree);
    return TREE_SUCCESS;
}


void node_dtor (Node *node)
{
    assert(node);

    if (!is_leaf(node->right))

        node_dtor(node->right);

    else
        free(node->right);

    if (!is_leaf(node->left))

        node_dtor(node->left);

    else
        free(node->left);

    free(node);
    return;

}

