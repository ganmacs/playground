#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
static const int MAX = 100000;
int N;
int V[MAX];
int dist[MAX];

int main(){
  cin >> N;
  int n, k, ans;

  for (int i = 0; i < N; i++) {
    cin >> n >> k;

    for (int j = 0; j < n; j++) cin >> V[j];

    if (n <= k) {
      cout << 0 << endl;
      continue;
    }

    for (int j = 0; j < n-1; j++) {
      dist[j] = V[j + 1] - V[j];
    }

    sort(dist, dist + n - 1, greater<int>());

    ans = V[n-1] - V[0];
    for (int j = 0; j < k-1; j++) {
      ans -= dist[j];
    }

    printf("%d\n", ans);
  }
}
