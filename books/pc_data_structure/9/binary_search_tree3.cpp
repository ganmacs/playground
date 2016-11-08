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

node *find(node *node, int k)
{
  if (node == NIL) return NIL;

  if (node->key == k) {
    return node;
  } else if(node->key > k) {
    return find(node->left, k);
  } else {
    return find(node->right, k);
  }
}

node *find_min(node *n) {
  while (n->left != NIL) {
    n = n->left;
  }
  return n;
}

void del_with_no_child(node *v)
{
  if (v->parent == NIL) {
    root = NIL;
  } else if (v->parent->left == v) {
    v->parent->left = NIL;
  } else {
    v->parent->right = NIL;
  }
}

void del_with_a_child(node *v)
{
  node *nn;
  if (v->left != NIL) {
    v->left->parent = v->parent;
    nn = v->left;
  } else {
    v->right->parent = v->parent;
    nn = v->right;
  }

  if (v->parent->left == v) {
    v->parent->left = nn;
  } else {
    v->parent->right = nn;
  }
}


void in(node *n)
{
  if (n == NIL) return;
  in(n->left);
  printf(" %d", n->key);
  in(n->right);
}

void del(node *z)
{
  node *y = z;
  if (y == NIL) return;

  if (y->left != NIL && y->right != NIL) {
    y = find_min(y->right);
    z->key = y->key;
  }

  if (y->left == NIL && y->right == NIL) {
    del_with_no_child(y);
  } else {
    del_with_a_child(y);
  }
  free(y);
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
    } else if (c == "delete") {
      cin >> j;
      del(find(root, j));
    } else if (c == "find") {
      cin >> j;
      if (find(root, j) != NIL)  cout << "yes" << endl;
      else cout << "no" << endl;
    }
  }

  return 0;
}
