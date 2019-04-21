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

const int INF = 10000000;

int a[100001], b[100];

int main(int argc, char *argv[])
{
  int N;
  cin >> N;


  for (int i = 0; i < N; i++) {
    cin >> b[i];
  }

  for (int i = 0; i < (1 << N); i++) {
    int v = 0;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        v += b[j];
      }
    }

    a[v]++;
  }

  int ans = 0;
  for (int i = 0; i < 100001; i++) {
    if (a[i] != 0) {
      ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
