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
static const int MAX = 200001;

struct T {
  int idx, count, time;

  bool operator < (const T &o) const {
    if (count == o.count) return idx > o.idx;
    return o.count > count;
  }
};

int main(){
  T teams[100000];
  int N, R, L;
  cin >> N >> R >> L;
  priority_queue<T> p;

  for (int i = 0; i < N; i++) {
    teams[i].idx = i;
    teams[i].count = 0;
    teams[i].time = 0;
  }

  int d, t, x, last = 0;
  for (int i = 0; i < R; i++) {
    cin >> d >> t >> x;

    if (!p.empty()) {
      T tt = p.top(); p.pop();
      teams[tt.idx].time += (last-x);
      p.push(teams[tt.idx]);
    }

    teams[d].count += t;
    last = x;

    p.push(teams[d]);
  }

  T tt = teams[d];
  tt.time += (L - last);
  p.push(tt);

  for (int i = 0; i < N; i++) {
    printf("%d ", teams[i].count);
  }
  cout << endl;

  cout << p.top().idx << endl;
}
