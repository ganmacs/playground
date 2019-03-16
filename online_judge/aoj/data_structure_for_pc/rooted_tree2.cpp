#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

const int MAX = 100000;

struct Node { int p, l, r, d; };

Node T[MAX];

void set_depth(int id, int depth) {
  T[id].d = depth;
  if (T[id].r != -1) set_depth(T[id].r, depth);
  if (T[id].l != -1) set_depth(T[id].l, depth + 1);
}

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    T[i].p = -1;
    T[i].l = -1;
    T[i].r = -1;
  };

  for (int i = 0; i < N; i++) {
    int id, k, ck, prev;
    cin >> id >> k;

    for (int j = 0; j < k; j++) {
      cin >> ck;

      if (j == 0) {
        T[id].l = ck;
      } else {
        T[prev].r = ck;
      }
      prev = ck;
      T[ck].p = id;
    }
  }

  int root = -1;
  for (int i = 0; i < N; i++) {
    if (T[i].p == -1) {
      root = i;
      break;
    }
  }

  set_depth(root, 0);

  for (int i = 0; i < N; i++) {
    printf("node %d: parent = %d, depth = %d, ", i, T[i].p, T[i].d);
    if (T[i].p == -1) {
      printf("root, ");
    } else if (T[i].l == -1) {
      printf("leaf, ");
    } else {
      printf("internal node, ");
    }

    cout << "[";
    bool first = true;
    for (int j = T[i].l; j != -1 ; j = T[j].r) {
      if (!first) cout << ", ";
      cout << j;
      first = false;
    }
    cout << "]";

    cout << endl;
  }
  return 0;
}
