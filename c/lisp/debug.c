#include <stdio.h>
#include "debug.h"

void print_ast(ast_t *ast)
{
  while (!is_nil(ast)){
    switch(ast->type) {
    case AST_CELL:
      printf("(");
      print_ast(ast->car);

      if (ast->cdr->type == AST_INT || ast->cdr->type == AST_SYMBOL) {
        printf(" . ");
        print_ast(ast->cdr);
      } else {
        while (!is_nil(ast->cdr) && (ast->cdr->type == AST_CELL)) {
          printf(" ");
          print_ast(ast->cdr->car);
          ast->cdr = ast->cdr->cdr;
        }
      }
      printf(")");
      return;
    case AST_INT:
      printf("%d", ast->value);
      return;
    case AST_SYMBOL:
      printf("%s", ast->name);
      return;
    }
  }
}
