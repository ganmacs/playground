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

unsigned long long int dd[200001];

int main()
{
  int N;
  unsigned long long int s = 0;
  unsigned long long int ans = 0;
  cin >> N;
  dd[0] = 0;
  vector<unsigned long long int> V(N);

  for (int i = 0; i < N; i++) {
    cin >> V[i];
    dd[i + 1] = V[i] + dd[i];
    s += V[i];
  }

  for (int i = 0; i <= N; i++) {
    if (2*dd[i] == s) {
      break;
    } else if (2*dd[i] > s) {
      unsigned long long int s1 = dd[i] - (s - dd[i]);
      unsigned long long int s2 = 1e18;

      if (i >= 2) {
        s2 = s - 2*dd[i-1];
      }

      // cout << s1 << " " << s2 << endl;
      ans = min(s1, s2);
      break;
    }
  }

  cout << ans << endl;
  return 0;
}
