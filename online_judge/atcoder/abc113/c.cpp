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


int main()
{
  int N, M, P, Y;
  vector<pair<int, int>> V2, V1;
  map<int, map<int, int>> M2;
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    cin >> P >> Y;
    V2.push_back({P, Y});
    V1.push_back({P, Y});
  }
  sort(V2.begin(), V2.end());

  int v = -1, k = 1;
  for (auto& vi: V2) {
    if (v != vi.first) {
      k = 1;
      v = vi.first;
    } else {
      k++;
    }

    M2[vi.first][vi.second] = k;
  }

  for (auto& vi: V1) {
    printf("%06d%06d\n", vi.first, M2[vi.first][vi.second]);
  }
  return 0;
}
