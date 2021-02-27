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

int P[212345];

int main(int argc, char *argv[])
{

  long long int N;
  int m = 212345, k, ans = 0;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> k;

    if (k < m) {
      ans++;
      m = k;
    }
  }

  cout << ans << endl;
  return 0;
}
