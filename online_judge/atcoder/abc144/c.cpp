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
  unsigned long long int N;
  cin >> N;
  unsigned long long int ans = N-1;

  for (long long i = 2; i*i <= N; i++) {
    if (N % i == 0) {
      ans = min(ans, (i-1) + (N/i)-1);
    }
  }

  cout << ans << endl;
  return 0;
}
