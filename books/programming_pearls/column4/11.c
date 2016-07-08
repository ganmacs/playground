#include <stdio.h>
#include <stdlib.h>

/* const int t = 0; */
/* const int t = 1; */
/* const int t = 2; */
/* const int t = 3; */
/* const int t = 4; */
/* const int t = 5; */
/* const int t = 6; */
const int t = 7;

int binarysearch(int x[], int n)
{
  int p = n / 2;

  printf("%d--\n", x[p]);

  if (x[p] == t) {
    printf("Found\n");
    return 1;
  }

  if (p == 0) {
    printf("not found\n");
    return 0;
  }

  if (x[p] > t){
    return binarysearch(x, p - 1);
  } else {
    return binarysearch(x + p + 1, p);
  }
}

int main(int argc, char *argv[])
{
  int a[] = { 1, 2, 3, 4, 5, 6, 7 };
  printf("%d\n", binarysearch(a, 7));
  return 0;
}
