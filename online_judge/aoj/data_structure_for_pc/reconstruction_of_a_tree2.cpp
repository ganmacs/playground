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

struct Node { int p, l, r; };
Node t[1000];

int N;

void postorder(int id) {
  if (t[id].l != -1) postorder(t[id].l);
  if (t[id].r != -1) postorder(t[id].r);
  printf(" %d", id);
}

vector<int> n, pre, in, post;
int p;

void rec(int l, int r) {
  if (l >= r) return;
  int tt = pre[p++];
  int m = distance(in.begin(), find(in.begin(), in.end(), tt));
  rec(l, m);
  rec(m + 1, r);
  post.push_back(tt);
}

int main(int argc, char *argv[])
{
  int N, v,root;

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> v;
    pre.push_back(v);
  }

  for (int i = 0; i < N; i++) {
    cin >> v;
    in.push_back(v);
  }

  p = 0;
  rec(0, pre.size());

  for (int i = 0; i < post.size(); i++) {
    if (i == 0) {
      printf("%d", post[i]);
    } else {
      printf(" %d", post[i]);
    }
  }
  puts("");

  return 0;
}
