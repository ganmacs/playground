#ifndef PARSE_H
#define PARSE_H

#include "mlisp.h"

ast_t *parse();

void destory_ast(ast_t *ast);

int is_nil();

#endif
