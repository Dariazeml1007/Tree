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

int main(const int argc, const char* argv[])
{
    struct Node node = {};
    struct Tree my_tree = {};

    FILE *file = fopen ("dump.dot", "w");
    if (!file)
    {
        printf("File hasn't opened");
        return 0;
    }

    my_tree.name_file = "tree.txt";
    if (reading_tree (&my_tree) != TREE_SUCCESS)
        assert(0 && "Reading tree from file error");

    import_to_tree (&my_tree, &node);

    dump (&node, file);

    if (argc == 1)
    {
        printf ("You can use flag --guess\n"
                "You can use flag --define\n");
        return TREE_SUCCESS;
    }

    if (argc == 2)
    {
        if (strcmp(argv[1], "--guess") == 0)
        {
            guess(&node);
        }
        else
        {
            printf ("Not correct command");
        }
    }

    if (fclose(file) != 0)
    {
        printf ("File hasn't closed");
        return 0;
    }

}

