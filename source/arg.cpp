#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "akinator.h"
#include "tree.h"
#include "arg.h"

int process_args (const int argc, const char* argv[], Argv_type *flags)
{
    assert(argv);

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
            flags->is_guess = true;

        }
        else if (strcmp(argv[1], "--define") == 0)
        {
            flags->is_define = true;
        }
        else
        {
            printf ("Not correct command");
        }
    }
    return TREE_SUCCESS;
}
