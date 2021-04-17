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

const unsigned long long L = 1e19;

int main()
{
  long long N;
  cin >> N;

  long long int ans = 0;

  if (N % 2 == 0) {
    while (N) {
      ans += (N/(2*5));
      N /= 5;
    }
  }

  cout << ans << endl;
  return 0;
}
