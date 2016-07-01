#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
t(char tempalte[], char *vars[])
{
  int i = 0;
  char c;
  int var_mode = 0;
  int v = 0;

  while ((c = tempalte[i]) != '\0') {
    i++;

    if (var_mode) {
      if ((c - '0') >= 0 && (c - '0') < 10) {
        v = (v * 10) + (c - '0');
        continue;
      } else {
        printf("%s", vars[v]);
      }
    }

    if (c == '$') {
      var_mode = 1;
      continue;
    }

    v = 0;
    var_mode = 0;
    printf("%c", c);
  }
}


int main(int argc, char *argv[])
{
  char *src = "Hello this is $0, \nToday is $1 \n$2 $3 $4 $5 $6 $7 $8 $9 $10\nThanks \n$0 :)\n";
  char *template = malloc(sizeof(char) * 100);
  strcpy(template, src);
  char *v[10] = { "ganmacs", "2016/3", "saikou", "saikou1", "saikou2", "saikou3", "saikou4", "saikou5", "saikou6", "saikou7" };

  t(template, v);
  return 0;
}
