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
  vector<vector<int> > w;

  cin >> N;

  int v;
  for (int i = 0; i < N; i++) {
    cin >> v;

    bool found = false;
    for (int i = 0; i < w.size(); i++) {
      if (w[i].back() >= v) {
        w[i].push_back(v);
        found = true;
        break;
      }
    }

    if (!found) {
      vector<int> vvv;
      vvv.push_back(v);
      w.push_back(vvv);
    }
  }

  cout << w.size() << endl;
  return 0;
}
