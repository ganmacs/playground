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

int
main()
{

  int N;
  cin >> N;
  vector<int> V(N);
  for (auto& vi: V) {
    cin >> vi;
  };
  vector<int> V1;

  while (true) {
    sort(V.begin(), V.end());
    V1.clear();
    for (int i = 1; i < V.size(); i++) {
      if ((V[i] % V[0]) != 0) {
        V1.push_back(V[i] % V[0]);
      }
    }

    if(V1.size() == 0) {
      cout << V[0] << endl;
      return 0;
    }
    V1.push_back(V[0]);

    sort(V1.begin(), V1.end());
    V.clear();
    for (int i = 1; i < V1.size(); i++) {
      if ((V1[i] % V1[0]) != 0) {
        V.push_back(V1[i] % V1[0]);
      }
    }

    if(V.size() == 0) {
      cout << V1[0] << endl;
      return 0;
    }
    V.push_back(V1[0]);

  }

  return 0;
}
