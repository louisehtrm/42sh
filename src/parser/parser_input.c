#include "parser.h"

/**
 * \brief Parse either an expression, or nothing
 *
 * input:  EOF  |  list EOF | '\n' | list '\n'
 */

enum parser_status parse_input(struct token *tok, struct ast **tree, int *i)
{
    struct ast **base_tree = tree;

    while (tok[*i].type != EOFP)
    {
        if (tok[*i].type == EOFP) /* check EOPF */
            return PARSER_OK;
        while (tok[*i].type == LINEBREAK) /* check linebreak */
            (*i)++;
        struct ast *tmp_tree = NULL;
        enum parser_status status =
            parse_list(tok, &tmp_tree, i); /* parse the list */
        if (status != PARSER_OK) /* if no list, handle an error */
            return handle_parse_error(status, &tmp_tree);
        (*base_tree)->left = tmp_tree;
        if (tok[*i].type == EOFP /*|| tok[*i].type == LINEBREAK*/)
            return PARSER_OK;
        if (tok[*i].type == LINEBREAK)
        {
            while (tok[*i].type == LINEBREAK)
                (*i)++;
            struct token tmp;
            tmp.type = SEMICOLON;
            tmp.com = ";";
            tmp.arg = NULL;
            tmp.opt = NULL;
            (*base_tree)->right = ast_new(tmp);
            base_tree = &((*base_tree)->right);
            continue;
        }
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    }
    return PARSER_OK;
}
