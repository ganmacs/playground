#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef struct edge {
  int from, to, w;
} edge;

typedef struct node {
  int id;
  int rank;
  node *next;
} node;

const int MAX = 100000;
node *nodes[MAX];
int n, en;
vector<edge> E;

int find_set(int x)
{
  node *xx = nodes[x];
  while (xx->next != NULL) xx = xx->next;
  return xx->id;
}

int same(int x, int y)
{
  return (find_set(x) == find_set(y));
}

void unite(int x, int y)
{
  if (same(x, y)) return;
  node *xx = nodes[x];
  while (xx->next != NULL) xx = xx->next;
  node *yy = nodes[y];
  while (yy->next != NULL) yy = yy->next;

  if (xx->rank == yy->rank) {
    xx->next = yy;
    yy->rank++;
  } else if (xx->rank > yy->rank){
    yy->next = xx;
  } else {
    xx->next = yy;
  }
}

void init_uf(int n)
{
  for (int i = 0; i < n; i++) {
    node *n = new node();
    n->id = i;
    n->rank = 0;
    n->next = NULL;
    nodes[i] = n;
  }
}

bool mcost(const edge &e1, const edge &e2) { return e1.w < e2.w; }

int msp()
{
  sort(E.begin(), E.end(), mcost);

  int www = 0;

  for (int i = 0; i < (int)E.size(); i++) {
    edge e = E[i];
    if (!same(e.to, e.from)) {
      www += e.w;
      unite(e.to, e.from);
    }
  }
  return www;
}

int main()
{
  int s, t, w;
  cin >> n >> en;
  for (int i = 0; i < en; i++) {
    cin >> s >> t >> w;
    edge *e = new edge();
    e->from = s;
    e->to = t;
    e->w = w;
    E.push_back(*e);
  }

  init_uf(n);
  cout << msp() << endl;
}
