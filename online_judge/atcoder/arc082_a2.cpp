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
  int N, ans = 0, a;
  cin >> N;

  for (int i = 0; i < 100010; i++) S[i] = 0;
  for (int i = 0; i < N; i++) {
    cin >> a;
    S[a]++;
  }

  for (int i = 0; i < 100010; i++) {
    ans = max(ans, S[i] + S[i + 1] + S[i + 2]);
  }

  printf("%d\n", ans);
}
