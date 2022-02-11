#include "lexer.h"

struct token *lexer(char *str, size_t *length)
{
    struct list *lst = lexer_list(str, length);
    struct token *tokens = parser_token(lst, length);
    free_list(lst);
    return tokens;
}
