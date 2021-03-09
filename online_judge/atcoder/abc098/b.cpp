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
  int N;
  unsigned long ans = 0;
  string S;
  cin >> N >> S;

  for (int i = 1; i < N-1; i++) {
    set<char> s1, s2;

    for (int j = 0; j < i; j++) {
      s1.insert(S[j]);
    }

    for (int j = i; j < N; j++) {
      s2.insert(S[j]);
    }

    vector<int> v;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end() , inserter(v, v.end()));

    ans = max(ans, v.size());
  }

  cout << ans << endl;

  return 0;
}
