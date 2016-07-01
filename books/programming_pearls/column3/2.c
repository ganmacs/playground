/* 0から溶けてるのでm渡されてもとける */

#include<stdio.h>
#include<stdlib.h>

#define K  6

int main(int argc, char *argv[])
{
  int m = 6;
  int c[] = {1, 2, 3, 4, 5, 6};
  int a[] = {0, 0, 0, 0, 0, 0};


  for (int n = 0; n < 6; n++) {
    a[n] = c[K - 1];

    int k = 0;
    for (int j = n - 1; j >= 0; j--) {
      a[n] += a[j] * c[k];
      k++;
    }
  }

  for (int i = 0; i < K; i++) {
    printf("%d\n", a[i]);
  }

  return 0;
}
