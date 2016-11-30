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
int c, r, M[10][10000], maxv;

int value(int m[][10000])
{
  int nv = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      nv += !m[i][j];
    }
  }
  return nv;
}

void mprint()
{
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
}

int main(){
  vector<int> vec[1025];
  vec[0].push_back(0);

  for (int i = 1; i < 1025; i++) {
    int v = i;
    while (v) {
      if (v % 2 == 1) {
        vec[i].push_back(1);
      } else {
        vec[i].push_back(0);
      }
      v /= 2;
    }
  }

  while (cin >> r >> c, c || r) {
    maxv = 0;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) cin >> M[i][j];
    }

    int lim = pow(2, r) - 1;
    for (int i = 0; i <= lim; i++) {
      // flip cro
      for (int j = (int)vec[i].size()-1; j >= 0; j--) {
        if (vec[i][j]) {
          for (int k = 0; k < c; k++) M[j][k] = !M[j][k]; // flip
        }
      }

      // flip row
      vector<int> vv;
      for (int j = 0; j < c; j++) {
        int v = 0;
        for (int k = 0; k < r; k++) v += M[k][j];
        if (v * 2 > r) {
          for (int k = 0; k < r; k++) M[k][j] = !M[k][j];
          vv.push_back(j);
        }
      }

      maxv = max(maxv, value(M));

      // defaults row
      for (int j = 0; j < (int)vv.size(); j++) {
        for (int k = 0; k < r; k++) M[k][vv[j]] = !M[k][vv[j]];
      }

      // defaults cro
      for (int j = (int)vec[i].size()-1; j >= 0; j--) {
        if (vec[i][j])
          for (int k = 0; k < c; k++) M[j][k] = !M[j][k]; // flip
      }
    }

    cout << maxv << endl;
  }
}
