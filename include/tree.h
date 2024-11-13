#ifndef TREE
#define TREE

typedef const char* info_t;
#define specif_for_tree_elem "%s"


typedef enum
{
    TREE_SUCCESS = 0,
    TREE_ALLOCATION_MEMORY_ERROR = 1,
    TREE_FILE_NOT_OPENED = 2,
    TREE_FILE_NOT_CLOSED = 3,
    TREE_STAT_ERROR = 4,
    TREE_NO_FREE_ELEM = 5

}Tree_errors;

struct Node
{
    info_t date;
    Node *right;
    Node *left;
};

struct Tree
{
    char *name_file;
    char *text;
    FILE *file;
};
void insert_node (Node *node, info_t value);
void print_tree (Node *node);
int reading_tree (Tree *my_tree);
void import_to_tree (Tree *my_tree, Node *node);
#endif


