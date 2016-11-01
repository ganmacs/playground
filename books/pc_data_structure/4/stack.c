#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int stack[MAX], top;

void push(int v)
{
  /* is_full */
  stack[top++] = v;
}

int pop()
{
  /* is_empty */
  return stack[--top];
}

int main(int argc, char *argv[])
{
  int op;

  top = 0;
  char s[100];
  while (scanf("%s", s) != EOF) {
    if (s[0] == '+') {
      push(pop() + pop());
    }
    else if (s[0] == '-') {
      op = pop();
      push(pop() -  op);
    }
    else if (s[0] == '*') {
      push(pop() * pop());
    }
    else {
      push(atoi(s));
    }
  }
  printf("%d\n", pop());
  return 0;
}
