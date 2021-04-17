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
#include <numeric>

using namespace std;

int main()
{
  int N, a;
  cin >> N;

  long long ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> a;
    ans += (a-1);
  }

  cout << ans << endl;
  return 0;
}
