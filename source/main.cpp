#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "tree.h"
#include "tree_dump.h"
#include "akinator.h"
#include "arg.h"



int main(const int argc, const char* argv[])
{
    struct Node node = {};
    struct Tree my_tree = {};
    struct Argv_type flags = {};
    my_tree.root_tree = &node;

    if (tree_ctor (&my_tree, "tree.txt", "dump.dot") != TREE_SUCCESS)
        assert(0 && "Ctor tree error");

    if (reading_tree (&my_tree) != TREE_SUCCESS)
        assert(0 && "Reading tree from file error");

    import_to_tree (&my_tree, &node);

    dump (&node, my_tree.pfile_dump);

    process_args(argc, argv, &flags);

    if (flags.is_define)
    {
        if (define (&my_tree) != TREE_SUCCESS)
            assert(0 && "Define error");
    }

    if (flags.is_guess)
    {
        guess(&my_tree);
    }

    tree_dtor(&my_tree);

}

