#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *c_table[15] = {
  "cite",
  "citsila",
  "cits",
  "citp",
  "cityl",
  "cito",
  "citna",
  "citn",
  "citc",
  "cita",
  "cinh",
  "cin",
  "cim",
  "cill",
  "cilb",
};

static char *c_ans[15] = {
  "et-ic",
  "al-is-tic",
  "s-tic",
  "p-tic",
  "-lyt-ic",
  "ot-ic",
  "an-tic",
  "n-tic",
  "c-tic",
  "at-ic",
  "h-nic",
  "n-ic",
  "m-ic",
  "l-lic",
  "b-lic",
};

void
reverse(char s[])
{
  int size = strlen(s) - 1;
  for (int i = 0; i <= size/2; i++) {
    char tmp = s[i];
    s[i] = s[size - i];
    s[size - i] = tmp;
  }
}

void
hifunation(char s[])
{
  int size = strlen(s);
  reverse(s);

  for (int i = 0; i < 15; i++) {
    int s_size = strlen(c_table[i]);
    int j = 0;
    while (j < s_size && c_table[i][j] == s[j]) j++;

    if (j == s_size) {
      reverse(s);

      int kk = size - strlen(c_table[i]);

      for (int l = kk; l < 10; l++) {
        s[l] = c_ans[i][l - kk];
      }
      break;
    }
  }
  printf("%s\n", s);
}


int main(int argc, char *argv[])
{
  char *c = "clinic";
  char *c1 = malloc(sizeof(char) * 10);
  strcpy(c1, c);

  hifunation(c1);
  return 0;
}
