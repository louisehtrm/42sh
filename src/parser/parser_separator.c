#include "parser.h"

/**
 * \brief Parse separator
 *
 * separator:     ';' ('\n')* | ('\n')+
 */

enum parser_status parse_separator(struct token *tok, struct ast **tree, int *i)
{
    struct token tok_cur = tok[*i];

    if (tok_cur.type == SEMICOLON || tok_cur.type == LINEBREAK)
    {
        struct ast *sep_ast = ast_new(tok_cur);
        (*i)++;
        while (tok[*i].type != EOFP && tok[*i].type == LINEBREAK)
            (*i)++;
        *tree = sep_ast;
        return PARSER_OK;
    }
    else
    {
        /* return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree); */
        return PARSER_UNEXPECTED_TOKEN;
    }
}
