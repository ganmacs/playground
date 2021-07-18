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

vector<long long> D, A;

void dfs(long long i) {
  if (200000 < i || i == 0) return;
  A.push_back(i);

  for (auto& vi: D) {
    dfs(i*10 + vi);
  }
}

int main()
{
  int N, K, a;
  cin >> N >> K;
  map<int, int> V;

  for (int i = 0; i < 10; i++) V[i]++;
  for (int i = 0; i < K; i++) {
    cin >> a;
    V[a]--;
  }

  for (auto& vi: V) {
    if (vi.second >= 1) D.push_back(vi.first);
  }

  for (auto& vi: D) dfs(vi);
  sort(A.begin(), A.end());

  for (auto& vi: A) {
    if (vi >= N) {
      cout << vi << endl;
      return 0;
    }
  }

  return 0;
}
