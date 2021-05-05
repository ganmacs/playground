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
  int N;
  cin >> N;
  string s;
  map<string, int> V;

  for (int i = 0; i < N; i++) {
    cin >> s;
    V[s]++;
  }

  vector<pair<int, string>> V2;
  for (auto& vi: V) {
    V2.push_back(make_pair(-vi.second, vi.first));
  }
  sort(V2.begin(), V2.end());

  int k = -1;
  for (auto& vi: V2) {
    if (k != -1 && vi.first != k) {
      break;
    }
    k = vi.first;
    cout << vi.second << endl;
  };
  return 0;
}
