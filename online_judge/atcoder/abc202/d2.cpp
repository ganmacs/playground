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

int A, B;
long long N;

unsigned long long combination(int n, int r) {
  unsigned long long num = 1;
  for (int i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}

string dfs(int a, int b, long long N)
{
  if (a == 0) {
    string aa(b, 'b');
    return aa;
  } else if (b == 0) {
    string aa(a, 'a');
    return aa;
  }

  auto t = combination(a + b - 1, min(a-1, b));
  if (N > t) {
    return "b" + dfs(a, b-1, N-t);
  } else {
    return "a" + dfs(a-1, b, N);
  }
}


int main()
{
  cin >> A >> B >> N;
  cout << dfs(A, B, N) << endl;
  return 0;
}
