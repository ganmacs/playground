#include <iostream>
using namespace std;

#define M 100000

int v[M];

int partition(int p, int r)
{
  int x = v[r], i = p - 1, j = 0;

  for (j = p; j < r; j++) {
    if (v[j] <= x) {
      i++;
      swap(v[i], v[j]);
    }
  }
  swap(v[i + 1], v[r]);

  return i + 1;
}

void pp(int r)
{
  for (int i = 0; i <= r; i++) {
    if (i != 0)
      cout << ' ';
    cout << v[i];
  }
  cout << endl;
}

int solve(int l, int r)
{
  int pi = r;
  swap(v[pi], v[l]);

  int x = v[l];
  int ll = l + 1;
  int rr = r;
  int f = 0;

  while (ll < rr) {
    while(ll < rr && v[ll] <= x) ll++;
    while(ll < rr && v[rr] > x) rr--;
    swap(v[ll], v[rr]);
  }
  pp(r);

  if (v[ll] > x) f = 1;
  swap(v[ll - f], v[l]);
  return ll - f;
}

int partition2(int l, int r)
{
  int pi = l - 1;
  int i = l;
  int t = v[r];

  for (; i < r; i++) {
    if (v[i] <= t) {
      pi++;
      swap(v[pi], v[i]);
    }
  }

  swap(v[pi + 1], v[r]);
  return pi + 1;
}

int main(int argc, char *argv[])
{
  int n, i = 0;

  cin >> n;
  for (i = 0; i < n; i++) cin >> v[i];

  int t = partition2(0, n-1);

  for (i = 0; i < n; i++) {
    if (i != 0)
      cout << ' ';

    if (t == i) {
      cout << '[' << v[i] << ']';
    } else {
      cout << v[i];
    }
  }

  cout << endl;

  return 0;
}
