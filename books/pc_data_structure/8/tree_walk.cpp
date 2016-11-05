#include <iostream>
using namespace std;

struct Node { int p, l, r; };

const int N = 1000;
Node node[N];
int n;

void preorder(int i)
{
  cout << " " << i;
  if (node[i].l != -1) preorder(node[i].l);
  if (node[i].r != -1) preorder(node[i].r);
}

void inorder(int i)
{
  if (node[i].l != -1) inorder(node[i].l);
  cout << " " << i;
  if (node[i].r != -1) inorder(node[i].r);
}

void postorder(int i)
{
  if (node[i].l != -1) postorder(node[i].l);
  if (node[i].r != -1) postorder(node[i].r);
  cout << " " << i;
}

int main()
{
  int i, v, p = 0, l, r;
  cin >> n;

  for (i = 0; i < n; i++) {
    node[i].p = -1; node[i].l = -1; node[i].r = -1;
  }

  for (i = 0; i < n; i++) {
    cin >> v >> l >> r;
    node[v].l = l;
    node[v].r = r;
    if (l != -1) node[l].p = v;
    if (r != -1) node[r].p = v;
  }

  for (i = 0; i < n; i++) {
    if (node[i].p == -1) {
      p = i; break;
    }
  }

  cout << "Preorder" << endl;
  preorder(p);
  cout << endl;

  cout << "Inorder" << endl;
  inorder(p);
  cout << endl;

  cout << "Postorder" << endl;
  postorder(p);
  cout << endl;

  return 0;
}
