#include<stdio.h>

struct hoge1 {
  float x;
  int y[10][20];
};

struct hoge2 {
  char a;
  double b;
  struct hoge1 c;
};

int* getelem(struct hoge2 *hoge)
{
  return &hoge[1].c.y[5][13];
}
