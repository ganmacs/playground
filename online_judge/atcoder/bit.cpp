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
  int N= 5;
  vector<vector<int> > S;

  for (int i = 0; i < (1 << N); i++) {
    vector<int> ss;
    for (int j = 0; j < N; j++) {
      if (i & (1 << j)) {
        ss.push_back(j);
      }
    }

    S.push_back(ss);
  }

  for (auto is: S) {
    for (auto iis: is) {
      cout << iis << " ";
    }
    cout << endl;
  }

  return 0;
}
