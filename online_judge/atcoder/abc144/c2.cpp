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
  unsigned long long N, ans = 1e19;
  cin >> N;

  for (unsigned long long i = 1; i*i <= N; i++) {
    if ((N % i) == 0) {
      ans = min((i + (N/i) - (unsigned long long)2), ans);
    }
  }

  cout << ans << endl;
  return 0;
}
