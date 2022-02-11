#include <err.h>
#include <fcntl.h>
#include <io/cstream.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils/vec.h>

#include "eval_ast/eval_ast.h"
#include "hash_map/hash_map.h"
#include "pretty_print/prettyprint.h"

struct hash_map *hash_func;

/* global variables for the cd command */
char last_dir[260];
char curr_dir[260];

/* main function that build and evaluate the tree */
int main_42sh(struct token *tokens, size_t *length)
{
    hash_func = hash_map_init(3);

    init_cd_variables();

    struct token init_tok;
    init_tok.type = SEMICOLON;
    init_tok.com = ";";
    init_tok.arg = NULL;
    init_tok.opt = NULL;
    struct ast *t = ast_new(init_tok);
    struct ast **tree = &t;
    int i = 0;
    int res = 0;
    enum parser_status final = parse_input(tokens, tree, &i);
    if (final == 1)
    {
        ast_free(*tree);
        free_struct_tok(tokens, *length);
        hash_map_free(hash_func);
        errx(2, "Syntax error");
    }
    else
    {
        int exit = eval_ast(*tree, &res);
        if (res == -1)
            res = exit;
        ast_free(*tree);
        free_struct_tok(tokens, *length);
        hash_map_free(hash_func);
    }
    return res;
}

/* Parse the command line arguments and return a character stream */
static struct cstream *parse_args(int argc, char *argv[])
{
    /* If launched without argument, read the standard input */
    if (argc == 1)
    {
        if (isatty(STDIN_FILENO))
            return cstream_readline_create();
        return cstream_file_create(stdin, /* fclose_on_free */ false);
    }

    /* 42sh FILENAME */
    if (argc == 2)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            errx(2, "Failed to open input file");
            // return NULL;
        }

        return cstream_file_create(fp, /* fclose_on_free */ true);
    }

    errx(2, "Usage: %s [COMMAND]\n", argv[0]);
}

/* Read and print lines on newlines until EOF and return an error code */
int eval_sev_lines(struct cstream *cs, struct vec *line)
{
    enum error err;
    size_t final_length = 0;
    struct list *final_list = malloc(sizeof(struct list));
    final_list->value = NULL;
    final_list->next = NULL;
    struct list *tmp = final_list;

    while (true)
    {
        /* Read the next character */
        int c;
        if ((err = cstream_pop(cs, &c)))
            errx(2, "fail to parse the content of the file");

        /* If the end of file was reached, stop right there */
        if (c == EOF)
            break;

        /* If a newline was met, print the line */
        if (c == '\n')
        {
            vec_push(line, c);
            size_t length = 0;
            struct list *lst = lexer_list(vec_cstring(line), &length);
            tmp->next = lst;
            while (tmp->next)
                tmp = tmp->next;
            final_length += length;
            vec_reset(line);
            continue;
        }

        /* Otherwise, add the character to the line */
        vec_push(line, c);
    }

    tmp = final_list;
    final_list = final_list->next;
    free(tmp);
    struct token *tokens = parser_token(final_list, &final_length);
    free_list(final_list);
    return main_42sh(tokens, &final_length);
}

/* eval line from the user when -c is used */
int eval_line(char *str)
{
    struct token *tokens = NULL;
    size_t length = 0;
    tokens = lexer(str, &length);
    return main_42sh(tokens, &length);
}

int main(int argc, char *argv[])
{
    int final;

    /* Case with an argument */
    if (argc > 1 && !strcmp(argv[1], "-c"))
    {
        if (argc <= 2)
            errx(2, "Usage: %s [COMMAND]\n", argv[0]);

        // init(argc, argv, 0);
        char *str = argv[2];
        final = eval_line(str);
    }

    /* Other case : parse command line arguments and get an input stream */
    else
    {
        // init(argc, argv, 1);
        struct cstream *cs;
        cs = parse_args(argc, argv);

        /* Create a vector to hold the current line */
        struct vec line;
        vec_init(&line);

        /* Run the test loop */
        final = eval_sev_lines(cs, &line);

        cstream_free(cs);
        vec_destroy(&line);
    }
    return final;
}
