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

unsigned long long combination(int n, int r) {
  unsigned long long num = 1;
  for (int i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}

string solve(int a, int b, long long k) {
  if (a == 0) {
    return string(b, 'b');
  } else if (b == 0) {
    return string(a, 'a');
  }

  auto v = combination(a + b - 1, b);
  if (k <= v) {
    return "a" + solve(a-1, b, k);
  } else {
    return "b" + solve(a, b-1, k-v);
  }
}

int main()
{
  int A, B;
  long long K;
  cin >> A >> B >> K;
  cout << solve(A, B, K) << endl;
  return 0;
}
