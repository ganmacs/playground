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
  map<string, int> MA, M2;
  int N;
  string S;
  cin >> N >> S;

  for (int i = 0; i < (N-2); i++) {
    string sss = "xxx";
    sss[0] = S[i];
    if (M2[sss] != 0) continue;
    M2[sss]++;

    for (int j = i + 1; j < (N-1); j++) {
      sss[1] = S[j];
      if (M2[sss] != 0) continue;
      M2[sss]++;

      for (int k = j + 1; k < N; k++) {
        sss[2] = S[k];
        MA[sss]++;
      }
    }
  }

  cout << MA.size() << endl;
  return 0;
}
