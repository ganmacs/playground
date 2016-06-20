#include <stdio.h>
#include <stdlib.h>

#define N 100

/* char * */
/* int_to_bin2(unsigned int i) */
/* { */
/*   if (i == 0) return "0"; */
/*   char result[100] = {'\0'} ; */

/*   if (i % 2 == 0) { */
/*     snprintf(result, 100, "0%s", int_to_bin2(i >> 1)); */
/*   } else { */
/*     snprintf(result, 100, "1%s", int_to_bin2(i >> 1)); */
/*   } */

/*   return result; */
/* } */

char *
int_to_bin(unsigned int i)
{
  if (i == 0) return "";
  char *v = int_to_bin(i >> 1);

  int k = i % 2;
  printf("%d", k);
  return v;
}

char *
int_to_bin3(unsigned int n)
{
  if (n == 0) return 0;

  char *result = malloc(sizeof(char) * N);

  for (int i = 0; i < N; i++) {
    result[i] = 0;
  }

  for (int i = 0; i < N && n != 0; i++) {
    result[i] = n % 2;
    n = n >> 1;
  }

  return result;
}

void
print_bin(char* result)
{
  for (int i = N - 1; i >= 0; i--) {
    if (result[i] == 0) {
      printf("%d", 0);
    } else {
      printf("%d", 1);
    }
  }

  puts("");
}


int
main(int argc, char *argv[])
{
  char *r1 = int_to_bin3(1023);
  print_bin(r1);

  return 0;
}
