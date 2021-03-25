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

int main()
{
  int N, K, ans = 1;
  cin >> N >> K;

  int v = K;
  while (v < N) {
    v += (K-1);
    ans++;
  }

  cout << ans << endl;
  return 0;
}
