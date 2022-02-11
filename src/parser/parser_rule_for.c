#include <stdlib.h>
#include <string.h>

#include "parser.h"

/**
 * \brief Parse for command
 *
 * while:  For WORD ([';']|[('\n')* 'in' (WORD)* (';'|'\n')]) ('\n')* do_group
 */

enum parser_status parse_rule_for(struct token *tok, struct ast **tree, int *i)
{
    /* FOR */
    struct token tok_for = tok[*i];
    if (tok_for.type != FOR)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    (*i)++;

    /* WORD */
    struct token tok_cur = tok[*i];
    if (tok_cur.type != COMMAND)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    (*i)++;

    /* [';'] */
    tok_cur = tok[*i];
    struct ast *list_for = NULL;
    if (tok_cur.type != SEMICOLON)
    {
        /* '\n' */
        while (tok[*i].type == LINEBREAK)
            (*i)++;

        /* IN */
        tok_cur = tok[*i];
        if (tok_cur.type == IN)
        {
            (*i)++;

            /* WORD* */
            list_for = ast_new(tok[*i]);
            (*i)++;

            /* (';' | '\n') */
            tok_cur = tok[*i];
            if (tok_cur.type != SEMICOLON && tok_cur.type != LINEBREAK)
                return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &list_for);
            (*i)++;
        }
    }
    else
        (*i)++;
    /* ('\n')* */
    while (tok[*i].type == LINEBREAK)
        (*i)++;

    /* do_group */
    struct ast *do_ast = NULL;
    enum parser_status status = parse_do_group(tok, &do_ast, i);
    if (status != PARSER_OK)
    {
        ast_free(list_for);
        return handle_parse_error(status, &do_ast);
    }

    /* everything okay : create the tree */
    *tree = ast_new(tok_for);
    (*tree)->condition = list_for;
    (*tree)->left = do_ast;
    return PARSER_OK;
}
