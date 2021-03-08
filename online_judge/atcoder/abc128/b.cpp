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

bool cmp(pair<pair<string, int>,  int> &l, pair<pair<string, int>, int> &r) {
  return l.first.second > r.first.second;
}

bool cmp1(pair<pair<string, int>,  int> &l, pair<pair<string, int>, int> &r) {
  return l.first.first < r.first.first;
}


int main(int argc, char *argv[])
{

  int N, p;
  string s;
  vector<pair<pair<string, int>, int> > m;

  cin >> N;


  for (int i = 0; i < N; i++) {
    cin >> s >> p;
    m.push_back(make_pair(make_pair(s, -p), i));
  }

  sort(m.begin(), m.end());


  for (auto mi: m) {
    cout << mi.second + 1 << endl;
  }


  return 0;
}
