/* シグネチャで並べて同じシグネチャの中で名前順に並べる */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
pow(int base, int n)
{
  int ret = 1;
  for (int i = 0; i < n; i++) {
    ret = ret * base;
  }
  return ret;
}

int
sigtable(char c)
{
  int ret = c - 'A';
  if (ret < 0) return 0;
  else if (ret < 3) return 2;
  else if (ret < 6) return 3;
  else if (ret < 9) return 4;
  else if (ret < 12) return 5;
  else if (ret < 15) return 6;
  else if (ret < 19) return 7;
  else if (ret < 22) return 8;
  else if (ret < 25) return 9;
  else return 0;
}

int
sig(char *str)
{
  int ret = 0;
  int size = (int)strlen(str);

  for (int i = 0; i < size; i++) {
    ret += pow(10, size - i - 1) * sigtable(str[i]);
  }

  return ret;
}

int main(int argc, char *argv[])
{
  printf("%d\n", sig("LESK M"));
  return 0;
}
