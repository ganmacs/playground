#ifndef PARSE_H
#define PARSE_H

typedef struct ast_t {
  int type;

  union {
    int value;
    char *name;

    struct {
      struct ast_t *car;
      struct ast_t *cdr;
    };
  };
} ast_t;

typedef enum {
  AST_INT,
  AST_SYMBOL,
  AST_CELL,

  AST_TRUE,
  AST_NIL,
  AST_RPAREN,
  AST_DOT,
} ast_type_t;

ast_t *parse();

int is_nil();

#endif
