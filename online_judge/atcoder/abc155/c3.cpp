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

  map<string, int> m;

  for (int i = 0; i < N; i++) {
    cin >> s;
    m[s]++;
  }

  vector<pair<int, string> > ve;
  for (auto& vi: m) {
    ve.push_back(make_pair(-vi.second, vi.first));
  };
  sort(ve.begin(), ve.end());


  int k = 1e9;
  for (auto& vi: ve) {
    if (k == 1e9) {
      k = vi.first;
    } else if (k != vi.first) {
      break;
    }

    cout << vi.second << endl;
  };

  return 0;
}
