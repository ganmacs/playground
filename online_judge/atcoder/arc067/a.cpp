#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

long long primes[10000];
const int L = 1000000007;

void ff(int n) {
  int i = 2;

  while (n >= 2) {
    while (n % i == 0) {
      primes[i]++;
      n /= i;
    }
    i++;
  }
}

int main()
{
  int N;
  long long ans = 1;
  cin >> N;

  for (int i = 1; i <= N; i++) ff(i);
  for (auto& vi: primes) {
    ans = ans*(vi + 1) % L;
  }

  cout << ans << endl;
  return 0;
}
