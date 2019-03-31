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
  char t[223456], d[223456];

  cin >> N >> Q;
  cin >> s;

  for (int i = 0; i < N; i++) {
    m[s[i]].push_back(i);
  }


  for (int i = 0; i < Q; i++) {
    cin >> t[i] >> d[i];
  }

  int fail = 0;
  for (int i = 0; i < Q; i++) {
    vector<int> ve(100);
    ve = m[t[i]];
    m[t[i]].clear();

    int diff = d[i] == 'R' ? 1 : -1;

    while (!ve.empty()) {
      int v = ve.back();
      ve.pop_back();
      int nex = v + diff;
      if ((nex < 0 || nex >= N)) {
        fail++;
      } else {
        m[s[nex]].push_back(nex);
      }
    }
  }

  cout << (N-fail) << endl;
}
