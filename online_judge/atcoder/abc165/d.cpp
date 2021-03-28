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
  long long A, B, N;
  cin >> A >> B >> N;

  long long k = max((long long)min(B, N), 0LL);
  long long int ans = 0;
  for (long long int i = 0; (k - i) >= 0 && i < 100000; i++) {
    long long  r = floor((1.0*A*(k-i))/B) - A * floor((1.0*(k-i))/B);
    ans = max(r, ans);
  }

  cout << ans << endl;
  return 0;
}
