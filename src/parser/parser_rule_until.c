#include "parser.h"

/**
 * rule_until: Until compound_list do_group
 */

enum parser_status parse_rule_until(struct token *tok, struct ast **tree,
                                    int *i)
{
    struct token tok_while = tok[*i];
    if (tok_while.type != UNTIL)
        return PARSER_UNEXPECTED_TOKEN;
    (*i)++;

    /* compound_list */
    struct ast *condition_ast = NULL;
    enum parser_status status = parse_compound_list(tok, &condition_ast, i);
    if (status != PARSER_OK)
        return handle_parse_error(status, &condition_ast);

    /* check for the separator before the do */
    if (*i > 0 && tok[*i - 1].type != LINEBREAK
        && tok[*i - 1].type != SEMICOLON)
        return handle_parse_error(status, &condition_ast);

    /* do_group */
    struct ast *do_ast = NULL;
    status = parse_do_group(tok, &do_ast, i);
    if (status != PARSER_OK)
    {
        ast_free(condition_ast);
        return handle_parse_error(status, &do_ast);
    }
    /* EVRYTHING OK : composition of the tree */
    *tree = ast_new(tok_while);
    (*tree)->condition = condition_ast;
    (*tree)->left = do_ast;
    return PARSER_OK;
}
