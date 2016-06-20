#include <stdio.h>
#include <stdlib.h>

#define N 100
#define INT_LEN(n) (int)(sizeof(n) / sizeof(int))

char*
create_bitmap(unsigned int ns[], int n)
{
  char* s = malloc(sizeof(char) * N);

  for (int i = 0; i < N; i++) {
    s[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    s[ns[i]] = 1;
  }

  return s;
}

void
print_sorted(char *in)
{
  printf("{ \n");
  for (int i = 0; i < N; i++) {
    if (in[i] == 1) printf("  %d, \n", i);
  }
  printf("}\n");
}

int
main(int argc, char *argv[])
{
  unsigned int seed[] = {10, 77, 82, 30, 2, 40, 100, 1, 60, 4, 40, 99, 13, 83, 31, 69, 63, 8, 71, 97, 55, 86, 29};
  char *r2 = create_bitmap(seed, INT_LEN(seed));
  print_sorted(r2);
  return 0;
}
