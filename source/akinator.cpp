#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "akinator.h"
#include "tree.h"

const int size_of_node_array = 15;
const int max_size = 50;
const int size_of_answer = 5;

void guess(Tree *my_tree)
{
    assert(my_tree);
    Node *current_node = my_tree->root_tree;

    char answer[size_of_answer] = "";
    while(true)
    {
        printf ("%s?\nAnswer:", current_node->data);
        scanf("%s", answer);
        if(strcmp(answer, "YES") == 0)
        {
            if (!is_leaf(current_node))
                current_node = current_node->right;
            else
            {
                printf ("You have guessed %s", current_node->data);
                break;
            }

        }
        else if(strcmp(answer, "NO") == 0)
        {
            if (!is_leaf(current_node))
                current_node = current_node->left;
            else
            {
                printf ("Sorry, we don't know ");
                break;
            }

        }
    }

    return;
}

bool is_leaf(Node *node)
{
    assert(node);

    if (!node->left && !node->right)
    {
        return true;
    }

    return false;
}

Node* search (Node *node, const char *item)
{
    assert(node);
    assert(item);

    if(is_leaf(node))
    {
        if(strcmp(node->data, item) == 0)
        {
            return node;
        }
        else
        {
            return NULL;
        }
    }

    Node *left_result = search(node->left, item);
    if(left_result != NULL)
    {
        return left_result;
    }

    Node *right_result = search(node->right, item);
    if(right_result != NULL)
    {
        return right_result;
    }

    return NULL;
}

int define (Tree *my_tree)
{
    assert(my_tree);

    printf ("Printf an item: ");
    char *item = (char*) calloc (max_size, sizeof (char));
    scanf ("%s", item);
    struct Node *result_node = search(my_tree->root_tree, item);
    if (!result_node)
    {
        printf ("Not found");
        return NO_SUCH_ITEM_ERROR;
    }
    printf ("%s is ", result_node->data);

    Node **array= (Node**) calloc (size_of_node_array , sizeof(Node*));
    if (!array)
    {
        printf ("Allocation error");
        return TREE_ALLOCATION_MEMORY_ERROR;
    }

    int i = 0;

    while (result_node)
    {
        array[i++] = result_node;
        result_node = result_node->parent;
    }

    for (int j = i - 1 ; j > 0; j--)
    {
        if (array[j-1] == array[j]->right)
            printf ("%s ", array[j]->data);
        else
            printf ("NOT %s ", array[j]->data);
    }

    printf ("\n");
    free(array);
    free(item);
    return TREE_SUCCESS;

}
