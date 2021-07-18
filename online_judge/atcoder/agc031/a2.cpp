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

const int L = 1e9 + 7;

int main()
{
  int N;
  string S;
  cin >> N >> S;
  map<char, int> M;

  for (auto& vi: S) {
    M[vi]++;
  }

  long long ans = 1;
  for (auto& vi: M) {
    ans = ans * (vi.second + 1) % L;
  }

  cout << ans-1 << endl;
}
