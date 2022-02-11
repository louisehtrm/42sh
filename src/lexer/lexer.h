#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

#include "memory.h"

struct list
{
    char *value;
    struct list *next;
};

enum type_tok
{
    IF = 0,
    THEN = 1,
    ELSE = 2,
    ELIF = 3,
    FI = 4,
    COMMAND = 5,
    LINEBREAK = 6,
    SEMICOLON = 7,
    LEFT_AC = 8,
    RIGHT_AC = 9,
    AND = 10,
    OR = 11,
    PIPE = 12,
    NOT = 13,
    WHILE = 14,
    UNTIL = 15,
    FOR = 16,
    REDIR = 17,
    DONE = 18,
    DO = 19,
    IN = 20,
    EOFP = 21,
    LEFT_PAR,
    RIGHT_PAR,
    ESP,
    FUNC,
    ALIAS
};

struct token
{
    enum type_tok type;
    char *com;
    char *arg;
    char *opt;
};

struct token_model
{
    char *str;
    enum type_tok type;
};

/* list_lexer.c */
void free_list(struct list *lst);
struct list *lexer_list(char *str, size_t *length);

/* token_lexer.c */
struct token *parser_token(struct list *lst, size_t *length);
void free_struct_tok(struct token *tokens, size_t length);

/* lexer.c */
struct token *lexer(char *str, size_t *length);

#endif /* ! LEXER_H */
