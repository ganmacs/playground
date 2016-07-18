#ifndef MLISP_H
#define MLISP_H

typedef struct env_t {
  char *name;
  struct obj_t* val;
  struct env_t *next;
} env_t;

typedef struct obj_t *primitive_t(struct env_t *env, struct obj_t *list);

typedef enum {
  TINT,
  TSYMBOL,
  TPRIMITIVE,
  TCELL,

  TNIL
} type_t;

typedef struct obj_t {
  /* type of object */
  type_t type;

  /* size of object */
  int size;

  /* actual value of object */
  union {
    /* store int value */
    int value;

    /* store string value */
    char *name;

    /* store primitive (function etc...) */
    primitive_t *fn;

    /* store cons cell */
    struct {
      struct obj_t *car;
      struct obj_t *cdr;
    };
  };
} obj_t;

typedef enum {
  AST_INT,
  AST_SYMBOL,
  AST_CELL,

  AST_TRUE,
  AST_NIL,
  AST_RPAREN,
  AST_DOT,
} ast_type_t;

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

obj_t *NIL;

#endif
