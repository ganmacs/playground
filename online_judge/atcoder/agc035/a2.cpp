#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<int> V(N);
  map<int, int> M;
  for (auto& vi: V) {
    cin >> vi;
    M[vi]++;
  }

  if (M.size() > 3) {
    cout << "No" << endl;
    return 0;
  }

  vector<int> V2;
  for (auto& vi: M) {
    V2.push_back(vi.first);
  }

  if (M.size() == 1) {
    cout << ((M[0] == N) ? "Yes" : "No") << endl;
  } else if (M.size() == 2) {
    cout << ((M[0] != 0 && (2*M[0] == M[V2[1]])) ? "Yes" : "No") << endl;
  } else {
    if ((V2[0] ^ V2[1] ^ V2[2]) != 0) {
      cout << "No" << endl;
      return 0;
    }
    cout << ((M[V2[0]] == M[V2[1]] && M[V2[1]] == M[V2[2]]) ? "Yes" : "No") << endl;
  }

  return 0;
}
