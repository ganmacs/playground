#include <stdio.h>
#include <stdlib.h>

#define N 7

typedef struct Point {
  double a;
  double b;
  double v;
} Point;

Point *new_p(double a, double b, double v)
{
  Point* p = malloc(sizeof(Point));
  p->a = a;
  p->b = b;
  p->v = v;
  return p;
}

void destroy_p(Point * p)
{
  free(p);
}

int
comp_func (const void *c1, const void *c2)
{
  Point *i1 = *(Point **)c1;
  Point *i2 = *(Point **)c2;

  double v = i1->v - i2->v;
  if (v == 0.0) {
    return 0;
  } else if(v > 0) {
    return 1;
  } else {
    return - 1;
  }
}

double func_y(double a, double x, double b)
{
  return a * x + b;
}

int b_search(double t, Point* ary[], int size)
{
  int l = 0, r = size - 1, p;

  while (l <= r) {
    p = (l + r) / 2;
    if (t > ary[p]->v)      l = p + 1;
    else if (t < ary[p]->v) r = p - 1;
    else return p;
  }
  return - 1;
}

int main(int argc, char *argv[])
{
  double ab[N][2] = {
    { - 0.5, 9 },
    { 2, 4 },
    { 1, 7 },
    { 0, 1 },
    { 0, 10 },
    { 1, 6 },
    { 1, 6 },
  };
  double p[2] = { 0.5, 7 };     /* input  point */
  Point *p0 = new_p( - 1, -1, p[1]);
  Point *r[N + 1] = { p0 };
  for (int i = 1; i < N + 1; i++) {
    double v = func_y(ab[i - 1][0], p[0], ab[i - 1][1]);
    r[i] = new_p(ab[i - 1][0], ab[i - 1][1], v);
  }

  qsort(r, N + 1, sizeof(Point *), comp_func);
  int rr = b_search(p[1], r, N + 1);


  if (rr == - 1) {
    puts("Not Found");
    return 1;
  }

  if (rr + 1 <= N + 1) {
    printf("Upper side bound is (%f, %f)\n", r[rr + 1]->a, r[rr + 1]->b);
  }

  if (rr - 1 >= 0) {
    printf("Lower side bound is (%f, %f)\n", r[rr - 1]->a, r[rr -  1]->b);
  }

  for (int i = 0; i < N + 1; i++) {
    destroy_p(r[i]);
  }
  return 0;
}
