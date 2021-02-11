
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
  int A[3][3];
  bool B[3][3];
  int N, n;
  std::map<int, pair<int, int> > mp;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> A[i][j];
      B[i][j] = false;
      mp[A[i][j]] = make_pair(i, j);
    }
  }
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> n;
    auto itr = mp.find(n);
    if(itr != mp.end()) {
      B[itr->second.first][itr->second.second] = true;
    }
  }

  for (int i = 0; i < 3; i++) {
    if (B[i][0] && B[i][1] && B[i][2]) {
      cout << "Yes" << endl;
      return 0;
    }

    if (B[0][i] && B[1][i] && B[2][i]) {
      cout << "Yes" << endl;
      return 0;
    }
  }

  if (B[0][0] && B[1][1] && B[2][2]) {
    cout << "Yes" << endl;
    return 0;
  }

  if (B[0][2] && B[1][1] && B[2][0]) {
    cout << "Yes" << endl;
    return 0;
  }


  cout << "No" << endl;
  return 0;
}
