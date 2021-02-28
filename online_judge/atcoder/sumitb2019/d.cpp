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
  string S;
  set<string> sss, ss, s;
  cin >> N >> S;

  for (int i = 0; i < N; i++) {
    string f = "xxx";
    f[0] = S[i];
    if (s.find(f) != s.end()) continue;
    s.insert(f);

    for (int j = i + 1; j < N; j++) {
      f[1] = S[j];
      if (ss.find(f) != ss.end()) continue;
      ss.insert(f);

      for (int k = j + 1; k < N; k++) {
        f[2] = S[k];
        sss.insert(f);
      }
    }
  }

  cout << sss.size() << endl;
  return 0;
}
