#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "eval_ast.h"

/* Evaluate the pipe command */
int eval_pipe(struct ast *node, int *res)
{
    int status1 = 0;
    int status2 = 0;
    int fd[2];
    if (pipe(fd) == -1)
        return -2;

    int pid_1 = fork();
    if (pid_1 < 0)
        return -2;

    if (pid_1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        eval_ast(node->left, res);
        close(fd[1]);
        exit(*res);
    }
    else
    {
        close(fd[1]);
        waitpid(pid_1, &status2, 0);
        int pid_2 = fork();
        if (pid_2 < 0)
            return -2;
        if (pid_2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            eval_ast(node->right, res);
            exit(*res);
        }
        else
        {
            waitpid(pid_2, &status1, 0);
            close(fd[0]);
        }
    }

    int res_1 = 0;
    if (WIFEXITED(status1))
        res_1 = WEXITSTATUS(status1);

    *res = res_1;

    return -2;
}
