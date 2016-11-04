#include <stdio.h>

#define M 10000
#define N 2000001

int main(int argc, char *argv[])
{
  int n, i, K[M + 1];
  unsigned short A[N], B[N];

  scanf("%d", &n);
  for (i = 0; i <= M; i++) K[i] = 0;


  for (i = 0; i < n; i++) {
    scanf("%hu", &A[i + 1]);
    K[A[i + 1]]++;
  }

  for (i = 1; i <= M; i++) K[i] += K[i - 1];

  for (i = 1; i <= n; i++) {
    B[K[A[i]]] = A[i];
    K[A[i]]--;
  }

  for (i = 1; i <= n; i++) {
    if (i != 1) printf(" ");
    printf("%hu",  B[i]);
  }
  puts("");

  return 0;
}
