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

const long long int MAX = 43554432;

struct Node { int p, sib, deg, dep, hei, l, r; };

Node T[MAX];

int set_depth_and_get_height(int id, int depth) {
  T[id].dep = depth;

  int r = 0, l = 0;
  if (T[id].l != -1) {
    l = set_depth_and_get_height(T[id].l, depth + 1) + 1;
  }

  if (T[id].r != -1) {
    r = set_depth_and_get_height(T[id].r, depth + 1) + 1;
  }
  T[id].hei = max(l, r);

  return T[id].hei;
}

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    T[i].p = T[i].sib = T[i].l = T[i].r = -1;
    T[i].deg = T[i].dep = T[i].hei = 0;
  };

  for (int i = 0; i < N; i++) {
    int id, l, r;
    cin >> id >> l >> r;

    int deg = 0;
    if (l != -1) {
      T[l].p = id;
      T[id].l = l;
      deg++;
    }

    if (r != -1) {
      T[r].p = id;
      T[id].r = r;
      deg++;
    }
    T[id].deg = deg;

    if (r != -1 && l != -1) {
      T[r].sib = l;
      T[l].sib = r;
    }
  }

  int root;
  for (int i = 0; i < N; i++) {
    if (T[i].p == -1) {
      root = i;
      break;
    }
  }
  set_depth_and_get_height(root, 0);

  for (int i = 0; i < N; i++) {
    printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, ", i, T[i].p, T[i].sib, T[i].deg, T[i].dep, T[i].hei);
    if (T[i].p == -1) {
      puts("root");
    } else if (T[i].deg == 0) {
      puts("leaf");
    } else {
      puts("internal node");
    }
  }
  return 0;
}
