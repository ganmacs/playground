#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

int M[51][51];

int main()
{
  int h, w;
  string in[51];
  scanf("%d %d", &h, &w);
  for (int i = 0; i < h; i++) cin >> in[i];

  for (int i = 1; i < h + 1; i++) {
    for (int j = 1; j < w + 1; j++) {
      M[i][j] = in[i-1][j-1] - '0';
      if (i > 1 && j > 1) {
        M[i][j] += min(M[i-1][j], M[i][j-1]);
      } else if (i > 1) {
        M[i][j] += M[i-1][j];
      } else {
        M[i][j] += M[i][j-1];
      }
    }
  }
  cout << M[h][w] << endl;
}
