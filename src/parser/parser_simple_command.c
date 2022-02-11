#include "parser.h"

/**
 * \brief simple_command :  (prefix)+
 * |   (prefix)* (element)+
 */

enum parser_status parse_simple_command(struct token *tok, struct ast **tree,
                                        int *i)
{
    enum parser_status status = parse_prefix(tok, tree, i);
    if (status == ERROR)
        return PARSER_UNEXPECTED_TOKEN;
    if (status != PARSER_OK) /* case (element)+ */
    {
        struct ast *element_ast = NULL;
        status = parse_element(tok, &element_ast, i);
        if (status != PARSER_OK)
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, &element_ast);
        element_ast->left = *tree;
        *tree = element_ast;

        /*connect the two tree but i dont know how */
        while (1)
        {
            struct ast *element_ast_mult;
            status = parse_element(tok, &element_ast_mult, i);
            if (status != PARSER_OK)
                return PARSER_OK;
            element_ast_mult->left = *tree;
            *tree = element_ast_mult;
        }
        return PARSER_OK;
    }
    while (1)
    {
        // struct ast *ast_sev = NULL;
        status = parse_prefix(tok, tree, i);
        if (status != PARSER_OK)
        {
            if (status == ERROR)
                return status;
            status = parse_element(tok, tree, i);
            if (status != PARSER_OK)
                return PARSER_OK;
            return PARSER_OK;
        }

        // ast_sev->left = *tree;
        //*tree = ast_sev;
    }
}
