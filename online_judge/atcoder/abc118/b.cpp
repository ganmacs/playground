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

int A[100];

int main(int argc, char *argv[])
{
  int N, M, k, l;

  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    A[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> l;
      A[l-1]++;
    }
  }

  auto ans = 0;
  for (int i = 0; i < M; i++) {
    if (A[i] == N) {
      ans++;
    }
  }
  cout << ans << endl;

  return 0;
}
