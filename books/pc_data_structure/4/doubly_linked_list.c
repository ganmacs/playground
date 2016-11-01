#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
  int n;
  struct list *next;
  struct list *prev;
} list;

list *top;

void insert(int n)
{
  list *l = malloc(sizeof(list));
  l->n = n;
  l->next = top->next;
  top->next->prev = l;
  top->next = l;
  l->prev = top;
}

void delete_node(list *l)
{
  if (l == top)
    return;

  l->next->prev = l->prev;
  l->prev->next = l->next;
  free(l);
}

void delete(int j)
{
  list *l = top->next;

  for (l = top->next; l != top; l = l->next) {
    if (l->n == j) {
      delete_node(l);
      break;
    }
  }
}

void delete_last() { delete_node(top->prev); }
void delete_first() { delete_node(top->next); }

void pp()
{
  if (top == NULL)
    return;

  int i = 0;
  list *l;

  for (l = top->next; l != top; l = l->next) {
    if (i != 0)
      printf(" ");

    printf("%d", l->n);
    i++;
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int n, i, j;
  char cmd[20];


  scanf("%d", &n);
  top = malloc(sizeof(list));
  top->n = -1;
  top->next = top;
  top->prev = top;

  for (i = 0; i < n; i++) {
    scanf("%s", cmd);
    if (cmd[0] == 'i') {        /* insert */
      scanf("%d", &j); insert(j);
    } else if(strcmp("deleteFirst", cmd) == 0) {
      delete_first();
    } else if(strcmp("deleteLast", cmd) == 0) {
      delete_last();
    } else {                    /* delete */
      scanf("%d", &j); delete(j);
    }
  }
  pp();

  return 0;
}
