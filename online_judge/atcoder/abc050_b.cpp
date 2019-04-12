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

int main(int argc, char *argv[])
{
  int N, T[200], M, P[200], X[200];
  long long sum;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> T[i];
    sum += T[i];
  }

  cin >> M;

  for (int i = 0; i < M; i++) {
    cin >> P[i] >> X[i];
    P[i]--;
  }

  for (int i = 0; i < M; i++) {
    cout << (sum + X[i] - T[P[i]]) << endl;
  }

  return 0;
}
