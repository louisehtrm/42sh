#include "ast.h"

#include <stdlib.h>

struct ast *ast_new(struct token tok)
{
    struct ast *new = malloc(sizeof(struct ast));
    new->token = tok;
    new->left = NULL;
    new->right = NULL;
    new->condition = NULL;
    return new;
}

void ast_free(struct ast *ast)
{
    if (ast)
    {
        /*if (ast->token.com)
          free(ast->token.com);
          if (ast->token.arg)
          free(ast->token.arg);
          if (ast->token.opt)
          free(ast->token.opt);*/

        if (ast->left)
            ast_free(ast->left);
        if (ast->right)
            ast_free(ast->right);
        if (ast->condition)
            ast_free(ast->condition);
    }

    free(ast);
    ast = NULL;
}
