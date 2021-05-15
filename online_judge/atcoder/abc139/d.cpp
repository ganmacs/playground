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
  int N;
  cin >> N;

  unsigned long long ans = 0;

  for (int i = 1; i < N; i++) {
    ans += i;
  }

  cout << ans << endl;
  return 0;
}
