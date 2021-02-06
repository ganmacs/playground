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

int NN = 1000002;

int main(int argc, char *argv[])
{
  int N, M;
  pair<unsigned int, int> v[NN];

  cin >> N >> M;

  int a, b;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    v[i] = make_pair(a, b);
  }
  sort(v, v + N);

  long long int r = 0, kk;

  for (int i = 0; i < N; i++) {
    kk = min(M, v[i].second);
    M -= kk;
    r += kk * v[i].first;


    if (M == 0) {
      break;
    }
  }
  cout << r << endl;

  return 0;
}
