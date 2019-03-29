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
  int N, minv = 1e8;
  int v[1000];
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }



  for (int i = 0; i < (1 << N); i++) {
    int ans = 0, a = 0, b = 0;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        a += v[j];
      } else {
        b += v[j];
      }
    }

    minv = min(max(a, b), minv);
  }

  cout << minv << endl;
}
