#include "eval_ast.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_map/hash_map.h"

struct hash_map *hash_func;

int exit_function(struct ast *tree, int *res)
{
    *res = -1;
    if (tree->token.arg == NULL)
    {
        /* exit the last command */
        int exit = 0;
        return exit;
    }
    else
    {
        int exit = atoi(tree->token.arg);
        if (exit >= 0 && exit < 256)
            return exit;
        /* don't know yeat */
        return -1;
    }
}

int eval_command(struct ast *tree, int *res)
{
    int ex = -2;
    struct token tok = tree->token;
    char *str = tok.com;
    if (!strcmp("echo", str))
        *res = echo_command(tok);
    else if (!strcmp("false", str))
        *res = 1;
    else if (!strcmp("true", str))
        *res = 0;
    else if (!strcmp("cd", str))
        *res = cd_command(tok);
    else
    {
        if ((*tree).left) /* assign func */
        {
            hash_map_insert(hash_func, str, (*tree).left);
        }
        else /* call of a function or other command */
        {
            struct ast *ast_command = hash_map_get(hash_func, str);
            if (ast_command == NULL)
            {
                *res = exec_other_command(tok);
            }
            else
            {
                ex = eval_ast(ast_command, res);
            }
        }
    }
    return ex;
}

int eval_if(struct ast *node, int *res)
{
    int exit = eval_ast(node->condition, res);
    if (*res == -1)
        return exit;
    if (*res == 0)
        exit = eval_ast(node->left, res);
    else
    {
        //*res = 0;
        exit = eval_ast(node->right, res);
    }
    return exit;
}

/**
 * \brief   Evaluate
 *          Return 0 if true, else 1
 */
int eval_ast(struct ast *tree, int *res)
{
    int exit = 0;
    struct ast *node = tree;
    if (node == NULL)
        return -2;
    if (!strcmp(node->token.com, "exit"))
        return exit_function(tree, res);
    else if (node->token.type == SEMICOLON)
    {
        exit = eval_ast(node->left, res);
        if (*res == -1)
            return exit;
        exit = eval_ast(node->right, res);
    }
    else if (node->token.type == IF)
    {
        exit = eval_if(node, res);
    }
    else if (node->token.type == COMMAND)
    {
        exit = eval_command(node, res);
    }
    else if (node->token.type == WHILE)
    {
        exit = eval_while(node, res);
    }
    else if (node->token.type == FOR)
    {
        exit = eval_for(node, res);
    }
    else if (node->token.type == REDIR)
    {
        exit = eval_redirection(node, res);
    }
    else if (node->token.type == AND || node->token.type == OR)
    {
        exit = eval_operators(node, res);
    }
    else if (node->token.type == PIPE)
    {
        exit = eval_pipe(node, res);
    }
    else if (node->token.type == UNTIL)
    {
        exit = eval_until(node, res);
    }
    return exit;
}
