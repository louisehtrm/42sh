#include "parser.h"

/**
 * \brief Parse list expressions
 *
 * list:       and_or ((';'|'&') and_or)* [';'|'&']
 */

enum parser_status parse_list(struct token *tok, struct ast **tree, int *i)
{
    enum parser_status status;
    status = parse_and_or(tok, tree, i); /* parse and/or */
    if (status != PARSER_OK)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);

    if ((tok[*i].type != SEMICOLON)
        && (tok[*i].type != AND)) /* parse ';' or '|' */
        return PARSER_OK;

    while (1) /* for the '*' */
    {
        if ((tok[*i].type != SEMICOLON)
            && (tok[*i].type != AND)) /* parse ';' or '|' */
            return PARSER_OK;

        struct ast *ope_ast;
        ope_ast = ast_new(tok[*i]);
        (*i)++;

        /* attach the new node to the ast */
        ope_ast->left = *tree;
        *tree = ope_ast;

        if (tok[*i].type == EOFP)
            return PARSER_OK;

        /* parse and/or command in the right side */
        status = parse_and_or(tok, &ope_ast->right, i);
        if (status != PARSER_OK)
            return PARSER_OK;
    }
    if ((tok[*i].type == SEMICOLON) || (tok[*i].type == AND))
        return PARSER_OK;

    return PARSER_OK;
}
