#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct node {
  int key;
  node *left;
  node *right;
  node *parent;
};

node *root, *NIL;

void insert(int j)
{
  node *y = NIL, *x = root;
  node *z = (node *)malloc(sizeof(node));
  z->key = j;
  z->left = NIL;
  z->right = NIL;

  while (x != NIL) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;

  if (y == NIL) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
}

void in(node *n)
{
  if (n == NIL) return;
  in(n->left);
  printf(" %d", n->key);
  in(n->right);
}

void pre(node *n)
{
  if (n == NIL) return;
  printf(" %d", n->key);
  pre(n->left);
  pre(n->right);
}

void print()
{
  in(root);
  puts("");
  pre(root);
  puts("");
}

int main()
{
  int n, j;
  string c;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> c;

    if (c == "insert") {
      cin >> j;
      insert(j);
    } else if (c == "print") {
      print();
    }
  }

  return 0;
}
