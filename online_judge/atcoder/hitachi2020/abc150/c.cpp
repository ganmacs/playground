#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int NN = 100005;

int main(int argc, char *argv[])
{

  int N, P[8], Q[8];

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> P[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> Q[i];
  }


  // // int A, B, M, a[NN], b[NN], x, y, c;
  // int ma = NN*2, mb = NN*2, mxy = NN*3;

  // cin >> A >> B >> M;


  // for (int i = 1; i < A + 1; i++) {
  //   cin >> a[i];
  //   ma = min(a[i], ma);
  // }

  // for (int i = 1; i < B + 1; i++) {
  //   cin >> b[i];
  //   mb = min(b[i], mb);
  // }

  // for (int i = 0; i < M; i++) {
  //   cin >> x >> y >> c;
  //   mxy = min(a[x] + b[y] - c, mxy);
  // }

  // cout << min(mxy, ma + mb) << endl;
}
