#include "parser.h"

/**
 * case_item: ['('] WORD ('|' WORD)* ')' ('\n')*  [ compound_list ]
 */

enum parser_status parse_case_item(struct token *tok, struct ast **tree, int *i)
{
    (void)*tok;
    (void)**tree;
    (void)*i;
    return PARSER_UNEXPECTED_TOKEN;
}
