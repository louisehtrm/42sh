#include <stdbool.h>

#include "parser.h"

/**
 * \brief Parse a prefix
 *
 * input:  ASSIGNMENT_WORD
 |   redirection
 */

enum parser_status parse_prefix(struct token *tok, struct ast **tree, int *i)
{
    if (tok[*i].type == COMMAND)
    {
        struct ast *command_ast; /* create the tree */
        command_ast = ast_new(tok[*i]);
        *tree = command_ast;
        (*i)++;
        return PARSER_OK;
    }
    if (tok[*i].type == REDIR)
    {
        enum parser_status status = parse_redirection(tok, tree, i);
        if (status != PARSER_OK)
            return handle_parse_error(status, tree);
        return PARSER_OK;
    }
    return PARSER_UNEXPECTED_TOKEN;
}
