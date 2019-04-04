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
  int N, h[100000], ans[100000];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }

  ans[0] = 0;
  ans[1] = abs(h[1] - h[0]);
  for (int i = 2; i < N; i++) {
    ans[i] = min(ans[i-1] + abs(h[i-1]-h[i]), ans[i-2] + abs(h[i-2]-h[i]));
  }

  cout << ans[N-1] << endl;
}
