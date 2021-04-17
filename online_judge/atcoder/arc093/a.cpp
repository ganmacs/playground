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
#include <numeric>

using namespace std;

int main()
{
  int N;
  long long s = 0;
  cin >> N;
  vector<int> V(N + 2);

  V[0] = 0;
  V[N + 1] = 0;
  for (int i = 0; i < N; i++) {
    cin >> V[i + 1];
  }

  for (int i = 0; i <= N; i++) {
    s += abs(V[i + 1] - V[i]);
  }

  for (int i = 1; i <= N; i++) {
    long long ss = s;
    ss -= abs(V[i]-V[i-1]);
    ss -= abs(V[i]-V[i+1]);
    ss += abs(V[i-1]-V[i+1]);
    cout << ss << endl;
  }

  return 0;
}
