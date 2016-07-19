#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "util.h"

#define SYMBOL_MAX_LEN 50

/* static ast_t *True = &(ast_t){ AST_TRUE }; */
static ast_t *Nil = &(ast_t){ AST_NIL };
static ast_t *RParen = &(ast_t){ AST_RPAREN };
static ast_t *Dot = &(ast_t){ AST_DOT };
static char symbol_chars[] = "+-*/";

static char peek() {
  char c = getchar();
  ungetc(c, stdin);
  return c;
}

ast_t *new_symbol(char *sym)
{
  ast_t* ast = malloc(sizeof(ast_t));
  ast->name = strdup(sym);
  ast->type = AST_SYMBOL;
  return ast;
}

ast_t *new_int(int value)
{
  ast_t* ast = malloc(sizeof(ast_t));
  ast->value = value;
  ast->type = AST_INT;
  return ast;
}

ast_t *new_cell(ast_t* car, ast_t* cdr)
{
  ast_t* ast = malloc(sizeof(ast_t));
  ast->type = AST_CELL;
  ast->car = car;
  ast->cdr = cdr;
  return ast;
}

ast_t *reverse(ast_t *cell)
{
  ast_t* ret = Nil;
  while (cell != Nil) {
    ast_t *head = cell;
    cell = cell->cdr;
    head->cdr = ret;
    ret = head;
  }
  return ret;
}

ast_t *read_quote()
{
  ast_t *v = new_cell(parse(), Nil);
  return new_cell(new_symbol("quote"), v);
}

ast_t *read_lists()
{
  ast_t *head = Nil;

  for(;;) {
    ast_t *ast = parse();
    if (ast == NULL) {
      error("Paren is Unmatch");
    } else if (ast == Dot) {
      ast_t *last = parse();
      if (parse() != RParen)
        error("Paren is Unmatch");
      ast_t *t = reverse(head);
      t->cdr = last;
      return t;
    } else if (ast == RParen) {
      return reverse(head);
    }
    head = new_cell(ast, head);
  }
}

ast_t *read_symbol(char v)
{
  char buf[SYMBOL_MAX_LEN + 1];
  buf[0] = v;
  int i = 1;
  while (isalpha(peek()) || isdigit(peek()) || strchr(symbol_chars, peek())) {
    if (i >= SYMBOL_MAX_LEN)
      error("symbol name is too long");
    buf[i++] = getchar();
  }
  buf[i] = '\0';

  return new_symbol(buf);
}

ast_t *read_int(char v)
{
  int r = v - '0';
  while (isdigit(peek())) {
    r = (getchar() - '0') + (r * 10);
  }
  return new_int(r);
}

int is_nil(ast_t *ast)
{
  return ast == Nil;
}

void destory_ast(ast_t *ast)
{
  if (ast == NULL)
    return;

  switch(ast->type) {
  case AST_CELL:
    destory_ast(ast->car);
    destory_ast(ast->cdr);
    free(ast);
    return;
  case AST_SYMBOL:
    free(ast->name);
    free(ast);
    return;
  case AST_INT:
    free(ast);
    return;
  }
}

ast_t *parse()
{
  char c = getchar();

  if (c == '(')
    return read_lists();
  if (c == ' ')
    return parse();
  if (c == '\'')
    return read_quote();
  if (c == ')')
    return RParen;
  if (c == '.')
    return Dot;
  if (c == EOF)
    return NULL;
  if (isdigit(c))
    return read_int(c);
  if (isalpha(c) || strchr(symbol_chars, c))
    return read_symbol(c);
  perror("Invalid token");
  exit(1);
}
