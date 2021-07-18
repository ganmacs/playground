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

int main()
{
  int N;
  cin >> N;
  vector<long long> A(N), B(N);
  for (auto& vi: A) cin >> vi;
  for (auto& vi: B) cin >> vi;

  long long t = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] <= B[i]) {
      t += (B[i]-A[i])/2;
    } else {
      t -= (A[i]-B[i]);
    }
  }

  if (t >= 0) {
    puts("Yes");
  } else {
    puts("No");
  }
  return 0;
}
