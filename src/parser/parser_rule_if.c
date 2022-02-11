#include "parser.h"

/**
 * rule_if: If compound_list Then compound_list [else_clause] Fi
 */

enum parser_status parse_rule_if(struct token *tok, struct ast **tree, int *i)
{
    /* 'if' */
    struct token tok_if = tok[*i];
    if (tok_if.type != IF)
        return PARSER_UNEXPECTED_TOKEN;
    (*i)++;

    /* compound_list */
    struct ast *condition_ast = NULL;
    enum parser_status list_status =
        parse_compound_list(tok, &condition_ast, i);
    if (list_status != PARSER_OK)
        return handle_parse_error(list_status, &condition_ast);

    /* check for the separator */
    if (*i > 0 && tok[*i - 1].type != LINEBREAK
        && tok[*i - 1].type != SEMICOLON)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &condition_ast);

    /* 'then' */
    struct token tok_cur = tok[*i];
    if (tok_cur.type != THEN)
    {
        // elena don't know how u handle
        ast_free(condition_ast);
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    }
    (*i)++;

    /* compound_list */
    struct ast *then_ast = NULL;
    list_status = parse_compound_list(tok, &then_ast, i);
    if (list_status != PARSER_OK)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &condition_ast);

    /* else_clause maybe */
    tok_cur = tok[*i];
    struct ast *else_ast = NULL;
    if (tok_cur.type == ELSE || tok_cur.type == ELIF)
    {
        enum parser_status status_else = parse_else_clause(tok, &else_ast, i);
        if (status_else == PARSER_UNEXPECTED_TOKEN)
        {
            ast_free(condition_ast);
            ast_free(then_ast);
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &else_ast);
        }
    }

    /* fi */
    tok_cur = tok[*i];
    if (tok_cur.type != FI)
    {
        ast_free(condition_ast);
        ast_free(then_ast);
        ast_free(else_ast);
        return PARSER_UNEXPECTED_TOKEN;
    }
    *tree = ast_new(tok_if);
    (*tree)->condition = condition_ast;
    (*tree)->left = then_ast;
    (*tree)->right = else_ast;
    (*i)++;
    return PARSER_OK;
}
