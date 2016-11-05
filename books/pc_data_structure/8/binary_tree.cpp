#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node { int p, l, r; };

const int N = 30;
Node node[N];
int n, dep[N], he[N];

void pp(int i)
{
  Node n = node[i];
  int sib = -1;
  int deg = (n.l != -1) + (n.r != -1);

  if (n.p != -1) {
    if (node[n.p].l == i) {
      sib = node[n.p].r;
    } else {
      sib = node[n.p].l;
    }
  }

  cout << "node "       << i         << ": ";
  cout << "parent = "   << node[i].p << ", ";
  cout << "sibling = "  << sib       << ", ";
  cout << "degree = "   << deg       << ", ";
  cout << "depth = "    << dep[i]    << ", ";
  cout << "height = "   << he[i]     << ", ";

  if (n.p == -1) {
    cout << "root";
  } else if (n.l == -1 &&  n.r == -1) {
    cout << "leaf";
  } else {
    cout << "internal node";
  }

  cout << endl;
}

int dd(int i, int d)
{
  int l = 0, r = 0;
  dep[i] = d;

  if (node[i].l != -1)
    l = dd(node[i].l, d + 1) + 1;

  if (node[i].r != -1)
    r = dd(node[i].r, d + 1) + 1;

  he[i] = max(l, r);
  return he[i];
}

int main(int argc, char *argv[])
{
  int i, k, p = 0;
  cin >> n;

  for (i = 0; i < n; i++) {
    node[i].p = -1; node[i].l = -1; node[i].r = -1;
  }

  for (i = 0; i < n; i++) {
    cin >> k >> node[k].l >> node[k].r;
    if (node[k].l != -1) node[node[k].l].p = k;
    if (node[k].r != -1) node[node[k].r].p = k;
  }

  for (i = 0; i < n; i++) {
    if (node[i].p == -1) {
      p = i; break;
    }
  }

  dd(i, 0);

  for (i = 0; i < n; i++) {
    pp(i);
  }
  return 0;
}
