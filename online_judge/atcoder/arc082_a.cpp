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

int S[100010];

int main(int argc, char *argv[])
{
  int N, ans = 0, minv = 2000000, maxv = -1;
  cin >> N;
  map<int, int> m;
  for (int i = 0; i < N; i++) {
    cin >> S[i];
    m[S[i]]++;
  }
  sort(S, S + N);

  if (N < 3) {
    if (abs(S[0]-S[1]) <= 1) {
      ans = 2;
    } else {
      ans = 1;
    }
  } else {
    for (int i = 0; i < N-2; i++) {
      ans = max(ans, m[i] + m[i + 1] + m[i + 2]);
    }
  }

  printf("%d\n", ans);
}
