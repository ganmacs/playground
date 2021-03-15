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
  long long int a, ans = 0;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;

    while (a % 2 == 0) {
      a /= 2;
      ans++;
    }
  }

  cout << ans << endl;

  return 0;
}
