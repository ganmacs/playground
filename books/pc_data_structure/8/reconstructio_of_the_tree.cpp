#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<int> pre, in, post;
int n, kk = 0, pos;

void f(int l, int r)
{
  if (l >= r) return;
  int root = pre[pos++];
  int v = distance(in.begin(), find(in.begin(), in.end(), root));
  f(l, v);
  f(v + 1, r);
  post.push_back(root);
}

void solve()
{
  f(0, pre.size());
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << post[i];
  }
  cout << endl;
}

int main()
{
  int v;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> v;
    pre.push_back(v);
  }

  for (int i = 0; i < n; i++) {
    cin >> v;
    in.push_back(v);
  }

  solve();
  return 0;
}
