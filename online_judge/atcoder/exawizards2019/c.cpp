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

int main(int argc, char *argv[])
{
  int N, Q;
  string s;
  map<char, vector<int> > m;
  char t[123456], d[123456];

  cin >> N >> Q;
  cin >> s;

  for (int i = 0; i < Q; i++) {
    cin >> t[i] >> d[i];
  }

  int ans = 0;
  for (int j = 0; j < N; j++) {
    for (int i = Q-1; i >= 0; i--) {
      if (t[i] == s[j] && d[i] == 'L') {
        ans++;
      }
    }
  }

  // for (int i = 0; i < N; i++) {
  //   m[s[i]].push_back(i);
  // }

  // int fail = 0;
  // for (int i = 0; i < Q; i++) {
  //   vector<int> ve(100);
  //   ve = m[t[i]];
  //   m[t[i]].clear();

  //   int diff = d[i] == 'R' ? 1 : -1;
  //   while (!ve.empty()) {
  //     int v = ve.back();
  //     ve.pop_back();
  //     int nex = v + diff;
  //     if ((nex < 0 || nex >= N)) {
  //       fail++;
  //     } else {
  //       m[s[nex]].push_back(nex);
  //     }
  //   }
  // }

  // cout << (N-fail) << endl;
}
