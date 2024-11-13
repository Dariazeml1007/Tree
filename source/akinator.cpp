#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys\stat.h>

#include "akinator.h"
#include "tree.h"

void guess(Node *node)
{
    printf ("%s?\nAnswer:", node->date);
    char answer[5] = "";
    scanf("%s", answer);
    if (strcmp(answer, "YES") == 0)
    {
        if (node->right)
            guess(node->right);
        else
        {
            printf ("You have guessed %s", node->date);
            return;
        }
    }

    if (strcmp(answer, "NO") == 0)
    {
        if (node->left)
            guess(node->left);
        else
        {
            printf ("Sorry, we don't know ");
            return;
        }
    }

    return;


}
