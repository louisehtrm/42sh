#include "parser.h"

/**
 * else_clause:  Else compound_list |
 Elif compund_list Then compound_list [else_clause]
 */

enum parser_status parse_else_clause(struct token *tok, struct ast **tree,
                                     int *i)
{
    struct token tok_else = tok[*i];
    if (tok_else.type == ELSE)
    {
        (*i)++;
        struct ast *else_ast = NULL;
        enum parser_status status = parse_compound_list(tok, &else_ast, i);
        if (status != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        *tree = else_ast;
        return PARSER_OK;
    }
    if (tok_else.type == ELIF)
    {
        (*i)++;
        /* compound_list */
        struct ast *condition_ast = NULL;
        enum parser_status status = parse_compound_list(tok, &condition_ast, i);
        if (status != PARSER_OK)
            return handle_parse_error(status, &condition_ast);

        /* then */
        struct token tok_cur = tok[*i];
        if (tok_cur.type != THEN)
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &condition_ast);
        (*i)++;

        /* compound_list */
        struct ast *then_ast = NULL;
        status = parse_compound_list(tok, &then_ast, i);
        if (status != PARSER_OK)
        {
            ast_free(then_ast);
            return handle_parse_error(status, &condition_ast);
        }

        /* else_clause maybe */
        struct ast *else_ast = NULL;
        parse_else_clause(tok, &else_ast, i);

        tok_else.type = IF;
        *tree = ast_new(tok_else);
        (*tree)->condition = condition_ast;
        (*tree)->left = then_ast;
        (*tree)->right = else_ast;
        return PARSER_OK;
    }
    return PARSER_UNEXPECTED_TOKEN;
}
