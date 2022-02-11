#include "parser.h"

/**
 * case_clause: case_item (';;' ('\n')* case_item)* [;;] ('\n')*
 */

enum parser_status parse_case_clause(struct token *tok, struct ast **tree,
                                     int *i)
{
    (void)*tok;
    (void)**tree;
    (void)*i;
    return PARSER_UNEXPECTED_TOKEN;
}
