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
  string S;
  cin >> S;

  int si = S.length()-7;

  for (int i = 0; i < S.length(); i++) {
    string ts = "";
    for (int j = 0; j < i; j++) {
      ts += S[j];
    }

    for (int j = i + si; j < S.length(); j++) {
      ts += S[j];
    }

    if (ts == "keyence") {
      cout << "YES" << endl;
      return 0;
    }
  }

  cout << "NO" << endl;
  return 0;
}
