#include "parser.h"

/**
 * rule_case: Case WORD ('\n')* 'in' ('\n')* [case_clause] Esac
 */

enum parser_status parse_rule_case(struct token *tok, struct ast **tree, int *i)
{
    (void)*tok;
    (void)**tree;
    (void)*i;
    return PARSER_UNEXPECTED_TOKEN;
}
