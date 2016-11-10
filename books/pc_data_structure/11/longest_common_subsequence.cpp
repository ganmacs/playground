#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n;
string X, Y;

// int lcs(int xi, int yi, int xs, int ys)
// {
//   int T[1001][1001];

//   if (xi >= xs || yi >= ys) return 0;
//   if (T[xi][yi] != -1) return T[xi][yi];
//   int ret = 0;

//   for (int i = xi; i < xs; i++) {
//     for (int j = yi; j < ys; j++) {
//       if (X[i] == Y[j]) {
//         ret = max(ret, lcs(i + 1, j + 1, xs, ys) + 1);
//       }
//     }
//   }
//   return T[xi][yi] = ret;
// }

int lcs()
{
  int c[1001][1001];
  int xs = X.size();
  int ys = Y.size();
  int v = 0;
  X = ' ' + X;
  Y = ' ' + Y;

  for (int i = 0; i <= xs; i++) c[i][0] = 0;
  for (int i = 0; i <= ys; i++) c[0][i] = 0;

  for (int i = 1; i <= xs; i++) {
    for (int j = 1; j <= ys; j++) {
      if (X[i] == Y[j]) {
        c[i][j] = c[i-1][j-1] + 1;
      } else {
        c[i][j] = max(c[i-1][j], c[i][j-1]);
      }
      v = max(v, c[i][j]);
    }
  }

  return v;
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> X >> Y;
    cout << lcs() << endl;
  }
  return 0;
}
