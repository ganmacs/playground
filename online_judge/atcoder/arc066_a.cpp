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
const long long MOD = 1e9 + 7;

int main(int argc, char *argv[])
{
  int N, A[123456];
  map<long long , long long> B;
  long long ans = 1;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[A[i]]++;
  }

  if (N % 2 == 1 && B[0] != 1) {
    cout << 0 << endl;
    return 0;
  }

  for (auto v : B) {
    if (N%2 == 1 && v.first == 0) continue;
    if (v.second != 2) {
      cout << 0 << endl;
      return 0;
    }

    ans *= 2;
    ans %= MOD;
  }

  cout << ans << endl;

  return 0;
}
