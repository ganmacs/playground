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

long int H[102];

int main()
{
  int N, ans = 0;
  cin >> N;

  cin >> H[0];
  ans += H[0];
  for (int i = 1; i < N-1; i++) {
    cin >> H[i];

    auto v = min(H[i], H[i-1]);
    ans += v;
  }

  ans += H[N-2];

  cout << ans << endl;

  return 0;
}
