#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct point { int id, x, y; };
struct node {
  int l, r;
  point *p;
};

const int MAX = 500000;
int n, nd = 0;
node T[MAX];
point P[MAX];
vector<int> vec;

bool lessX(const point &p1, const point &p2) { return p1.x < p2.x; }
bool lessY(const point &p1, const point &p2) { return p1.y < p2.y; }

int make_kd_tree(int l, int r, int depth) {
  if (l >= r) return -1;
  int m = (l + r) / 2;
  int t = nd++;

  if (depth % 2 == 0) {
    sort(P + l, P + r, lessX);
  } else {
    sort(P + l, P + r, lessY);
  }

  T[t].p = &P[m];
  T[t].l = make_kd_tree(l, m, depth + 1);
  T[t].r = make_kd_tree(m + 1, r, depth + 1);

  return t;
}

void find(int root, int sx, int tx, int sy, int ty, int depth)
{
  node node = T[root];
  int xx = node.p->x;
  int yy = node.p->y;

  if (sx <= xx && xx <= tx && sy <= yy && yy <= ty) {
    vec.push_back(node.p->id);
  }

  if (depth % 2 == 0) {
    if (node.l != -1 && sx <= xx)
      find(node.l, sx, tx, sy, ty, depth + 1);

    if (node.r != -1 && tx >= xx)
      find(node.r, sx, tx, sy, ty, depth + 1);
  } else {
    if (node.l != -1 && sy <= yy)
      find(node.l, sx, tx, sy, ty, depth + 1);

    if (node.r != -1 && ty >= yy)
      find(node.r, sx, tx, sy, ty, depth + 1);
  }
}

int main()
{
  int sx, tx, sy, ty, root, aa, bb, q;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &aa, &bb);
    P[i].x = aa; P[i].y = bb; P[i].id = i;
    T[i].l = -1; T[i].r = -1, T[i].p = NULL;
  }

  root = make_kd_tree(0, n, 0);

  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    vec.clear();
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    find(root, sx, tx, sy, ty, 0);
    sort(vec.begin(), vec.end());
    for (int i = 0; i < (int)vec.size(); i++) {
      printf("%d\n", vec[i]);
    }
    printf("\n");
  }
  return 0;
}
