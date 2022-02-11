#include <err.h>
#include <stdio.h>
#include <string.h>

#include "eval_ast.h"

/* Evaluate the while command */
int eval_while(struct ast *node, int *res)
{
    int exit = 0;
    int res_condition = 0;
    exit = eval_ast(node->condition, &res_condition);
    if (*res == -1)
        return exit;
    while (!res_condition)
    {
        exit = eval_ast(node->left, res);
        if (*res == -1)
            return exit;
        exit = eval_ast(node->condition, &res_condition);
        if (*res == -1)
            return exit;
    }
    return exit;
}
