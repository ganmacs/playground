#include <cstdio>
#include <iostream>
using namespace std;

int n;
int A[600000];

void max_heapify(int i)
{
  int left = i * 2;
  int right = (i * 2) + 1;
  int v = i;

  if (left <= n && A[left] > A[v]) v = left;
  if (right <= n && A[right] > A[v]) v = right;

  if (v != i) {
    swap(A[v], A[i]);
    max_heapify(v);
  }
}

int main()
{
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> A[i];

  for (int i = n/2; i >= 1; i--) max_heapify(i);

  for (int i = 1; i <= n; i++) {
    cout << " " << A[i];
  }
  cout << endl;


  return 0;
}
