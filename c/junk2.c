#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int v;
  struct Node* next;
} Node;

int main(int argc, char *argv[])
{
  int N = 10;
  Node *root =  malloc(sizeof(Node));
  Node *tmp =  root;

  for (int i = 0; i < N; i++) {
    tmp->next = malloc(sizeof(Node));
    tmp->v = i;
    tmp = tmp->next;
  }

  Node *tmp2 =  root;
  while (tmp2 != NULL) {
    printf("%d\n", root->v);
    root = root->next;
  }

  return 0;
}
