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
    TREE_NO_FREE_ELEM = 5,
    NO_SUCH_ITEM_ERROR = 6

}Tree_errors;

struct Node
{
    info_t data;
    Node *parent;
    Node *right;
    Node *left;
};

struct Tree
{
    const char *name_of_dump_file;
    const char *name_of_file_with_tree;
    char *text;
    FILE *pfile_tree;
    FILE *pfile_dump;
    Node *root_tree;
};
void insert_node (Node *node, info_t value);
void print_tree (Node *node);
int reading_tree (Tree *my_tree);
void import_to_tree (Tree *my_tree, Node *node);
void node_dtor (Node *node);
int tree_ctor (Tree *my_tree, const char *name_of_file_with_tree, const char * name_of_dump_file);
int tree_dtor (Tree *my_tree);
#endif


