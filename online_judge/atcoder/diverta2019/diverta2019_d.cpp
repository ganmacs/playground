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
  long long N;
  long long ans = 0;
  cin >> N;

  for (long long i = 1; i <=  N/2; i++) {
    if (N % i == N/i) ans += i;
  }
  ans++;

  cout << ans << endl;
  return 0;
}
