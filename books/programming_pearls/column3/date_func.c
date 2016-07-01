#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a < b ? b : a)

void date_func(int y, int d)
{
  int leap[2][13] = {
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }, /* leap */
  };
  int i = 0;
  while (i < 13 && (leap[((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))][i] < d)) i++;
  printf("%d月%d日\n", i, d - leap[((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))][i - 1]);
}

int main(int argc, char *argv[])
{
  int year = 2004;
  int nth = 366;

  date_func(year, nth);
  return 0;
}
