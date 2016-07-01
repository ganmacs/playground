#include<stdio.h>
#include<stdlib.h>

void
sample()
{
  int income = 0;
  double tax;

  if (income <= 2200) {
    tax = 0;
  } else if(income <= 2700 ){
    tax = 0.14 * (income - 2200);
  } else if(income <= 3200 ){
    tax = 70 + 0.15 * (income - 2700);
  } else if(income <= 3700 ){
    tax = 145 + 0.16 * (income - 3200);
  } else if(income <= 4200 ){
    tax = 225 + 0.17 * (income - 3700);
  }
  /* some expr */
  else {
    tax = 53090 +  0.7 * (income - 102200);
  }

  printf("%f\n", tax);
}

void
my()
{
  int income = 4300;
  int  lib[]   = { 2200, 2700, 3200, 3700, 4200, 100000 };
  double par[] = {    0, 0.14, 0.15, 0.16, 0.17,    100 };
  int base[]   = {    0,   0,    70,  145, 2250, 100000};

  for (int i = 0; i < 6; i++) {
    if (income < lib[i]) {
      printf("%f\n", (double)base[i] + par[i]* (income - lib[i - 1]));
    }
  }
}

int main(int argc, char *argv[])
{
  my();
  return 0;
}
