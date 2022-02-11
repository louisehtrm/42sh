#include <err.h>
#include <stdio.h>

#include "eval_ast.h"

/**
 *  Print s  char by char, even \n and \t
 */
void char_by_char_print(char *s)
{
    int mid = 0;
    if (s == NULL)
        s = "";
    else
    {
        for (int i = 0; s[i]; i++)
        {
            if (s[i] == '\'')
            {
                if (mid)
                    mid = 0;
                else
                {
                    if (i == 0 || (i > 0 && s[i - 1] != '\\'))
                        mid = 1;
                    else
                        putchar('\'');
                }
                continue;
            }
            else if (s[i] == '\n')
            {
                putchar('\\');
                putchar('n');
            }
            else if (s[i] == '\t')
            {
                putchar('\\');
                putchar('t');
            }
            // not sure about this ...
            else if (s[i] == '\\')
            {
                if (s[i + 1] != '\0' && s[i + 1] == '\'')
                {
                    if (mid)
                        putchar('\\');
                    continue;
                }
                i++;
                if (s[i + 1] && (s[i + 1] == '\'' || s[i + 1] == '"'))
                    i++;
                if (s[i])
                {
                    putchar(s[i - 1]);
                    putchar(s[i]);
                }
            }
            else
                putchar(s[i]);
        }
    }
}

void option_e_print(char *s)
{
    int mid = 0;
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\'') /* there is a simple quote */
        {
            if (mid)
                mid = 0;
            else
            {
                if (i == 0 || (i > 0 && s[i - 1] != '\\'))
                    mid = 1;
                else
                    putchar('\'');
            }
            i++;
            continue;
        }
        if (s[i] == '\\')
        {
            if (s[i + 1] != '\0' && s[i + 1] == '\'')
            {
                if (mid)
                    putchar('\\');
                i++;
                continue;
            }
            i++;
            if (s[i])
            {
                if (s[i] == '\\')
                    i++;
                if (s[i])
                {
                    if (s[i] == 'n')
                        putchar('\n');
                    else if (s[i] == 't')
                        putchar('\t');
                    else if (s[i] == '\\')
                        putchar('\\');
                    else
                        putchar(s[i]);
                    i++;
                }
            }
        }
        else
        {
            putchar(s[i++]);
        }
    }
}

void print_opt(struct token tok, int i)
{
    char *str = tok.opt;
    putchar('-');
    while (str[i])
    {
        putchar(str[i]);
        i++;
    }
    if (tok.arg)
        putchar(' ');
}

/**
 * \brief   Execute the echo command of the token
 *          Return 0
 */
int echo_command(struct token tok)
{
    if (tok.opt != NULL && tok.opt[0] != '\0')
    {
        int n_opt = 0;
        int e_opt = 0;
        int is_opt = 0;
        for (int i = 0; tok.opt[i]; i++)
        {
            if (tok.opt[i] == '-')
            {
                if (is_opt)
                {
                    print_opt(tok, i);
                    break;
                }
                is_opt = 1;
            }
            else if (is_opt && tok.opt[i] == 'e'
                     && (tok.opt[i + 1] == '\0' || tok.opt[i + 1] == ' '))
            {
                e_opt = 1;
                is_opt = 0;
            }
            else if (is_opt && tok.opt[i] == 'e'
                     && (tok.opt[i + 1] != '\0' && tok.opt[i + 1] == 'n'))
            {
                e_opt = 1;
                n_opt = 1;
                is_opt = 0;
                i++;
                break;
            }
            else if (is_opt && tok.opt[i] == 'n'
                     && (tok.opt[i + 1] == '\0' || tok.opt[i + 1] == ' '))
            {
                n_opt = 1;
                is_opt = 0;
            }
            else if (is_opt && tok.opt[i] == 'n'
                     && (tok.opt[i + 1] != '\0' && tok.opt[i + 1] == 'e'))
            {
                e_opt = 1;
                n_opt = 1;
                is_opt = 0;
                i++;
                break;
            }
            else if (is_opt && tok.opt[i] == 'E'
                     && (tok.opt[i + 1] == '\0' || tok.opt[i + 1] == ' '))
            {
                e_opt = 0;
                is_opt = 0;
            }
            else if (is_opt)
            {
                print_opt(tok, i);
                break;
            }
        }
        if (tok.arg == NULL)
            putchar('\n');
        else
        {
            if (n_opt && e_opt)
                option_e_print(tok.arg);
            else if (n_opt)
                char_by_char_print(tok.arg);
            else if (e_opt)
            {
                option_e_print(tok.arg);
                putchar('\n');
            }
            else
            {
                char_by_char_print(tok.arg);
                putchar('\n');
            }
        }
    }
    else
    {
        char_by_char_print(tok.arg);
        putchar('\n');
    }
    return 0;
}
