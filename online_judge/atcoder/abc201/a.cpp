#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int A1, A2, A3;

  cin >> A1 >> A2 >> A3;
  int A[3] = {A1, A2, A3};

  do {
    if (A[2] - A[1] == A[1] - A[0]) {
      cout << "Yes" << endl;
      return 0;
    }
  } while (next_permutation(A, A + 3));

  cout << "No" << endl;
  return 0;
}
