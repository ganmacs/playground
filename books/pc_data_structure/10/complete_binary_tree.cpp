#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
  int A[500];
  int n, i;
  cin >> n;

  for (i = 1; i < n + 1; i++) cin >> A[i];

  for (i = 1; i < n + 1; i++) {
    cout << "node " << i << ": ";
    cout << "key = " << A[i] << ", ";
    if (i >= 2) cout << "parent key = " << A[i/2] << ", ";

    if ((2 * i) < n + 1) cout << "left key = " << A[i*2] << ", ";
    if (((2 * i) + 1) < n + 1) cout << "right key = " << A[((2 * i) + 1)] << ", ";
    cout << endl;
  }

  return 0;
}
