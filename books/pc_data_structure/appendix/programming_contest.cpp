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
  int idx, score, time;

  bool operator < (const T &o) const {
    if (score == o.score) return idx > o.idx;
    return score < o.score;
  }
};

int main(){
  T teams[100000 + 1];
  int N, R, L;
  cin >> N >> R >> L;
  priority_queue<T> p;

  for (int i = 1; i <= N; i++) {
    teams[i].idx = i;
    teams[i].score = 0;
    teams[i].time = 0;
    p.push(teams[i]);
  }


  int d, t, x, last = 0;
  for (int i = 0; i < R; i++) {
    cin >> d >> t >> x;

    while (!p.empty() && teams[p.top().idx].score != p.top().score)  p.pop();

    teams[d].score += x;
    teams[p.top().idx].time += (t - last);
    p.push(teams[d]);
    last = t;
  }

  while (!p.empty() && teams[p.top().idx].score != p.top().score)  p.pop();
  teams[p.top().idx].time +=  (L - last);

  int max = 0;
  int id = - 1;
  for (int i = 1; i <= N; i++) {
    if (max < teams[i].time) {
      max = teams[i].time;
      id = teams[i].idx;
    }
  }

  cout << id << endl;
}
