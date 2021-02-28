#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;


int A[200001];
int B[200001];

int main(int argc, char *argv[])
{

  int N;

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[i] = A[i];
  }

  sort(A, N + A, greater<int>());

  for (int i = 0; i < N; i++) {
    if (B[i] == A[0]) {
      cout << A[1] << endl;
    } else {
      cout << A[0] << endl;
    }
  }

  return 0;
}
