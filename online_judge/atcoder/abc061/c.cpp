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

int main()
{
  int N, a, b;
  long long K;
  vector<pair<int, int>> V;
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    V.push_back(make_pair(a, b));
  }

  sort(V.begin(), V.end());

  for (auto& vi: V) {
    if (K <= vi.second) {
      cout << vi.first << endl;
      return 0;
    } else {
      K -= vi.second;
    }
  }

  return 0;
}
