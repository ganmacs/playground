#sumitb2019_cinclude <algorithm>
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
  int N, a;
  string b;
  vector<pair<string, pair<int, int> > > vec;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> b >> a;
    vec.push_back(make_pair(b, make_pair(-a, i + 1)));
  }

  sort(vec.begin(), vec.end());


  for (const auto& vi: vec) {
    cout <<  vi.second.second << endl;
  }

  return 0;
}
