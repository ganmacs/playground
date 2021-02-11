#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int NN = 1000001;

int
main()
{
  int N;
  int A[NN];
  int B[NN];

  cin >> N;

  for (int i = 1; i < N + 1; i++) {
    cin >> A[i];

    B[A[i]] = i;
  }


  cout << B[1];

  for (int i = 2; i < N + 1; i++) {
    cout << " " << B[i];
  }

  cout << endl;

  return 0;
}
