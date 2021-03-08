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
  long long int N, t;
  int ans = 100;
  cin >> N;

  // to_string(1).length();

  for (long long unsigned int i = 1; i*i <= N; i++) {
    if (N%i == 0) {
      t = N/i;
      int k = max(to_string(i).length(), to_string(t).length());
      ans = min(k, ans);
    }
  }

  cout << ans << endl;
  return 0;
}
