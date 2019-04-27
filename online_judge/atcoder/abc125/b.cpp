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

int main(int argc, char *argv[])
{
  int N, V[100], C[100];
  cin >> N;

  for (int i = 0; i < N; i++) cin >> V[i];
  for (int i = 0; i < N; i++) cin >> C[i];

  long long ans = 0;
  for (int i = 0; i < N; i++) {
    if (V[i] > C[i]) {
      ans += V[i]-C[i];
    }
  }

  cout << ans << endl;

  return 0;
}
