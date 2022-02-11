#include "parser.h"

/**
 * do_group: Do compound_list Done
 */

enum parser_status parse_do_group(struct token *tok, struct ast **tree, int *i)
{
    /* DO */
    struct token tok_cur = tok[*i];
    if (tok_cur.type != DO)
        return PARSER_UNEXPECTED_TOKEN;
    (*i)++;

    /* compound_list */
    enum parser_status status = parse_compound_list(tok, tree, i);
    if (status != PARSER_OK)
        return handle_parse_error(status, tree);

    /* DONE */
    tok_cur = tok[*i];
    if (tok_cur.type != DONE)
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    (*i)++;
    return PARSER_OK;
}
