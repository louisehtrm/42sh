#include <stdbool.h>

#include "parser.h"

/**
 * \brief Parse a funcdec
 *
 * input: WORD '(' ')' ('\n')* shell_command
 */

struct hash_map *hash_func;

enum parser_status parse_funcdec(struct token *tok, struct ast **tree, int *i)
{
    if (tok[*i].type == COMMAND)
    {
        // char* key = tok[*i].com;
        struct ast *comd_ast;
        comd_ast = ast_new(tok[*i]);
        (*i)++;

        /* attach the new node to the ast */
        comd_ast->left = *tree;
        *tree = comd_ast;

        if (tok[*i].type == LEFT_PAR)
        {
            (*i)++;
            if (tok[*i].type == RIGHT_PAR)
            {
                (*i)++;
                while (tok[*i].type == LINEBREAK)
                    (*i)++;
                struct ast *ast_func = NULL;
                enum parser_status status =
                    parse_shell_command(tok, &ast_func, i);
                if (status != PARSER_OK)
                {
                    ast_free(ast_func);
                    return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
                }
                /* insert my function in my hash map */
                /* hash_map_insert(hash_func, key, ast_func); */
                (*tree)->left = ast_func;
                return PARSER_OK;
            }
            return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
        }
        return handle_parse_error(PARSER_UNEXPECTED_TOKEN, tree);
    }
    return PARSER_UNEXPECTED_TOKEN;
}
