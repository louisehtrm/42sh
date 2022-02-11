#include <stdbool.h>

#include "parser.h"

/**
 * \brief Parse an element
 *
 * input:  WORD
 |   redirection
 */

enum parser_status parse_element(struct token *tok, struct ast **tree, int *i)
{
    if (tok[*i].type == COMMAND)
    {
        struct ast *element_ast = ast_new(tok[*i]);
        *tree = element_ast;
        (*i)++;
        return PARSER_OK;
    }
    if (tok[*i].type == REDIR)
    {
        enum parser_status status = parse_redirection(tok, tree, i);
        if (status != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        return PARSER_OK;
    }
    return PARSER_UNEXPECTED_TOKEN;
}
