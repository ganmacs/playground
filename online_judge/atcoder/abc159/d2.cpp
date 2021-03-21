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
  string s;
  cin >> N;
  map<string, int> M;
  vector<string> V;

  for (int i = 0; i < N; i++) {
    cin >> s;
    V.push_back(s);
    M[s]++;
  }

  long long int ans = 0;
  for (auto& vi: M) {
    if (vi.second < 2) continue;
    for (int i = 1; i < vi.second; i++) {
      ans += i;
    }
  };

  for (auto& vi: V) {
    if (M[vi] < 2) {
      cout << ans << endl;
    } else {
      cout << (ans - (M[vi]-1)) << endl;
    }
  };

  return 0;
}
