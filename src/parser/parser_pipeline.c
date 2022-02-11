#include <stdbool.h>

#include "parser.h"

/**
 * \brief Parse a pipeline
 *
 * input:  ['!'] command ('|' ('\n')* command)*
 */

enum parser_status parse_pipeline(struct token *tok, struct ast **tree, int *i)
{
    enum parser_status status;
    struct token tok_cur = tok[*i];
    struct ast *not = NULL;
    int i_b = *i;

    if (tok_cur.type == NOT) /* there is a not */
    {
        (*i)++;
        status = parse_command(tok, &not, i);
    }
    else
        status = parse_command(tok, tree, i);

    if (not != NULL) /* the case where the not is fill */
    {
        *tree = ast_new(tok[i_b]);
        (*tree)->left = not ;
    }

    if (status != PARSER_OK)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    while (1)
    {
        if (tok[*i].type != PIPE) /* there is no pipe, parser OK */
            return PARSER_OK;
        struct ast *pipe_ast; /* create the tree */
        pipe_ast = ast_new(tok[*i]);
        (*i)++;

        /* attach the new node to the ast */
        pipe_ast->left = *tree;
        *tree = pipe_ast;

        while (tok[*i].type == LINEBREAK) /* continue if linebreak */
            (*i)++;
        status = parse_command(tok, &pipe_ast->right,
                               i); /* parser another command */

        if (status != PARSER_OK)
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    }
}
