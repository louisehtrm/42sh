#include "eval_ast.h"

/*
 * \brief   Evaluate a negation tree
 *          Return 0 if true, else 1
 */

int eval_negation(struct ast *node, int *res)
{
    int res_tree = 0;
    int exit = eval_ast(node->left, &res_tree);
    if (*res == -1)
        return exit;
    if (res_tree)
        *res = 0;
    else
        *res = 1;
    return exit;
}
