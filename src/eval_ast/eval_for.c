#include <err.h>
#include <stdio.h>
#include <string.h>

#include "eval_ast.h"

/* Return the number of words between IN and SEPARATOR in for WORD in WORD*"*/
int number_words_for(struct token tok)
{
    int i = 0;
    int wrd = 1;
    char *arg = tok.arg;
    if (!arg)
        return 1;
    while (arg[i] != '\0')
    {
        if (arg[i] == ' ')
        {
            wrd++;
        }

        i++;
    }
    return wrd + 1;
}

/* Evaluate the for command */
int eval_for(struct ast *node, int *res)
{
    *res = 0;
    int exit = 0;
    int nb_loop = 0;
    if (node->condition)
        nb_loop = number_words_for(node->condition->token);

    for (int i = 0; i < nb_loop; i++)
    {
        exit = eval_ast(node->left, res);
        if (*res == -1)
            return exit;
    }
    return exit;
}
