/* 2つの日付が与えられるとその間の日すを計算する */
/* A. それぞれの日付が年で何番目かを計算し、同じ年数ならなら引く、違えば足してかつその間の日数も足す */

/* 日付 -> 曜日 */
/* 基準の日の曜日を覚える。そこからの日付の長さを求めて7で割ったあまりを曜日の数(日曜が０，月曜が１とかと比べる) */

/* 年と月からカレンダーを出力する */
/*  */

#include <stdio.h>
#include <stdlib.h>

#define is_leap(x) ((x % 400 == 0) || ((x % 4 == 0) &&( x % 100 != 0)))

static int M[2][13] = {
  {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 },
  {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }
};

int
nth_date(int d[])
{
  int v = M[is_leap(d[0])][d[1] - 1];
  return v + d[2];
}

int rest_date(int d[])
{
  printf("%d\n", nth_date(d));
  return M[is_leap(d[0])][12] - nth_date(d);
}

void
calc_diff(int l[], int r[])
{
  if (l[0] == r[0]) {
    printf("%d\n", nth_date(r) - nth_date(l));
    return;
  }

  int diff = rest_date(l) + nth_date(r);;
  for (int i = l[0] + 1; i < r[0]; i++) {
    diff += M[is_leap(i)][12];
  }
  printf("%d\n", diff);
}

int
to_day_of_week(int ymd[])
{
  int y = ymd[0];
  int m = ymd[1];
  int d = ymd[2];

  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  if (m < 3) y--;
  return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

static char D[7] = { 'S', 'M', 'T', 'W', 'T', 'F', 'S' };

void
to_calendar(int d[]) {
  int y = d[0];
  int m = d[1];

  static int C[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  };
  int k[] = {y, m, 1};
  int j = to_day_of_week(k);


  for (int i = 0; i < 7; i++) printf(" %c ", D[i]);
  puts("");
  for (int i = 0; i < j; i++) printf("   ");

  for (int i = 1; i <= C[is_leap(y)][m]; i++) {
    if (j == 0) puts("");
    printf("%2d ", i);
    j = (j + 1) % 7;
  }
}

int main(int argc, char *argv[])
{
  int one[3] =   {2003, 3, 2};
  int other[3] = {2003, 3, 5};

  calc_diff(one, other);

  int d[] = {2016, 7, 1};
  printf("%d\n", to_day_of_week(d));

  int d2[] = {2016, 2};
  to_calendar(d2);
}
