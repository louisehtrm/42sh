#ifndef EVAL_AST_H
#define EVAL_AST_H

#include "../parser/parser.h"

int echo_command(struct token tok);
int eval_ast(struct ast *tree, int *res);
int eval_negation(struct ast *tree, int *res);
int eval_while(struct ast *node, int *res);
int eval_until(struct ast *node, int *res);
int eval_for(struct ast *node, int *res);
int eval_operators(struct ast *node, int *res);
int eval_redirection(struct ast *tree, int *res);
int exec_other_command(struct token tok);
int eval_pipe(struct ast *node, int *res);
int cd_command(struct token tok);
void init_cd_variables();

#endif /* !EVAL_AST_H */
