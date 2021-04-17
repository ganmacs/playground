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
  int N, M, a;
  cin >> N >> M;
  priority_queue<int> q;

  for (int i = 0; i < N; i++) {
    cin >> a;
    q.push(a);
  }
  int v;
  while (M && !q.empty()) {
    v = q.top();
    q.pop();
    M--;
    v >>= 1;
    if (v != 0) {
      q.push(v);
    }
  }

  long long int ans = 0;
  while (!q.empty()) {
    ans += q.top();
    q.pop();
  }

  cout << ans << endl;
  return 0;
}
