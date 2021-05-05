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
#include <numeric>

using namespace std;

int main()
{
  string S1, S2, S3;
  map<char, int> M;
  cin >> S1 >> S2 >> S3;
  int N1 = S1.length();
  int N2 = S2.length();
  int N3 = S3.length();

  for (auto& vi: S1) M[vi]++;
  for (auto& vi: S2) M[vi]++;
  for (auto& vi: S3) M[vi]++;

  if (S1 == S3 || S2 == S3 || M.size() > 10) {
    cout << "UNSOLVABLE" << endl;
    return 0;
  }

  vector<int> V({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  vector<char> MA;
  for (auto& vi: M) {
    MA.push_back(vi.first);
  }

  do {
    vector<string> sv({S1, S2, S3});

    for (int i = 0; i < MA.size(); i++) {
      for (auto& vvi: sv) {
        replace(vvi.begin(), vvi.end(), MA[i], (char)('0' + V[i]));
      };
    }

    bool ng = false;
    for (auto& vvi: sv) {
      if (vvi[0] == '0') ng = true;
    }
    if (ng) continue;

    if (stoll(sv[0]) + stoll(sv[1]) == stoll(sv[2])) {
      for (auto& vvi: sv) {
        cout << vvi << endl;
      }
      return 0;
    }
  } while (next_permutation(V.begin(), V.end()));

  cout << "UNSOLVABLE" << endl;
  return 0;
}
