#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

typedef struct node {
  int id;
  int rank;
  node *next;
} node;

const int MAX = 10000;
node *nodes[MAX];

using namespace std;
int n, q;

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

int main()
{
  int com, x, y;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    nodes[i] = new node;
    nodes[i]->id = i;
    nodes[i]->rank = 0;
    nodes[i]->next = NULL;
  }


  for (int i = 0; i < q; i++) {
    cin >> com >> x >> y;
    if (com == 0) {
      unite(x, y);
    } else {
      cout << same(x, y) << endl;
    }
  }

  return 0;
}
