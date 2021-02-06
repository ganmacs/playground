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

const int INF = 10000000;

// struct second_order {
//   bool operator()(const value_type& x, const value_type& y) const {
//     return x.second > y.second;
//   }
// };

int main(int argc, char *argv[])
{
  int N, a[20000], b[20000], c[123456], ans[123345];
  map<int, queue<int> > bb, cc;
  map<int, int> m;

  cin >> N;
  for (int i = 0; i < N-1; i++) {
    cin >> a[i] >> b[i];
    a[i] -= 1;
    b[i] -= 1;

    bb[a[i]].push(b[i]);
    cc[b[i]].push(a[i]);

    m[a[i]]++;
    m[b[i]]++;
  }

  std::vector<pair<int, int> > d;

  for (auto it = m.begin(); it != m.end(); ++it) {
    d.push_back(make_pair(it->first, it->second));
  }

  sort(d.begin(), d.end(), [](const pair<int, int> &x, const pair<int, int> &y) { return x.second > y.second; });

  for (int i = 0; i < N; i++) {
    cin >> c[i];
  }

  sort(c, c + N, greater<int>());

  for (int i = 0; i <  N; i++) {
    printf("%d %d\n", d[i].first, d[i].second);
    ans[i] = -1;
  }

  int aaans = 0;
  int ii = 0;

  for (int i = 0; i < N; i++) {
    int pi = d[i].first;
    if (ans[pi] != -1) continue;

    ans[pi] = c[ii];
    ii++;

    while (!bb[pi].empty()) {
      auto v = bb[pi].front();
      bb[pi].pop();

      if (ans[v] == -1) {
        ans[v] = c[ii];
        aaans += min(ans[v], ans[pi]);
        printf("%d\n", min(ans[v], ans[pi]));
        ii++;
      }
    }

    while (!cc[pi].empty()) {
      auto v = cc[pi].front();
      cc[pi].pop();

      if (ans[v] == -1) {
        ans[v] = c[ii];
        ii++;
        aaans += min(ans[v], ans[pi]);
        printf("%d\n", min(ans[v], ans[pi]));

      }
    }
  }

  for (int i = 0; i < N; i++) {
    printf("%d ", ans[i]);
  }
  puts("");
  printf("%d\n", aaans);

  // printf("%d %d\n", d[i].first, d[i].second);


  return 0;
}
