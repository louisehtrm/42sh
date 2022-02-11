#include <err.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

void free_struct_tok(struct token *tokens, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        if (tokens[i].arg)
            free(tokens[i].arg);
        if (tokens[i].opt)
            free(tokens[i].opt);
        if (tokens[i].com)
            free(tokens[i].com);
    }
    free(tokens);
}

/* associate the token to a str */
struct token parser(char *str, struct token *tokens, int i)
{
    static struct token_model exprs[] = {
        { "\n", LINEBREAK }, { ";", SEMICOLON }, { "|", PIPE },
        { "{", LEFT_AC },    { "}", RIGHT_AC },  { "if", IF },
        { "then", THEN },    { "else", ELSE },   { "elif", ELIF },
        { "fi", FI },        { "&&", AND },      { "||", OR },
        { "!", NOT },        { "while", WHILE }, { "until", UNTIL },
        { "for", FOR },      { "*>", REDIR },    { "*<", REDIR },
        { "*>&", REDIR },    { "*<&", REDIR },   { "*>>", REDIR },
        { "*<>", REDIR },    { "*>|", REDIR },   { "do", DO },
        { "done", DONE },    { "(", LEFT_PAR },  { ")", RIGHT_PAR },
        { "&", ESP }
    };

    struct token tok;
    tok.com = str;
    tok.arg = NULL;
    tok.opt = NULL;

    if (!strcmp(str, "in"))
    {
        tok.type = IN;
        return tok;
        int j = i - 1;
        while (j > 0 && tokens[j].type == LINEBREAK)
            j--;
        j--;
        if ((i > 1 && tokens[i - 2].type == FOR) || tokens[j].type == FOR)
        {
            tok.type = IN;
            return tok;
        }
    }

    for (unsigned i = 0; i < sizeof(exprs) / sizeof(*exprs); ++i)
    {
        if (!fnmatch(exprs[i].str, str, 0))
        {
            tok.type = exprs[i].type;
            return tok;
        }
    }

    tok.type = COMMAND;
    return tok;
}

struct token *new_arg(struct token *tokens, size_t j, char *str, size_t len)
{
    if (tokens[j - 1].arg == NULL)
        tokens[j - 1].arg = str;
    else
    {
        len += strlen(tokens[j - 1].arg) + 2;
        char *new = my_malloc(len);
        strcpy(new, tokens[j - 1].arg);
        strcat(new, " ");
        strcat(new, str);
        free(str);
        free(tokens[j - 1].arg);
        new[len - 1] = '\0';
        tokens[j - 1].arg = new;
    }
    return tokens;
}

struct token *new_opt(struct token *tokens, size_t j, char *str, size_t len)
{
    if (tokens[j - 1].opt == NULL)
        tokens[j - 1].opt = str;
    else
    {
        len += strlen(tokens[j - 1].opt) + 2;
        char *new = my_malloc(len);
        strcpy(new, tokens[j - 1].opt);
        strcat(new, " ");
        strcat(new, str);
        free(str);
        free(tokens[j - 1].opt);
        new[len - 1] = '\0';
        tokens[j - 1].opt = new;
    }
    return tokens;
}

/* create the tokens table */
struct token *create_token(struct list *lst, size_t *length,
        struct token *tokens)
{
    size_t final_length = *length;
    int j = 0;
    int echo_mode = 0;
    for (size_t i = 0; i < *length; ++i)
    {
        char *str = lst->value;
        size_t len = strlen(str);
        tokens[j] = parser(str, tokens, j);

        if ((tokens[j].type == LINEBREAK || tokens[j].type == SEMICOLON
                    || tokens[j].type == OR || tokens[j].type == RIGHT_PAR
                    || tokens[j].type == PIPE || tokens[j].type == REDIR
                    || tokens[j].type == LEFT_PAR || tokens[j].type == AND)
                && echo_mode)
            echo_mode = 0;

        else if (echo_mode)
        {
            if (str[0] == '-')
                tokens = new_opt(tokens, j, str, len);
            else
                tokens = new_arg(tokens, j, str, len);
            final_length--;
            j--;
        }

        else if (tokens[j].type == COMMAND)
        {
            if (!strcmp(tokens[j].com, "echo") && !echo_mode
                && (j == 0 || (j > 0 && tokens[j - 1].type != COMMAND)))
                echo_mode = 1;
            else if (j > 0 && tokens[j - 1].type == COMMAND)
            {
                if (str[0] == '-')
                    tokens = new_opt(tokens, j, str, len);
                else
                    tokens = new_arg(tokens, j, str, len);
                final_length--;
                j--;
            }
        }

        j++;

        lst = lst->next;
    }

    tokens[j].type = EOFP;
    tokens[j].com = NULL;
    tokens[j].arg = NULL;
    tokens[j].opt = NULL;

    final_length++;

    *length = final_length;

    return tokens;
}

/* main function */
struct token *parser_token(struct list *lst, size_t *length)
{
    struct token *tokens = my_malloc((*length + 1) * sizeof(struct token));
    tokens = create_token(lst, length, tokens);

    return tokens;
}
