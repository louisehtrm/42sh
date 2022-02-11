#include "parser.h"

/**
 * \brief command :  simple_command
 |   shell_command  (redirection)*
 |   funcdec (redirection)*
 */

enum parser_status parse_command(struct token *tok, struct ast **tree, int *i)
{
    int after = *i + 1;
    int afterafter = *i + 2;
    int func = 0;

    if (tok[*i].type != EOFP && tok[after].type == LEFT_PAR
        && tok[afterafter].type == RIGHT_PAR)
        func = 1;

    enum parser_status status = PARSER_UNEXPECTED_TOKEN;
    if (func == 0)
        status = parse_simple_command(tok, tree, i);
    if (status == ERROR)
        return PARSER_UNEXPECTED_TOKEN;
    if (status == PARSER_OK) /* there is a simple command */
        return status;

    status = parse_shell_command(tok, tree, i);
    if (status == PARSER_OK) /* there is a shell command */
    {
        while (1)
        {
            status = parse_redirection(tok, tree, i);
            if (status != PARSER_OK)
                return PARSER_OK;
        }
    }
    status = parse_funcdec(tok, tree, i); /* there is a funcdec command */
    if (status == PARSER_OK)
    {
        while (1)
        {
            status = parse_redirection(tok, tree, i);
            if (status != PARSER_OK)
                return PARSER_OK;
        }
    }
    return PARSER_UNEXPECTED_TOKEN;
}
