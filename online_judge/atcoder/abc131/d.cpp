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
#include <numeric>

using namespace std;

int main()
{
  int N, a, b;
  cin >> N;
  vector<pair<int, int>> V(N);
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    V[i] = make_pair(b, a);
  };
  sort(V.begin(), V.end());

  unsigned long long s = 0;
  for (int i = 0; i < N; i++) {
    s += V[i].second;
    if (s > V[i].first) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;
  return 0;
}
