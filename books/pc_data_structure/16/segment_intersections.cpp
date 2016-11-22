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

struct point { int i, x, y, pos; };
struct line { point p1, p2; };

static const int MAX = 100000;
static const int LEFT = 1;
static const int RIGHT = 2;
static const int BOTTOM = 0;
static const int TOP = 3;

line p[MAX];
point ep[MAX*2];

bool ysort(const point &a, const point &b) {
  if (a.y == b.y) {
    return a.pos < b.pos;
  } else return a.y < b.y;

}

int main(){
  set<int> S;
  int x1, y1, x2, y2, pos1, pos2;
  int n, j = 0, ans = 0;

  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;

    if (y1 == y2) {             // horizonal
      if (x1 > x2) swap(x1, x2);
      pos1 = LEFT; pos2 = RIGHT;
    } else {                    // vertical
      if (y1 > y2) swap(y1, y2);
      pos1 = BOTTOM; pos2 = TOP;
    }

    p[i].p1.x = x1;
    p[i].p1.y = y1;
    p[i].p1.i = i;
    p[i].p1.pos = pos1;

    p[i].p2.x = x2;
    p[i].p2.y = y2;
    p[i].p2.i = i;
    p[i].p2.pos = pos2;

    ep[j++] = p[i].p1;
    ep[j++] = p[i].p2;
  }

  sort(ep, ep + j, ysort);
  for (int i = 0; i < j; i++) {
    if (ep[i].pos == BOTTOM) {
      S.insert(ep[i].x);
    } else if(ep[i].pos == TOP) {
      S.erase(ep[i].x);
    } else if (ep[i].pos == LEFT) {
      ans += distance(S.lower_bound(p[ep[i].i].p1.x), S.upper_bound(p[ep[i].i].p2.x));
    }
  }

  cout << ans << endl;
}
