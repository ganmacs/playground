#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;
static const int MAX = 100000;
int bit[MAX + 1], n;

void init()
{
  for (int i = 0; i < (n + 1); i++)
    bit[i] = 0;
}

void add(int i, int x)
{
  while (i <= n) {
    bit[i] += x;
    i += (i & -i);
  }
}

int sum(int i)
{
  int v = 0;
  while (i > 0) {
    v += bit[i];
    i -= (i & -i);
  }
  return v;
}

int main()
{
  n = 8;
  init();
  add(1, 5);
  add(2, 3);
  add(3, 7);
  add(4, 9);
  add(5, 6);
  add(6, 4);
  add(7, 1);
  add(8, 2);
  cout << sum(1) << endl;
  cout << sum(2) << endl;
  cout << sum(3) << endl;
  cout << sum(4) << endl;
  cout << sum(5) << endl;
  cout << sum(6) << endl;
  cout << sum(7) << endl;
  cout << sum(8) << endl;
}
