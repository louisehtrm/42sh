#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#include "parser.h"

/**
 * \brief Parse a redirection
 *
 * input:
 |   [IONUMBER] '<' WORD
 |   [IONUMBER] '>' WORD
 |   [IONUMBER] '>>' WORD
 |   [IONUMBER] '<<' HEREDOC
 |   [IONUMBER] '<<-' HEREDOC
 |   [IONUMBER] '>&' WORD
 |   [IONUMBER] '<&' WORD
 |   [IONUMBER] '>|' WORD
 |   [IONUMBER] '<>' WORD
 */

int update_token(struct token *tokens, int i)
{
    char *str = tokens[i].com;
    if (!str)
        return 1;
    int len = 0;
    int len2 = 0;

    while (str[len] != '\0' && str[len] != '>' && str[len] != '<')
        len++;
    if (len == 0)
        return 0;
    while (str[len + len2] != '\0')
        len2++;

    char *fd_str = my_malloc(len + 1);
    char *redir = my_malloc(len2 + 1);

    for (int i = 0; i < len; i++)
        fd_str[i] = str[i];
    for (int i = 0; i < len2; i++)

        redir[i] = str[len + i];

    fd_str[len] = '\0';
    redir[len2] = '\0';

    tokens[i].opt = fd_str;
    if (tokens[i].com)
        free(tokens[i].com);
    tokens[i].com = redir;
    return 0;
}

enum parser_status parse_redirection(struct token *tokens, struct ast **tree,
                                     int *i)
{
    if (tokens[*i].type != REDIR)
        return ERROR;

    if (update_token(tokens, *i) == 1)
        return ERROR;

    /*if (tree == NULL)
        return ERROR;*/

    struct token tok_redir = tokens[*i];

    (*i)++;
    struct token tok_right = tokens[*i];
    if (tok_right.type != COMMAND)
        return handle_parse_error(ERROR, tree);

    /*struct token tok_new;
    tok_new.type = SEMICOLON;
    tok_new.com = ";";
    tok_new.arg = NULL;
    tok_new.opt = NULL;*/

    struct ast *redir = ast_new(tok_redir);
    redir->left = *tree;
    redir->right = ast_new(tok_right);
    /*struct ast *new = ast_new(tok_new);
    new->left = redir;
    new->right = NULL;
    *tree = new;*/
    *tree = redir;

    (*i)++;

    /*if ((*tree)->left == NULL || (*tree)->right == NULL)
        return ERROR;*/

    /*struct token last_tok = tokens[*i];
    if (last_tok.type != SEMICOLON && last_tok.type != REDIR
            && last_tok.type != EOFP && last_tok.type != RIGHT_PAR )
        return handle_parse_error(ERROR, tree);*/
    return PARSER_OK;
}
