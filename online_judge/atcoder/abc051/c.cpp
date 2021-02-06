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

int d[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

bool MAP[2000][2000];
vector<pair<int, int> > v;

int main(int argc, char *argv[])
{
  int sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;

  sx += 1000;
  sy += 1000;
  tx += 1000;
  ty += 1000;

  int dx = tx-sx;
  int dy = ty-sy;

  for (int i = 0; i < dy; i++) printf("U");
  for (int i = 0; i < dx; i++) printf("R");
  for (int i = 0; i < dy; i++) printf("D");
  for (int i = 0; i < dx + 1; i++) printf("L");
  for (int i = 0; i < dy + 1; i++) printf("U");
  for (int i = 0; i < dx + 1; i++) printf("R");
  printf("DR");
  for (int i = 0; i < dy + 1; i++) printf("D");
  for (int i = 0; i < dx + 1; i++) printf("L");
  printf("U");

  puts("");
  return 0;
}
