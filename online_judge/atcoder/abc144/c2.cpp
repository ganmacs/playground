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
  unsigned long long int N, ans = 1e19;
  cin >> N;

  for (unsigned long long int i = 1; i*i <= N; i++) {
    if (N % i == 0) {
      ans = min(ans, i + N/i - 2);
    }
  }

  cout << ans << endl;
  return 0;
}
