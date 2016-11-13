#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct point { int x, y, id; };
struct node {
  struct point *p;
  struct node *l;
  struct node *r;
};

const int MAX = 500000;
node N[MAX];
point P[MAX];
vector<int> vec;
int n, nd = 1;

bool lessX(const point &p1, const point &p2) { return p1.x < p2.x; }
bool lessY(const point &p1, const point &p2) { return p1.y < p2.y; }

node *kd(int l, int r, int d)
{
  if (l >= r) return NULL;
  int m = (l + r) / 2;
  int t = nd++;

  if (d % 2 == 0) {
    sort(P + l, P + r, lessX);
  } else {
    sort(P + l, P + r, lessY);
  }

  N[t].p = &P[m];
  N[t].l = kd(l, m, d + 1);
  N[t].r = kd(m + 1, r, d + 1);

  return &N[t];
}

void find(node *root, int sx, int tx, int sy, int ty, int d)
{
  int x = root->p->x;
  int y = root->p->y;

  if (sx <= x && x <= tx && sy <= y && y <= ty)
    vec.push_back(root->p->id);

  if (d % 2 == 0) {
    if (root->l != NULL && sx <= x)
      find(root->l, sx, tx, sy, ty, d + 1);

    if (root->r != NULL && tx >= x)
      find(root->r, sx, tx, sy, ty, d + 1);
  } else {
    if (root->l != NULL && sy <= y)
      find(root->l, sx, tx, sy, ty, d + 1);

    if (root->r != NULL && ty >= y)
      find(root->r, sx, tx, sy, ty, d + 1);
  }
}

int main()
{
  int sx, tx, sy, ty, aa, bb, q;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d %d", &aa, &bb);
    P[i].x = aa; P[i].y = bb; P[i].id = i;
    N[i].l = NULL, N[i].r = NULL; N[i].p = NULL;
  }

  node *root = kd(0, n, 0);

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
