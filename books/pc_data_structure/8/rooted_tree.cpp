#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct CELL { int p, l, r; };

const int MAX = 100000;
CELL cl[MAX];
int depth[MAX];
int n;

void p(int i, int d)
{
  CELL t = cl[i];
  int l = 0, v = t.l;

  printf("node %d: parent = %d, depth = %d, ", i, t.p, d);

  if (t.p == -1) {
    cout << "root, ";
  } else if (v == -1) {
    cout << "leaf, ";
  } else {
    cout << "internal node, ";
  }

  cout << "[";
  while (v != -1) {
    if (l != 0) cout << ", ";
    cout << v;
    v = cl[v].r;
    l++;
  }
  cout << "]" << endl;
}

void de(int i, int d)
{
  depth[i] = d;
  if (cl[i].l != - 1) de(cl[i].l, d + 1);
  if (cl[i].r != - 1) de(cl[i].r, d);
}

int main(int argc, char *argv[])
{
  cin >> n;
  int i, j, k, l, m, prev;
  for (i = 0; i < n; i++) {
    cl[i].l = -1;
    cl[i].r = -1;
    cl[i].p = -1;
  }

  for (i = 0; i < n; i++) {
    cin >> k >> l;

    for (j = 0; j < l; j++) {
      cin >> m;
      if (j == 0) {           // first child
        cl[k].l = m;
      } else {
        cl[prev].r = m;
      }
      prev = m;
      cl[m].p = k;
    }
  }

  // get parent id
  int pi;
  for (i = 0; i < n; i++) if (cl[i].p == -1) pi = i;
  de(pi, 0);

  for (i = 0; i < n; i++) p(i, depth[i]);
  return 0;
}
