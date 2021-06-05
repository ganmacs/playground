#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;
  long long ans = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= K; j++) {
      ans += (i*100 + j);
    }
  }

  cout << ans << endl;

  return 0;
}
