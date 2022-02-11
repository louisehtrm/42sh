#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "eval_ast.h"

size_t nb_words(char *s)
{
    if (s == NULL)
        return 0;

    size_t nb = 1;
    for (int i = 0; s[i]; i++)
        if (s[i] == ' ')
            nb++;

    return nb;
}

size_t word_len(char *s, int i)
{
    size_t len = 0;
    int j = i;
    while (s[j] && s[j] != ' ')
    {
        len++;
        j++;
    }
    return len;
}

char **tok_to_array(struct token tok)
{
    size_t nb_w = 1;
    size_t nb_w_opt = nb_words(tok.opt);
    size_t nb_w_arg = nb_words(tok.arg);
    nb_w += nb_w_arg + nb_w_opt;

    char **arr = malloc(sizeof(char *) * (nb_w + 1));
    arr[nb_w] = NULL;

    /* first cell with command name */
    arr[0] = tok.com;

    /* loop through tok.opt */
    int i = 0;
    size_t j = 1;
    for (; j < nb_w_opt + 1; j++)
    {
        size_t len = word_len(tok.opt, i);

        size_t k = 0;
        char *word = malloc(len + 1);
        while (k < len)
            word[k++] = tok.opt[i++];
        word[len] = '\0';
        i++;
        arr[j] = word;
    }

    /* loop throught tok.arg */
    i = 0;
    for (size_t k = 0; k < nb_w_arg; k++)
    {
        size_t len = word_len(tok.arg, i);

        size_t c = 0;
        char *word = malloc(len + 1);
        while (c < len)
            word[c++] = tok.arg[i++];
        word[len] = '\0';
        i++;
        arr[j + k] = word;
    }
    return arr;
}

void free_arr(char **arr)
{
    for (int i = 1; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}

void print_arr(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++)
        printf("arr[%d] : %s\n", i, arr[i]);
}

/* Execute the other builtins command */
int exec_other_command(struct token tok)
{
    char **arr = tok_to_array(tok);

    pid_t pid;
    int status;
    int return_value = 0;

    pid = fork();
    if (pid == -1)
    {
        errx(1, "fork failed");
    }
    if (pid == 0)
    {
        execvp(tok.com, arr);
        errx(127, "%s: command not found", tok.com);
        /*exit(127);*/
    }
    else
    {
        if (waitpid(pid, &status, 0) > 0)
        {
            if (WIFEXITED(status) && !WEXITSTATUS(status))
                return_value = 0;
            else if (WIFEXITED(status) && WEXITSTATUS(status))
            {
                if (WEXITSTATUS(status) == 127)
                    return_value = 127;
                else
                    return_value = 1;
            }
            else
                return_value = 130;
        }
    }
    free_arr(arr);
    return return_value;
}
