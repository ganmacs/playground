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
static const int MAX = 2000;

struct team { int i, count, duration, miss_count[11]; };

team tt[MAX + 10];
int n;
int M, T, P, R;
int m, t, p, j;

bool msort(const team &t1, const team &t2)
{
  if (t1.count == t2.count) {
    if (t1.duration == t2.duration) {
      return t1.i > t2.i;       // index
    }
    return t1.duration < t2.duration;
  }

  return t1.count > t2.count;
}

int main(){
  cin >> M >> T >> P >> R;

  while (!(M == 0 && T == 0 && P == 0 && R == 0)) {
    for (int i = 1; i <= T; i++) {
      tt[i].i = i;
      tt[i].count = 0;
      tt[i].duration = 0;
      for (int j = 0; j < 11; j++) tt[i].miss_count[j] = 0;
    }

    for (int i = 0; i < R; i++) {
      cin >> m >> t >> p >> j;
      if (j == 0) {
        tt[t].count++;
        tt[t].duration += (m + tt[t].miss_count[p]);
      } else {
        tt[t].miss_count[p] += 20;
      }
    }

    sort(tt + 1, tt + (T + 1), msort);

    for (int i = 1; i <= T; i++) {
      cout << tt[i].i;
      if (i == T) continue;

      if (tt[i].count == tt[i + 1].count && tt[i].duration == tt[i + 1].duration) {
        cout << "=";
      } else {
        cout << ",";
      }
    }
    cout << endl;

    cin >> M >> T >> P >> R;
  }
}
