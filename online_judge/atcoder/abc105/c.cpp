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

long long N;

bool dfs(long long v, int k) {
  k *= -2;

  if (N == v) {
    return true;
  } else if (N < 0 && k < 2*N) {
    return false;
  } else if (N > 0 && k > N*2) {
    return false;
  }

  if (dfs(v + k, k)) {
    cout << 1;
    return true;
  }

  if (dfs(v, k)) {
    cout << 0;
    return true;
  }

  return false;
}

int main(int argc, char *argv[])
{

  cin >> N;

  if (N == 0) {
    cout << 0 << endl;
  } else {
    int v = max(N%2, (-N)%2);
    dfs(v, 1);
    if (v == 1) cout << 1;
    cout << endl;
  }

  return 0;
}
