#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "eval_ast.h"

/* redir '>' : output redirection
int redir_s(struct ast *tree, char *file, char *fd_str, int *res)
{
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 1;

    int stdout_dup = dup(fd_redir);
    int fd = 0;
    (void)file;

        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (fd == -1)
            return 1;

    if (dup2(fd, fd_redir) == -1)
        return 1;

    eval_ast(tree->left, res);

    fflush(stdout);

    dup2(stdout_dup, fd_redir);
    close(stdout_dup);
    return 0;
}*/

/* redir '<' : input redirection */
int redir_is(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 0;

    int stdout_dup = dup(fd_redir);

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, fd_redir) == -1)
    {
        *res = 1;
        return ex;
    }

    ex = eval_ast(tree->left, res);

    fflush(stdin);

    dup2(stdout_dup, STDOUT_FILENO);
    close(stdout_dup);
    return ex;
}

/* redir '>&' when simple case */
int redir_and_s(struct ast *tree, char *file, int *res)
{
    int ex = -2;
    int stdout_dup = dup(STDOUT_FILENO);
    int stderr_dup = dup(STDERR_FILENO);

    int fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, STDERR_FILENO) == -1)
    {
        *res = 1;
        return ex;
    }

    ex = eval_ast(tree->left, res);

    fflush(stdout);
    fflush(stderr);

    dup2(stdout_dup, STDOUT_FILENO);
    dup2(stderr_dup, STDERR_FILENO);
    close(stdout_dup);
    close(stderr_dup);

    return ex;
}

/* redir '>&' -> need to test ????????????????????????????,*/
int redir_and(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 1;

    int i = 0;
    while (file[i] != '\0' && file[i] >= '0' && file[i] <= '9')
        i++;
    if (file[i] == '\0')
    {
        int fd = atoi(file);
        if (fcntl(fd, F_GETFD) == -1)
        {
            *res = 1;
            return ex;
        }

        int std = dup(fd_redir);
        dup2(fd, fd_redir);

        ex = eval_ast(tree->left, res);

        fflush(stdout);
        dup2(std, fd_redir);
        close(std);
    }
    else
    {
        if (fd_str)
            close(fd_redir);
        else
            ex = redir_and_s(tree, file, res);
    }
    return ex;
}

/* redir '<&' -> need to tsst ???????????????????????????*/
int redir_iand(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 0;

    int i = 0;
    while (file[i] != '\0' && file[i] >= '0' && file[i] <= '9')
        i++;
    if (file[i] == '\0')
    {
        int fd = atoi(file);
        if (fcntl(fd, F_GETFD) == -1)
        {
            *res = 1;
            return ex;
        }

        int std = dup(fd_redir);
        dup2(fd, fd_redir);

        ex = eval_ast(tree->left, res);

        fflush(stdin);
        dup2(std, fd_redir);
        close(std);
    }
    else
        close(fd_redir);
    return ex;
}

/* redir '>>' */
int redir_dob(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 1;

    int stdout_dup = dup(fd_redir);

    int fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, fd_redir) == -1)
    {
        *res = 1;
        return ex;
    }

    ex = eval_ast(tree->left, res);

    fflush(stdout);

    dup2(stdout_dup, fd_redir);
    close(stdout_dup);
    return ex;
}

/* redir '<>' -> error for now ???????????????????? */
int redir_dif(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 0;

    int stdout_dup = dup(fd_redir);

    int fd = open(file, O_RDWR);
    if (fd == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, fd_redir) == -1)
    {
        *res = 1;
        return ex;
    }

    ex = eval_ast(tree->left, res);

    fflush(stdin);

    dup2(stdout_dup, fd_redir);
    close(stdout_dup);
    return ex;
}

/* redir '>|'  */
int redir_pipe(struct ast *tree, char *file, char *fd_str, int *res)
{
    int ex = -2;
    int fd_redir;
    if (fd_str)
        fd_redir = atoi(fd_str);
    else
        fd_redir = 1;

    int stdout_dup = dup(fd_redir);

    int fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1)
    {
        *res = 1;
        return ex;
    }

    if (dup2(fd, fd_redir) == -1)
    {
        *res = 1;
        return ex;
    }

    ex = eval_ast(tree->left, res);

    fflush(stdout);

    dup2(stdout_dup, fd_redir);
    close(stdout_dup);
    return ex;
}

int eval_redirection(struct ast *tree, int *res)
{
    if (tree->left == NULL || tree->right == NULL)
    {
        *res = 127;
        return -2;
    }

    int ex = 0;
    char *redir_symbol = tree->token.com;
    char *fd_str = tree->token.opt;
    char *file = tree->right->token.com;

    if (!strcmp(redir_symbol, ">"))
    {
        ex = redir_pipe(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, "<"))
    {
        ex = redir_is(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, ">&"))
    {
        ex = redir_and(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, "<&"))
    {
        ex = redir_iand(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, ">>"))
    {
        ex = redir_dob(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, "<>"))
    {
        ex = redir_dif(tree, file, fd_str, res);
    }
    else if (!strcmp(redir_symbol, ">|"))
    {
        ex = redir_pipe(tree, file, fd_str, res);
    }
    else
        ex = 1;
    return ex;
}
