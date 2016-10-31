#include <cstdio>
#include <iostream>
using namespace std;
static const int M = 1000;

void print_int_ary(int v[], int size)
{
  for (int i = 0; i < size-1; i++) {
    cout << v[i];
    cout << ' ';
  }
  cout << v[size-1];
  cout << endl;
}


int main(int argc, char *argv[])
{
  int v[M];
  int n, i, count = 0, flg = 1;

  cin >> n;
  for (i = 0; i < n; i++) cin >> v[i];

  while(flg) {
    flg = 0;

    for (i = n - 1; i > 0; i--) {
      if (v[i] < v[i-1]) {
        count++;
        flg = 1;
        swap(v[i], v[i-1]);
      }
    }
  }

  print_int_ary(v, n);

  cout << count << endl;
  return 0;
}
