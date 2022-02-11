#include <err.h>
#include <stdio.h>
#include <string.h>

#include "eval_ast.h"

/* Evaluate the operator command
 */
int eval_operators(struct ast *node, int *res)
{
    int exit = eval_ast(node->left, res);
    if (*res == -1)
        return exit;
    if (node->token.type == OR && !(*res))
        return exit;
    if (node->token.type == OR || (node->token.type == AND && !(*res)))
        exit = eval_ast(node->right, res);
    return exit;
}
