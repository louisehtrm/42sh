#include <stdbool.h>

#include "parser.h"

/**
 * \brief Parse a shell_command
 *
 * input:  pipeline (('&&'|'||') ('\n')* pipeline)*
 */

enum parser_status parse_and_or(struct token *tok, struct ast **tree, int *i)
{
    enum parser_status status = parse_pipeline(tok, tree, i);
    if (status != PARSER_OK)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    while (1)
    {
        if ((tok[*i].type != AND)
            && (tok[*i].type != OR)) /* there is no ope, parser OK */
            return PARSER_OK;
        struct ast *ope_ast; /* create the tree */
        ope_ast = ast_new(tok[*i]);
        (*i)++;

        /* attach the new node to the ast */
        ope_ast->left = *tree;
        *tree = ope_ast;

        while (tok[*i].type == LINEBREAK) /* continue if linebreak */
            (*i)++;
        status = parse_pipeline(tok, &ope_ast->right,
                                i); /* parser another pipeline */
        if (status != PARSER_OK)
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    }
}
