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

string s1, s2, s3;

int main()
{
  cin >> s1 >> s2 >> s3;
  set<char> ss;

  for (auto& vi: s1) ss.insert(vi);
  for (auto& vi: s2) ss.insert(vi);
  for (auto& vi: s3) ss.insert(vi);

  if (ss.size() >= 11) {
    cout << "UNSOLVABLE" << endl;
    return 0;
  }

  vector<char> V2;
  for (auto vi: ss) V2.push_back(vi);
  vector<int> V;
  for (int i = 0; i <= 9; i++) V.push_back(i);
  int N = ss.size();

  do {
    string ss1 = s1;
    string ss2 = s2;
    string ss3 = s3;

    for (int i = 0; i < N; i++) {
      replace(ss1.begin(), ss1.end(), V2[i], (char)('0' + V[i]));
      replace(ss2.begin(), ss2.end(), V2[i], (char)('0' + V[i]));
      replace(ss3.begin(), ss3.end(), V2[i], (char)('0' + V[i]));
    }

    if (ss1[0] == '0' || ss2[0] == '0' || ss3[0] == '0') continue;

    if (stol(ss1) + stol(ss2) == stol(ss3) && stol(ss1) > 0 && stol(ss2) > 0 && stol(ss3) > 0) {
      cout << ss1 << endl;
      cout << ss2 << endl;
      cout << ss3 << endl;
      return 0;
    }
  } while (next_permutation(V.begin(), V.end()));

  cout << "UNSOLVABLE" << endl;
  return 0;
}
