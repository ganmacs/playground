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
  int N, M;
  map<string,  int> m;
  string s[200], t[200];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> s[i];
    m[s[i]] += 1;
  }
  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> t[i];
    m[t[i]] -= 1;
  }

  int maxv = -2000;
  for (auto i = m.begin(); i != m.end() ; ++i ) {
    maxv = max(maxv, i->second);
  }

  if (maxv < 0) {
    cout << 0 << endl;
  } else {
    cout << maxv << endl;
  }

  return 0;
}
