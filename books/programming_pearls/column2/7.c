#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct Tape {
  int row;
  int col;
  int val;
} Tape;

Tape*
new_pack(int row, int col, int val)
{
  Tape* p = malloc(sizeof(Tape));

  p->row = row;
  p->col = col;
  p->val = val;
  return p;
}

int
comp_func_row (const void *c1, const void *c2)
{
  Tape* i1 = *(Tape **)c1;
  Tape* i2 = *(Tape **)c2;
  return i1->row - i2->row;
}

int
comp_func_col (const void *c1, const void *c2)
{
  Tape* i1 = *(Tape **)c1;
  Tape* i2 = *(Tape **)c2;
  return i1->col - i2->col;
}

int main(int argc, char *argv[])
{
  Tape *tape[N * N];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      tape[j + (10 * i)] = new_pack(i, j, j + (10 * i));
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("(%2d, %2d, %2d), ", tape[j + (10 * i)]->row, tape[j + (10 * i)]->col, tape[j + (10 * i)]->val);
    }
    puts("");
  }
  puts("------------");

  qsort(tape, N * N, sizeof(Tape *), comp_func_col);

  for (int i = 0; i < N; i++) {
    qsort(&tape[i*10] , N, sizeof(Tape *), comp_func_row);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("(%2d, %2d, %2d), ", tape[j + (10 * i)]->row, tape[j + (10 * i)]->col, tape[j + (10 * i)]->val);
    }
    puts("");
  }


  return 0;
}
