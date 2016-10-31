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
  int n, j, t;


  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];

  for (int i = 1; i < n; i++) {
    print_int_ary(v, n);

    j = i-1;
    t = v[i];
    while (j >= 0 && v[j] > t) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = t;
  }

  print_int_ary(v, n);
}
