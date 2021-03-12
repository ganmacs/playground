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
  int ac = 0, wa = 0, N, M;
  string p, S;
  map<string, int> acc, waa;
  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    cin >> p >> S;
    if (S == "AC") {
      if (acc.find(p) != acc.end()) {
        continue;
      }

      acc[p]++;
      wa += waa[p];
      ac++;
    } else {
      waa[p]++;
    }
  }

  cout << ac << " " << wa << endl;
  return 0;
}
