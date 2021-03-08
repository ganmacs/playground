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

int A[1000];

int main(int argc, char *argv[])
{
  int N, K, M, sum = 0;
  cin >> N >> K >> M;

  for (int i = 0; i < (N-1); i++) {
    cin >> A[i];
    sum += A[i];
  }

  for (int i = 0; i <= K; i++) {
    if ((sum + i)/N >= M) {
      cout << i << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}
