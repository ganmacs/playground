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

  if (S[0] != 'A') {
    cout << "WA" << endl;
    return 0;
  }

  int c = 0;
  for (int i = 2; i <= S.size()-2; i++) {
    if (S[i] == 'C') c++;
  }

  if (c != 1) {
    cout << "WA" << endl;
    return 0;
  }


  int ng = 0;
  for (int i = 0; i < S.size(); i++) {
    if (S[i] >= 'a' && S[i] <= 'z') continue;
    ng++;
  }

  if (ng == 2) {
    cout << "AC" << endl;
  } else {
    cout << "WA" << endl;
  }

  return 0;
}
