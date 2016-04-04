#include<stdio.h>

extern int sharing_function(void);

int main(){
  printf("sharing_function() returns %d\n", sharing_function());
  return 0;
}
