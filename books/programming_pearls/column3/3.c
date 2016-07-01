#include <stdio.h>
#include <stdlib.h>

#define C "X"

/*

  XXXX
  X   X
  XXXX
  X   X
  XXXX

  XXXX
  XX
  XX
  XX
  XXXX

*/
void
p_blank(int x) {
  for (int i = 0; i < x; i++) {
    printf(" ");
  }
}

void
p_char(int x) {
  for (int i = 0; i < x; i++) {
    printf("X");
  }
}

void
p_b(){
  p_char(4); puts("");
  p_char(1); p_blank(3); p_char(1); puts("");
  p_char(4); puts("");
  p_char(1); p_blank(3); p_char(1); puts("");
  p_char(4); puts("");

}

void
p_i()
{
  p_char(4); puts("");

  for (int i = 0; i < 3; i++) {
    p_blank(1); p_char(2); puts("");
  }

  p_char(4); puts("");
}


int main(int argc, char *argv[])
{

  char input = 'I';

  switch(input) {
  case 'B':
    p_b();
    return 0;
  case 'I':
    p_i();
    return 0;
    /* all charactor */
  default:
    puts("nothing");
  }
  return 0;
}
