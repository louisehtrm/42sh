#include "parser.h"

#include <err.h>

enum parser_status handle_parse_error(enum parser_status status,
                                      struct ast **tree)
{
    // warnx("unexpected token");
    ast_free(*tree);
    *tree = NULL;
    return status;
}
