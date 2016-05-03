#include <stdio.h>

int loop(int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d\n", i);
  }
  return i;
}
