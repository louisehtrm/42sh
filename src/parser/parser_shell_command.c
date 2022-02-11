#include "parser.h"

/**
 * \brief '{' compound_list '}'
 |   '(' compound_list ')'
 |   rule_for
 |   rule_while
 |   rule_until
 |   rule_case
 |   rule_if
 */

enum parser_status parse_shell_command(struct token *tok, struct ast **tree,
                                       int *i)
{
    struct token tok_cur = tok[*i];
    enum parser_status status;
    if (tok_cur.type == LEFT_AC) /* '{' compound_list '}' */
    {
        (*i)++;
        status = parse_compound_list(tok, tree, i);
        if (status != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        if (tok[*i].type == RIGHT_AC)
        {
            (*i)++;
            return PARSER_OK;
        }
        return PARSER_UNEXPECTED_TOKEN;
    }
    if (tok_cur.type == LEFT_PAR) /* '(' compound_list ')' */
    {
        (*i)++;
        status = parse_compound_list(tok, tree, i);
        if (status != PARSER_OK)
            return PARSER_UNEXPECTED_TOKEN;
        if (tok[*i].type == RIGHT_PAR)
        {
            (*i)++;
            return PARSER_OK;
        }
        return PARSER_UNEXPECTED_TOKEN;
    }
    if ((status = parse_rule_for(tok, tree, i)) == PARSER_OK) /* rule_for */
        return status;
    if ((status = parse_rule_while(tok, tree, i)) == PARSER_OK) /* rule_while */
        return status;
    if ((status = parse_rule_until(tok, tree, i)) == PARSER_OK) /* rule_until */
        return status;
    if ((status = parse_rule_case(tok, tree, i)) == PARSER_OK) /* rule_case */
        return status;
    if ((status = parse_rule_if(tok, tree, i)) == PARSER_OK) /* rule_if */
        return status;
    return PARSER_UNEXPECTED_TOKEN;
}
