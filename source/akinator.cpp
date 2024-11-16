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

int create_array_features (Item_t *item);
int dump_different(Item_t* item_first, Item_t* item_second);
int dump_similar (Item_t* item_first, Item_t* item_second, int *flag_is_nothing_in_common);
int ctor_item(Tree *my_tree, Item_t *item);

int guess(Tree *my_tree)
{
    assert(my_tree);
    Node *current_node = my_tree->root_tree;

    char answer[size_of_answer] = "";
    printf ("You can answer, using \"YES\" or \"NO\" or \"EXIT\" \n");
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
        else if(strcmp(answer, "EXIT") == 0)
        {
            return TREE_SUCCESS;
        }
        else if(strcmp(answer, "NO") == 0)
        {
            if (!is_leaf(current_node))
                current_node = current_node->left;
            else
            {
                printf ("Sorry, we don't know, do you what to broad my base ?\n");
                scanf("%s", answer);
                if(strcmp(answer, "YES") == 0)
                {
                    if (insert_node(current_node) != TREE_SUCCESS)
                        return TREE_INSERT_ERROR;

                    return TREE_SUCCESS;
                }
                else
                    break;
            }

        }
    }

    return TREE_SUCCESS;
}

int insert_node (Node *node)
{

    assert(node);

    char *item = (char*)calloc(max_size, sizeof(char));
    if (!item)
    {
        printf ("Allocation Error\n");
        return TREE_ALLOCATION_MEMORY_ERROR;
    }
    printf ("What did you think of ?\n");
    scanf ("\n%[^\n]", item);

    char *dif = (char*)calloc(max_size, sizeof(char));
    if (!dif)
    {
        printf ("Allocation Error\n");
        return TREE_ALLOCATION_MEMORY_ERROR;
    }


    printf ("What feature does %s have, unlike %s ?\n", item, node->data);
    scanf("\n%[^\n]", dif);

    Node *right_leaf = (Node *)calloc (1, sizeof(Node));

    if (!right_leaf)
    {
        printf ("Allocation Error\n");
        return TREE_ALLOCATION_MEMORY_ERROR;
    }


    Node *left_leaf = (Node *)calloc (1, sizeof(Node));

    if (!left_leaf)
    {
        printf ("Allocation Error\n");
        return TREE_ALLOCATION_MEMORY_ERROR;
    }

    node->right = right_leaf;
    right_leaf->data = item;
    right_leaf->parent = node;

    node->left = left_leaf;
    left_leaf->data = node->data;
    left_leaf->parent = node;

    node->data = dif;

    return TREE_SUCCESS;
}


bool is_leaf(Node *node)
{
    assert(node);

    return !node->left && !node->right;
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

int create_array_features (Item_t *item)
{
    assert(item);


    item->array_features= (Node**) calloc (item->amount_of_features, sizeof(Node*));

    if (!item->array_features)
        return TREE_ALLOCATION_MEMORY_ERROR;

    while (item->node)
    {
        item->array_features[item->amount_of_features++] = item->node;
        item->node = item->node->parent;
    }

    return TREE_SUCCESS;
}

int ctor_item(Tree *my_tree, Item_t *item)
{
    assert(item);
    assert(my_tree);

    item->name = (char*) calloc (max_size, sizeof (char));
    scanf ("\n%[^\n]", item->name);
    item->node= search(my_tree->root_tree, item->name);
    if (!item->node)
    {
        printf ("Not found");
        return NO_SUCH_ITEM_ERROR;
    }
    item->amount_of_features = 0;
    return TREE_SUCCESS;

}

int define (Tree *my_tree)
{
    assert(my_tree);

    Item_t item = {};
    printf ("Printf an item: ");

    if (ctor_item(my_tree, &item) != TREE_SUCCESS)
        return NO_SUCH_ITEM_ERROR;

    printf ("%s is ", item.node->data);

    if (create_array_features(&item) != TREE_SUCCESS)
        return TREE_ALLOCATION_MEMORY_ERROR;

    for (int j = item.amount_of_features - 1 ; j > 0; j--)
    {
        if (item.array_features[j-1] == item.array_features[j]->right)
            printf ("%s ", item.array_features[j]->data);
        else
            printf ("NOT %s ", item.array_features[j]->data);
    }

    printf ("\n");
    free(item.array_features);
    free(item.name);
    return TREE_SUCCESS;

}

int difference (Tree *my_tree)
{
    assert(my_tree);

    Item_t item_first = {};
    Item_t item_second = {};

    printf ("Print first item: ");
    if (ctor_item(my_tree, &item_first) != TREE_SUCCESS)
        return NO_SUCH_ITEM_ERROR;

    printf ("Print second item: ");
    if (ctor_item(my_tree, &item_second) != TREE_SUCCESS)
        return NO_SUCH_ITEM_ERROR;

    printf ("%s and %s ", item_first.name, item_second.name);

    if (create_array_features(&item_first) != TREE_SUCCESS)
        return TREE_ALLOCATION_MEMORY_ERROR;

    if (create_array_features(&item_second) != TREE_SUCCESS)
        return TREE_ALLOCATION_MEMORY_ERROR;

    item_first.amount_of_features--;
    item_second.amount_of_features--;

    int flag_is_nothing_in_common = 0;

    while (item_first.array_features[item_first.amount_of_features] == item_second.array_features[item_second.amount_of_features])
    {

        dump_similar(&item_first, &item_second, &flag_is_nothing_in_common);

        item_first.amount_of_features--;
        item_second.amount_of_features--;
    }

    if (flag_is_nothing_in_common == 0)
        printf ("have nothing in common");
    else
        dump_different(&item_first, &item_second);

    printf ("\n");
    free(item_first.array_features);
    free(item_second.array_features);
    free(item_first.name);
    free(item_second.name);

    return TREE_SUCCESS;
}

int dump_similar (Item_t* item_first, Item_t* item_second, int *flag_is_nothing_in_common)
{
    assert(item_first);
    assert(item_second);

    if (item_first->array_features[item_first->amount_of_features - 1] == item_first->array_features[item_first->amount_of_features]->right &&
        item_second->array_features[item_second->amount_of_features - 1] == item_second->array_features[item_second->amount_of_features]->right )
    {
        printf ("are %s, ", item_first->array_features[item_first->amount_of_features]->data);
        *flag_is_nothing_in_common = 1;
    }
    else if (item_first->array_features[item_first->amount_of_features - 1] == item_first->array_features[item_first->amount_of_features]->left &&
             item_second->array_features[item_second->amount_of_features - 1] == item_second->array_features[item_second->amount_of_features]->left )
    {
        printf ("are NOT %s, ", item_first->array_features[item_first->amount_of_features]->data);
        *flag_is_nothing_in_common = 1;
    }

    return TREE_SUCCESS;
}

int dump_different(Item_t* item_first, Item_t* item_second)
{
    assert(item_first);
    assert(item_second);

    if (item_first->array_features[item_first->amount_of_features] == item_first->array_features[item_first->amount_of_features + 1]->right)
        printf ("but %s is %s ", item_first->name, item_first->array_features[item_first->amount_of_features + 1]->data);
    else
        printf ("but %s is %s ", item_second->name, item_second->array_features[item_second->amount_of_features + 1]->data);

    return TREE_SUCCESS;
}
