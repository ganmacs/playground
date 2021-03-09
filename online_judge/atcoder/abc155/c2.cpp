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

bool cmp(pair<string, int>& a, pair<string, int>& b)
{
  return a.second > b.second;
}

int main(int argc, char *argv[])
{
  map<string, int> mm;
  vector<pair<string, int> > vv;
  string s;
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> s;
    if (mm.find(s) != mm.end()) {
      mm[s]++;
    } else {
      mm[s] = 1;
    }
  }

  for (auto &mi: mm) {
    vv.push_back(mi);
  }
  sort(vv.begin(), vv.end(), cmp);
  vector<string> v2;

  auto v = -1;
  for (auto& it : vv) {
    if (v == -1) {
      v = it.second;
    } else if (v != it.second) {
      break;
    }

    v2.push_back(it.first);

    // cout << it.first << endl;
  }

  sort(v2.begin(), v2.end());
  for (auto vi: v2) {
    cout << vi << endl;
  }

  return 0;
}
