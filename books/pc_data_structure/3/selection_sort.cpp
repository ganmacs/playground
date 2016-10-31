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
  int n, minj, count = 0;

  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];

  for (int i = 0; i < n; i++) {
    minj = i;
    for (int j = i; j < n; j++) {
      if (v[j] < v[minj])
        minj = j;
    }

    if (i != minj) {
      count++;
      swap(v[i], v[minj]);
    }
  }

  print_int_ary(v, n);
  cout << count << endl;
  return 0;
}
