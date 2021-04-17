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
  map<string, int> ss;
  int N;
  string S;
  cin >> N >> S;

  for (int i = 0; i < N-2; i++) {
    string ts = "xxx";
    ts[0] = S[i];
    for (int j = i + 1; j < N-1; j++) {
      ts[1] = S[j];
      for (int k = j + 1; k < N; k++) {
        ts[2] = S[k];
        ss[ts]++;
      }
    }
  }

  cout << ss.size() << endl;
  return 0;
}
