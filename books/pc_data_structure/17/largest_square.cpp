#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int MAX = 1410;

int h, w;
int P[MAX + 1][MAX + 1];

int ls()
{
  int ans = 0;
  for (int i = 0; i < w; i++) ans |= P[0][i];
  for (int i = 0; i < h; i++) ans |= P[i][0];

  for (int i = 1; i < h; i++) {
    for (int j = 1; j < w; j++) {
      if (P[i][j] == 0) continue;
      P[i][j] = min(P[i-1][j], min(P[i][j-1], P[i-1][j-1])) + 1;
      ans = max(ans, P[i][j]);
    }
  }

  return ans * ans;
}

int main(){
  int v;
  cin >> h >> w;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> v;
      P[i][j] = (v == 1) ? 0 : 1;
    }
  }

  cout << ls() << endl;
  return 0;
}
