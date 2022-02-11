#include "prettyprint.h"

#include <stddef.h>
#include <stdio.h>

char *reversed_type[] = { "IF",      "THEN",     "ELSE",      "ELIF",
                          "FI",      "COMMAND",  "LINEBREAK", "SEMICOLON",
                          "LEFT_AC", "RIGHT_AC", "AND",       "OR",
                          "PIPE",    "NOT",      "WHILE",     "UNTIL",
                          "FOR",     "REDIR",    "EOFP" };

static void print_token(struct ast *tree, int *cdd, int depth, char *pos,
                        int child_nb, int last)
{
    for (int i = 0; i < depth; i++)
    {
        putchar(' ');
        putchar(' ');
        if (cdd[i])
        {
            putchar('|');
            if (i == depth - 1)
                putchar('-');
            else
                putchar(' ');
        }
        else if (i == depth - 1 && last)
        {
            putchar('`');
            putchar('-');
        }
        else
        {
            putchar(' ');
            putchar(' ');
        }
    }
    struct token tok = tree->token;
    printf("%s: %s,  c: '%d'", pos, reversed_type[tok.type], child_nb);
    printf(", com: '%s',  arg: '%s',  opt: '%s'\n", tok.com, tok.arg, tok.opt);
}

static void print_tree(struct ast *tree, int *cdd, int depth, char *pos, int l)
{
    int child_nb = 0;
    if (tree->left)
        child_nb++;
    if (tree->right)
        child_nb++;
    if (tree->condition)
        child_nb++;

    int last = 1;

    print_token(tree, cdd, depth, pos, child_nb, l);

    if (tree->condition)
    {
        last = (tree->left || tree->right) == 0;
        cdd[depth] = !last;
        print_tree(tree->condition, cdd, depth + 1, "C", last);
    }
    if (tree->left)
    {
        last = tree->right == NULL;
        cdd[depth] = !last;
        print_tree(tree->left, cdd, depth + 1, "L", last);
    }
    if (tree->right)
    {
        last = 1;
        cdd[depth] = 0;
        print_tree(tree->right, cdd, depth + 1, "R", last);
    }
}

void pretty_print(struct ast *tree, char *tags)
{
    int child_depth_data[DEPTH_MAX] = { 0 };
    int depth = 0;

    printf("----------\nAST:\ntags:%s.\n----------\n", tags);

    print_tree(tree, child_depth_data, depth, "", 0);
}
