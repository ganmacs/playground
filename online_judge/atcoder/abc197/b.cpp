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

// bool used[101][101];
// int a[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main()
{
  int H, W, X, Y, ans = 0;
  cin >> H >> W >> Y >> X;
  queue<pair<int, int> > q;
  vector<string> V(H);

  for (auto& vi: V) {
    cin >> vi;
  };

  X--;
  Y--;

  int xx = X;
  int yy = Y + 1;
  while (yy < H && V[yy][xx] == '.') {
    ans++;
    yy++;
  }

  xx = X;
  yy = Y - 1;
  while (yy >= 0 && V[yy][xx] == '.') {
    ans++;
    yy--;
  }

  xx = X + 1;
  yy = Y;
  while (xx < W && V[yy][xx] == '.') {
    ans++;
    xx++;
  }

  xx = X - 1;
  yy = Y;
  while (xx >= 0 && V[yy][xx] == '.') {
    ans++;
    xx--;
  }



  // for (auto& vi: V) {
  //   cout << vi << endl;
  // };


  cout << (ans + 1) << endl;

  return 0;
}
