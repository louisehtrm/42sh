#include "parser.h"

/**
 * compound_list:   ('\n')* and_or ((';'|'\n') ('\n')* and_or)* [(';'|'\n')
 * ('\n')*]
 */

enum parser_status parse_compound_list(struct token *tok, struct ast **tree,
                                       int *i)
{
    while (tok[*i].type == LINEBREAK) /* ('\n')* */
        (*i)++;
    enum parser_status status = parse_and_or(tok, tree, i); /* parse and/or */
    if (status != PARSER_OK)
        return PARSER_UNEXPECTED_TOKEN;
    while (1)
    {
        if (tok[*i].type != SEMICOLON && tok[*i].type != LINEBREAK
            && tok[*i].type != ESP)
            return PARSER_OK;
        struct ast *sep_ast = NULL; /* create the tree */
        if (tok[*i].type == LINEBREAK)
        {
            struct token new;
            new.type = SEMICOLON;
            new.com = ";";
            new.arg = NULL;
            new.opt = NULL;
            sep_ast = ast_new(new);
        }
        else
            sep_ast = ast_new(tok[*i]);
        (*i)++;

        /* attach the new node to the ast */
        sep_ast->left = *tree;
        *tree = sep_ast;

        while (tok[*i].type == LINEBREAK) /* ('\n')* */
            (*i)++;

        /* parse at the right */
        status = parse_and_or(tok, &sep_ast->right, i);
        if (status != PARSER_OK)
            return PARSER_OK;
    }

    /*if ((tok[*i].type != SEMICOLON) && (tok[*i].type != LINEBREAK))
      {
      (*i)++;
      while (tok[*i].type == LINEBREAK) // ('\n')*
      (*i)++;
      return PARSER_OK;
      }*/
    return PARSER_OK;
}
