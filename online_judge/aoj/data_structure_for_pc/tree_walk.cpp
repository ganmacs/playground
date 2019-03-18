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

struct Node { int p, l, r; };

Node t[1000];

void preorder(int id) {
  printf(" %d", id);
  if (t[id].l != -1) preorder(t[id].l);
  if (t[id].r != -1) preorder(t[id].r);
}

void inorder(int id) {
  if (t[id].l != -1) inorder(t[id].l);
  printf(" %d", id);
  if (t[id].r != -1) inorder(t[id].r);
}

void postorder(int id) {
  if (t[id].l != -1) postorder(t[id].l);
  if (t[id].r != -1) postorder(t[id].r);
  printf(" %d", id);
}

int main(int argc, char *argv[])
{
  int N, id, l, r;
  cin >> N;

  for (int i = 0; i < N; i++) {
    t[i].p = -1;
  }

  for (int i = 0; i < N; i++) {
    cin >> id >> l >> r;
    t[id].l = l;
    t[id].r = r;
    if (l != -1) t[l].p = id;
    if (r != -1) t[r].p = id;
  }

  int root;
  for (int i = 0; i < N; i++) {
    if (t[i].p == -1) {
      root = i;
      break;
    }
  }
  puts("Preorder");
  preorder(root);
  cout << endl;

  puts("Inorder");
  inorder(root);
  cout << endl;

  puts("Postorder");
  postorder(root);
  cout << endl;

  return 0;
}
