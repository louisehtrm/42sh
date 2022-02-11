#pragma once

#include <stddef.h>

#include "../lexer/lexer.h"
#include "../utils/xalloc.h"

/**
 * This is a AST structure.
 */

struct ast
{
    struct token token;
    struct ast *left;
    struct ast *right;
    struct ast *condition;
};

/**
 ** \brief add a root in the ast
 */
struct ast *ast_new(struct token tok);

/**
 ** \brief Recursively free the given ast
 */
void ast_free(struct ast *tree);
