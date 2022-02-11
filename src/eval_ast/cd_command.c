#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "eval_ast.h"

char last_dir[260];
char curr_dir[260];

void init_cd_variables()
{
    last_dir[0] = '\0';
    getcwd(curr_dir, sizeof(curr_dir));
}

/*
 * Execute the cd command
 */
int cd_command(struct token tok)
{
    /* cd - */
    if (tok.opt && !strcmp("-", tok.opt) && !tok.arg)
    {
        /* no last directory */
        if (last_dir[0] == '\0')
            return 1;
        else
        {
            if (chdir(last_dir))
                return 1;
            getcwd(last_dir, 260);
            printf("%s\n", last_dir);
            char *backup_lastdir = malloc(260);
            strcpy(backup_lastdir, last_dir);
            strcpy(last_dir, curr_dir);
            strcpy(curr_dir, backup_lastdir);
            free(backup_lastdir);
        }
    }
    else
    {
        /* normal cd command */
        char *path = malloc(260 * sizeof(char));
        strcpy(path, curr_dir);
        if (path[strlen(path) - 1] != '/')
            strcat(path, "/");
        strcat(path, tok.arg);

        if (chdir(path))
        {
            if (path)
                free(path);
            errx(1, "No such file or directory");
        }

        stpcpy(last_dir, curr_dir);
        strcpy(curr_dir, path);
        if (path)
            free(path);
    }
    return 0;
}
