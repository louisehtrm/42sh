#pragma once

#ifndef PARSER_H
#    define PARSER_H

#    include <stdio.h>

#    include "../ast/ast.h"
#    include "../hash_map/hash_map.h"

enum parser_status
{
    PARSER_OK,
    PARSER_UNEXPECTED_TOKEN,
    ERROR
};

enum parser_status handle_parse_error(enum parser_status status,
                                      struct ast **tree);
enum parser_status parse_input(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_list(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_and_or(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_pipeline(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_command(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_simple_command(struct token *tok, struct ast **tree,
                                        int *i);
enum parser_status parse_shell_command(struct token *tok, struct ast **tree,
                                       int *i);
enum parser_status parse_funcdec(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_redirection(struct token *tok, struct ast **tree,
                                     int *i);
enum parser_status parse_prefix(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_element(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_compound_list(struct token *tok, struct ast **tree,
                                       int *i);
enum parser_status parse_rule_for(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_rule_while(struct token *tok, struct ast **tree,
                                    int *i);
enum parser_status parse_rule_until(struct token *tok, struct ast **tree,
                                    int *i);
enum parser_status parse_rule_case(struct token *tok, struct ast **tree,
                                   int *i);
enum parser_status parse_rule_if(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_else_clause(struct token *tok, struct ast **tree,
                                     int *i);
enum parser_status parse_do_group(struct token *tok, struct ast **tree, int *i);
enum parser_status parse_case_clause(struct token *tok, struct ast **tree,
                                     int *i);
enum parser_status parse_case_item(struct token *tok, struct ast **tree,
                                   int *i);

#endif
