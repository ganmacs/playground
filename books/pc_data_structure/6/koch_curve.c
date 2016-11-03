#include <stdio.h>
#include <math.h>

double TH = M_PI * 60 / 180;

void koch(double p0x, double p0y, double p1x, double p1y, int i)
{
  if (i == 0) return;
  double sx = (2.0 * p0x + p1x) / 3.0;
  double sy = (2.0 * p0y + p1y) / 3.0;
  double tx = (p0x + 2 * p1x) / 3.0;
  double ty = (p0y + 2 * p1y) / 3.0;
  double ux = (tx - sx) * cos(TH) - (ty - sy) * sin(TH) + sx;
  double uy = (tx - sx) * sin(TH) + (ty - sy) * cos(TH) + sy;

  koch(p0x, p0y, sx, sy, i - 1);
  printf("%.8f %.8f\n", sx, sy); /* s */
  koch(sx, sy, ux, uy, i - 1);
  printf("%.8f %.8f\n", ux, uy); /* u */
  koch(ux, uy, tx, ty, i - 1);
  printf("%.8f %.8f\n", tx, ty); /* t */
  koch(tx, ty, p1x, p1y, i - 1);
}

int main(int argc, char *argv[])
{
  int i;
  scanf("%d", &i);
  printf("%.8f %.8f\n", 0.0, 0.0);
  koch(0.0, 0.0, 100.0, 0.0, i);
  printf("%.8f %.8f\n", 100.0, 0.0);
  return 0;
}
